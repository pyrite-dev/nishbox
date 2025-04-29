pipeline {
	agent any
	stages {
		stage("Build") {
			steps {
			}
		}
	}
	post {
		always {
			discordSend(
				webhookURL: params.webhook1,
				link: env.BUILD_URL,
				result: currentBuild.currentResult,
				title: env.JOB_NAME
			)
		}
	}
}
