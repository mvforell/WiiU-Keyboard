#ifndef PROGRAM_H
#define PROGRAM_H

#include "vpad.h"
#include "types.h"
#include "draw.h"

struct renderFlags {
	int menu;
	int QWERTY;
	int change_theme;
	int textLength;
	int keyAPressed;
	int keyBPressed;
	int keyCPressed;
	int keyDPressed;
	int keyEPressed;
	int keyFPressed;
	int keyGPressed;
	int keyHPressed;
	int keyIPressed;
	int keyJPressed;
	int keyKPressed;
	int keyLPressed;
	int keyMPressed;
	int keyNPressed;
	int keyOPressed;
	int keyPPressed;
	int keyQPressed;
	int keyRPressed;
	int keySPressed;
	int keyTPressed;
	int keyUPressed;
	int keyVPressed;
	int keyWPressed;
	int keyXPressed;
	int keyYPressed;
	int keyZPressed;
	int keyBackspacePressed;
	int keySpacePressed;
	int b;
	int plus;
	int bTouched;
	int plusTouched;
	int HomeTouched;	
	int touch;
	char theme[32];
	char text[256];
	char touching[32];
};

void _entryPoint();
void render(struct renderFlags *flags);
void drawChar(char character, int xpos, int ypos, int scale, char r, char g, char b, char a);
void fillTV(char r, char g, char b, char a);
void drawStringTV(int x, int line, char * string);

#endif /* PROGRAM_H */