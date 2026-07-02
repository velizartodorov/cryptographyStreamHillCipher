@echo off
echo Building and running StreamHillCipherEncoding tests...
echo.

REM Build the test project
echo Building test project...
msbuild TestProject.vcxproj /p:Configuration=Debug /p:Platform=x64 /verbosity:minimal

if %ERRORLEVEL% neq 0 (
    echo Build failed!
    pause
    exit /b 1
)

echo.
echo Running tests...
echo.

REM Run the tests
if exist "x64\Debug\TestProject.exe" (
    x64\Debug\TestProject.exe
) else (
    echo Test executable not found!
    echo Please check the build output above.
)

echo.
echo Tests completed.
pause
