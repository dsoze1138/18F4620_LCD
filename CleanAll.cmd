@FOR /F "tokens=*" %%i IN ('dir /s/b *.x') DO @call CleanDir.cmd "%%i"
@pause