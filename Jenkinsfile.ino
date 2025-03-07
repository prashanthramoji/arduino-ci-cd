pipeline {
    agent any
    
    stages {
        stage('Clone Repository') {
            steps {
                git 'https://github.com/prashanthramoji/your-arduino-project.git'
            }
        }

        stage('Install Dependencies') {
            steps {
                sh 'arduino-cli core update'
                sh 'arduino-cli core install arduino:avr'  // Modify for your board
            }
        }

        stage('Compile Sketch') {
            steps {
                sh 'arduino-cli compile --fqbn arduino:avr:uno ./YourSketchFolder'
            }
        }

        stage('Upload to Board') {
            steps {
                sh 'arduino-cli upload -p /dev/ttyUSB0 --fqbn arduino:avr:uno ./YourSketchFolder'
            }
        }

        stage('Cleanup') {
            steps {
                sh 'rm -rf /var/lib/jenkins/workspace/Arduino_CI_CD/*'
            }
        }
    }
}

