pipeline {
	agent any
	environment {
		WEBHOOK_NISHBOX = credentials("webhook-nishbox")
		WEBHOOK_ORIN = credentials("webhook-orin")
	}
	stages {
		stage("Get submodules") {
			steps {
				sh "git submodule update --init --recursive --force"
			}
			post {
				always {
					post_always(true, false)
				}
			}
		}
		stage("Build") {
			parallel {
				stage("Build for AppImage") {
					agent any
					steps {
						sh "git submodule update --init --recursive"
						sh "premake5 gmake --engine=static"
						sh "gmake config=release_native -j9"
						sh "pack -d data base.pak"
						sh "rm -rf app apps appc"
						sh "mkdir -p app/usr/bin"
						sh "mkdir -p app/usr/lib/x86_64-linux-gnu"
						sh "cp /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2 app/usr/lib/x86_64-linux-gnu/"
						sh "cp /usr/lib/x86_64-linux-gnu/libc.so* app/usr/lib/x86_64-linux-gnu/"
						sh "cp /usr/lib/x86_64-linux-gnu/libstdc++.so* app/usr/lib/x86_64-linux-gnu/"
						sh "cp /usr/lib/x86_64-linux-gnu/libgcc_s.so* app/usr/lib/x86_64-linux-gnu/"
						sh "cp base.pak app/"
						sh "cp src/icon.png app/nishbox.png"
						sh "echo '[Desktop Entry]' > app/nishbox.desktop"
						sh "echo 'Icon=nishbox' >> app/nishbox.desktop"
						sh "echo 'Type=Application' >> app/nishbox.desktop"
						sh "echo 'Categories=Game;' >> app/nishbox.desktop"
						sh "echo '#!/bin/sh' > app/AppRun"
						sh "echo 'cd \$APPDIR' >> app/AppRun"
						sh "chmod +x app/AppRun"
						sh "cp -rf app apps"
						sh "cp -rf app appc"
						sh "cp -rf bin/*/*/nishbox appc/usr/bin/"
						sh "cp -rf bin/*/*/nishbox_server apps/usr/bin/"
						sh "echo 'exec \$APPDIR/usr/bin/nishbox' >> appc/AppRun"
						sh "echo 'exec \$APPDIR/usr/bin/nishbox_server' >> apps/AppRun"
						sh "echo 'Name=NishBox' >> appc/nishbox.desktop"
						sh "echo 'Exec=nishbox' >> appc/nishbox.desktop"
						sh "echo 'Name=NishBox Dedicated Server' >> apps/nishbox.desktop"
						sh "echo 'Exec=nishbox_server' >> apps/nishbox.desktop"
						sh "ARCH=x86_64 appimagetool appc nishbox64.AppImage"
						sh "ARCH=x86_64 appimagetool apps nishbox_server64.AppImage"
						archiveArtifacts(
							"nishbox64.AppImage, nishbox_server64.AppImage"
						)
					}
					post {
						always {
							post_always(false, false)
						}
					}
				}
				stage("Build for Windows 64-bit") {
					agent any
					steps {
						sh "git submodule update --init --recursive"
						sh "premake5 gmake --engine=dynamic --opengl=gdi"
						sh "gmake config=release_win64 -j9"
						sh "pack -d data base.pak"
						sh "./tool/pack.sh Win64 nishbox nishbox64.zip"
						sh "makensis -DCONFIG=Release -DPLATFORM=Win64 install.nsi"
						sh "mv install.exe install64.exe"
						archiveArtifacts(
							"nishbox64.zip, install64.exe"
						)
					}
					post {
						always {
							post_always(false, false)
						}
					}
				}
				stage("Build for Windows 32-bit") {
					agent any
					steps {
						sh "git submodule update --init --recursive"
						sh "premake5 gmake --engine=dynamic --opengl=gdi"
						sh "gmake config=release_win32 -j9"
						sh "pack -d data base.pak"
						sh "./tool/pack.sh Win32 nishbox nishbox32.zip"
						sh "makensis -DCONFIG=Release -DPLATFORM=Win32 install.nsi"
						sh "mv install.exe install32.exe"
						archiveArtifacts(
							"nishbox32.zip, install32.exe"
						)
					}
					post {
						always {
							post_always(false, false)
						}
					}
				}
			}
			post {
				always {
					post_always(true, true)
				}
			}
		}
	}
}

def post_always(cmt,art){
	def list = [env.WEBHOOK_NISHBOX, env.WEBHOOK_ORIN]
	for(int i = 0; i < list.size(); i++){
		discordSend(
			webhookURL: list[i],
			link: env.BUILD_URL,
			result: currentBuild.currentResult,
			title: "${env.JOB_NAME} - ${env.STAGE_NAME}",
			showChangeset: cmt,
			enableArtifactsList: art,
			description: "**Build:** ${env.BUILD_NUMBER}\n**Status:** ${currentBuild.currentResult}"
		)
	}
}
