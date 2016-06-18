#ifndef PROGRAM_H
#define PROGRAM_H

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
	int keyColonPressed;
	int keyPeriodPressed;
	int keyBackspacePressed;
	int keySpacePressed;
	int b;
	int x;
	int plus;
	int bTouched;
	int xTouched;
	int plusTouched;
	int HomeTouched;	
	int touch;
	char theme[32];
	char text[256];
	char touching[32];
	char rc;
	char gc;
	char bc;
};

void launchKeyboard();
void render(struct renderFlags *flags);
void drawChar(char character, int xpos, int ypos, int scale, char r, char g, char b, char a);
void fillTV(char r, char g, char b, char a);
void drawStringTV(int x, int line, char * string);
void drawOwnString(int xpos, int ypos, char * string, int length, char r, char g, char b, char a);

#endif /* PROGRAM_H */