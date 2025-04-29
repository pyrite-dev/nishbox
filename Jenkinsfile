pipeline {
	agent any
	stages {
		stage("Build") {
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
