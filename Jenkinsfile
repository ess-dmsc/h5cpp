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

def cmake_function(container_name, cmake_exec) {
    sh """docker exec ${containter_name} sh -c \"
        cd build
        ${cmake_exec} --version
        ${cmake_exec} -DCOV=1 -DCMAKE_BUILD_TYPE=Debug ../${project}
    \""""
}

def build_function(container_name) {
    sh """docker exec ${containter_name} sh -c \"
        cd build
        make --version
        make unit_tests VERBOSE=1
    \""""
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
                def conan_remote = "ess-dmsc-local"
                sh """docker exec ${centos_containter_name} sh -c \"
                    mkdir build
                    cd build
                    conan --version
                    conan remote add \
                        --insert 0 \
                        ${conan_remote} ${local_conan_server}
                    conan install ../${project} --build=missing
                \""""
                sh """docker exec ${fedora_containter_name} sh -c \"
                    mkdir build
                    cd build
                    conan --version
                    conan remote add \
                        --insert 0 \
                        ${conan_remote} ${local_conan_server}
                    conan install ../${project} --build=missing
                \""""
            } catch (e) {
                failure_function(e, 'Get dependencies failed')
            }
        }

        stage('Run CMake') {
            try {
                cmake_function('cmake3', centos_containter_name)
                cmake_function('cmake', fedora_containter_name)
            } catch (e) {
                failure_function(e, 'CMake failed')
            }
        }

        stage('Build') {
            try {
                build_function(centos_containter_name)
                build_function(fedora_containter_name)
            } catch (e) {
                failure_function(e, 'Build failed')
            }
        }

        stage('Run tests') {
            dir("${project}/tests") {

                try {
                    sh """docker exec ${centos_containter_name} sh -c \"
                        cd build
                        make run_tests
                    \""""
                } catch(e) {
                    failure_function(e, 'Run tests (centos) failed')
                } finally {
                    sh "docker cp ${centos_containter_name}:/home/jenkins/build/test/unit_tests_run.xml unit_tests_run.xml"
                    junit 'unit_tests_run.xml'
                }


                try {
                    sh """docker exec ${fedora_containter_name} sh -c \"
                        cd build
                        make generate_coverage
                    \""""
                } catch(e) {
                    failure_function(e, 'Run rests (fedora) failed')
                } finally {
                    sh "docker cp ${fedora_containter_name}:/home/jenkins/build/test/unit_tests_run.xml unit_tests_run.xml"
                    junit 'unit_tests_run.xml'
                }
            }
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
