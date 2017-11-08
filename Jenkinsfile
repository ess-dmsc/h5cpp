project = "h5cc"
def base_container_name = "${project}-${env.BRANCH_NAME}-${env.BUILD_NUMBER}"

def failure_function(exception_obj, failureMessage) {
    def toEmails = [[$class: 'DevelopersRecipientProvider']]
    emailext body: '${DEFAULT_CONTENT}\n\"' + failureMessage +'\"\n\nCheck console output at $BUILD_URL to view the results.',
        recipientProviders: toEmails,
        subject: '${DEFAULT_SUBJECT}'
    slackSend color: 'danger',
        message: "@afonso.mukai ${project}-${env.BRANCH_NAME}: " + failureMessage

    throw exception_obj
}

def docker_dependencies(container_name) {
    def conan_remote = "ess-dmsc-local"
    sh """docker exec ${containter_name} sh -c \"
        mkdir build
        cd build
        conan --version
        conan remote add \
            --insert 0 \
            ${conan_remote} ${local_conan_server}
        conan install ../${project} --build=missing
    \""""
}

def docker_cmake(container_name, cmake_exec) {
    sh """docker exec ${containter_name} sh -c \"
        cd build
        ${cmake_exec} --version
        ${cmake_exec} -DCOV=1 -DCMAKE_BUILD_TYPE=Debug ../${project}
    \""""
}

def docker_build(container_name) {
    sh """docker exec ${containter_name} sh -c \"
        cd build
        make --version
        make unit_tests VERBOSE=1
    \""""
}

def docker_tests(container_name) {
    dir("${project}/tests") {
        try {
            sh """docker exec ${containter_name} sh -c \"
                cd build
                make run_tests
            \""""
        } catch(e) {
            failure_function(e, 'Run tests (${containter_name}) failed')
        } finally {
            sh "docker cp ${containter_name}:/home/jenkins/build/test/unit_tests_run.xml unit_tests_run.xml"
            junit 'unit_tests_run.xml'
        }
    }
}

def centos = docker.image('essdmscdm/centos-build-node:0.7.0')
def fedora = docker.image('essdmscdm/fedora-build-node:0.3.0')

def centos_containter_name = "${base_container_name}-centos"
def fedora_containter_name = "${base_container_name}-fedora"


node('docker') {
    // Delete workspace when build is done
    cleanWs()

    dir("${project}/code") {
        stage('Checkout project') {
            try {
                scm_vars = checkout scm
            } catch (e) {
                failure_function(e, 'Checkout failed')
            }
        }
    }

    try {

        centos_container = centos.run("\
            --name ${centos_containter_name} \
            --tty \
            --env http_proxy=${env.http_proxy} \
            --env https_proxy=${env.https_proxy} \
        ")

        fedora_container = fedora.run("\
            --name ${fedora_containter_name} \
            --tty \
            --env http_proxy=${env.http_proxy} \
            --env https_proxy=${env.https_proxy} \
        ")

        // Copy sources to container.
        dir("${project}") {
            sh "docker cp code ${centos_containter_name}:/home/jenkins/${project}"
            sh "docker cp code ${fedora_containter_name}:/home/jenkins/${project}"
        }

        stage('Get dependencies') {
            try {
                docker_dependencies(${centos_containter_name})
                docker_dependencies(${fedora_containter_name})
            } catch (e) {
                failure_function(e, 'Get dependencies failed')
            }
        }

        stage('Run CMake') {
            try {
                docker_cmake(centos_containter_name, 'cmake3')
                docker_cmake(fedora_containter_name, 'cmake')
            } catch (e) {
                failure_function(e, 'CMake failed')
            }
        }

        stage('Build') {
            try {
                docker_build(${centos_containter_name})
                docker_build(${fedora_containter_name})
            } catch (e) {
                failure_function(e, 'Build failed')
            }
        }

        stage('Run tests') {
            docker_tests(${centos_containter_name})
            docker_tests(${fedora_containter_name})
        }

    } catch(e) {
        failure_function(e, 'Unknown build failure')
    } finally {
        centos_container.stop()
        fedora_container.stop()
    }
}

stage("Generate docs") {
    node ("fedora") {

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
                    cmake -DCOV=1 ../code"
            } catch (e) {
                failure_function(e, 'Generate docs / CMake failed')
            }

            try {
                sh "make generate_coverage"
                //sh "make memcheck"
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
                    zoomCoverageChart: false
                ])
            } catch (e) {
                failure_function(e, 'Generate docs / generate coverage failed')
            }

            try {
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
                    sh "shopt -u dotglob && rm -rf ./*"
                    sh "mv -f ../build/doc/build/* ./"
                    sh "git add -A"
                    sh "git commit -a -m 'Auto-publishing docs from Jenkins build ${BUILD_NUMBER} for branch ${BRANCH_NAME}'"

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
