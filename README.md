# WiiU-Keyboard

This is a keyboard for the Nintendo WiiU.

Binaries can be found in the Release section.

Support and further information can be found at https://gbatemp.net/threads/wip-wiiu-keyboard.414995.

The font the characters are inspired by can be found here: http://www.ffonts.net/Mister-Pixel-16-pt-Small-Caps.font (Copyright (c) Christophe Badani, 2003)

Big thanks to CreeperMario who ported this to HBL and made it available for use by other developers! <3

# Using in other projects

CreeperMario said in the comment on his pull request:

>The keyboard can now be opened by calling launchKeyboard(&returnedString); (with char returnedString[256] abive it). Once the >user presses HOME, the string is returned and can be re-printed to the screen using OSScreenPutFontEx.

>Most importantly, any user can easily insert the keyboard into their HBL program by copying draw.c, draw.h, keyboard.c and > > > >keyboard.h to their own project.

![Screenshot Keyboard](http://abload.de/img/fru16.jpg)
![Screenshot Settings](http://abload.de/img/mmqca.jpg)
![Screenshot Change Theme](http://abload.de/img/errfk.jpg)
