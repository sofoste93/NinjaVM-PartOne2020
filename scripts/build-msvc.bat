@echo off
setlocal

set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist "%VSWHERE%" (
    echo Visual Studio Installer could not be found.
    exit /b 1
)

for /f "usebackq tokens=*" %%i in (`"%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set "VSROOT=%%i"
if not defined VSROOT (
    echo Visual Studio C++ tools were not found.
    exit /b 1
)
set "VCVARS=%VSROOT%\VC\Auxiliary\Build\vcvars64.bat"

call "%VCVARS%" >nul
if errorlevel 1 exit /b %errorlevel%

if not exist build mkdir build
cl /nologo /std:c11 /W4 /Iinclude src\main.c src\vm.c /Fe:build\njvm.exe
