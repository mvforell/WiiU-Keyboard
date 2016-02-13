#ifndef PROGRAM_H
#define PROGRAM_H
#include "../../../libwiiu/src/coreinit.h"
#include "../../../libwiiu/src/vpad.h"
#include "../../../libwiiu/src/types.h"
#include "../../../libwiiu/src/draw.h"

struct renderFlags {
	int menu;
	int QWERTY;
	int change_theme;
	int textLength;
	// int keyAPressed;
	// int keyBPressed;
	// int keyCPressed;
	// int keyDPressed;
	// int keyEPressed;
	// int keyFPressed;
	// int keyGPressed;
	// int keyHPressed;
	// int keyIPressed;
	// int keyJPressed;
	// int keyKPressed;
	// int keyLPressed;
	// int keyMPressed;
	// int keyNPressed;
	// int keyOPressed;
	// int keyPPressed;
	// int keyQPressed;
	// int keyRPressed;
	// int keySPressed;
	// int keyTPressed;
	// int keyUPressed;
	// int keyVPressed;
	// int keyWPressed;
	// int keyXPressed;
	// int keyYPressed;
	// int keyZPressed;
	// int a;
	int b;
	// int x;
	// int y;
	// int l;
	// int r;
	// int zl;
	// int zr;
	int plus;
	// int minus;
	// int start;
	// int pow;
	int touch;
	// int du;
	// int dd;
	// int dl;
	// int dr;
	// char startUp[255];
	char theme[32];
	char text[256];
	// char aPressed[32];
	// char bPressed[32];
	// char xPressed[32];
	// char yPressed[32];
	// char lPressed[32];
	// char rPressed[32];
	// char zlPressed[32];
	// char zrPressed[32];
	// char plusPressed[32];
	// char minusPressed[32];
	// char power[32];
	char touching[32];
	// char dUp[32];
	// char dDown[32];
	// char dLeft[32];
	// char dRight[32];
};

void _entryPoint();
void render(struct renderFlags *flags);
// void wait(unsigned int ticks);
void drawChar(char character, int xpos, int ypos, int scale, char r, char g, char b, char a);
void fillTV(char r, char g, char b, char a);
void drawStringTV(int x, int line, char * string);

#endif /* PROGRAM_H */