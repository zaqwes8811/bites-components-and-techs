# http://www.seas.gwu.edu/~drum/java/lectures/appendix/installer/install.html
# define installer name

# OS detection 
# http://stackoverflow.com/questions/14409801/nsis-detect-windows-version

!include "MUI2.nsh"
!include WinVer.nsh
!include wver.nsh
!include "LogicLib.nsh"

Function LogWinVer

    ${WinVerGetMajor} $R0
    ${WinVerGetMinor} $R1
    ${WinVerGetBuild} $R2
    ${WinVerGetServicePackLevel} $R3

    ; determine windows product name
    ${If} $R0 == 5 
            ${If} $R1 == 0
                    DetailPrint "Windows 2000 SP $R3"
            ${ElseIf} $R1 == 1
                    DetailPrint "Windows XP SP $R3"
            ${ElseIf} $R1 == 2
                    DetailPrint "Windows Server 2003 SP $R3"
            ${EndIf}
    ${ElseIf} $R0 == 6
            ${If} $R1 == 0
                    ${If} ${IsServerOS}
                            DetailPrint "Windows Server 2008 SP $R3"
                    ${Else}
                            DetailPrint "Windows Vista SP $R3"
                    ${EndIf}
            ${ElseIf} $R1 == 1
                    ${If} ${IsServerOS}
                            DetailPrint "Windows Server 2008 R2 SP $R3"
                    ${Else}
                            DetailPrint "Windows 7 SP $R3"
                    ${EndIf}
            ${ElseIf} $R1 == 2
                    ${If} ${IsServerOS} 
                            DetailPrint "Windows Server 2012 SP $R3"
                    ${Else}
                            DetailPrint "Windows 8 SP $R3"
                    ${EndIf}
            ${ElseIf} $R1 == 3
                    ${If} ${IsServerOS}
                            DetailPrint "Windows Server 2012 R2 SP $R3"
                    ${Else}
                            DetailPrint "Windows 8.1 SP $R3"
                    ${EndIf}
            ${EndIf}
    ${EndIf}

    ; version
    DetailPrint "Kernel $R0.$R1 build $R2"


    ; x86 or x64:
    Call LogWinVer
    System::Call "kernel32::GetCurrentProcess() i .s"
    System::Call "kernel32::IsWow64Process(i s, *i .r0)"
    StrCmp $0 "0" is32bit is64bit

    is32bit:
            DetailPrint "32 bit"
            Goto exit
    is64bit:
            DetailPrint "64 bit"
    exit:
FunctionEnd

OutFile "installer.exe"
 
# set desktop as install directory
InstallDir $DESKTOP\App

; The default installation directory
#InstallDir $PROGRAMFILES\Example1

# Deps
Var QtBinPath ;Declare the variable
Var OpenSSLBinPath ;
Var ExeFileDir ;
var myVar

!define MUI_LANGDLL_ALLLANGUAGES
!insertmacro MUI_LANGUAGE "Russian"
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_RESERVEFILE_LANGDLL

# http://nsis.sourceforge.net/Get_Windows_version

Function .onInit
!insertmacro MUI_LANGDLL_DISPLAY ;This has to come after the language macros
FunctionEnd

; The text to prompt the user to enter a directory
DirText "This will install My Cool Program on your computer. Choose a directory"

# default section start
Section
	${GetWindowsVersion} $myVar
	MessageBox MB_OK "2003 SP1 is required $myVar"
	
	CreateDirectory $INSTDIR

	 
	# define output path
	SetOutPath $INSTDIR
	 
	# specify file to go in output path
	File "c:\\packer_release.exe"
	File "C:\\Qt\\5.4\\mingw491_32\\bin\\Qt5Core.dll"
	File "C:\\Qt\\5.4\\mingw491_32\\bin\\Qt5Widgets.dll"
	File "C:\\Qt\\5.4\\mingw491_32\\bin\\Qt5Gui.dll"
	File "C:\\Qt\\5.4\\mingw491_32\\bin\\libgcc_s_dw2-1.dll"
	File "C:\\Qt\\5.4\\mingw491_32\\bin\\libwinpthread-1.dll"
	File "C:\\Qt\\5.4\\mingw491_32\\bin\\libstdc++-6.dll"
	File "C:\\Qt\\5.4\\mingw491_32\\bin\\icudt53.dll"
	File "C:\\Qt\\5.4\\mingw491_32\\bin\\icuin53.dll"
	File "C:\\Qt\\5.4\\mingw491_32\\bin\\icuuc53.dll"
	
	File "/oname=tar.exe" "tar.exe__" 
		 
	# define uninstaller name
	WriteUninstaller $INSTDIR\uninstaller.exe
	
	# FIXME: make lnk
SectionEnd
 
# create a section to define what the uninstaller does.
# the section will always be named "Uninstall"
Section "Uninstall"
	 
	# Always delete uninstaller first
	Delete $INSTDIR\uninstaller.exe
	 
	# now delete installed file
	Delete $INSTDIR\packer_release.exe
	Delete $INSTDIR\tar.exe
	Delete $INSTDIR\*.dll

	# App folder
	RMDir $INSTDIR
	
	# FIXME: rm lnk and reg
 
SectionEnd