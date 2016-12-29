@echo off

if not defined DevEnvDir (
	call vcvarsall.bat
	)

pushd ..\build
cl -EHsc ..\code\main.cpp User32.lib ..\code\libs\SDL2.lib ..\code\libs\SDL2main.lib ..\code\libs\SDL2test.lib
popd