project = "h5cpp"

node ("macos") {
    // Delete workspace when build is done
    cleanWs()

    stage("Checkout") {
        dir("${project}/code") {
            try {
                checkout scm
            } catch (e) {
                failure_function(e, 'MacOSX / Checkout failed')
            }
        }
    }

    stage("CMake") {
        dir("${project}/build") {
            try {
                sh "cmake ../code"
            } catch (e) {
                failure_function(e, 'MacOSX / CMake failed')
            }
        }

    }

    stage("Build") {
        dir("${project}/build") {
            try {
                sh "make h5cpp_shared"
            } catch (e) {
                failure_function(e, 'MacOSX / build failed')
            }
        }
    }
}
