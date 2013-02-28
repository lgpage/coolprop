REM ******** set the variables ************
call "C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\vcvarsall.bat"
call "C:\Program Files\Microsoft Visual Studio 10.0\VC\vcvarsall.bat"

REM ******* compile all the sources ***************
cl /c /I../../CoolProp /EHsc /DCOOLPROP_LIB ../../CoolProp/*.cpp
cl /c /I../../CoolProp /EHsc /DCOOLPROP_LIB ../../CoolProp/purefluids/*.cpp
cl /c /I../../CoolProp /EHsc /DCOOLPROP_LIB ../../CoolProp/pseudopurefluids/*.cpp

link /DLL CoolProp.obj *.obj /OUT:CoolProp.dll
dumpbin /EXPORTS CoolProp.dll > exports.txt
erase *.obj
