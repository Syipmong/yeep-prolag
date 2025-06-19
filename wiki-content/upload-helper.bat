@echo off
title Yeep Wiki Documentation Helper
echo.
echo ===============================================
echo    Yeep Programming Language - Wiki Helper
echo ===============================================
echo.

echo This directory contains comprehensive wiki documentation for Yeep.
echo.
echo Available wiki pages:
echo.

for %%f in (*.md) do (
    if not "%%f"=="README.md" (
        echo   - %%f
    )
)

echo.
echo To upload to GitHub Wiki:
echo 1. Go to: https://github.com/itsthatblackhat/yeep-prolag/wiki
echo 2. Create new pages using the content from each .md file
echo 3. Use the filename (without .md) as the page title
echo.
echo Recommended upload order:
echo 1. Home.md (main page)
echo 2. Installation-Guide.md
echo 3. Language-Tutorial.md
echo 4. Language-Reference.md
echo 5. Standard-Library.md
echo 6. Examples-Gallery.md
echo 7. (Continue with remaining files)
echo.
echo For detailed instructions, see README.md in this directory.
echo.
pause
