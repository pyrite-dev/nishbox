pipeline {
	agent any
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
