project = "h5cpp"
coverage_os = "fedora"

images = [
    'centos': [
        'name': 'essdmscdm/centos7-build-node:1.0.1',
        'sh': 'sh'
    ],
    'centos-gcc6': [
        'name': 'essdmscdm/centos7-gcc6-build-node:1.0.0',
        'sh': '/usr/bin/scl enable rh-python35 devtoolset-6 -- /bin/bash'
    ],
    'fedora': [
        'name': 'essdmscdm/fedora25-build-node:1.0.0',
        'sh': 'sh'
    ],
    'debian': [
        'name': 'essdmscdm/debian9-build-node:1.0.0',
        'sh': 'sh'
    ],
    'ubuntu1604': [
        'name': 'essdmscdm/ubuntu16.04-build-node:2.0.0',
        'sh': 'sh'
    ],
    'ubuntu1710': [
        'name': 'essdmscdm/ubuntu17.10-build-node:1.0.0',
        'sh': 'sh'
    ]
]

base_container_name = "${project}-${env.BRANCH_NAME}-${env.BUILD_NUMBER}"

def failure_function(exception_obj, failureMessage) {
    def toEmails = [[$class: 'DevelopersRecipientProvider']]
    emailext body: '${DEFAULT_CONTENT}\n\"' + failureMessage +'\"\n\nCheck console output at $BUILD_URL to view the results.',
        recipientProviders: toEmails,
        subject: '${DEFAULT_SUBJECT}'
    slackSend color: 'danger',
        message: "@afonso.mukai ${project}-${env.BRANCH_NAME}: " + failureMessage

    throw exception_obj
}

def Object container_name(image_key) {
    return "${base_container_name}-${image_key}"
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
        conan install --build=outdated ../${project}/conanfile_ess.txt
    \""""
}

def docker_build(image_key) {
    cmake_exec = "/home/jenkins/${project}/build/bin/cmake"
    def custom_sh = images[image_key]['sh']
        try {
            sh """docker exec ${container_name(image_key)} ${custom_sh} -c \"
                cd ${project}/build
                ${cmake_exec} --version
                ${cmake_exec} -DCMAKE_BUILD_TYPE=Release ..
                make --version
                make run_tests
            \""""
        } catch(e) {
            failure_function(e, 'Run tests (${container_name(image_key)}) failed')
        }
}

def docker_build_coverage(image_key) {
    cmake_exec = "/home/jenkins/${project}/build/bin/cmake"
    abs_dir = pwd()
    def custom_sh = images[image_key]['sh']
        try {
            sh """docker exec ${container_name(image_key)} ${custom_sh} -c \"
                cd ${project}/build
                ${cmake_exec} --version
                ${cmake_exec} -DCMAKE_BUILD_TYPE=Debug -DCOV=1 ..
                make --version
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

def get_pipeline(image_key)
{
    return {
        stage("${image_key}") {
            try {
                def container = get_container(image_key)
                def custom_sh = images[image_key]['sh']

                // Copy sources to container and change owner and group.
                    sh "docker cp ${project}_code ${container_name(image_key)}:/home/jenkins/${project}"
                    sh """docker exec --user root ${container_name(image_key)} ${custom_sh} -c \"
                        chown -R jenkins.jenkins /home/jenkins/${project}
                        \""""

                try {
                    docker_dependencies(image_key)
                } catch (e) {
                    failure_function(e, "Get dependencies for ${image_key} failed")
                }

                if (image_key == coverage_os) {
                    docker_build_coverage(image_key)
                } else {
                    docker_build(image_key)
                }
            } catch(e) {
                failure_function(e, "Unknown build failure for ${image_key}")
            } finally {
                sh "docker stop ${container_name(image_key)}"
                sh "docker rm -f ${container_name(image_key)}"
            }
        }
    }
}

def get_macos_pipeline()
{
    return {
        stage("MacOSX") {
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
                        sh "cmake ../code"
                    } catch (e) {
                        failure_function(e, 'MacOSX / CMake failed')
                    }

                    try {
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
                        bat 'C:\\Users\\dmgroup\\AppData\\Local\\Programs\\Python\\Python36\\Scripts\\conan.exe install --build=outdated -s compiler="Visual Studio" -s compiler.version=14 ..\\conanfile_default.txt'
                    } catch (e) {
                        failure_function(e, 'Windows10 / getting dependencies failed')
                    }

                    try {
                        bat 'cmake -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 14 2015 Win64" ..'
                    } catch (e) {
                        failure_function(e, 'Windows10 / CMake failed')
                    }

                    try {
                        bat "cmake --build . --config Release --target unit_tests"
                        bat "bin\\unit_tests.exe"
                    } catch (e) {
		                junit 'test/unit_tests_run.xml'
                        failure_function(e, 'Windows10 / build+test failed')
                    }

                }
            }
        }
    }
}

node('docker') {
    stage('Checkout') {
        dir("${project}_code") {
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
    builders['macOS'] = get_macos_pipeline()
    builders['Windows10'] = get_win10_pipeline()
    

    parallel builders
    // Delete workspace when build is done
    cleanWs()
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
            }
        }

        dir("${project}/build") {
            try {
                sh "HDF5_ROOT=$HDF5_ROOT \
                    CMAKE_PREFIX_PATH=$HDF5_ROOT \
                    cmake ../code"
                sh "make html"
                if (env.BRANCH_NAME != 'master') {
                    archiveArtifacts artifacts: 'doc/build/'
                }
            } catch (e) {
                failure_function(e, 'Generate docs / make html failed')
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
            }
        }
    }
}
