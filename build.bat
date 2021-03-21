@echo off
if not exist build (mkdir build)
pushd build
cl /nologo /Zi /EHsc /I"..\include" "..\src\pasc.cpp" "..\src\io.cpp" "..\src\ctoken.cpp" "..\src\clexer.cpp"
popd
