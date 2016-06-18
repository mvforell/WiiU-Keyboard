# How to compile

You need to have devkitPPC installed and the binaries in your PATH.
If you haven't, create a new environmental variable called WIILOAD and set its value to "tcp:< your WiiU's IP adress >".
(Or comment out line 128 in the Makefile if you don't want to use this awesome tool)

Now open a terminal, cd to the root folder of this project and run make. If you've setup everything correctly,
everything should build just fine and the new .elf file will be sent to your console (if you haven't disabled it).
