@Library('ecdc-pipeline')
import ecdcpipeline.ContainerBuildNode
import ecdcpipeline.PipelineBuilder

project = "h5cpp"
// coverage_os = "centos7-release"
coverage_os = "None"
documentation_os = "debian9-release"

container_build_nodes = [
  'centos7': ContainerBuildNode.getDefaultContainerBuildNode('centos7-gcc8'),
  'centos7-release': ContainerBuildNode.getDefaultContainerBuildNode('centos7-gcc8'),
  'debian9': ContainerBuildNode.getDefaultContainerBuildNode('debian9'),
  'debian9-release': ContainerBuildNode.getDefaultContainerBuildNode('debian9'),
  'ubuntu1804': ContainerBuildNode.getDefaultContainerBuildNode('ubuntu1804-gcc8'),
  'ubuntu1804-release': ContainerBuildNode.getDefaultContainerBuildNode('ubuntu1804-gcc8')
]

// Define number of old builds to keep. These numbers are somewhat arbitrary,
// but based on the fact that for the master branch we want to have a certain
// number of old builds available, while for the other branches we want to be
// able to deploy easily without using too much disk space.
def num_artifacts_to_keep
if (env.BRANCH_NAME == 'master') {
  num_artifacts_to_keep = '5'
} else {
  num_artifacts_to_keep = '1'
}

// Set number of old builds to keep.
properties([[
  $class: 'BuildDiscarderProperty',
  strategy: [
    $class: 'LogRotator',
    artifactDaysToKeepStr: '',
    artifactNumToKeepStr: num_artifacts_to_keep,
    daysToKeepStr: '',
    numToKeepStr: num_artifacts_to_keep
  ]
]]);

def failure_function(exception_obj, failureMessage) {
  def toEmails = [[$class: 'DevelopersRecipientProvider']]
  emailext body: '${DEFAULT_CONTENT}\n\"' + failureMessage + '\"\n\nCheck console output at $BUILD_URL to view the results.', recipientProviders: toEmails, subject: '${DEFAULT_SUBJECT}'
  throw exception_obj
}

pipeline_builder = new PipelineBuilder(this, container_build_nodes)
pipeline_builder.activateEmailFailureNotifications()

builders = pipeline_builder.createBuilders { container ->
  pipeline_builder.stage("${container.key}: Checkout") {
    dir(pipeline_builder.project) {
      scm_vars = checkout scm
    }
    container.copyTo(pipeline_builder.project, pipeline_builder.project)
  }  // stage

  pipeline_builder.stage("${container.key}: Configure Conan") {
    def conan_remote = "ess-dmsc-local"
    container.sh """
      mkdir build
      cd build
      conan remote add \
        --insert 0 \
        ${conan_remote} ${local_conan_server}
    """
  }  // stage

  pipeline_builder.stage("${container.key}: CMake") {
    def cmake_options
    def cmake_prefix
    switch (container.key) {
      case 'centos7':
        cmake_options = '-DWITH_MPI=1 -DCONAN_FILE=conanfile_ess_mpi.txt -DCMAKE_BUILD_TYPE=Debug -DWITH_BOOST=OFF'
        cmake_prefix = 'CC=/usr/lib64/mpich-3.2/bin/mpicc CXX=/usr/lib64/mpich-3.2/bin/mpicxx'
        break
      case 'centos7-release':
        cmake_options = '-DWITH_MPI=1 -DCONAN_FILE=conanfile_ess_mpi.txt -DCMAKE_BUILD_TYPE=Release'
        cmake_prefix = 'CC=/usr/lib64/mpich-3.2/bin/mpicc CXX=/usr/lib64/mpich-3.2/bin/mpicxx'
        break
      case 'debian9':
        cmake_options = '-DCMAKE_BUILD_TYPE=Debug'
        cmake_prefix = ''
        break
      case 'debian9-release':
        cmake_options = '-DCMAKE_BUILD_TYPE=Release'
        cmake_prefix = ''
        break
      case 'ubuntu1804':
        cmake_options = '-DCMAKE_BUILD_TYPE=Debug'
        cmake_prefix = ''
        break
      case 'ubuntu1804-release':
        cmake_options = '-DCMAKE_BUILD_TYPE=Release'
        cmake_prefix = ''
        break
      default:
        cmake_options = '-DCMAKE_BUILD_TYPE=Debug'
        cmake_prefix = ''
        break
    }

    container.sh """
      cd build
      cmake --version
      ${cmake_prefix} cmake ${cmake_options} ../${pipeline_builder.project}
    """
  }  // stage

  pipeline_builder.stage("${container.key}: Build") {
    container.sh """
    cd build
    . ./activate_run.sh
    make --version
    make -j4 unit_tests
    """
  }  // stage

  pipeline_builder.stage("${container.key}: Test") {
    if (container.key != coverage_os) {
      try {
        container.sh """
                cd build
                make run_tests
            """
      } catch(e) {
        failure_function(e, 'Run tests failed')
      }
    }
  }

  pipeline_builder.stage("${container.key}: Coverage") {
    if (container.key == coverage_os) {
        try {
            container.sh """
                cd build
                make generate_coverage
            """
            container.copyFrom('build', '.')
        } catch(e) {
            container.copyFrom('build/test/unit_tests_run.xml', 'unit_tests_run.xml')
            junit 'unit_tests_run.xml'
        }

        abs_dir = pwd()
        dir("build") {
            sh "../redirect_coverage.sh ./coverage/coverage.xml ${abs_dir}/${project}/src/h5cpp"
            try {
                step([
                    $class: 'CoberturaPublisher',
                    autoUpdateHealth: true,
                    autoUpdateStability: true,
                    coberturaReportFile: 'coverage/coverage.xml',
                    failUnhealthy: false,
                    failUnstable: false,
                    maxNumberOfBuilds: 0,
                    onlyStable: false,
                    sourceEncoding: 'ASCII',
                    zoomCoverageChart: true
                ])
            } catch(e) {
                failure_function(e, 'Publishing coverage reports from failed')
            }
        }
    }
  }

  if (container.key == documentation_os) {
    pipeline_builder.stage("Documentation") {
      container.sh """
        pip --proxy=${http_proxy} install --user sphinx breathe
        export PATH=$PATH:~/.local/bin
        cd build
        make html
      """

      if (pipeline_builder.branch == 'master') {
        container.copyTo(pipeline_builder.project, "docs")
        container.sh """
          cd docs

          git config user.email 'dm-jenkins-integration@esss.se'
          git config user.name 'cow-bot'
          git config remote.origin.fetch '+refs/heads/*:refs/remotes/origin/*'

          git fetch
          git checkout gh-pages
          git pull
          shopt -u dotglob && rm -rf ./*
          mv -f ../build/doc/build/* ./
          mv -f ../build/doc/doxygen_html ./doxygen
          find ./ -type d -name "CMakeFiles" -prune -exec rm -rf {} \\;
          find ./ -name "Makefile" -exec rm -rf {} \\;
          find ./ -name "*.cmake" -exec rm -rf {} \\;
          rm -rf ./_sources
          git add -A
          git commit --amend -m 'Auto-publishing docs from Jenkins build ${BUILD_NUMBER} for branch ${BRANCH_NAME}'
        """

        container.copyFrom("docs", "docs")
        dir("docs") {
          withCredentials([usernamePassword(
            credentialsId: 'cow-bot-username',
            usernameVariable: 'USERNAME',
            passwordVariable: 'PASSWORD'
          )]) {
            sh "../${pipeline_builder.project}/push_to_repo.sh ${USERNAME} ${PASSWORD}"
          }
        }
      } else {
        container.copyFrom("build", "build")
        archiveArtifacts artifacts: 'build/doc/build/'
      }
    }
  }
}

def get_macos_pipeline(build_type)
{
    return {
        stage("macOS-${build_type}") {
            node ("macos") {
            // Delete workspace when build is done
                cleanWs()

                dir("${project}/code") {
                    try {
                        checkout scm
                    } catch (e) {
                        failure_function(e, 'MacOSX / Checkout failed')
                    }
                }

                dir("${project}/build") {
                    try {
                        sh "cmake -DCMAKE_BUILD_TYPE=${build_type} -DDISABLE_TESTS=True ../code"
                    } catch (e) {
                        failure_function(e, 'MacOSX / CMake failed')
                    }

                    try {
                        sh "make -j4"
                    } catch (e) {
                        failure_function(e, 'MacOSX / build+test failed')
                    }
                }

            }
        }
    }
}

def get_win10_pipeline()
{
    return {
        stage("Windows 10") {
            node ("windows10") {
            // Delete workspace when build is done
            cleanWs()

                try {
                    checkout scm
                    bat "mkdir _build"
                } catch (e) {
                    failure_function(e, 'Windows10 / Checkout failed')
                }

                dir("_build") {
                    try {
                        bat 'cmake -DCMAKE_BUILD_TYPE=Release -DWITH_BOOST=OFF -G "Visual Studio 15 2017 Win64" ..'
                    } catch (e) {
                        failure_function(e, 'Windows10 / CMake failed')
                    }

                    try {
                        bat "cmake --build . --config Release --target unit_tests"
                        bat """call activate_run.bat
    	                       .\\bin\\Release\\unit_tests.exe
    	                    """
                    } catch (e) {
                        failure_function(e, 'Windows10 / build+test failed')
                    }

                }
            }
        }
    }
}

node {
  dir("${project}") {
    try {
      scm_vars = checkout scm
    } catch (e) {
      failure_function(e, 'Checkout failed')
    }
  }

  builders['macOS-release'] = get_macos_pipeline('Release')
  builders['macOS-debug'] = get_macos_pipeline('Debug')
  builders['Windows10'] = get_win10_pipeline()


  try {
    parallel builders
  } catch (e) {
    pipeline_builder.handleFailureMessages()
    throw e
  } finally {
    // Delete workspace when build is done
    cleanWs()
  }
}
