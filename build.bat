@echo off
if not exist build (mkdir build)
pushd build
cl /nologo /Zi /EHsc /I"..\include" "..\src\*.cpp" 
popd