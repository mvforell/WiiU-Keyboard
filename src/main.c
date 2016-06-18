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
#include "main.h"

void Menu_Main()
{
	InitOSFunctionPointers();
	InitVPadFunctionPointers();
	memoryInitialize();
	
	OSScreenInit();
	//Grab the buffer size for each screen (TV and gamepad)
	int buf0_size = OSScreenGetBufferSizeEx(0);
	//int buf1_size = OSScreenGetBufferSizeEx(1);
	//Set the buffer area.
	OSScreenSetBufferEx(0, (void *)0xF4000000);
	OSScreenSetBufferEx(1, (void *)0xF4000000 + buf0_size);
	//Clear both framebuffers.
	for(int i = 0; i < 2; i++) {
		fillScreen(0,0,0,0);
		flipBuffers();
	}
	OSScreenEnableEx(0, 1);
	OSScreenEnableEx(1, 1);
	
	char returnedString[256];
	launchKeyboard(&returnedString);
	fillScreen(0, 0, 0, 255);
	drawString(0, 0, returnedString);
	flipBuffers();
	sleep(10);
	
	for(int i = 0; i < 2; i++) {
		fillScreen(0,0,0,0);
		flipBuffers();
	}
}
