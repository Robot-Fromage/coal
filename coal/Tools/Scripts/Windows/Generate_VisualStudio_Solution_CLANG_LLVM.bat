@echo off

:: Ensure local scope
setlocal

:: Ensure current dir
pushd %~dp0

:: CD 3 steps up to root/COAL
cd ../../../

:: Make Generated dir for generated project if not exist
IF NOT EXIST Generated_VisualStudio_Solution_CLANG_LLVM ( MKDIR Generated_VisualStudio_Solution_CLANG_LLVM )

:: Step in Generated dir
cd Generated_VisualStudio_Solution_CLANG_LLVM

:: Clean cmake garbage if there
IF EXIST CMakeFiles ( rmdir /S /Q CMakeFiles )
IF EXIST cmake_install.cmake ( del cmake_install.cmake )
IF EXIST CMakeCache.txt ( del CMakeCache.txt )

:: Rebuild Project
cmake -G "Visual Studio 15 2017 Win64" -T"llvm" -DCOAL_USE_CONFIG:BOOL=ON ../Source

:: Create symbolic link to solution in root
cd ../../
IF EXIST COAL_CLANG_LLVM.sln ( del COAL_CLANG_LLVM.sln )
mklink "COAL_CLANG_LLVM.sln" "COAL\Generated_VisualStudio_Solution_CLANG_LLVM\COAL.sln"
