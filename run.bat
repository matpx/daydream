@echo off

.\toolchain\zig\zig.exe build || goto :error
.\zig-out\bin\daydream.exe || goto :error

:error
exit /b %errorlevel%
