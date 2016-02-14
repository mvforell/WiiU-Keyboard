#include "program.h"

#define WAIT_KEY 0x0A00000
#define WAIT_MENU 0x1900000

void _entryPoint()
{
	/****************************>           Get Handles           <****************************/
	//Get a handle to coreinit.rpl
	unsigned int coreinit_handle;
	OSDynLoad_Acquire("coreinit.rpl", &coreinit_handle);
	//Get a handle to vpad.rpl */
	unsigned int vpad_handle;
	OSDynLoad_Acquire("vpad.rpl", &vpad_handle);
	/****************************>       External Prototypes       <****************************/
	//VPAD functions
	int(*VPADRead)(int controller, VPADData *buffer, unsigned int num, int *error);
	//OS functions
	void(*_Exit)();
	/****************************>             Exports             <****************************/
	//VPAD functions
	OSDynLoad_FindExport(vpad_handle, 0, "VPADRead", &VPADRead);
	//OS functions
	OSDynLoad_FindExport(coreinit_handle, 0, "_Exit", &_Exit);
	/****************************>             Globals             <****************************/
	struct renderFlags flags;
	flags.touch=0;
	flags.menu=0;
	flags.QWERTY=0;
	flags.change_theme=0;
	flags.textLength=1;
	flags.keyAPressed=0;
	flags.keyBPressed=0;
	flags.keyCPressed=0;
	flags.keyDPressed=0;
	flags.keyEPressed=0;
	flags.keyFPressed=0;
	flags.keyGPressed=0;
	flags.keyHPressed=0;
	flags.keyIPressed=0;
	flags.keyJPressed=0;
	flags.keyKPressed=0;
	flags.keyLPressed=0;
	flags.keyMPressed=0;
	flags.keyNPressed=0;
	flags.keyOPressed=0;
	flags.keyPPressed=0;
	flags.keyQPressed=0;
	flags.keyRPressed=0;
	flags.keySPressed=0;
	flags.keyTPressed=0;
	flags.keyUPressed=0;
	flags.keyVPressed=0;
	flags.keyWPressed=0;
	flags.keyXPressed=0;
	flags.keyYPressed=0;
	flags.keyZPressed=0;
	flags.keyBackspacePressed=0;
	flags.keySpacePressed=0;
	flags.b=0;
	flags.plus=0;
	flags.bTouched=0;
	flags.plusTouched=0;
	flags.HomeTouched=0;
	
	VPADData vpad_data;

	__os_snprintf(flags.theme, 32, "Classic");
	__os_snprintf(flags.touching, 32, "");
	flags.text[0] = ' ';
	/****************************>            VPAD Loop            <****************************/

	/* Enter the VPAD loop */
	int error;
	//Read initial vpad status
	VPADRead(0, &vpad_data, 1, &error);

	while(1)
	{
		VPADRead(0, &vpad_data, 1, &error);
		
		if (vpad_data.tpdata.touched == 1) {
			flags.touch=1;
			__os_snprintf(flags.touching, 32, "%i, %i", vpad_data.tpdata.x, vpad_data.tpdata.y);
			if (vpad_data.tpdata.x > 350 && vpad_data.tpdata.x < 650 && vpad_data.tpdata.y < 3250 && vpad_data.tpdata.y > 3100) {
				if (!flags.QWERTY)
					flags.QWERTY = 1;
				else
					flags.QWERTY = 0;
				int wait = WAIT_MENU;
				while (--wait) {}
			}
			if (flags.menu && vpad_data.tpdata.x > 3000 && vpad_data.tpdata.x < 3700 && vpad_data.tpdata.y < 3250 && vpad_data.tpdata.y > 3100) {
				flags.change_theme = 1;
				int wait = WAIT_MENU;
				while (--wait) {}
			}
			if (flags.change_theme && vpad_data.tpdata.x > 350 && vpad_data.tpdata.x < 700 && vpad_data.tpdata.y < 3250 && vpad_data.tpdata.y > 3100) {
				__os_snprintf(flags.theme, 32, "Classic");
				flags.change_theme = 0;
				flags.menu = 0;
				int wait = WAIT_MENU;
				while (--wait) {}
			}
			if (vpad_data.tpdata.x > 3770 && vpad_data.tpdata.x < 3910 && vpad_data.tpdata.y < 520 && vpad_data.tpdata.y > 250) {
				int wait = WAIT_MENU;
				while (--wait) {}
				if (flags.menu)
					flags.bTouched=1;
				else
					flags.plusTouched=1;
			}
			if (vpad_data.tpdata.x > 140 && vpad_data.tpdata.x < 350 && vpad_data.tpdata.y < 550 && vpad_data.tpdata.y > 230) {
				int wait = WAIT_MENU;
				while (--wait) {}
				flags.HomeTouched=1;
			}
			if (vpad_data.tpdata.x > 320 && vpad_data.tpdata.x < 410 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1600) {
				flags.text[flags.textLength - 1] = 'A';
				++flags.textLength;
				int wait = WAIT_KEY;
				while (--wait) {}
				flags.keyAPressed=1;
			}
			if (vpad_data.tpdata.x > 430 && vpad_data.tpdata.x < 520 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1600) {
				flags.text[flags.textLength - 1] = 'B';
				++flags.textLength;
				int wait = WAIT_KEY;
				while (--wait) {}
				flags.keyBPressed=1;
			}
			if (vpad_data.tpdata.x > 550 && vpad_data.tpdata.x < 630 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1600) {
				flags.text[flags.textLength - 1] = 'C';
				++flags.textLength;
				int wait = WAIT_KEY;
				while (--wait) {}
				flags.keyCPressed=1;
			}
			if (vpad_data.tpdata.x > 660 && vpad_data.tpdata.x < 750 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1600) {
				flags.text[flags.textLength - 1] = 'D';
				++flags.textLength;
				int wait = WAIT_KEY;
				while (--wait) {}
				flags.keyDPressed=1;
			}
			if (vpad_data.tpdata.x > 780 && vpad_data.tpdata.x < 860 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1600) {
				flags.text[flags.textLength - 1] = 'E';
				++flags.textLength;
				int wait = WAIT_KEY;
				while (--wait) {}
				flags.keyEPressed=1;
			}
			if (vpad_data.tpdata.x > 890 && vpad_data.tpdata.x < 980 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1600) {
				flags.text[flags.textLength - 1] = 'F';
				++flags.textLength;
				int wait = WAIT_KEY;
				while (--wait) {}
				flags.keyFPressed=1;
			}
			if (vpad_data.tpdata.x > 1000 && vpad_data.tpdata.x < 1080 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1600) {
				flags.text[flags.textLength - 1] = 'G';
				++flags.textLength;
				int wait = WAIT_KEY;
				while (--wait) {}
				flags.keyGPressed=1;
			}
			if (vpad_data.tpdata.x > 1120 && vpad_data.tpdata.x < 1200 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1600) {
				flags.text[flags.textLength - 1] = 'H';
				++flags.textLength;
				int wait = WAIT_KEY;
				while (--wait) {}
				flags.keyHPressed=1;
			}
			if (vpad_data.tpdata.x > 1250 && vpad_data.tpdata.x < 1280 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1600) {
				flags.text[flags.textLength - 1] = 'I';
				++flags.textLength;
				int wait = WAIT_KEY;
				while (--wait) {}
				flags.keyIPressed=1;
			}
			if (vpad_data.tpdata.x > 1330 && vpad_data.tpdata.x < 1415 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1600) {
				flags.text[flags.textLength - 1] = 'J';
				++flags.textLength;
				int wait = WAIT_KEY;
				while (--wait) {}
				flags.keyJPressed=1;
			}
			if (vpad_data.tpdata.x > 1450 && vpad_data.tpdata.x < 1545 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1600) {
				flags.text[flags.textLength - 1] = 'K';
				++flags.textLength;
				int wait = WAIT_KEY;
				while (--wait) {}
				flags.keyKPressed=1;
			}
			if (vpad_data.tpdata.x > 1570 && vpad_data.tpdata.x < 1650 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1600) {
				flags.text[flags.textLength - 1] = 'L';
				++flags.textLength;
				int wait = WAIT_KEY;
				while (--wait) {}
				flags.keyLPressed=1;
			}
			if (vpad_data.tpdata.x > 1675 && vpad_data.tpdata.x < 1780 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1600) {
				flags.text[flags.textLength - 1] = 'M';
				++flags.textLength;
				int wait = WAIT_KEY;
				while (--wait) {}
				flags.keyMPressed=1;
			}
			if (vpad_data.tpdata.x > 1800 && vpad_data.tpdata.x < 1900 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1600) {
				flags.text[flags.textLength - 1] = 'N';
				++flags.textLength;
				int wait = WAIT_KEY;
				while (--wait) {}
				flags.keyNPressed=1;
			}
			if (vpad_data.tpdata.x > 1915 && vpad_data.tpdata.x < 2005 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1600) {
				flags.text[flags.textLength - 1] = 'O';
				++flags.textLength;
				int wait = WAIT_KEY;
				while (--wait) {}
				flags.keyOPressed=1;
			}
			if (vpad_data.tpdata.x > 2030 && vpad_data.tpdata.x < 2120 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1600) {
				flags.text[flags.textLength - 1] = 'P';
				++flags.textLength;
				int wait = WAIT_KEY;
				while (--wait) {}
				flags.keyPPressed=1;
			}
			if (vpad_data.tpdata.x > 2145 && vpad_data.tpdata.x < 2230 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1600) {
				flags.text[flags.textLength - 1] = 'Q';
				++flags.textLength;
				int wait = WAIT_KEY;
				while (--wait) {}
				flags.keyQPressed=1;
			}
			if (vpad_data.tpdata.x > 2260 && vpad_data.tpdata.x < 2350 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1600) {
				flags.text[flags.textLength - 1] = 'R';
				++flags.textLength;
				int wait = WAIT_KEY;
				while (--wait) {}
				flags.keyRPressed=1;
			}
			if (vpad_data.tpdata.x > 2380 && vpad_data.tpdata.x < 2460 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1600) {
				flags.text[flags.textLength - 1] = 'S';
				++flags.textLength;
				int wait = WAIT_KEY;
				while (--wait) {}
				flags.keySPressed=1;
			}
			if (vpad_data.tpdata.x > 2490 && vpad_data.tpdata.x < 2580 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1600) {
				flags.text[flags.textLength - 1] = 'T';
				++flags.textLength;
				int wait = WAIT_KEY;
				while (--wait) {}
				flags.keyTPressed=1;
			}
			if (vpad_data.tpdata.x > 2600 && vpad_data.tpdata.x < 2700 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1600) {
				flags.text[flags.textLength - 1] = 'U';
				++flags.textLength;
				int wait = WAIT_KEY;
				while (--wait) {}
				flags.keyUPressed=1;
			}
			if (vpad_data.tpdata.x > 2715 && vpad_data.tpdata.x < 2815 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1600) {
				flags.text[flags.textLength - 1] = 'V';
				++flags.textLength;
				int wait = WAIT_KEY;
				while (--wait) {}
				flags.keyVPressed=1;
			}
			if (vpad_data.tpdata.x > 3050 && vpad_data.tpdata.x < 3140 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1600) {
				flags.text[flags.textLength - 1] = 'Y';
				++flags.textLength;
				int wait = WAIT_KEY;
				while (--wait) {}
				flags.keyYPressed=1;
			}
			if (vpad_data.tpdata.x > 3160 && vpad_data.tpdata.x < 3250 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1600) {
				flags.text[flags.textLength - 1] = 'Z';
				++flags.textLength;
				int wait = WAIT_KEY;
				while (--wait) {}
				flags.keyZPressed=1;
			}
			if (vpad_data.tpdata.x > 3510 && vpad_data.tpdata.x < 3650 && vpad_data.tpdata.y < 2090 && vpad_data.tpdata.y > 1950) {
				if (flags.textLength > 1) {
					--flags.textLength;
					flags.text[flags.textLength - 1] = ' ';
					int wait = WAIT_KEY;
					while (--wait) {}
					flags.keyBackspacePressed=1;
				}
			}
			if (vpad_data.tpdata.x > 3440 && vpad_data.tpdata.x < 3730 && vpad_data.tpdata.y < 1820 && vpad_data.tpdata.y > 1660) {
				flags.text[flags.textLength - 1] = ' ';
				++flags.textLength;
				int wait = WAIT_KEY;
				while (--wait) {}
				flags.keySpacePressed=1;
			}
		}
		if ((vpad_data.btn_hold & BUTTON_B) || flags.bTouched)
			flags.b=1;

		if ((vpad_data.btn_hold & BUTTON_PLUS) || flags.plusTouched)
			flags.plus=1;

		if((vpad_data.btn_hold & BUTTON_HOME) || flags.HomeTouched)
			break;

		render(&flags);
	}
	
	
	//WARNING: DO NOT CHANGE THIS. YOU MUST CLEAR THE FRAMEBUFFERS AND IMMEDIATELY CALL EXIT FROM THIS FUNCTION. RETURNING TO LOADER CAUSES FREEZE.
	int ii=0;
	for(ii;ii<2;ii++)
	{
		fillScreen(0,0,0,0);
		flipBuffers();
	}
	_Exit();
}

void render(struct renderFlags *flags)
{
	int i=0;
	for(i;i<2;i++)
	{
		fillScreen(64, 64, 64, 0); //The part until fillTV() will only be shown on the Gamepad

		if (flags->menu) {
			drawString(0, 4, "Current theme: ");
			drawString(15, 4, flags->theme);
			drawString(0, 8, "NOTE: not usable yet.");

			if (!flags->change_theme) {
				drawString(27, 0, "SETTINGS");
				if (!flags->QWERTY)
					drawString(0, 2, "QWERTY");
				else
					drawString(0, 2, "QWERTZ");
				drawString(48, 2, "Change theme");
			} else {
				drawString(25, 0, "CHANGE THEME");
				drawString(0, 2, "Classic");
			}
		}
		if(flags->b) {
			flags->menu = 0;
			flags->change_theme = 0;
		}
		if(flags->plus) {
				flags->menu = 1;
		}

		if (!flags->menu) {
			drawString(27, 0, "Keyboard");
			int i, x = 50, y, plusy = 0, minusy = 0;
			char c = 'A';
			for (i = 0; i < 26; ++i) {
				drawChar(c, x, 230, 1, 255, 255, 255, 0);
				c++;
				x += 25;
			}
			c = 'A';
			x = 50;
			for (i = 0; i < 26; ++i) {
				if (c == 'A' && flags->keyAPressed)
					drawChar(c, x, 255, 2, 255, 255, 0, 0);
				else if (c == 'B' && flags->keyBPressed)
					drawChar(c, x, 255, 2, 255, 255, 0, 0);
				else if (c == 'C' && flags->keyCPressed)
					drawChar(c, x, 255, 2, 255, 255, 0, 0);
				else if (c == 'D' && flags->keyDPressed)
					drawChar(c, x, 255, 2, 255, 255, 0, 0);
				else if (c == 'E' && flags->keyEPressed)
					drawChar(c, x, 255, 2, 255, 255, 0, 0);
				else if (c == 'F' && flags->keyFPressed)
					drawChar(c, x, 255, 2, 255, 255, 0, 0);
				else if (c == 'G' && flags->keyGPressed)
					drawChar(c, x, 255, 2, 255, 255, 0, 0);
				else if (c == 'H' && flags->keyHPressed)
					drawChar(c, x, 255, 2, 255, 255, 0, 0);
				else if (c == 'I' && flags->keyIPressed)
					drawChar(c, x, 255, 2, 255, 255, 0, 0);
				else if (c == 'J' && flags->keyJPressed)
					drawChar(c, x, 255, 2, 255, 255, 0, 0);
				else if (c == 'K' && flags->keyKPressed)
					drawChar(c, x, 255, 2, 255, 255, 0, 0);
				else if (c == 'L' && flags->keyLPressed)
					drawChar(c, x, 255, 2, 255, 255, 0, 0);
				else if (c == 'M' && flags->keyMPressed)
					drawChar(c, x, 255, 2, 255, 255, 0, 0);
				else if (c == 'N' && flags->keyNPressed)
					drawChar(c, x, 255, 2, 255, 255, 0, 0);
				else if (c == 'O' && flags->keyOPressed)
					drawChar(c, x, 255, 2, 255, 255, 0, 0);
				else if (c == 'P' && flags->keyPPressed)
					drawChar(c, x, 255, 2, 255, 255, 0, 0);
				else if (c == 'Q' && flags->keyQPressed)
					drawChar(c, x, 255, 2, 255, 255, 0, 0);
				else if (c == 'R' && flags->keyRPressed)
					drawChar(c, x, 255, 2, 255, 255, 0, 0);
				else if (c == 'S' && flags->keySPressed)
					drawChar(c, x, 255, 2, 255, 255, 0, 0);
				else if (c == 'T' && flags->keyTPressed)
					drawChar(c, x, 255, 2, 255, 255, 0, 0);
				else if (c == 'U' && flags->keyUPressed)
					drawChar(c, x, 255, 2, 255, 255, 0, 0);
				else if (c == 'V' && flags->keyVPressed)
					drawChar(c, x, 255, 2, 255, 255, 0, 0);
				else if (c == 'W' && flags->keyWPressed)
					drawChar(c, x, 255, 2, 255, 255, 0, 0);
				else if (c == 'X' && flags->keyXPressed)
					drawChar(c, x, 255, 2, 255, 255, 0, 0);
				else if (c == 'Y' && flags->keyYPressed)
					drawChar(c, x, 255, 2, 255, 255, 0, 0);
				else if (c == 'Z' && flags->keyZPressed)
					drawChar(c, x, 255, 2, 255, 255, 0, 0);
				else
					drawChar(c, x, 255, 2, 255, 255, 255, 0);
				c++;
				x += 25;
			}

			x = 750;
			y = 240;
			for (i = 0; i < 10; ++i)
			{
				if (flags->keyBackspacePressed)
					drawLine(x, y - minusy, x, y + plusy, 255, 255, 0, 0);
				else
					drawLine(x, y - minusy, x, y + plusy, 255, 255, 255, 0);
				++x;
				++plusy;
				++minusy;
			}
			if (flags->keyBackspacePressed)
				drawFillRect(x, y + 3, x + 20, y - 3, 255, 255, 0, 0);
			else
				drawFillRect(x, y + 3, x + 20, y - 3, 255, 255, 255, 0);

			if (flags->keySpacePressed) {
				drawRect(735, 265, 800, 285, 255, 255, 0, 0);
				drawRect(736, 264, 799, 286, 255, 255, 0, 0);
				drawRect(737, 263, 798, 287, 255, 255, 0, 0);
			} else {
				drawRect(735, 265, 800, 285, 255, 255, 255, 0);
				drawRect(736, 264, 799, 286, 255, 255, 255, 0);
				drawRect(737, 263, 798, 287, 255, 255, 255, 0);
			}
		}

		if (!flags->change_theme && !flags->menu) {
			drawString(0, 3, "Your text:");
			drawString(0, 5, flags->text);

			drawString(25, 16, flags->touching);
		}

		if (!flags->menu) {
			if (flags->plus) {
				drawFillCircle(820, 450, 16, 255, 255, 0, 0);
				drawFillCircle(820, 450, 13, 64, 64, 64, 0);
				drawFillRect(818, 440, 822, 460, 255, 255, 0, 0);
				drawFillRect(810, 452, 830, 448, 255, 255, 0, 0);
			} else {
				drawFillCircle(820, 450, 16, 255, 255, 255, 0);
				drawFillCircle(820, 450, 13, 64, 64, 64, 0);
				drawFillRect(818, 440, 822, 460, 255, 255, 255, 0);
				drawFillRect(810, 452, 830, 448, 255, 255, 255, 0);
			}
		} else {
			if (flags->b) {
				drawFillCircle(820, 450, 16, 255, 255, 0, 0);
				drawFillCircle(820, 450, 13, 64, 64, 64, 0);
				drawChar('B', 816, 441, 1, 255, 255, 0, 0);
			} else {
				drawFillCircle(820, 450, 16, 255, 255, 255, 0);
				drawFillCircle(820, 450, 13, 64, 64, 64, 0);
				drawChar('B', 816, 441, 1, 255, 255, 255, 0);
			}
		}
		drawFillCircle(30, 452, 22, 255, 255, 255, 0);
		drawFillCircle(30, 452, 19, 64, 64, 64, 0);

		int m, x = 15, y = 450;
		for (m = 0; m < 16; ++m) {
			drawLine(x + m, y, x + 30 - m, y + m, 255, 255, 255, 0);
			--y;
		}
		drawFillRect(20, 450, 40, 465, 255, 255, 255, 0);
		drawFillRect(26, 453, 34, 458, 64, 64, 64, 0);

		fillTV(64, 64, 64, 0);

		drawStringTV(45, 0, "Keyboard");
		drawStringTV(0, 3, "Your text:");
		drawStringTV(0, 5, flags->text);

		flipBuffers();
	}

	flags->touch=0;
	flags->keyAPressed=0;
	flags->keyBPressed=0;
	flags->keyCPressed=0;
	flags->keyDPressed=0;
	flags->keyEPressed=0;
	flags->keyFPressed=0;
	flags->keyGPressed=0;
	flags->keyHPressed=0;
	flags->keyIPressed=0;
	flags->keyJPressed=0;
	flags->keyKPressed=0;
	flags->keyLPressed=0;
	flags->keyMPressed=0;
	flags->keyNPressed=0;
	flags->keyOPressed=0;
	flags->keyPPressed=0;
	flags->keyQPressed=0;
	flags->keyRPressed=0;
	flags->keySPressed=0;
	flags->keyTPressed=0;
	flags->keyUPressed=0;
	flags->keyVPressed=0;
	flags->keyWPressed=0;
	flags->keyXPressed=0;
	flags->keyYPressed=0;
	flags->keyZPressed=0;
	flags->keyBackspacePressed=0;
	flags->keySpacePressed=0;
	flags->b=0;
	flags->plus=0;
	flags->bTouched=0;
	flags->plusTouched=0;
	flags->HomeTouched=0;
}

void drawChar(char character, int xpos, int ypos, int scale, char r, char g, char b, char a) /*   23/26 = ~88%   */
{
	int x = xpos, y = ypos, i;
	float plusx = 3.5;

	if (scale != 1 && scale != 2)
		return;

	if (character == 'A') {
		drawFillRect(x, y + 1 * scale, x + 1 * scale, y + 18 * scale, r, g, b, a);
		drawFillRect(x + 1 * scale, y, x + 2 * scale, y + 18 * scale, r, g, b, a);

		drawFillRect(x + 2 * scale, y, x + 7 * scale, y + 2 * scale, r, g, b, a);
		drawFillRect(x + 2 * scale, y + 9 * scale, x + 7 * scale, y + 11 * scale, r, g, b, a);

		drawFillRect(x + 7 * scale, y, x + 8 * scale, y + 18 * scale, r, g, b, a);
		drawFillRect(x + 8 * scale, y + 1 * scale, x + 9 * scale, y + 18 * scale, r, g, b, a);
	}

	if (character == 'B') {
		drawFillRect(x, y, x + 8  * scale, y + 1 * scale, r, g, b, a);

		drawFillRect(x, y + 1 * scale, x + 2 * scale, y + 17 * scale, r, g, b, a);
		drawFillRect(x + 7 * scale, y + 1 * scale, x + 9 * scale, y + 7.5 * scale, r, g, b, a);
		drawFillRect(x + 2 * scale, y + 8 * scale, x + 8 * scale, y + 9 * scale, r, g, b, a);
		if (scale == 1)
			drawFillRect(x + 7 * scale, y + 10 * scale, x + 9 * scale, y + 17 * scale, r, g, b, a);
		else
			drawFillRect(x + 7 * scale, y + 9 * scale + 1, x + 9 * scale, y + 17 * scale, r, g, b, a);

		drawFillRect(x, y + 17 * scale, x + 8 * scale, y + 18 * scale, r, g, b, a);
	}

	if (character == 'C') {
		x += 1;
		drawFillRect(x + 1 * scale, y, x + 7 * scale, y + 2 * scale, r, g, b, a);

		drawFillRect(x, y + 1 * scale, x + 2 * scale, y + 17 * scale, r, g, b, a);

		drawFillRect(x + 7 * scale, y + 1 * scale, x + 8 * scale, y + 3 * scale, r, g, b, a);
		drawFillRect(x + 7 * scale, y + 15 * scale, x + 8 * scale, y + 17 * scale, r, g, b, a);

		drawFillRect(x + 1 * scale, y + 16 * scale, x + 7 * scale, y + 18 * scale, r, g, b, a);
	}

	if (character == 'D') {
		drawFillRect(x, y, x + 7 * scale, y + 1 * scale, r, g, b, a);
		drawFillRect(x, y + 1 * scale, x + 2 * scale, y + 17 * scale, r, g, b, a);

		if (scale == 1) {
			drawFillRect(x + 6.5 * scale, y + 1.5 * scale, x + 8 * scale, y + 17 * scale, r, g, b, a);
			drawFillRect(x + 8.5 * scale, y + 3 * scale, x + 8.5 * scale, y + 15 * scale, r, g, b, a);
		} else {
			drawFillRect(x + 6.5 * scale, y + 1 * scale, x + 8 * scale, y + 17 * scale, r, g, b, a);
			drawFillRect(x + 8.5 * scale, y + 2.5 * scale, x + 8.5 * scale, y + 15.5 * scale, r, g, b, a);
		}

		drawFillRect(x, y + 17 * scale, x + 7 * scale, y + 18 * scale, r, g, b, a);
	}

	if (character == 'E') {
		drawFillRect(x, y, x + 8 * scale, y + 1.5 * scale, r, g, b, a);
		drawFillRect(x, y + 1 * scale, x + 2 * scale, y + 16 * scale, r, g, b, a);

		drawFillRect(x + 2 * scale, y + 8.5 * scale, x + 7 * scale, y + 9.5 * scale, r, g, b, a);
		if (scale == 1)
			drawFillRect(x, y + 17 * scale, x + 8 * scale, y + 18 * scale, r, g, b, a);
		else
			drawFillRect(x, y + 16.5 * scale, x + 8 * scale, y + 18 * scale, r, g, b, a);
	}

	if (character == 'F') {
		x += 1;
		drawFillRect(x, y, x + 8 * scale, y + 1.5 * scale, r, g, b, a);

		drawFillRect(x, y + 1 * scale, x + 2 * scale, y + 18 * scale, r, g, b, a);
		drawFillRect(x + 2 * scale, y + 8.5 * scale, x + 7 * scale, y + 9.5 * scale, r, g, b, a);
	}

	if (character == 'G') {
		drawFillRect(x + 1 * scale, y, x + 7 * scale, y + 1 * scale, r, g, b, a);
		drawFillRect(x, y + 1.5 * scale, x + 2 * scale, y + 16.5 * scale, r, g, b, a);
		drawFillRect(x + 6.5 * scale, y + 1.5 * scale, x + 8 * scale, y + 3 * scale, r, g, b, a);

		drawFillRect(x + 6.5 * scale, y + 9 * scale, x + 8 * scale, y + 17.5 * scale, r, g, b, a);
		drawFillRect(x + 5.5 * scale, y + 9 * scale, x + 8 * scale, y + 10 * scale, r, g, b, a);
		drawFillRect(x + 7.5 * scale, y + 17 * scale, x + 8 * scale, y + 18 * scale, r, g, b, a);
		drawFillRect(x + 1 * scale, y + 17 * scale, x + 6.5 * scale, y + 18 * scale, r, g, b, a);
	}

	if (character == 'H') {
		drawFillRect(x, y, x + 2 * scale, y + 18 * scale, r, g, b, a);

		drawFillRect(x + 2 * scale, y + 8 * scale, x + 6 * scale, y + 10 * scale, r, g, b, a);

		drawFillRect(x + 6 * scale, y, x + 8 * scale, y + 18 * scale, r, g, b, a);
	}

	if (character == 'I') {
		x += 6;
		drawFillRect(x, y, x + 2 * scale, y + 18 * scale, r, g, b, a);
	}

	if (character == 'J') {
		x -= 3;
		drawFillRect(x + 7 * scale, y, x + 9 * scale, y + 16 * scale, r, g, b, a);
		drawFillRect(x + 1 * scale, y + 16 * scale, x + 8 * scale, y + 18 * scale, r, g, b, a);
		drawFillRect(x, y + 14 * scale, x + 2 * scale, y + 16 * scale, r, g, b, a);
	}

	if (character == 'K') {
		x -= 1;
		drawFillRect(x, y, x + 2 * scale, y + 18 * scale, r, g, b, a);
		drawFillRect(x + 7 * scale, y, x + 9 * scale, y + 7.5 * scale, r, g, b, a);
		drawFillRect(x + 2 * scale, y + 8 * scale, x + 8 * scale, y + 9 * scale, r, g, b, a);
		if (scale == 1)
			drawFillRect(x + 7 * scale, y + 10 * scale, x + 9 * scale, y + 17 * scale, r, g, b, a);
		else
			drawFillRect(x + 7 * scale, y + 9 * scale + 1, x + 9 * scale, y + 17 * scale, r, g, b, a);

		drawFillRect(x + 7 * scale, y + 17 * scale, x + 10.5 * scale, y + 18 * scale, r, g, b, a);
	}

	if (character == 'L') {
		drawFillRect(x, y, x + 2 * scale, y + 18 * scale, r, g, b, a);
		drawFillRect(x + 1 * scale, y + 16 * scale, x + 8 * scale, y + 18 * scale, r, g, b, a);
	}

	if (character == 'M') {
		x -= 2;
		drawFillRect(x, y, x + 1.5 * scale, y + 18 * scale, r, g, b, a);

		for (i = 0; i < 4; ++i) {
			drawFillRect(x + 1.5 * scale + i * scale, y + 1.5 * scale + 1.5 * i * scale, x + 2.5 * scale + i * scale, y + 3 * scale + 1.5 * i * scale, r, g, b, a);
		}
		for (i = 3; i >= 0; --i) {
			drawFillRect(x + 1.5 * scale + plusx * scale, y + 1.5 * scale + 1.5 * i * scale, x + 2.5 * scale + plusx * scale, y + 3 * scale + 1.5 * i * scale, r, g, b, a);
			++plusx;
		}

		drawFillRect(x + 9 * scale, y, x + 10.5 * scale, y + 18 * scale, r, g, b, a);
	}

	if (character == 'N') {
		x -= 1;
		drawFillRect(x, y, x + 1.5 * scale, y + 18 * scale, r, g, b, a);

		for (i = 0; i < 5; ++i) {
			drawFillRect(x + 2 * scale + 1.5 * i * scale, y + 0.5 * scale + 3.5 * i * scale, x + 3.5 * scale + 1.5 * i * scale, y + 3.5 * scale + 3.5 * i * scale, r, g, b, a);
		}
		drawFillRect(x, y, x + 3.5 * scale, y, r, g, b, a);
		drawFillRect(x + 8 * scale, y + 18 * scale, x + 11 * scale, y + 18 * scale, r, g, b, a);

		if (scale == 1)
			drawFillRect(x + 10 * scale, y, x + 11 * scale, y + 18 * scale, r, g, b, a);
		else
			drawFillRect(x + 9.5 * scale, y, x + 11 * scale, y + 18 * scale, r, g, b, a);
	}

	if (character == 'O') {
		x += 1;
		drawFillRect(x + 1 * scale, y, x + 8 * scale, y + 2 * scale, r, g, b, a);

		drawFillRect(x + 7 * scale, y + 2 * scale, x + 9 * scale, y + 16 * scale, r, g, b, a);
		drawFillRect(x, y + 2 * scale, x + 2 * scale, y + 16 * scale, r, g, b, a);

		drawFillRect(x + 1 * scale, y + 16 * scale, x + 8 * scale, y + 18 * scale, r, g, b, a);
	}

	if (character == 'P') {
		drawFillRect(x, y, x + 8  * scale, y + 1 * scale, r, g, b, a);

		drawFillRect(x, y + 1 * scale, x + 2 * scale, y + 18 * scale, r, g, b, a);
		drawFillRect(x + 7 * scale, y + 1 * scale, x + 9 * scale, y + 8 * scale, r, g, b, a);
		drawFillRect(x + 2 * scale, y + 8 * scale, x + 8 * scale, y + 9 * scale, r, g, b, a);
	}

	if (character == 'Q') {
		drawFillRect(x + 1 * scale, y, x + 8 * scale, y + 2 * scale, r, g, b, a);

		drawFillRect(x + 7 * scale, y + 2 * scale, x + 9 * scale, y + 16 * scale, r, g, b, a);
		drawFillRect(x, y + 2 * scale, x + 2 * scale, y + 16 * scale, r, g, b, a);

		drawFillRect(x + 1 * scale, y + 16 * scale, x + 8 * scale, y + 18 * scale, r, g, b, a);

		drawFillRect(x + 4 * scale, y + 15 * scale, x + 5 * scale, y + 16 * scale, r, g, b, a);
		drawFillRect(x + 6 * scale, y + 18 * scale, x + 7 * scale, y + 19 * scale, r, g, b, a);
		drawFillRect(x + 7 * scale, y + 19 * scale, x + 8 * scale, y + 20 * scale, r, g, b, a);
	}

	if (character == 'R') {
		drawFillRect(x, y, x + 8  * scale, y + 1 * scale, r, g, b, a);

		drawFillRect(x, y + 1 * scale, x + 2 * scale, y + 18 * scale, r, g, b, a);
		drawFillRect(x + 7 * scale, y + 1 * scale, x + 9 * scale, y + 7.5 * scale, r, g, b, a);
		drawFillRect(x + 2 * scale, y + 8 * scale, x + 8 * scale, y + 9 * scale, r, g, b, a);
		if (scale == 1)
			drawFillRect(x + 7 * scale, y + 10 * scale, x + 9 * scale, y + 17 * scale, r, g, b, a);
		else
			drawFillRect(x + 7 * scale, y + 9 * scale + 1, x + 9 * scale, y + 17 * scale, r, g, b, a);

		drawFillRect(x + 7 * scale, y + 17 * scale, x + 10.5 * scale, y + 18 * scale, r, g, b, a);
	}

	if (character == 'S') {
		x += 2;
		if (scale == 1)
			drawFillRect(x + 7 * scale, y + 2 * scale, x + 8 * scale, y + 3 * scale, r, g, b, a);
		else
			drawFillRect(x + 6.5 * scale, y + 1.5 * scale, x + 8 * scale, y + 3 * scale, r, g, b, a);

		drawFillRect(x + 1 * scale, y, x + 7 * scale, y + 1 * scale, r, g, b, a);
		drawFillRect(x, y + 1.5 * scale, x + 1.5 * scale, y + 8 * scale, r, g, b, a);

		drawFillRect(x + 1 * scale, y + 8.5 * scale, x + 7 * scale, y + 9.5 * scale, r, g, b, a);

		drawFillRect(x + 6.5 * scale, y + 10 * scale, x + 8 * scale, y + 16.5 * scale, r, g, b, a);
		drawFillRect(x + 1 * scale, y + 17 * scale, x + 7 * scale, y + 18 * scale, r, g, b, a);

		drawFillRect(x, y + 15 * scale, x + 1.5 * scale, y + 16.5 * scale, r, g, b, a);
	}

	if (character == 'T') {
		drawFillRect(x, y, x + 10 * scale, y + 1.5 * scale, r, g, b, a);
		drawFillRect(x + 4 * scale, y, x + 6 * scale, y + 18 * scale, r, g, b, a);
	}

	if (character == 'U') {
		drawFillRect(x + 8 * scale, y, x + 10 * scale, y + 16 * scale, r, g, b, a);
		drawFillRect(x + 1 * scale, y + 16 * scale, x + 9 * scale, y + 18 * scale, r, g, b, a);
		drawFillRect(x, y, x + 2 * scale, y + 16 * scale, r, g, b, a);
	}

	if (character == 'V') {
		x += 1;
		drawFillRect(x, y, x + 2 * scale, y + 4 * scale, r, g, b, a);
		drawFillRect(x + 1 * scale, y + 4 * scale, x + 3 * scale, y + 8 * scale, r, g, b, a);
		drawFillRect(x + 2 * scale, y + 8 * scale, x + 4 * scale, y + 12 * scale, r, g, b, a);
		drawFillRect(x + 3 * scale, y + 12 * scale, x + 5 * scale, y + 16 * scale, r, g, b, a);

		drawFillRect(x + 4 * scale, y + 16 * scale, x + 6 * scale, y + 18 * scale, r, g, b, a);

		drawFillRect(x + 5 * scale, y + 12 * scale, x + 7 * scale, y + 16 * scale, r, g, b, a);
		drawFillRect(x + 6 * scale, y + 8 * scale, x + 8 * scale, y + 12 * scale, r, g, b, a);
		drawFillRect(x + 7 * scale, y + 4 * scale, x + 9 * scale, y + 8 * scale, r, g, b, a);
		drawFillRect(x + 8 * scale, y, x + 10 * scale, y + 4 * scale, r, g, b, a);
	}

	//W

	//X

	if (character == 'Y') {
		drawFillRect(x, y, x + 2 * scale, y + 4 * scale, r, g, b, a);
		drawFillRect(x + 1 * scale, y + 4 * scale, x + 3 * scale, y + 7 * scale, r, g, b, a);

		drawFillRect(x + 2 * scale, y + 7 * scale, x + 6 * scale, y + 9 * scale, r, g, b, a);

		drawFillRect(x + 5 * scale, y + 4 * scale, x + 7 * scale, y + 7 * scale, r, g, b, a);
		drawFillRect(x + 6 * scale, y, x + 8 * scale, y + 4 * scale, r, g, b, a);

		drawFillRect(x + 3 * scale, y + 9 * scale, x + 5 * scale, y + 18 * scale, r, g, b, a);
	}

	if (character == 'Z') {
		drawFillRect(x, y, x + 8 * scale, y + 1.5 * scale, r, g, b, a);
		drawFillRect(x + 6 * scale, y + 1 * scale, x + 8 * scale, y + 4 * scale, r, g, b, a);
		drawFillRect(x + 5 * scale, y + 4.5 * scale, x + 7 * scale, y + 7.5 * scale, r, g, b, a);

		drawFillRect(x + 3 * scale, y + 8 * scale, x + 5 * scale, y + 10 * scale, r, g, b, a);

		drawFillRect(x + 1 * scale, y + 10.5 * scale, x + 3 * scale, y + 13.5 * scale, r, g, b, a);
		drawFillRect(x, y + 14 * scale, x + 2 * scale, y + 17 * scale, r, g, b, a);
		drawFillRect(x, y + 16.5 * scale, x + 8 * scale, y + 18 * scale, r, g, b, a);
	}
}

void fillTV(char r, char g, char b, char a)
{
	unsigned int coreinit_handle;
	OSDynLoad_Acquire("coreinit.rpl", &coreinit_handle);
	unsigned int(*OSScreenClearBufferEx)(unsigned int bufferNum, unsigned int temp);
	OSDynLoad_FindExport(coreinit_handle, 0, "OSScreenClearBufferEx", &OSScreenClearBufferEx);
	uint32_t num = (r << 24) | (g << 16) | (b << 8) | a;
	OSScreenClearBufferEx(0, num);
}

void drawStringTV(int x, int line, char * string)
{
	unsigned int coreinit_handle;
	OSDynLoad_Acquire("coreinit.rpl", &coreinit_handle);
	unsigned int(*OSScreenPutFontEx)(unsigned int bufferNum, unsigned int posX, unsigned int line, void * buffer);
	OSDynLoad_FindExport(coreinit_handle, 0, "OSScreenPutFontEx", &OSScreenPutFontEx);
	OSScreenPutFontEx(0, x, line, string);
}