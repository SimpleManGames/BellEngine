@echo on
pushd ..\
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE\devenv.exe" /build release "\Bell\vendor\enet\enet.sln"
popd
PAUSE