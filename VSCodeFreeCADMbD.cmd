@echo off
setlocal

set "WORKSPACE=%~dp0"
set "VS2026="
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist "%VSWHERE%" (
    echo Visual Studio Installer was not found.
    exit /b 1
)
for /f "usebackq tokens=*" %%i in (`call "%VSWHERE%" -latest -version "[18.0,19.0)" -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set "VS2026=%%i"
if not defined VS2026 (
    echo Install Visual Studio 2026 with Desktop development with C++.
    exit /b 1
)
call "%VS2026%\Common7\Tools\VsDevCmd.bat" -arch=x64 -host_arch=x64
if errorlevel 1 exit /b 1
cd /d "%WORKSPACE%"
code --new-window .
