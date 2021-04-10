@ECHO OFF

ECHO compiling cpp file

cl gen_redirection.cpp

ECHO runing gen_redirection.exe on libcef file
gen_redirection.exe < libcef > out

ECHO cleaning ...
del gen_redirection.exe

PAUSE
