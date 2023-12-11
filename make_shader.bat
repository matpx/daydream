@echo off

.\toolchain\sokol-tools-bin\bin\win32\sokol-shdc.exe --input=shader\unlit.glsl --output=shader\include\shader\unlit.h --slang=glsl330  || goto :error

:error
exit /b %errorlevel%
