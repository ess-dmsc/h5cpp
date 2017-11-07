project = "h5cc"

def centos = docker.image('essdmscdm/centos-build-node:0.7.0')
def fedora = docker.image('essdmscdm/fedora-build-node:0.3.0')

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


node('docker') {
    // Delete workspace when build is done
    cleanWs()

    dir("${project}") {
        stage('Checkout project') {
            try {
                scm_vars = checkout scm
            } catch (e) {
                failure_function(e, 'Checkout failed')
            }
        }
    }


    try {
        def container_name = "${base_container_name}-centos"
        container = centos.run("\
            --name ${container_name} \
            --tty \
            --env http_proxy=${env.http_proxy} \
            --env https_proxy=${env.https_proxy} \
        ")

        // Copy sources to container.
        sh "docker cp ${project} ${container_name}:/home/jenkins/${project}"

        stage('Get dependencies') {
            def conan_remote = "ess-dmsc-local"
            sh """docker exec ${container_name} sh -c \"
                mkdir build
                cd build
                conan --version
                conan remote add \
                    --insert 0 \
                    ${conan_remote} ${local_conan_server}
                conan install ../${project} --build=missing
            \""""
        }

        stage('Run CMake') {
            sh """docker exec ${container_name} sh -c \"
                cd build
                cmake3 --version
                cmake3 -DCOV=1 -DCMAKE_BUILD_TYPE=Debug ../${project}
            \""""
        }

        stage('Build library') {
            sh """docker exec ${container_name} sh -c \"
                cd build
                make --version
                make h5cpp_shared VERBOSE=1
            \""""
        }

        stage('Build tests') {
            sh """docker exec ${container_name} sh -c \"
                cd build
                make unit_tests VERBOSE=1
            \""""
        }

        stage('Run tests') {
            sh """docker exec ${container_name} sh -c \"
                cd build
                make run_tests
            \""""
        }

    } catch(e) {
        failure_function(e, 'Failed')
    } finally {
        container.stop()
    }



}

/*
node ("centos7") {
    cleanWs()

    dir("${project}/code") {
        try {
            stage("Checkout project") {
                checkout scm
            }
        } catch (e) {
            failure_function(e, 'Checkout failed')
        }
    }

    dir("${project}/build") {
        try {
            stage("Run CMake") {
                sh "HDF5_ROOT=$HDF5_ROOT \
                    CMAKE_PREFIX_PATH=$HDF5_ROOT \
                    cmake3 -DCMAKE_BUILD_TYPE=Debug ../code"
            }
        } catch (e) {
            failure_function(e, 'CMake failed')
        }

        try {
            stage("Build project") {
                sh "make VERBOSE=1"
            }
        } catch (e) {
            failure_function(e, 'Build failed')
        }

        try {
            stage("Run tests") {
                sh "make run_tests"
                junit 'test/unit_tests_run.xml'
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
          }
        } catch (e) {
            junit 'test/unit_tests_run.xml'
            failure_function(e, 'Tests failed')
        }

        try {
            stage("Build docs") {
                sh "make html"
                if (env.BRANCH_NAME != 'master') {
                  archiveArtifacts artifacts: 'doc/build/'
                }
          }
        } catch (e) {
            failure_function(e, 'Docs generation failed')
        }
    }

    dir("${project}/docs") {
        try {
            stage("Publish docs") {
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
            }
        } catch (e) {
            failure_function(e, 'Publishing docs failed')
        }
    }
}
*/
