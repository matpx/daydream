@echo off

meson compile -C build || goto :error
.\build\src\daydream.exe || goto :error

:error
exit /b %errorlevel%
