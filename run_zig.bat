@echo off

.\toolchain\zig-windows-x86_64\zig-upx.exe build || goto :error
.\zig-out\bin\daydream.exe || goto :error

:error
exit /b %errorlevel%
