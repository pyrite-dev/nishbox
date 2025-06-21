pipeline {
	agent any
	environment {
		WEBHOOK_NISHBOX = credentials("webhook-nishbox")
		WEBHOOK_ORIN = credentials("webhook-orin")
		WEBHOOK_PRIVATE1 = credentials("webhook-private1")
	}
	stages {
		stage("Build"){
			parallel {
				stage("MSVC Build for 32-bit") {
					agent {
						label "2012r2-x86"
					}
					steps {
						bat "git submodule update --init --recursive"
						bat "premake5 vs2015 --engine=dynamic --opengl=gdi --cc=msc --prefix=C:/Games"
						bat "msbuild nishbox.sln /p:Configuration=Release"
						bat "pack -d data base.pak"
						bat "makensis /DCONFIG=Release /DPLATFORM=Native install.nsi"
						bat "move /y install.exe install32-vs2015.exe"
						archiveArtifacts(
							"install32-vs2015.exe"
						)
					}
					post {
						always {
							post_always(false, false)
						}
					}
				}
				stage("Build for AppImage") {
					agent any
					steps {
						sh "git submodule update --init --recursive"
						sh "premake5 gmake --engine=static"
						sh "gmake config=release_native -j9"
						sh "pack -d data base.pak"
						sh "rm -rf app"
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
						sh "cp -rf bin/*/*/nishbox app/usr/bin/"
						sh "echo 'exec \$APPDIR/usr/bin/nishbox \"\$@\"' >> app/AppRun"
						sh "echo 'Name=NishBox' >> app/nishbox.desktop"
						sh "echo 'Exec=nishbox' >> app/nishbox.desktop"
						sh "ARCH=x86_64 appimagetool app nishbox64.AppImage"
						archiveArtifacts(
							"nishbox64.AppImage"
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
						sh "premake5 gmake --engine=dynamic --opengl=gdi --prefix=C:/Games"
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
						sh "premake5 gmake --engine=dynamic --opengl=gdi --prefix=C:/Games"
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
					post_always(true, true, true)
				}
			}
		}
	}
}

def post_always(cmt,art,alw=false){
	def list = [env.WEBHOOK_NISHBOX, env.WEBHOOK_ORIN, env.WEBHOOK_PRIVATE1]
	for(int i = 0; i < list.size(); i++){
		if(alw || currentBuild.currentResult != "SUCCESS"){
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
}
