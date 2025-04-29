def set_post(){
	post {
		always {
			discordSend(
				webhookURL: env.WEBHOOK_NISHBOX,
				link: env.BUILD_URL,
				result: currentBuild.currentResult,
				title: env.JOB_NAME,
				showChangeset: true,
				enableArtifactsList: true
			)
		}
	}
}

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
		}
		set_post()
	}
}
