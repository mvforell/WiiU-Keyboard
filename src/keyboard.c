#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <malloc.h>
#include "dynamic_libs/os_functions.h"
#include "dynamic_libs/fs_functions.h"
#include "dynamic_libs/gx2_functions.h"
#include "dynamic_libs/sys_functions.h"
#include "dynamic_libs/vpad_functions.h"
#include "dynamic_libs/padscore_functions.h"
#include "dynamic_libs/socket_functions.h"
#include "dynamic_libs/ax_functions.h"
#include "fs/fs_utils.h"
#include "fs/sd_fat_devoptab.h"
#include "system/memory.h"
#include "utils/logger.h"
#include "utils/utils.h"
#include "common/common.h"
#include "keyboard.h"

#define WAIT 0x1

void launchKeyboard(char (*returnedString)[256])
{
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
	flags.keyColonPressed=0;
	flags.keyPeriodPressed=0;
	flags.keyBackspacePressed=0;
	flags.keySpacePressed=0;
	flags.b=0;
	flags.plus=0;
	flags.bTouched=0;
	flags.xTouched=0;
	flags.plusTouched=0;
	flags.HomeTouched=0;
	flags.rc=255;
	flags.gc=255;
	flags.bc=255;

	VPADData vpad_data;

	__os_snprintf(flags.theme, 32, "Zelda       ");
	__os_snprintf(flags.touching, 32, "");
	flags.text[0] = ' ';
	/****************************>            VPAD Loop            <****************************/

	/* Enter the VPAD loop */
	int error, n;
	//Read initial vpad status
	VPADRead(0, &vpad_data, 1, &error);

	while (1)
	{
		VPADRead(0, &vpad_data, 1, &error);

		if (vpad_data.tpdata.touched == 1) {
			flags.touch=1;
			__os_snprintf(flags.touching, 32, "%i, %i", vpad_data.tpdata.x, vpad_data.tpdata.y);

			if (flags.menu && !flags.change_theme && vpad_data.tpdata.x > 370 && vpad_data.tpdata.x < 720 && vpad_data.tpdata.y < 3280 && vpad_data.tpdata.y > 3125) {
				if (!flags.QWERTY)
					flags.QWERTY = 1;
				else
					flags.QWERTY = 0;
				flags.change_theme = 0;
				flags.menu = 0;
				int wait = WAIT;
				while (--wait) {}
			} else if (flags.menu && vpad_data.tpdata.x > 2950 && vpad_data.tpdata.x < 3640 && vpad_data.tpdata.y < 3290 && vpad_data.tpdata.y > 3120) {
				flags.change_theme = 1;
				int wait = WAIT;
				while (--wait) {}
			} else if (flags.change_theme && vpad_data.tpdata.x > 365 && vpad_data.tpdata.x < 640 && vpad_data.tpdata.y < 3280 && vpad_data.tpdata.y > 3120) {
				flags.rc = 255;
				flags.gc = 255;
				flags.bc = 255;
				__os_snprintf(flags.theme, 32, "Zelda       ");
				flags.change_theme = 0;
				flags.menu = 0;
				int wait = WAIT;
				while (--wait) {}
			} else if (flags.change_theme && vpad_data.tpdata.x > 885 && vpad_data.tpdata.x < 1090 && vpad_data.tpdata.y < 3280 && vpad_data.tpdata.y > 3120) {
				flags.rc = 0;
				flags.gc = 255;
				flags.bc = 0;
				__os_snprintf(flags.theme, 32, "Link        ");
				flags.change_theme = 0;
				flags.menu = 0;
				int wait = WAIT;
				while (--wait) {}
			} else if (flags.change_theme && vpad_data.tpdata.x > 1335 && vpad_data.tpdata.x < 1560 && vpad_data.tpdata.y < 3280 && vpad_data.tpdata.y > 3120) {
				flags.rc = 0;
				flags.gc = 255;
				flags.bc = 255;
				__os_snprintf(flags.theme, 32, "Zora        ");
				flags.change_theme = 0;
				flags.menu = 0;
				int wait = WAIT;
				while (--wait) {}
			} else if (vpad_data.tpdata.x > 3770 && vpad_data.tpdata.x < 3910 && vpad_data.tpdata.y < 520 && vpad_data.tpdata.y > 250) {
				int wait = WAIT;
				while (--wait) {}
				if (flags.menu)
					flags.bTouched=1;
				else
					flags.plusTouched=1;
			} else if (vpad_data.tpdata.x > 3740 && vpad_data.tpdata.x < 3930 && vpad_data.tpdata.y < 3815 && vpad_data.tpdata.y > 3490) {
				flags.xTouched=1;
			} else if (vpad_data.tpdata.x > 110 && vpad_data.tpdata.x < 320 && vpad_data.tpdata.y < 550 && vpad_data.tpdata.y > 215) {
				flags.HomeTouched=1;
			}


			else if (vpad_data.tpdata.x > 545 && vpad_data.tpdata.x < 775 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1400) {
				flags.text[flags.textLength - 1] = 'A';
				++flags.textLength;
				int wait = WAIT;
				while (--wait) {}
				flags.keyAPressed=1;
			} else if (vpad_data.tpdata.x > 1625 && vpad_data.tpdata.x < 1865 && vpad_data.tpdata.y < 1360 && vpad_data.tpdata.y > 850) {
				flags.text[flags.textLength - 1] = 'B';
				++flags.textLength;
				int wait = WAIT;
				while (--wait) {}
				flags.keyBPressed=1;
			} else if (vpad_data.tpdata.x > 1090 && vpad_data.tpdata.x < 1325 && vpad_data.tpdata.y < 1360 && vpad_data.tpdata.y > 850) {
				flags.text[flags.textLength - 1] = 'C';
				++flags.textLength;
				int wait = WAIT;
				while (--wait) {}
				flags.keyCPressed=1;
			} else if (vpad_data.tpdata.x > 1090 && vpad_data.tpdata.x < 1325 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1400) {
				flags.text[flags.textLength - 1] = 'D';
				++flags.textLength;
				int wait = WAIT;
				while (--wait) {}
				flags.keyDPressed=1;
			} else if (vpad_data.tpdata.x > 1090 && vpad_data.tpdata.x < 1325 && vpad_data.tpdata.y < 2420 && vpad_data.tpdata.y > 1950) {
				flags.text[flags.textLength - 1] = 'E';
				++flags.textLength;
				int wait = WAIT;
				while (--wait) {}
				flags.keyEPressed=1;
			} else if (vpad_data.tpdata.x > 1350 && vpad_data.tpdata.x < 1595 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1400) {
				flags.text[flags.textLength - 1] = 'F';
				++flags.textLength;
				int wait = WAIT;
				while (--wait) {}
				flags.keyFPressed=1;
			} else if (vpad_data.tpdata.x > 1625 && vpad_data.tpdata.x < 1865 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1400) {
				flags.text[flags.textLength - 1] = 'G';
				++flags.textLength;
				int wait = WAIT;
				while (--wait) {}
				flags.keyGPressed=1;
			} else if (vpad_data.tpdata.x > 1900 && vpad_data.tpdata.x < 2155 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1400) {
				flags.text[flags.textLength - 1] = 'H';
				++flags.textLength;
				int wait = WAIT;
				while (--wait) {}
				flags.keyHPressed=1;
			} else if (vpad_data.tpdata.x > 2450 && vpad_data.tpdata.x < 2700 && vpad_data.tpdata.y < 2420 && vpad_data.tpdata.y > 1950) {
				flags.text[flags.textLength - 1] = 'I';
				++flags.textLength;
				int wait = WAIT;
				while (--wait) {}
				flags.keyIPressed=1;
			} else if (vpad_data.tpdata.x > 2175 && vpad_data.tpdata.x < 2430 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1400) {
				flags.text[flags.textLength - 1] = 'J';
				++flags.textLength;
				int wait = WAIT;
				while (--wait) {}
				flags.keyJPressed=1;
			} else if (vpad_data.tpdata.x > 2450 && vpad_data.tpdata.x < 2700 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1400) {
				flags.text[flags.textLength - 1] = 'K';
				++flags.textLength;
				int wait = WAIT;
				while (--wait) {}
				flags.keyKPressed=1;
			} else if (vpad_data.tpdata.x > 2725 && vpad_data.tpdata.x < 2965 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1400) {
				flags.text[flags.textLength - 1] = 'L';
				++flags.textLength;
				int wait = WAIT;
				while (--wait) {}
				flags.keyLPressed=1;
			} else if (vpad_data.tpdata.x > 2175 && vpad_data.tpdata.x < 2430 && vpad_data.tpdata.y < 1360 && vpad_data.tpdata.y > 850) {
				flags.text[flags.textLength - 1] = 'M';
				++flags.textLength;
				int wait = WAIT;
				while (--wait) {}
				flags.keyMPressed=1;
			} else if (vpad_data.tpdata.x > 1900 && vpad_data.tpdata.x < 2155 && vpad_data.tpdata.y < 1360 && vpad_data.tpdata.y > 850) {
				flags.text[flags.textLength - 1] = 'N';
				++flags.textLength;
				int wait = WAIT;
				while (--wait) {}
				flags.keyNPressed=1;
			} else if (vpad_data.tpdata.x > 2725 && vpad_data.tpdata.x < 2965 && vpad_data.tpdata.y < 2420 && vpad_data.tpdata.y > 1950) {
				flags.text[flags.textLength - 1] = 'O';
				++flags.textLength;
				int wait = WAIT;
				while (--wait) {}
				flags.keyOPressed=1;
			} else if (vpad_data.tpdata.x > 2990 && vpad_data.tpdata.x < 3230 && vpad_data.tpdata.y < 2420 && vpad_data.tpdata.y > 1950) {
				flags.text[flags.textLength - 1] = 'P';
				++flags.textLength;
				int wait = WAIT;
				while (--wait) {}
				flags.keyPPressed=1;
			} else if (vpad_data.tpdata.x > 545 && vpad_data.tpdata.x < 775 && vpad_data.tpdata.y < 2420 && vpad_data.tpdata.y > 1950) {
				flags.text[flags.textLength - 1] = 'Q';
				++flags.textLength;
				int wait = WAIT;
				while (--wait) {}
				flags.keyQPressed=1;
			} else if (vpad_data.tpdata.x > 1350 && vpad_data.tpdata.x < 1595 && vpad_data.tpdata.y < 2420 && vpad_data.tpdata.y > 1950) {
				flags.text[flags.textLength - 1] = 'R';
				++flags.textLength;
				int wait = WAIT;
				while (--wait) {}
				flags.keyRPressed=1;
			} else if (vpad_data.tpdata.x > 810 && vpad_data.tpdata.x < 1065 && vpad_data.tpdata.y < 1900 && vpad_data.tpdata.y > 1400) {
				flags.text[flags.textLength - 1] = 'S';
				++flags.textLength;
				int wait = WAIT;
				while (--wait) {}
				flags.keySPressed=1;
			} else if (vpad_data.tpdata.x > 1625 && vpad_data.tpdata.x < 1865 && vpad_data.tpdata.y < 2420 && vpad_data.tpdata.y > 1950) {
				flags.text[flags.textLength - 1] = 'T';
				++flags.textLength;
				int wait = WAIT;
				while (--wait) {}
				flags.keyTPressed=1;
			} else if (vpad_data.tpdata.x > 2175 && vpad_data.tpdata.x < 2430 && vpad_data.tpdata.y < 2420 && vpad_data.tpdata.y > 1950) {
				flags.text[flags.textLength - 1] = 'U';
				++flags.textLength;
				int wait = WAIT;
				while (--wait) {}
				flags.keyUPressed=1;
			} else if (vpad_data.tpdata.x > 1350 && vpad_data.tpdata.x < 1595 && vpad_data.tpdata.y < 1360 && vpad_data.tpdata.y > 850) {
				flags.text[flags.textLength - 1] = 'V';
				++flags.textLength;
				int wait = WAIT;
				while (--wait) {}
				flags.keyVPressed=1;
			} else if (vpad_data.tpdata.x > 810 && vpad_data.tpdata.x < 1065 && vpad_data.tpdata.y < 2420 && vpad_data.tpdata.y > 1950) {
				flags.text[flags.textLength - 1] = 'W';
				++flags.textLength;
				int wait = WAIT;
				while (--wait) {}
				flags.keyWPressed=1;
			} else if (vpad_data.tpdata.x > 810 && vpad_data.tpdata.x < 1065 && vpad_data.tpdata.y < 1360 && vpad_data.tpdata.y > 850) {
				flags.text[flags.textLength - 1] = 'X';
				++flags.textLength;
				int wait = WAIT;
				while (--wait) {}
				flags.keyXPressed=1;
			} else if (vpad_data.tpdata.x > 545 && vpad_data.tpdata.x < 775 && vpad_data.tpdata.y < 1360 && vpad_data.tpdata.y > 850) {
				if (flags.QWERTY)
					flags.text[flags.textLength - 1] = 'Z';
				else
					flags.text[flags.textLength - 1] = 'Y';
				++flags.textLength;
				int wait = WAIT;
				while (--wait) {}
				if (flags.QWERTY)
					flags.keyZPressed=1;
				else
					flags.keyYPressed=1;
			} else if (vpad_data.tpdata.x > 1900 && vpad_data.tpdata.x < 2155 && vpad_data.tpdata.y < 2420 && vpad_data.tpdata.y > 1950) {
				if (flags.QWERTY)
					flags.text[flags.textLength - 1] = 'Y';
				else
					flags.text[flags.textLength - 1] = 'Z';
				++flags.textLength;
				int wait = WAIT;
				while (--wait) {}
				if (flags.QWERTY)
					flags.keyYPressed=1;
				else
					flags.keyZPressed=1;
			} else if (vpad_data.tpdata.x > 2450 && vpad_data.tpdata.x < 2700 && vpad_data.tpdata.y < 1360 && vpad_data.tpdata.y > 850) {
				flags.text[flags.textLength - 1] = ':';
				++flags.textLength;
				int wait = WAIT;
				while (--wait) {}
				flags.keyColonPressed=1;
			} else if (vpad_data.tpdata.x > 2725 && vpad_data.tpdata.x < 2965 && vpad_data.tpdata.y < 1360 && vpad_data.tpdata.y > 850) {
				flags.text[flags.textLength - 1] = '.';
				++flags.textLength;
				int wait = WAIT;
				while (--wait) {}
				flags.keyPeriodPressed=1;
			} else if (vpad_data.tpdata.x > 3295 && vpad_data.tpdata.x < 3645 && vpad_data.tpdata.y < 2375 && vpad_data.tpdata.y > 2000) { //intentionally bigger
				if (flags.textLength > 1) {
					--flags.textLength;
					flags.text[flags.textLength - 1] = ' ';
					int wait = WAIT;
					while (--wait) {}
					flags.keyBackspacePressed=1;
				}
			} else if (vpad_data.tpdata.x > 3080 && vpad_data.tpdata.x < 3725 && vpad_data.tpdata.y < 1760 && vpad_data.tpdata.y > 1485) {
				flags.text[flags.textLength - 1] = ' ';
				++flags.textLength;
				int wait = WAIT;
				while (--wait) {}
				flags.keySpacePressed=1;
			}
		}

		if ((vpad_data.btns_h & VPAD_BUTTON_X) || flags.xTouched) {
			for (n = 0; n < flags.textLength; ++n)
				flags.text[n] = ' ';
			flags.textLength = 1;
		} else if ((vpad_data.btns_h & VPAD_BUTTON_B) || flags.bTouched)
			flags.b=1;
		else if ((vpad_data.btns_h & VPAD_BUTTON_PLUS) || flags.plusTouched)
			flags.plus=1;
		else if((vpad_data.btns_h & VPAD_BUTTON_HOME) || flags.HomeTouched)
			break;

		render(&flags);
	}
	for(int i = 0; i < 256; i++) {
		(*returnedString)[i] = flags.text[i];
	}
}

void render(struct renderFlags *flags)
{
	char rr = flags->rc, gg = flags->gc, bb = flags->bc;
	for(int i = 0; i < 2; i++)
	{
		fillScreen(64, 64, 64, 0); //The part until fillTV() will only be shown on the Gamepad (because this is meant to be a gamepad-only application, that's also why the font is always the normal one on the TV)

		if (flags->menu) {
			drawOwnString(60, 120, "Current theme: ", 15, rr, gg, bb, 0);
			drawOwnString(260, 120, flags->theme, 12, rr, gg, bb, 0);

			if (!flags->change_theme) {
				drawOwnString(365, 30, "Settings", 8, rr, gg, bb, 0);

				if (!flags->QWERTY)
					drawOwnString(60, 80, "QWERTY", 6, rr, gg, bb, 0);
				else
					drawOwnString(60, 80, "QWERTZ", 6, rr, gg, bb, 0);

				drawOwnString(625, 80, "Change theme", 12, rr, gg, bb, 0);
			} else {
				drawOwnString(350, 30, "CHANGE THEME", 12, rr, gg, bb, 0);
				drawOwnString(60, 80, "Zelda", 7, 255, 255, 255, 0);
				drawOwnString(175, 80, "Link", 4, 0, 255, 0, 0);
				drawOwnString(275, 80, "Zora", 4, 0, 255, 255, 0);
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
			drawOwnString(365, 30, "Keyboard", 8, rr, gg, bb, 0);
			int i, x = 115, y = 200, plusy = 0, minusy = 0;


			if (flags->keyQPressed) {
				drawFillRect(97, 185, 152, 250, 100, 100, 100, 0);
				drawChar('Q', x, y, 2, 255, 255, 0, 0);
			} else {
				drawChar('Q', x, y, 2, rr, gg, bb, 0);
			}
			x += 60;
			if (flags->keyWPressed) {
				drawFillRect(155, 185, 214, 250, 100, 100, 100, 0);
				drawChar('W', x, y, 2, 255, 255, 0, 0);
			} else {
				drawChar('W', x, y, 2, rr, gg, bb, 0);
			}
			x += 60;
			if (flags->keyEPressed) {
				drawFillRect(215, 185, 272, 250, 100, 100, 100, 0);
				drawChar('E', x, y, 2, 255, 255, 0, 0);
			} else {
				drawChar('E', x, y, 2, rr, gg, bb, 0);
			}
			x += 60;
			if (flags->keyRPressed) {
				drawFillRect(273, 185, 332, 250, 100, 100, 100, 0);
				drawChar('R', x, y, 2, 255, 255, 0, 0);
			} else {
				drawChar('R', x, y, 2, rr, gg, bb, 0);
			}
			x += 60;
			if (flags->keyTPressed) {
				drawFillRect(333, 185, 391, 250, 100, 100, 100, 0);
				drawChar('T', x, y, 2, 255, 255, 0, 0);
			} else {
				drawChar('T', x, y, 2, rr, gg, bb, 0);
			}
			x += 60;
			if (flags->QWERTY) {
				if (flags->keyYPressed) {
					drawFillRect(392, 185, 452, 250, 100, 100, 100, 0);
					drawChar('Y', x, y, 2, 255, 255, 0, 0);
				} else {
					drawChar('Y', x, y, 2, rr, gg, bb, 0);
				}
				x += 60;
			} else {
				if (flags->keyZPressed) {
					drawFillRect(392, 185, 452, 250, 100, 100, 100, 0);
					drawChar('Z', x, y, 2, 255, 255, 0, 0);
				} else {
					drawChar('Z', x, y, 2, rr, gg, bb, 0);
				}
				x += 60;
			}
			if (flags->keyUPressed) {
				drawFillRect(453, 185, 512, 250, 100, 100, 100, 0);
				drawChar('U', x, y, 2, 255, 255, 0, 0);
			} else {
				drawChar('U', x, y, 2, rr, gg, bb, 0);
			}
			x += 68;
			if (flags->keyIPressed) {
				drawFillRect(513, 185, 572, 250, 100, 100, 100, 0);
				drawChar('I', x, y, 2, 255, 255, 0, 0);
			} else {
				drawChar('I', x, y, 2, rr, gg, bb, 0);
			}
			x += 52;
			if (flags->keyOPressed) {
				drawFillRect(573, 185, 631, 250, 100, 100, 100, 0);
				drawChar('O', x, y, 2, 255, 255, 0, 0);
			} else {
				drawChar('O', x, y, 2, rr, gg, bb, 0);
			}
			x += 60;
			if (flags->keyPPressed) {
				drawFillRect(632, 185, 690, 250, 100, 100, 100, 0);
				drawChar('P', x, y, 2, 255, 255, 0, 0);
			} else {
				drawChar('P', x, y, 2, rr, gg, bb, 0);
			}



			y += 70;
			x = 115;
			if (flags->keyAPressed) {
				drawFillRect(97, 255, 152, 320, 100, 100, 100, 0);
				drawChar('A', x, y, 2, 255, 255, 0, 0);
			} else {
				drawChar('A', x, y, 2, rr, gg, bb, 0);
			}
			x += 60;
			if (flags->keySPressed) {
				drawFillRect(153, 255, 214, 320, 100, 100, 100, 0);
				drawChar('S', x, y, 2, 255, 255, 0, 0);
			} else {
				drawChar('S', x, y, 2, rr, gg, bb, 0);
			}
			x += 60;
			if (flags->keyDPressed) {
				drawFillRect(215, 255, 272, 320, 100, 100, 100, 0);
				drawChar('D', x, y, 2, 255, 255, 0, 0);
			} else {
				drawChar('D', x, y, 2, rr, gg, bb, 0);
			}
			x += 60;
			if (flags->keyFPressed) {
				drawFillRect(273, 255, 332, 320, 100, 100, 100, 0);
				drawChar('F', x, y, 2, 255, 255, 0, 0);
			} else {
				drawChar('F', x, y, 2, rr, gg, bb, 0);
			}
			x += 60;
			if (flags->keyGPressed) {
				drawFillRect(333, 255, 391, 320, 100, 100, 100, 0);
				drawChar('G', x, y, 2, 255, 255, 0, 0);
			} else {
				drawChar('G', x, y, 2, rr, gg, bb, 0);
			}
			x += 61;
			if (flags->keyHPressed) {
				drawFillRect(392, 255, 452, 320, 100, 100, 100, 0);
				drawChar('H', x, y, 2, 255, 255, 0, 0);
			} else {
				drawChar('H', x, y, 2, rr, gg, bb, 0);
			}
			x += 59;
			if (flags->keyJPressed) {
				drawFillRect(453, 255, 512, 320, 100, 100, 100, 0);
				drawChar('J', x, y, 2, 255, 255, 0, 0);
			} else {
				drawChar('J', x, y, 2, rr, gg, bb, 0);
			}
			x += 61;
			if (flags->keyKPressed) {
				drawFillRect(513, 255, 572, 320, 100, 100, 100, 0);
				drawChar('K', x, y, 2, 255, 255, 0, 0);
			} else {
				drawChar('K', x, y, 2, rr, gg, bb, 0);
			}
			x += 60;
			if (flags->keyLPressed) {
				drawFillRect(573, 255, 631, 320, 100, 100, 100, 0);
				drawChar('L', x, y, 2, 255, 255, 0, 0);
			} else {
				drawChar('L', x, y, 2, rr, gg, bb, 0);
			}



			y += 70;
			x = 115;
			if (flags->QWERTY) {
				if (flags->keyZPressed) {
					drawFillRect(97, 325, 152, 390, 100, 100, 100, 0);
					drawChar('Z', x, y, 2, 255, 255, 0, 0);
				} else {
					drawChar('Z', x, y, 2, rr, gg, bb, 0);
				}
				x += 60;
			} else {
				if (flags->keyYPressed) {
					drawFillRect(97, 325, 152, 390, 100, 100, 100, 0);
					drawChar('Y', x, y, 2, 255, 255, 0, 0);
				} else {
					drawChar('Y', x, y, 2, rr, gg, bb, 0);
				}
				x += 60;
			}
			if (flags->keyXPressed) {
				drawFillRect(153, 325, 214, 390, 100, 100, 100, 0);
				drawChar('X', x, y, 2, 255, 255, 0, 0);
			} else {
				drawChar('X', x, y, 2, rr, gg, bb, 0);
			}
			x += 60;
			if (flags->keyCPressed) {
				drawFillRect(215, 325, 272, 390, 100, 100, 100, 0);
				drawChar('C', x, y, 2, 255, 255, 0, 0);
			} else {
				drawChar('C', x, y, 2, rr, gg, bb, 0);
			}
			x += 60;
			if (flags->keyVPressed) {
				drawFillRect(273, 325, 332, 390, 100, 100, 100, 0);
				drawChar('V', x, y, 2, 255, 255, 0, 0);
			} else {
				drawChar('V', x, y, 2, rr, gg, bb, 0);
			}
			x += 60;
			if (flags->keyBPressed) {
				drawFillRect(333, 325, 391, 390, 100, 100, 100, 0);
				drawChar('B', x, y, 2, 255, 255, 0, 0);
			} else {
				drawChar('B', x, y, 2, rr, gg, bb, 0);
			}
			x += 60;
			if (flags->keyNPressed) {
				drawFillRect(392, 325, 452, 390, 100, 100, 100, 0);
				drawChar('N', x, y, 2, 255, 255, 0, 0);
			} else {
				drawChar('N', x, y, 2, rr, gg, bb, 0);
			}
			x += 60;
			if (flags->keyMPressed) {
				drawFillRect(453, 325, 512, 390, 100, 100, 100, 0);
				drawChar('M', x, y, 2, 255, 255, 0, 0);
			} else {
				drawChar('M', x, y, 2, rr, gg, bb, 0);
			}

			y += 10;
			x += 69;
			if (flags->keyColonPressed) {
				drawFillRect(513, 325, 572, 390, 100, 100, 100, 0);
				drawChar(':', x, y, 2, 255, 255, 0, 0);
			} else {
				drawChar(':', x, y, 2, rr, gg, bb, 0);
			}

			y -= 7;
			x += 54;
			if (flags->keyPeriodPressed) {
				drawFillRect(573, 325, 631, 390, 100, 100, 100, 0);
				drawChar('.', x + 5, y, 2, 255, 255, 0, 0);
			} else {
				drawChar('.', x + 5, y, 2, rr, gg, bb, 0);
			}


			drawFillRect(95, 183, 695, 188, rr, gg, bb, 0);
			drawFillRect(95, 250, 690, 255, rr, gg, bb, 0);
			drawFillRect(95, 320, 630, 325, rr, gg, bb, 0);
			drawFillRect(95, 390, 630, 395, rr, gg, bb, 0);

			drawFillRect(92, 183, 97, 395, rr, gg, bb, 0);
			drawFillRect(152, 185, 157, 395, rr, gg, bb, 0);
			drawFillRect(214, 185, 219, 395, rr, gg, bb, 0);
			drawFillRect(272, 185, 277, 395, rr, gg, bb, 0);
			drawFillRect(332, 185, 337, 395, rr, gg, bb, 0);
			drawFillRect(391, 185, 396, 395, rr, gg, bb, 0);
			drawFillRect(452, 185, 457, 395, rr, gg, bb, 0);
			drawFillRect(512, 185, 517, 395, rr, gg, bb, 0);
			drawFillRect(572, 185, 577, 395, rr, gg, bb, 0);
			drawFillRect(631, 185, 636, 395, rr, gg, bb, 0);

			drawFillRect(690, 185, 695, 255, rr, gg, bb, 0);

			x = 710;
			y = 218;
			for (i = 0; i < 20; ++i)
			{
				if (flags->keyBackspacePressed)
					drawLine(x, y - minusy, x, y + plusy, 255, 255, 0, 0);
				else
					drawLine(x, y - minusy, x, y + plusy, rr, gg, bb, 0);
				++x;
				++plusy;
				++minusy;
			}
			if (flags->keyBackspacePressed)
				drawFillRect(x, y + 8, x + 40, y - 8, 255, 255, 0, 0);
			else
				drawFillRect(x, y + 8, x + 40, y - 8, rr, gg, bb, 0);

			if (flags->keySpacePressed) {
				drawFillRect(657, 275, 798, 307, 100, 100, 100, 0);
				drawRect(655, 275, 800, 307, 255, 255, 0, 0);
				drawRect(656, 274, 799, 308, 255, 255, 0, 0);
				drawRect(657, 273, 798, 309, 255, 255, 0, 0);
			} else {
				drawRect(655, 275, 800, 307, rr, gg, bb, 0);
				drawRect(656, 274, 799, 308, rr, gg, bb, 0);
				drawRect(657, 273, 798, 309, rr, gg, bb, 0);
			}
		}

		if (!flags->change_theme && !flags->menu) {
			drawOwnString(60, 90, "Your text:", 10, rr, gg, bb, 0);
			drawOwnString(60, 130, flags->text, flags->textLength - 1, rr, gg, bb, 0);
		}

		if (!flags->menu) {
			if (flags->plus) {
				drawFillCircle(822, 450, 16, 255, 255, 0, 0);
				drawFillCircle(822, 450, 13, 64, 64, 64, 0);
				drawFillRect(820, 440, 824, 460, 255, 255, 0, 0);
				drawFillRect(812, 452, 832, 448, 255, 255, 0, 0);
			} else {
				drawFillCircle(822, 450, 16, rr, gg, bb, 0);
				drawFillCircle(822, 450, 13, 64, 64, 64, 0);
				drawFillRect(820, 440, 824, 460, rr, gg, bb, 0);
				drawFillRect(812, 452, 832, 448, rr, gg, bb, 0);
			}
		} else {
			if (flags->b) {
				drawFillCircle(822, 450, 16, 255, 255, 0, 0);
				drawFillCircle(822, 450, 13, 64, 64, 64, 0);
				drawChar('B', 818, 441, 1, 255, 255, 0, 0);
			} else {
				drawFillCircle(822, 450, 16, rr, gg, bb, 0);
				drawFillCircle(822, 450, 13, 64, 64, 64, 0);
				drawChar('B', 818, 441, 1, rr, gg, bb, 0);
			}
		}
		drawFillCircle(27, 452, 22, rr, gg, bb, 0);
		drawFillCircle(27, 452, 19, 64, 64, 64, 0);

		int m, x = 12, y = 450;
		for (m = 0; m < 16; ++m) {
			drawLine(x + m, y, x + 30 - m, y + m, rr, gg, bb, 0);
			--y;
		}
		drawFillRect(17, 450, 37, 465, rr, gg, bb, 0);
		drawFillRect(23, 453, 31, 458, 64, 64, 64, 0);
		if (!flags->menu) {
			if (flags->x) {
				drawFillCircle(822, 30, 22, 255, 255, 0, 0);
				drawFillCircle(822, 30, 19, 64, 64, 64, 0);
				drawDiagLine(811, 20, 40, 3, 'r', 'd', 255, 255, 0, 0);
				drawDiagLine(811, 40, 20, 3, 'r', 'u', 255, 255, 0, 0);
			} else {
				drawFillCircle(822, 30, 22, rr, gg, bb, 0);
				drawFillCircle(822, 30, 19, 64, 64, 64, 0);
				drawDiagLine(811, 20, 40, 3, 'r', 'd', rr, gg, bb, 0);
				drawDiagLine(811, 40, 20, 3, 'r', 'u', rr, gg, bb, 0);
			}
		}

		drawOwnString(370, 440, "by cmdj13", 9, rr, gg, bb, 0);

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
	flags->keyColonPressed=0;
	flags->keyPeriodPressed=0;
	flags->keyBackspacePressed=0;
	flags->keySpacePressed=0;
	flags->b=0;
	flags->plus=0;
	flags->bTouched=0;
	flags->xTouched=0;
	flags->plusTouched=0;
	flags->HomeTouched=0;
}

void drawChar(char character, int xpos, int ypos, int scale, char r, char g, char b, char a)
{
	int x = xpos, y = ypos, i;
	float plusx = 3.5;

	if (scale != 1 && scale != 2)
		return;

	if (character == ':') {
		drawFillRect(x, y + 5, x + 2, y + 7, r, g, b, a);
		drawFillRect(x, y + 11, x + 2, y + 13, r, g, b, a);
	}

	if (character == '.') {
		drawFillRect(x, y + 16, x + 2, y + 18, r, g, b, a);
	}

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
		drawFillRect(x, y, x + 2 * scale, y + 18 * scale, r, g, b, a);
	}

	if (character == 'J') {
		drawFillRect(x + 7 * scale, y, x + 9 * scale, y + 16 * scale, r, g, b, a);
		drawFillRect(x + 1 * scale, y + 16 * scale, x + 8 * scale, y + 18 * scale, r, g, b, a);
		drawFillRect(x, y + 14 * scale, x + 2 * scale, y + 16 * scale, r, g, b, a);
	}

	if (character == 'K') {
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
		if (scale == 1)
			drawFillRect(x - 1, y, x + 1.5 * scale, y + 18 * scale, r, g, b, a);
		else
			drawFillRect(x, y, x + 1.5 * scale, y + 18 * scale, r, g, b, a);

		for (i = 0; i < 4; ++i) {
			drawFillRect(x + 1.5 * scale + i * scale, y + 1.5 * scale + 1.5 * i * scale, x + 2.5 * scale + i * scale, y + 3 * scale + 1.5 * i * scale, r, g, b, a);
		}
		for (i = 3; i >= 0; --i) {
			drawFillRect(x + 1.5 * scale + plusx * scale, y + 1.5 * scale + 1.5 * i * scale, x + 2.5 * scale + plusx * scale, y + 3 * scale + 1.5 * i * scale, r, g, b, a);
			++plusx;
		}

		if (scale == 1)
			drawFillRect(x + 9 * scale, y, x + 11 * scale, y + 18 * scale, r, g, b, a);
		else
			drawFillRect(x + 9 * scale, y, x + 10.5 * scale, y + 18 * scale, r, g, b, a);

		if (scale == 1)
			drawPixel(x + 5, y + 8, r, g, b, a);
	}

	if (character == 'N') {
		if (scale == 1)
			drawFillRect(x - 1, y, x + 1.5 * scale, y + 18 * scale, r, g, b, a);
		else
			drawFillRect(x + 0.5 * scale, y, x + 2 * scale, y + 18 * scale, r, g, b, a);

		for (i = 0; i < 5; ++i) {
			drawFillRect(x + 2 * scale + 1.5 * i * scale, y + 0.5 * scale + 3.5 * i * scale, x + 3.5 * scale + 1.5 * i * scale, y + 3.5 * scale + 3.5 * i * scale, r, g, b, a);
		}
		drawFillRect(x + 1, y, x + 3.5 * scale, y, r, g, b, a);
		if (scale == 1)
			drawFillRect(x + 8 * scale, y + 18 * scale, x + 12 * scale, y + 18 * scale, r, g, b, a);
		else
			drawFillRect(x + 8 * scale, y + 18 * scale, x + 11 * scale, y + 18 * scale, r, g, b, a);

		if (scale == 1)
			drawFillRect(x + 10 * scale, y, x + 12 * scale, y + 18 * scale, r, g, b, a);
		else
			drawFillRect(x + 9.5 * scale, y, x + 11 * scale, y + 18 * scale, r, g, b, a);
	}

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
		if (scale == 1)
			drawFillRect(x + 7 * scale, y + 2 * scale, x + 8 * scale, y + 3 * scale, r, g, b, a);
		else
			drawFillRect(x + 6.5 * scale, y + 1.5 * scale, x + 8 * scale, y + 3 * scale, r, g, b, a);

		drawFillRect(x + 1 * scale, y, x + 7 * scale, y + 1 * scale, r, g, b, a);
		if (scale == 1)
			drawFillRect(x, y + 2 * scale, x + 2 * scale, y + 7 * scale, r, g, b, a);
		else
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

	if (character == 'W') {
		drawFillRect(x, y, x + 2 * scale, y + 16 * scale, r, g, b, a);
		drawFillRect(x + 1.5 * scale, y + 15.5 * scale, x + 9.5 * scale, y + 17 * scale, r, g, b, a);

		drawFillRect(x + 5 * scale, y + 8.5 * scale, x + 6 * scale, y + 15.5 * scale, r, g, b, a);

		drawFillRect(x + 3 * scale, y + 17 * scale, x + 4 * scale, y + 18 * scale, r, g, b, a);
		drawFillRect(x + 7 * scale, y + 17 * scale, x + 8 * scale, y + 18 * scale, r, g, b, a);
		drawFillRect(x + 9 * scale, y, x + 11 * scale, y + 16 * scale, r, g, b, a);
	}

	if (character == 'X') {
		drawFillRect(x, y, x + 2 * scale, y + 2 * scale, r, g, b, a);
		drawFillRect(x + 8 * scale, y, x + 10 * scale, y + 2 * scale, r, g, b, a);

		drawFillRect(x + 1 * scale, y + 2.5 * scale, x + 3 * scale, y + 4.5 * scale, r, g, b, a);
		drawFillRect(x + 7 * scale, y + 2.5 * scale, x + 9 * scale, y + 4.5 * scale, r, g, b, a);

		drawFillRect(x + 2 * scale, y + 5 * scale, x + 4 * scale, y + 7.5 * scale, r, g, b, a);
		drawFillRect(x + 6 * scale, y + 5 * scale, x + 8 * scale, y + 7.5 * scale, r, g, b, a);

		drawFillRect(x + 3 * scale, y + 8 * scale, x + 7 * scale, y + 10 * scale, r, g, b, a);

		drawFillRect(x + 2 * scale, y + 10.5 * scale, x + 4 * scale, y + 13 * scale, r, g, b, a);
		drawFillRect(x + 6 * scale, y + 10.5 * scale, x + 8 * scale, y + 13 * scale, r, g, b, a);

		drawFillRect(x + 1 * scale, y + 13.5 * scale, x + 3 * scale, y + 15.5 * scale, r, g, b, a);
		drawFillRect(x + 7 * scale, y + 13.5 * scale, x + 9 * scale, y + 15.5 * scale, r, g, b, a);

		drawFillRect(x, y + 16 * scale, x + 2 * scale, y + 18 * scale, r, g, b, a);
		drawFillRect(x + 8 * scale, y + 16 * scale, x + 10 * scale, y + 18 * scale, r, g, b, a);
	}

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
	OSScreenClearBufferEx(0, (r << 24) | (g << 16) | (b << 8) | a);
}

void drawStringTV(int x, int line, char * string)
{
	OSScreenPutFontEx(0, x, line, string);
}

void drawOwnString(int xpos, int ypos, char * string, int length, char r, char g, char b, char a)
{
	int i, x = xpos, y = ypos, plusx = 0;
	char h;
	for (i = 0; i < length; ++i) {
		h = *(string + i);
		if (!(h >= 65 && h <= 90) && (h >= 97 && h <= 122)) {
			h -= 32;
		}
		drawChar(h, x + plusx, y, 1, r, g, b, a);
		if (h == 'E' || h == 'e' || h == 'Y' || h == 'y' || h == 'C' || h == 'c' || h == 'D' || h == 'd' || h == 'F' || h == 'f' || h == 'G' || h == 'g' || h == 'H' || h == 'h' || h == 'S' || h == 's')
			plusx += 12;
		else if (h == 'I' || h == 'i')
			plusx += 6;
		else if (h == 'K' || h == 'k' || h == 'V' || h == 'v' || h == 'X' || h == 'x' || h == 'T' || h == 't' || h == 'U' || h == 'u')
			plusx += 14;
		else if (h == 'W' || h == 'w')
			plusx += 15;
		else if (h == 'N' || h == 'n' || h == 'M' || h == 'm')
			plusx += 16;
		else
			plusx += 13;
	}
}
