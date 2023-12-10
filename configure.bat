@echo off

meson setup --wipe build || goto :error

:error
exit /b %errorlevel%