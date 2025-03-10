

pipeline {
    agent any
    environment {
        ARDUINO_CLI = "C:\\arduino-cli\\arduino-cli.exe" // Adjust path if different
        BOARD_TYPE = "arduino:avr:uno" // Change if using a different board
        SKETCH_FOLDER = "C:\\Users\\ramoj\\Documents\\Arduino\\Blink" // Update with your sketch folder path
        PORT = "COM3" // Change based on your connected Arduino port
    }
    stages {
        stage('Checkout Code') {
            steps {
                git branch: 'main', url: 'https://github.com/prashanthramoji/arduino-ci-cd.git'
            }
        }

        stage('Compile Sketch') {
            steps {
                bat """
                \\"${ARDUINO_CLI}\\" compile --fqbn ${BOARD_TYPE} \\"${SKETCH_FOLDER}\\"
                """
            }
        }

        stage('Upload to Arduino') {
            steps {
                bat """
                \\"${ARDUINO_CLI}\\" upload --fqbn ${BOARD_TYPE} --port ${PORT} \\"${SKETCH_FOLDER}\\"
                """
            }
        }

        stage('Post-Build Verification') {
            steps {
                echo "Build and upload completed successfully!"
            }
        }
    }
}
