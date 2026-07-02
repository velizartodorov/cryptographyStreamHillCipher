@echo off
echo Setting up Visual Studio environment and building project...

REM Try to find and use Visual Studio Developer Command Prompt
if exist "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat" (
    echo Using Visual Studio 2022 Community...
    call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"
) else if exist "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd.bat" (
    echo Using Visual Studio 2019 Community...
    call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd.bat"
) else if exist "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\Tools\VsDevCmd.bat" (
    echo Using Visual Studio 2017 Community...
    call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\Tools\VsDevCmd.bat"
) else (
    echo Visual Studio not found in standard locations.
    echo Please install Visual Studio or ensure it's in the PATH.
    pause
    exit /b 1
)

echo Building test project...
msbuild TestProject.vcxproj /p:Configuration=Debug /p:Platform=x64 /verbosity:minimal

if %ERRORLEVEL% neq 0 (
    echo Build failed!
    pause
    exit /b 1
)

echo Building main project...
msbuild StreamHillCipherEncoding.vcxproj /p:Configuration=Debug /p:Platform=x64 /verbosity:minimal

if %ERRORLEVEL% neq 0 (
    echo Main project build failed!
    pause
    exit /b 1
)

echo Build completed successfully!
echo.
echo Running tests...
if exist "x64\Debug\TestProject.exe" (
    x64\Debug\TestProject.exe
) else (
    echo Test executable not found!
)

pause
