#include "program.h"

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
	// flags.start=1;
	// flags.pow=1;
	flags.touch=0;
	flags.menu=0;
	flags.QWERTY=0;
	flags.change_theme=0;
	flags.textLength=1;
	// flags.keyAPressed=0;
	// flags.keyBPressed=0;
	// flags.keyCPressed=0;
	// flags.keyDPressed=0;
	// flags.keyEPressed=0;
	// flags.keyFPressed=0;
	// flags.keyGPressed=0;
	// flags.keyHPressed=0;
	// flags.keyIPressed=0;
	// flags.keyJPressed=0;
	// flags.keyKPressed=0;
	// flags.keyLPressed=0;
	// flags.keyMPressed=0;
	// flags.keyNPressed=0;
	// flags.keyOPressed=0;
	// flags.keyPPressed=0;
	// flags.keyQPressed=0;
	// flags.keyRPressed=0;
	// flags.keySPressed=0;
	// flags.keyTPressed=0;
	// flags.keyUPressed=0;
	// flags.keyVPressed=0;
	// flags.keyWPressed=0;
	// flags.keyXPressed=0;
	// flags.keyYPressed=0;
	// flags.keyZPressed=0;
	// flags.y=0;
	// flags.x=0;
	// flags.a=0;
	flags.b=0;
	// flags.l=0;
	// flags.r=0;
	// flags.zl=0;
	// flags.zr=0;
	// flags.du=0;
	// flags.dd=0;
	// flags.dl=0;
	// flags.dr=0;
	flags.plus=0;
	// flags.minus=0;
	
	VPADData vpad_data;
	
	// __os_snprintf(flags.aPressed, 32, "A button pressed");
	// __os_snprintf(flags.bPressed, 32, "B button pressed");
	// __os_snprintf(flags.xPressed, 32, "X button pressed");
	// __os_snprintf(flags.yPressed, 32, "Y button pressed");
	// __os_snprintf(flags.lPressed, 32, "L button pressed");
	// __os_snprintf(flags.rPressed, 32, "R button pressed");
	// __os_snprintf(flags.zlPressed, 32, "ZL button pressed");
	// __os_snprintf(flags.zrPressed, 32, "ZR button pressed");
	// __os_snprintf(flags.dUp, 32, "D-PAD UP button pressed");
	// __os_snprintf(flags.dDown, 32, "D-PAD DOWN button pressed");
	// __os_snprintf(flags.dLeft, 32, "D-PAD LEFT button pressed");
	// __os_snprintf(flags.dRight, 32, "D-PAD RIGHT button pressed");
	// __os_snprintf(flags.plusPressed, 32, "+ (plus) button pressed");
	// __os_snprintf(flags.minusPressed, 32, "- (minus) button pressed");
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
		
		float lStickStorageX = vpad_data.lstick.x;
		float lStickStorageY = vpad_data.lstick.y;
		float rStickStorageX = vpad_data.rstick.x;
		float rStickStorageY = vpad_data.rstick.y;
		
		if (vpad_data.tpdata.touched == 1) {
			flags.touch=1;
			__os_snprintf(flags.touching, 32, "%i, %i", vpad_data.tpdata.x, vpad_data.tpdata.y);
			if (vpad_data.tpdata.x > 350 && vpad_data.tpdata.x < 650 && vpad_data.tpdata.y < 3250 && vpad_data.tpdata.y > 3100) {
				if (!flags.QWERTY)
					flags.QWERTY = 1;
				else
					flags.QWERTY = 0;
				int wait = 0x3FFFFFF;
				while (--wait) {}
			}
			if (vpad_data.tpdata.x > 3000 && vpad_data.tpdata.x < 3700 && vpad_data.tpdata.y < 3250 && vpad_data.tpdata.y > 3100) {
				flags.change_theme = 1;
				int wait = 0x3FFFFFF;
				while (--wait) {}
			}
			if (flags.change_theme && vpad_data.tpdata.x > 350 && vpad_data.tpdata.x < 700 && vpad_data.tpdata.y < 3250 && vpad_data.tpdata.y > 3100) {
				__os_snprintf(flags.theme, 32, "Classic");
				flags.change_theme = 0;
				flags.menu = 0;
				int wait = 0x3FFFFFF;
				while (--wait) {}
			}
			if (vpad_data.tpdata.x > 550 && vpad_data.tpdata.x < 650 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1600) {
				flags.text[flags.textLength - 1] = 'A';
				++flags.textLength;
				int wait = 0x1CFFFFF;
				while (--wait) {}
				// flags.keyAPressed=1;
			}
			if (vpad_data.tpdata.x > 700 && vpad_data.tpdata.x < 770 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1600) {
				flags.text[flags.textLength - 1] = 'B';
				++flags.textLength;
				int wait = 0x1CFFFFF;
				while (--wait) {}
				// flags.keyBPressed=1;
			}
			if (vpad_data.tpdata.x > 820 && vpad_data.tpdata.x < 900 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1600) {
				flags.text[flags.textLength - 1] = 'C';
				++flags.textLength;
				int wait = 0x1CFFFFF;
				while (--wait) {}
				// flags.keyCPressed=1;
			}
			if (vpad_data.tpdata.x > 950 && vpad_data.tpdata.x < 1040 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1600) {
				flags.text[flags.textLength - 1] = 'D';
				++flags.textLength;
				int wait = 0x1CFFFFF;
				while (--wait) {}
				// flags.keyDPressed=1;
			}
			if (vpad_data.tpdata.x > 1100 && vpad_data.tpdata.x < 1180 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1600) {
				flags.text[flags.textLength - 1] = 'E';
				++flags.textLength;
				int wait = 0x1CFFFFF;
				while (--wait) {}
				// flags.keyEPressed=1;
			}
			if (vpad_data.tpdata.x > 1230 && vpad_data.tpdata.x < 1330 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1600) {
				flags.text[flags.textLength - 1] = 'F';
				++flags.textLength;
				int wait = 0x1CFFFFF;
				while (--wait) {}
				// flags.keyFPressed=1;
			}
			if (vpad_data.tpdata.x > 2600 && vpad_data.tpdata.x < 2700 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1600) {
				flags.text[flags.textLength - 1] = 'P';
				++flags.textLength;
				int wait = 0x1CFFFFF;
				while (--wait) {}
				// flags.keyPPressed=1;
			}
			if (vpad_data.tpdata.x > 3530 && vpad_data.tpdata.x < 3650 && vpad_data.tpdata.y < 2150 && vpad_data.tpdata.y > 2000) {
				if (flags.textLength > 1) {
					--flags.textLength;
					flags.text[flags.textLength - 1] = ' ';
					int wait = 0x1CFFFFF;
					while (--wait) {}
				}
			}
		}

		// //button A
		// if (vpad_data.btn_hold & BUTTON_A)
		// 	flags.a=1;
	
		//button B
		if (vpad_data.btn_hold & BUTTON_B)
			flags.b=1;

		// //button X
		// if (vpad_data.btn_hold & BUTTON_X)
		// 	flags.x=1;

		// //button Y
		// if (vpad_data.btn_hold & BUTTON_Y)
		// 	flags.y=1;

		// if (vpad_data.btn_hold & BUTTON_L)
		// 	flags.l=1;
			
		// if (vpad_data.btn_hold & BUTTON_R)
		// 	flags.r=1;
			
		// if (vpad_data.btn_hold & BUTTON_ZL)
		// 	flags.zl=1;
			
		// if (vpad_data.btn_hold & BUTTON_ZR)
		// 	flags.zr=1;
		
		// if (vpad_data.btn_hold & BUTTON_UP)
		// 	flags.du=1;
			
		// if (vpad_data.btn_hold & BUTTON_DOWN)
		// 	flags.dd=1;
		
		// if (vpad_data.btn_hold & BUTTON_LEFT)
		// 	flags.dl=1;
			
		// if (vpad_data.btn_hold & BUTTON_RIGHT)
		// 	flags.dr=1;
			
		if (vpad_data.btn_hold & BUTTON_PLUS)
			flags.plus=1;
			
		// if (vpad_data.btn_hold & BUTTON_MINUS)
		// 	flags.minus=1;

		//end
		if(vpad_data.btn_hold & BUTTON_HOME)
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
		fillScreen(64, 64, 64, 0); //This part (until fillTV()) will only be shown on the Gamepad

		if (flags->menu) {
			drawString(0, 4, "Current theme: ");
			drawString(15, 4, flags->theme);
			drawString(0, 16, "Press B to go back, HOME to exit.");

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
		// if(flags->start)
		// 	drawString(0,0,flags->startUp);
		// if(flags->a)
		// 	drawString(0,10,flags->aPressed);
		if(flags->b) {
			flags->menu = 0;
			flags->change_theme = 0;
		}
		// if(flags->x)
		// 	drawString(0,10,flags->xPressed);
		// if(flags->y)
		// 	drawString(0,10,flags->yPressed);
		// if(flags->l)
		// 	drawString(0,10,flags->lPressed);
		// if(flags->r)
		// 	drawString(0,10,flags->rPressed);
		// if(flags->zl)
		// 	drawString(0,10,flags->zlPressed);
		// if(flags->zr)
		// 	drawString(0,10,flags->zrPressed);
		// if(flags->plus)
		// 	drawString(0,10,flags->plusPressed);
		if(flags->plus) {
				flags->menu = 1;
		}			
		// if(flags->pow)
		// 	drawString(0,13,flags->power);
		// if(flags->touch) {
		// 	drawString(25, 16, flags->touching);
		// }
		// if(flags->du)
		// 	drawString(0,10,flags->dUp);
		// if(flags->dd)
		// 	drawString(0,10,flags->dDown);
		// if(flags->dl)
		// 	drawString(0,10,flags->dLeft);
		// if(flags->dr)
		// 	drawString(0,10,flags->dRight);

		if (!flags->menu) {
			drawString(27, 0, "Keyboard");
			int i, x = 100, y, plusy = 0, minusy = 0;
			char c = 'A';
			for (i = 0; i < 26; ++i) {
				if (c != 'N')
					drawChar(c, x, 230, 1, 255, 255, 255, 0);
				c++;
				x += 30;
			}
			c = 'A';
			x = 100;
			for (i = 0; i < 26; ++i) {
				if (c != 'N') {
					// if (c == 'A' && flags->keyAPressed)
					// 	drawChar(c, x, 255, 2, 255, 255, 0, 0);
					// if (c == 'B' && flags->keyBPressed)
					// 	drawChar(c, x, 255, 2, 255, 255, 0, 0);
					// if (c == 'C' && flags->keyCPressed)
					// 	drawChar(c, x, 255, 2, 255, 255, 0, 0);
					// if (c == 'D' && flags->keyDPressed)
					// 	drawChar(c, x, 255, 2, 255, 255, 0, 0);
					// if (c == 'E' && flags->keyEPressed)
					// 	drawChar(c, x, 255, 2, 255, 255, 0, 0);
					// if (c == 'F' && flags->keyFPressed)
					// 	drawChar(c, x, 255, 2, 255, 255, 0, 0);
					// if (c == 'G' && flags->keyGPressed)
					// 	drawChar(c, x, 255, 2, 255, 255, 0, 0);
					// if (c == 'H' && flags->keyHPressed)
					// 	drawChar(c, x, 255, 2, 255, 255, 0, 0);
					// if (c == 'I' && flags->keyIPressed)
					// 	drawChar(c, x, 255, 2, 255, 255, 0, 0);
					// if (c == 'J' && flags->keyJPressed)
					// 	drawChar(c, x, 255, 2, 255, 255, 0, 0);
					// if (c == 'K' && flags->keyKPressed)
					// 	drawChar(c, x, 255, 2, 255, 255, 0, 0);
					// if (c == 'L' && flags->keyLPressed)
					// 	drawChar(c, x, 255, 2, 255, 255, 0, 0);
					// if (c == 'M' && flags->keyMPressed)
					// 	drawChar(c, x, 255, 2, 255, 255, 0, 0);
					// if (c == 'N' && flags->keyNPressed)
					// 	drawChar(c, x, 255, 2, 255, 255, 0, 0);
					// if (c == 'O' && flags->keyOPressed)
					// 	drawChar(c, x, 255, 2, 255, 255, 0, 0);
					// if (c == 'P' && flags->keyPPressed)
					// 	drawChar(c, x, 255, 2, 255, 255, 0, 0);
					// if (c == 'Q' && flags->keyQPressed)
					// 	drawChar(c, x, 255, 2, 255, 255, 0, 0);
					// if (c == 'R' && flags->keyRPressed)
					// 	drawChar(c, x, 255, 2, 255, 255, 0, 0);
					// if (c == 'S' && flags->keySPressed)
					// 	drawChar(c, x, 255, 2, 255, 255, 0, 0);
					// if (c == 'T' && flags->keyTPressed)
					// 	drawChar(c, x, 255, 2, 255, 255, 0, 0);
					// if (c == 'U' && flags->keyUPressed)
					// 	drawChar(c, x, 255, 2, 255, 255, 0, 0);
					// if (c == 'V' && flags->keyVPressed)
					// 	drawChar(c, x, 255, 2, 255, 255, 0, 0);
					// if (c == 'W' && flags->keyWPressed)
					// 	drawChar(c, x, 255, 2, 255, 255, 0, 0);
					// if (c == 'X' && flags->keyXPressed)
					// 	drawChar(c, x, 255, 2, 255, 255, 0, 0);
					// if (c == 'Y' && flags->keyYPressed)
					// 	drawChar(c, x, 255, 2, 255, 255, 0, 0);
					// if (c == 'Z' && flags->keyZPressed)
					// 	drawChar(c, x, 255, 2, 255, 255, 0, 0);
					// else
						drawChar(c, x, 255, 2, 255, 255, 255, 0);
				}
				c++;
				x += 30;
			}

			x = 750;
			y = 230;
			for (i = 0; i < 10; ++i)
			{
				drawLine(x, y - minusy, x, y + plusy, 255, 255, 255, 0);
				++x;
				++plusy;
				++minusy;
			}
			drawFillRect(x, y + 3, x + 20, y - 3, 255, 255, 255, 0);
		}

		if (!flags->change_theme && !flags->menu) {
			drawString(0, 3, "Your text:");
			if (flags->text[0] == ' ')
				drawString(0, 5, "<no input>");
			else
				drawString(0, 5, flags->text);

			drawString(25, 16, flags->touching);
		}

		fillTV(64, 64, 64, 0);

		drawStringTV(45, 0, "Keyboard");
		drawStringTV(0, 3, "Your text:");
		if (flags->text[0] == ' ')
			drawStringTV(0, 5, "<no input>");
		else
			drawStringTV(0, 5, flags->text);

		flipBuffers();
	}

	// flags->start=1;
	// flags->pow=1;
	flags->touch=0;
	// flags->keyAPressed=0;
	// flags->keyBPressed=0;
	// flags->keyCPressed=0;
	// flags->keyDPressed=0;
	// flags->keyEPressed=0;
	// flags->keyFPressed=0;
	// flags->keyGPressed=0;
	// flags->keyHPressed=0;
	// flags->keyIPressed=0;
	// flags->keyJPressed=0;
	// flags->keyKPressed=0;
	// flags->keyLPressed=0;
	// flags->keyMPressed=0;
	// flags->keyNPressed=0;
	// flags->keyOPressed=0;
	// flags->keyPPressed=0;
	// flags->keyQPressed=0;
	// flags->keyRPressed=0;
	// flags->keySPressed=0;
	// flags->keyTPressed=0;
	// flags->keyUPressed=0;
	// flags->keyVPressed=0;
	// flags->keyWPressed=0;
	// flags->keyXPressed=0;
	// flags->keyYPressed=0;
	// flags->keyZPressed=0;
	// flags->a=0;
	flags->b=0;
	// flags->x=0;
	// flags->y=0;
	// flags->l=0;
	// flags->r=0;
	// flags->zl=0;
	// flags->zr=0;
	flags->plus=0;
	// flags->minus=0;
	// flags->du=0;
	// flags->dd=0;
	// flags->dl=0;
	// flags->dr=0;
}

// void wait(unsigned int ticks)
// {
//     unsigned int coreinit_handle;
//     OSDynLoad_Acquire("coreinit.rpl", &coreinit_handle);

//     unsigned int(*OSGetTick)();
//     OSDynLoad_FindExport(coreinit_handle, 0, "OSGetTick", &OSGetTick);

//     unsigned int start_ticks = OSGetTick();
//     unsigned int current_ticks = OSGetTick();

//     while (current_ticks < start_ticks + ticks)
//         current_ticks = OSGetTick();
// }

void drawChar(char character, int xpos, int ypos, int scale, char r, char g, char b, char a) /*   11/26= ~42%   */
{
	int x = xpos, y = ypos;

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
		drawFillRect(x, y, x + 8 * scale, y + 1.5 * scale, r, g, b, a);

		drawFillRect(x, y + 1 * scale, x + 2 * scale, y + 18 * scale, r, g, b, a);
		drawFillRect(x + 2 * scale, y + 8.5 * scale, x + 7 * scale, y + 9.5 * scale, r, g, b, a);
	}

	//G

	if (character == 'H') {
		drawFillRect(x, y, x + 2 * scale, y + 18 * scale, r, g, b, a);

		drawFillRect(x + 2 * scale, y + 8 * scale, x + 6 * scale, y + 10 * scale, r, g, b, a);

		drawFillRect(x + 6 * scale, y, x + 8 * scale, y + 18 * scale, r, g, b, a);
	}

	if (character == 'I') {
		drawFillRect(x, y, x + 2 * scale, y + 18 * scale, r, g, b, a);
	}

	//J

	//K

	if (character == 'L') {
		drawFillRect(x, y, x + 2 * scale, y + 18 * scale, r, g, b, a);
		drawFillRect(x + 1 * scale, y + 16 * scale, x + 8 * scale, y + 18 * scale, r, g, b, a);
	}

	//M

	// if (character == 'N') { //too edgy, not scalable
	// 	drawFillRect(x, y, x + 2, y + 19, r, g, b, a);
	// 	int i, plusx = 3, plusy = 0;
	// 	for (i = 0; i < 5; ++i) {
	// 		drawLine(x + plusx, y + plusy, x + plusx, y + plusy + 3, r, g, b, a);
	// 		++plusx;
	// 		drawLine(x + plusx, y + plusy, x + plusx, y + plusy + 3, r, g, b, a);
	// 		++plusx;
	// 		plusy += 4;
	// 	}
	// 	drawFillRect(x + 13, y, x + 15, y + 19, r, g, b, a);
	// }

	if (character == 'O') {
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

	if (character == 'O') {
		drawFillRect(x + 1 * scale, y, x + 8 * scale, y + 2 * scale, r, g, b, a);

		drawFillRect(x + 7 * scale, y + 2 * scale, x + 9 * scale, y + 16 * scale, r, g, b, a);
		drawFillRect(x, y + 2 * scale, x + 2 * scale, y + 16 * scale, r, g, b, a);

		drawFillRect(x + 1 * scale, y + 16 * scale, x + 8 * scale, y + 18 * scale, r, g, b, a);

		drawFillRect(x + 4 * scale, y + 15 * scale, x + 5 * scale, y + 16 * scale, r, g, b, a);
		drawFillRect(x + 6 * scale, y + 18 * scale, x + 7 * scale, y + 19 * scale, r, g, b, a);
		drawFillRect(x + 7 * scale, y + 19 * scale, x + 8 * scale, y + 20 * scale, r, g, b, a);
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