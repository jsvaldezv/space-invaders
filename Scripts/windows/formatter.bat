@echo off
title Build VS22 Project

echo ==========================================
echo                 Starting...
echo ==========================================

:: ============================================================================

set "directory=Source"

for /R "%directory%" %%f in (*) do 
(
    echo Processing file: %%f
    clang-format --style=file -i %%f
)

endlocal
