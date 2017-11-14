project = "h5cpp"

images = [
    'centos': [
        'name': 'essdmscdm/centos-build-node:0.8.0',
        'sh': 'sh',
        'cmake': 'cmake3'
    ],
    'centos-gcc6': [
        'name': 'essdmscdm/centos-gcc6-build-node:0.2.0',
        'sh': '/usr/bin/scl enable rh-python35 devtoolset-6 -- /bin/bash',
        'cmake': 'cmake'
    ],
    'fedora': [
        'name': 'essdmscdm/fedora-build-node:0.4.1',
        'sh': 'sh',
        'cmake': 'cmake'
    ],
    'ubuntu1604': [
        'name': 'essdmscdm/ubuntu16.04-build-node:0.0.1',
        'sh': 'sh',
        'cmake': 'cmake'
    ],
    'ubuntu1710': [
        'name': 'essdmscdm/ubuntu17.10-build-node:0.0.2',
        'sh': 'sh',
        'cmake': 'cmake'
    ]
]

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

def docker_cmake(container_name, cmake_exec) {
    sh """docker exec ${container_name} sh -c \"
        cd build
        ${cmake_exec} --version
        ${cmake_exec} -DCMAKE_BUILD_TYPE=Release ../${project}
    \""""
}

def docker_build(container_name) {
    sh """docker exec ${container_name} sh -c \"
        cd build
        make --version
        make unit_tests
    \""""
}

def docker_tests(container_name) {
    dir("${project}/tests") {
        try {
            sh """docker exec ${container_name} sh -c \"
                cd build
                make run_tests
            \""""
        } catch(e) {
            sh "docker cp ${container_name}:/home/jenkins/build/test/unit_tests_run.xml unit_tests_run.xml"
            junit 'unit_tests_run.xml'
            failure_function(e, 'Run tests (${container_name}) failed')
        }
    }
}

def cont_name(suffix) {
    return "${base_container_name}-${suffix}"
}

def Object get_container(container_name, image_name) {
    def image = docker.image(image_name)
    def container = image.run("\
        --name ${container_name} \
        --tty \
        --env http_proxy=${env.http_proxy} \
        --env https_proxy=${env.https_proxy} \
        ")
    return container
}

node('docker && dmbuild03.dm.esss.dk') {
    // Delete workspace when build is done
    cleanWs()

    stage('Checkout') {
        dir("${project}/code") {
            try {
                scm_vars = checkout scm
            } catch (e) {
                failure_function(e, 'Checkout failed')
            }
        }
    }

    try {
        centos_container = get_container(cont_name('centos'), 'essdmscdm/centos-build-node:0.8.0')
        fedora_container = get_container(cont_name('fedora'), 'essdmscdm/fedora-build-node:0.4.1')
        ub1604_container = get_container(cont_name('ub1604'), 'essdmscdm/ubuntu16.04-build-node:0.0.1')

        // Copy sources to container.
        dir("${project}") {
            sh "docker cp code ${cont_name('centos')}:/home/jenkins/${project}"
            sh "docker cp code ${cont_name('fedora')}:/home/jenkins/${project}"
            sh "docker cp code ${cont_name('ub1604')}:/home/jenkins/${project}"
        }

        stage('Dependencies') {
            try {
                docker_dependencies(cont_name('centos'))
                docker_dependencies(cont_name('fedora'))
                docker_dependencies(cont_name('ub1604'))
            } catch (e) {
                failure_function(e, 'Get dependencies failed')
            }
        }

        stage('CMake') {
            try {
                docker_cmake(cont_name('centos'), 'cmake3')
                docker_cmake(cont_name('fedora'), 'cmake')
                docker_cmake(cont_name('ub1604'), 'cmake')
            } catch (e) {
                failure_function(e, 'CMake failed')
            }
        }

        stage('Build') {
            try {
                docker_build(cont_name('centos'))
                docker_build(cont_name('fedora'))
                docker_build(cont_name('ub1604'))
            } catch (e) {
                failure_function(e, 'Build failed')
            }
        }

        stage('Run tests') {
            docker_tests(cont_name('centos'))
            docker_tests(cont_name('fedora'))
            docker_tests(cont_name('ub1604'))
        }

    } catch(e) {
        failure_function(e, 'Unknown build failure')
    } finally {
        centos_container.stop()
        fedora_container.stop()
        ub1604_container.stop()
    }
}


node ("fedora") {
    // Delete workspace when build is done
    cleanWs()

    stage("Coverage") {
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
                junit 'test/unit_tests_run.xml'
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
                junit 'test/unit_tests_run.xml'
            }
        }
    }

    stage("Documentation") {
        dir("${project}/build") {
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
