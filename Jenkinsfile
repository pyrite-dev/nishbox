pipeline {
	agent any
	environment {
		WEBHOOK_NISHBOX = credentials("webhook-nishbox")
		WEBHOOK_ORIN = credentials("webhook-orin")
	}
	stages {
		stage("Configure for Windows") {
			steps {
				sh "premake5 gmake --engine=dynamic --opengl=gdi"
			}
			post {
				always {
					post_always()
				}
			}
		}
		stage("Build for Windows") {
			parallel {
				stage("Build for Windows 64-bit") {
					agent any
					steps {
						sh "gmake config=release_win64 -j4"
						sh "./tool/pack.sh Win64 nishbox64"
						archiveArtifacts(
							"nishbox64.zip"
						)
					}
					post {
						always {
							post_always()
						}
					}
				}
				stage("Build for Windows 32-bit") {
					agent any
					steps {
						sh "gmake config=release_win32 -j4"
						sh "./tool/pack.sh Win32 nishbox32"
						archiveArtifacts(
							"nishbox32.zip"
						)
					}
					post {
						always {
							post_always()
						}
					}
				}
			}
		}
		post {
			always {
				post_always()
			}
		}
	}
}

def post_always(){
	def list = [env.WEBHOOK_NISHBOX, env.WEBHOOK_ORIN]
	for(int i = 0; i < list.size(); i++){
		discordSend(
			webhookURL: list[i],
			link: env.BUILD_URL,
			result: currentBuild.currentResult,
			title: "${env.JOB_NAME} - ${env.STAGE_NAME}",
			showChangeset: true,
			enableArtifactsList: true,
			description: "**Build:** ${env.BUILD_NUMBER}\n**Status:** ${currentBuild.currentResult}"
		)
	}
}
