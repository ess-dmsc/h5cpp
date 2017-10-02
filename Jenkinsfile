/*
 * h5cpp Jenkinsfile
 */
def failure_function(exception_obj, failureMessage) {
    def toEmails = [[$class: 'DevelopersRecipientProvider']]
    emailext body: '${DEFAULT_CONTENT}\n\"' + failureMessage + '\"\n\nCheck console output at $BUILD_URL to view the results.', recipientProviders: toEmails, subject: '${DEFAULT_SUBJECT}'
    throw exception_obj
}

node ("boost && centos7") {

    dir("code") {
        try {
            stage("Checkout projects") {
                checkout scm
            }
        } catch (e) {
            failure_function(e, 'Checkout failed')
        }
    }

    dir("build") {
        try {
            stage("Run CMake") {
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
                sh "make VERBOSE=1"
                sh "make api_doc"
            }
        } catch (e) {
            failure_function(e, 'Build failed')
        }

        try {
            stage("Run test") {
                sh "make test"
                sh "make coverage"
                step([
                    $class: 'CoberturaPublisher',
                    autoUpdateHealth: false,
                    autoUpdateStability: false,
                    coberturaReportFile: 'coverage.xml',
                    failUnhealthy: false,
                    failUnstable: false,
                    maxNumberOfBuilds: 0,
                    onlyStable: false,
                    sourceEncoding: 'ASCII',
                    zoomCoverageChart: false
                ])
          }
        } catch (e) {
            junit '*Tests.xml'
            failure_function(e, 'Tests failed')
        }
    }


}
