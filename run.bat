@echo off

.\toolchain\zig\zig.exe build -Doptimize=Debug || goto :error
.\zig-out\bin\daydream.exe || goto :error

:error
exit /b %errorlevel%
