VIFileVersion "1.0.0.0"
VIProductVersion "1.0.0.0"
VIAddVersionKey "FileVersion" "1.0.0.0"
VIAddVersionKey "CompanyName" "Pyrite Development Team"
VIAddVersionKey "LegalCopyright" "3-clause BSD"
VIAddVersionKey "FileDescription" "NishBox Installer"

LoadLanguageFile "${NSISDIR}\Contrib\Language Files\English.nlf"

Name "NishBox"
OutFile "install.exe"
InstallDir "C:\NishBox"
Icon "src/icon.ico"
LicenseData LICENSE

!include "x64.nsh"
!include "LogicLib.nsh"
!include "Sections.nsh"

Page license
Page directory
Page instfiles
UninstPage uninstConfirm
UninstPage instfiles

Section
	CreateDirectory "$INSTDIR"
	SetOutPath "$INSTDIR"
	File /oname=LICENSE.txt "LICENSE"
	File "bin\${CONFIG}\${PLATFORM}\nishbox.exe"
	File "bin\${CONFIG}\${PLATFORM}\nishbox_server.exe"
	File /nonfatal "engine\lib\${CONFIG}\${PLATFORM}\*.dll"
	File "base.pak"

	CreateDirectory "$SMPROGRAMS\NishBox"
	CreateShortcut "$SMPROGRAMS\NishBox\License.lnk" "$INSTDIR\LICENSE.txt" ""
	CreateShortcut "$SMPROGRAMS\NishBox\NishBox.lnk" "$INSTDIR\nishbox.exe" ""
	CreateShortcut "$SMPROGRAMS\NishBox\NishBox Dedicated Server.lnk" "$INSTDIR\nishbox_server.exe" ""
	CreateShortcut "$SMPROGRAMS\NishBox\Uninstall NishBox.lnk" "$INSTDIR\uninstall.exe" ""

	${If} ${RunningX64}
		SetRegView 64
	${Else}
		SetRegView 32
	${EndIf}

        WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\NishBox" "DisplayName" "NishBox"
        WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\NishBox" "InstallDir" "$INSTDIR"
        WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\NishBox" "UninstallString" '"$INSTDIR\uninstall.exe"

	WriteUninstaller "$INSTDIR\uninstall.exe"
SectionEnd

Section "Uninstall"
	RMDir /r "$INSTDIR"
	RMDir /r "$SMPROGRAMS\NishBox"

	${If} ${RunningX64}
		SetRegView 64
	${Else}
		SetRegView 32i
	${EndIf}

	DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\NishBox"
SectionEnd
