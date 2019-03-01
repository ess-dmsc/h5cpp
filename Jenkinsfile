project = "h5cpp"
coverage_os = "centos7-release"

images = [
    'centos7-release': [
        'name': 'essdmscdm/centos7-build-node:4.0.0',
        'cmake': 'CC=/usr/lib64/mpich-3.2/bin/mpicc CXX=/usr/lib64/mpich-3.2/bin/mpicxx cmake3',
        'sh': '/usr/bin/scl enable rh-python35 devtoolset-6 -- /bin/bash -e',
        'cmake_flags': '-DCOV=1 -DWITH_MPI=1 -DCONAN_FILE=conanfile_ess_mpi.txt -DCMAKE_BUILD_TYPE=Release'
    ],
    'debian9-release': [
        'name': 'essdmscdm/debian9-build-node:3.0.0',
        'cmake': 'cmake',
        'sh': 'bash -e',
        'cmake_flags': '-DCMAKE_BUILD_TYPE=Release'
    ],
    'ubuntu1804-release': [
        'name': 'essdmscdm/ubuntu18.04-build-node:2.0.0',
        'cmake': 'cmake',
        'sh': 'bash -e',
        'cmake_flags': '-DCMAKE_BUILD_TYPE=Release'
    ],

    'centos7-debug': [
            'name': 'essdmscdm/centos7-build-node:4.0.0',
            'cmake': 'CC=/usr/lib64/mpich-3.2/bin/mpicc CXX=/usr/lib64/mpich-3.2/bin/mpicxx cmake3',
            'sh': '/usr/bin/scl enable rh-python35 devtoolset-6 -- /bin/bash -e',
            'cmake_flags': '-DWITH_MPI=1 -DCONAN_FILE=conanfile_ess_mpi.txt -DCMAKE_BUILD_TYPE=Debug'
    ],
    'debian9-debug': [
            'name': 'essdmscdm/debian9-build-node:3.0.0',
            'cmake': 'cmake',
            'sh': 'bash -e',
            'cmake_flags': '-DCMAKE_BUILD_TYPE=Debug'
    ],
    'ubuntu1804-debug': [
            'name': 'essdmscdm/ubuntu18.04-build-node:2.0.0',
            'cmake': 'cmake',
            'sh': 'bash -e',
            'cmake_flags': '-DCMAKE_BUILD_TYPE=Debug'
    ]
]

base_container_name = "${project}-${env.BRANCH_NAME}-${env.BUILD_NUMBER}"

def failure_function(exception_obj, failureMessage) {
    def toEmails = [[$class: 'DevelopersRecipientProvider']]
    emailext body: '${DEFAULT_CONTENT}\n\"' + failureMessage +'\"\n\nCheck console output at $BUILD_URL to view the results.',
        recipientProviders: toEmails,
        subject: '${DEFAULT_SUBJECT}'
    throw exception_obj
}

def Object container_name(image_key) {
    return "${base_container_name}-${image_key}"
}

def Object get_container(image_key) {
    def image = docker.image(images[image_key]['name'])
    def container = image.run("\
            --name ${container_name(image_key)} \
        --tty \
        --network=host \
        --env http_proxy=${env.http_proxy} \
        --env https_proxy=${env.https_proxy} \
        --env local_conan_server=${env.local_conan_server} \
        ")
    return container
}

def docker_copy_code(image_key) {
    def custom_sh = images[image_key]['sh']
    sh "docker cp ${project} ${container_name(image_key)}:/home/jenkins/${project}"
    sh """docker exec --user root ${container_name(image_key)} ${custom_sh} -c \"
                        chown -R jenkins.jenkins /home/jenkins/${project}
                        \""""
}

def docker_dependencies(image_key) {
    def conan_remote = "ess-dmsc-local"
    def custom_sh = images[image_key]['sh']
    sh """docker exec ${container_name(image_key)} ${custom_sh} -c \"
        mkdir ${project}/build
        cd ${project}/build
        conan remote add \
            --insert 0 \
            ${conan_remote} ${local_conan_server}
    \""""
}

def docker_build(image_key, xtra_flags) {
    cmake_exec = images[image_key]['cmake']
    def custom_sh = images[image_key]['sh']
        try {
            sh """docker exec ${container_name(image_key)} ${custom_sh} -c \"
                cd ${project}/build
                ${cmake_exec} --version
                ${cmake_exec} ${xtra_flags} ..
                make --version
                make -j4 unit_tests
            \""""
        } catch(e) {
            failure_function(e, 'Run tests (${container_name(image_key)}) failed')
        }
}

def docker_test(image_key) {
    cmake_exec = "/home/jenkins/${project}/build/bin/cmake"
    def custom_sh = images[image_key]['sh']
    try {
        sh """docker exec ${container_name(image_key)} ${custom_sh} -c \"
                cd ${project}/build
                make run_tests
            \""""
    } catch(e) {
        failure_function(e, 'Run tests (${container_name(image_key)}) failed')
    }
}

def docker_coverage(image_key) {
    cmake_exec = "/home/jenkins/${project}/build/bin/cmake"
    abs_dir = pwd()
    def custom_sh = images[image_key]['sh']
        try {
            sh """docker exec ${container_name(image_key)} ${custom_sh} -c \"
                cd ${project}/build
                make generate_coverage
            \""""
            sh "docker cp ${container_name(image_key)}:/home/jenkins/${project} ./"
        } catch(e) {
            sh "docker cp ${container_name(image_key)}:/home/jenkins/${project}/build/test/unit_tests_run.xml unit_tests_run.xml"
            junit 'unit_tests_run.xml'
            failure_function(e, 'Run tests (${container_name(image_key)}) failed')
        }

    dir("${project}/build") {
        junit 'test/unit_tests_run.xml'
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
            failure_function(e, 'Publishing coverage reports from (${container_name(image_key)}) failed')
        }
    }
}

def get_pipeline(image_key)
{
    return {
        stage("${image_key}") {
            try {
                def container = get_container(image_key)

                docker_copy_code(image_key)
                docker_dependencies(image_key)
                docker_build(image_key, images[image_key]['cmake_flags'])

                if (image_key == coverage_os) {
                    docker_coverage(image_key)
                } else {
                    docker_test(image_key)
                }
            } catch (e) {
                failure_function(e, "Unknown build failure for ${image_key}")
            } finally {
                sh "docker stop ${container_name(image_key)}"
                sh "docker rm -f ${container_name(image_key)}"
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
                        sh "conan install --build=outdated ../code/conanfile_ess.txt"
                    } catch (e) {
                        failure_function(e, 'MacOSX / getting dependencies failed')
                    }

                    try {
                        sh "cmake -DCMAKE_BUILD_TYPE=${build_type} ../code"
                    } catch (e) {
                        failure_function(e, 'MacOSX / CMake failed')
                    }

                    try {
                        sh "make -j4 unit_tests"
                        sh "make run_tests"
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
                        bat 'cmake -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 14 2015 Win64" ..'
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

node('docker') {
    stage('Checkout') {
        dir("${project}") {
            try {
                scm_vars = checkout scm
            } catch (e) {
                failure_function(e, 'Checkout failed')
            }
        }
    }
    def builders = [:]
    for (x in images.keySet()) {
        def image_key = x
        builders[image_key] = get_pipeline(image_key)
    }
    builders['macOS-release'] = get_macos_pipeline('Release')
    builders['macOS-debug'] = get_macos_pipeline('Debug')
    builders['Windows10'] = get_win10_pipeline()


    try {
        parallel builders
    } catch (e) {
        failure_function(e, 'Job failed')
        throw e
    } finally {
        // Delete workspace when build is done
        cleanWs()
    }
}

node ("fedora") {
    // Delete workspace when build is done
    cleanWs()

    stage("Documentation") {
        dir("${project}/code") {
            try {
                checkout scm
            } catch (e) {
                failure_function(e, 'Generate docs / Checkout failed')
            } finally {
                // Delete workspace when build is done
                cleanWs()
            }
        }

        dir("${project}/build") {
            try {
                sh "HDF5_ROOT=$HDF5_ROOT \
                    CMAKE_PREFIX_PATH=$HDF5_ROOT \
                    cmake -DCONAN=DISABLE ../code"
                sh "make html"
                if (env.BRANCH_NAME != 'master') {
                    archiveArtifacts artifacts: 'doc/build/'
                }
            } catch (e) {
                failure_function(e, 'Generate docs / make html failed')
            } finally {
                // Delete workspace when build is done
                cleanWs()
            }
        }

        dir("${project}/docs") {
            try {
                  checkout scm

                  if (env.BRANCH_NAME == 'master') {
                    sh "git config user.email 'dm-jenkins-integration@esss.se'"
                    sh "git config user.name 'cow-bot'"
                    sh "git config remote.origin.fetch '+refs/heads/*:refs/remotes/origin/*'"

                    sh "git fetch"
                    sh "git checkout gh-pages"
                    sh "git pull"
                    sh "shopt -u dotglob && rm -rf ./*"
                    sh "mv -f ../build/doc/build/* ./"
                    sh "mv -f ../build/doc/doxygen_html ./doxygen"
                    sh 'find ./ -type d -name "CMakeFiles" -prune -exec rm -rf {} \\;'
                    sh 'find ./ -name "Makefile" -exec rm -rf {} \\;'
                    sh 'find ./ -name "*.cmake" -exec rm -rf {} \\;'
                    sh 'rm -rf ./_sources'
                    sh "git add -A"
                    sh "git commit --amend -m 'Auto-publishing docs from Jenkins build ${BUILD_NUMBER} for branch ${BRANCH_NAME}'"

                    withCredentials([usernamePassword(
                        credentialsId: 'cow-bot-username',
                        usernameVariable: 'USERNAME',
                        passwordVariable: 'PASSWORD'
                    )]) {
                        sh "../code/push_to_repo.sh ${USERNAME} ${PASSWORD}"
                    }

                }
            } catch (e) {
                failure_function(e, 'Generate docs / Publish docs failed')
            } finally {
                // Delete workspace when build is done
                cleanWs()
            }
        }
    }
}
