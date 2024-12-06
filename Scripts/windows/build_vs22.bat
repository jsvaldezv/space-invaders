@echo off
title Build VS22 Project

echo ==========================================
echo                 Starting...
echo ==========================================

:: ============================================================================

set filename=Config.cfg

for /f "tokens=2 delims==" %%a in ('findstr "PROJECT_NAME" %filename%') do set PROJECT_NAME=%%a
for /f "tokens=2 delims==" %%a in ('findstr "PROJECT_VERSION" %filename%') do set PROJECT_VERSION=%%a
for /f "tokens=2 delims==" %%a in ('findstr "CPP_VERSION" %filename%') do set CPP_VERSION=%%a

set GENERATOR="Visual Studio 17 2022"

:: ============================================================================

echo ==========================================
echo       Creating %GENERATOR% project...

cmake -G %GENERATOR% -B VS22 -T ClangCL ^
	-D PROJECT_NAME=%PROJECT_NAME% ^
	-D PROJECT_VERSION=%PROJECT_VERSION% ^
	-D CPP_VERSION=%CPP_VERSION%

echo ==========================================
echo            Opening %GENERATOR%...
echo ==========================================

start VS22/%PROJECT_NAME%.sln