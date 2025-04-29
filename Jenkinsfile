pipeline {
	agent any
	environment {
		WEBHOOK_NISHBOX = credentials("webhook-nishbox")
		WEBHOOK_ORIN = credentials("webhook-orin")
	}
	stages {
		stage("Build") {
			steps {
				echo "dummy"
			}
			post {
				always {
					post_always()
				}
			}
		}
	}
}

def post_always(){
	discordSend(
		webhookURL: env.WEBHOOK_NISHBOX,
		link: env.BUILD_URL,
		result: currentBuild.currentResult,
		title: env.JOB_NAME,
		showChangeset: true,
		enableArtifactsList: true,
		description: "**Build:** ${env.BUILD_NUMBER}\n**Status:** ${currentBuild.currentResult}"
	)
}
