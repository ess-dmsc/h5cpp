/*
 * h5cpp Jenkinsfile
 */
def failure_function(exception_obj, failureMessage) {
    def toEmails = [[$class: 'DevelopersRecipientProvider']]
    emailext body: '${DEFAULT_CONTENT}\n\"' + failureMessage + '\"\n\nCheck console output at $BUILD_URL to view the results.', recipientProviders: toEmails, subject: '${DEFAULT_SUBJECT}'
    throw exception_obj
}

node ("boost && fedora") {
    cleanWs()

    dir("code") {
        try {
            stage("Checkout project") {
                checkout scm
            }
        } catch (e) {
            failure_function(e, 'Checkout failed')
        }
    }

    dir("build") {
        try {
            stage("Run CMake") {
                sh 'gcov --version'
                sh 'gcovr --version'
                sh 'rm -rf ./*'
                sh "HDF5_ROOT=$HDF5_ROOT \
                    CMAKE_PREFIX_PATH=$HDF5_ROOT \
                    cmake -DCOV=on -DCMAKE_BUILD_TYPE=Debug ../code"
            }
        } catch (e) {
            failure_function(e, 'CMake failed')
        }

        try {
            stage("Build project") {
                //sh "make VERBOSE=1"
            }
        } catch (e) {
            failure_function(e, 'Build failed')
        }

        try {
            stage("Run tests") {
                //sh "make run_tests"
                //junit 'test/unit_tests_run.xml'
                //sh "make generate_coverage"
/*                sh "make memcheck"*/
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
                // Archive the build output artifacts.
                archiveArtifacts artifacts: 'doc/build/'
          }
        } catch (e) {
            failure_function(e, 'Docs generation failed')
        }
    }

    dir("code") {
        try {
            stage("Punlish docs") {
                checkout scm

                sh "git config user.email 'dm-jenkins-integration@esss.se'"
                sh "git config user.name 'cow-bot'"

                sh "git checkout -b gh-pages"
                sh "yes | cp -rf ../build/doc/build ./"
                sh "git add ."
                sh "git commit -a -m 'This is a test.'"

                //withCredentials([usernamePassword(
                 //   credentialsId: 'cow-bot-username',
                  //  usernameVariable: 'USERNAME',
                   // passwordVariable: 'PASSWORD'
                //)]) {
                //    sh "./expectscript ${USERNAME} ${PASSWORD}"
                //}

            }
        } catch (e) {
            failure_function(e, 'Publishing docs failed')
        }
    }
}
