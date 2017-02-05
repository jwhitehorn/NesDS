#include <nds.h>
#include <nds/system.h>
#include <nds/interrupts.h>

#include "common_shared.h"
#include "interrupts.h"
#include "touch.h"
#include "wifi_arm7.h"


#ifdef ARM7
#include <nds/arm7/i2c.h>
#endif

void hblank(){
}

void vblank(){	
	Wifi_Update();
}

void vcounter(){
	updateMyIPC();	
}



/*---------------------------------------------------------------------------------
	Copyright (C) 2005
		Dave Murphy (WinterMute)
	This software is provided 'as-is', without any express or implied
	warranty.  In no event will the authors be held liable for any
	damages arising from the use of this software.
	Permission is granted to anyone to use this software for any
	purpose, including commercial applications, and to alter it and
	redistribute it freely, subject to the following restrictions:
	1.	The origin of this software must not be misrepresented; you
		must not claim that you wrote the original software. If you use
		this software in a product, an acknowledgment in the product
		documentation would be appreciated but is not required.
	2.	Altered source versions must be plainly marked as such, and
		must not be misrepresented as being the original software.
	3.	This notice may not be removed or altered from any source
		distribution.
---------------------------------------------------------------------------------*/


//we need the irq handler exposed (so other projects that use custom IRQ handler can benefit..)

//---------------------------------------------------------------------------------
void irqInitExt(IntFn handler) {
//---------------------------------------------------------------------------------
	int i;

	irqInitHandler(handler);

	// Set all interrupts to dummy functions.
	for(i = 0; i < MAX_INTERRUPTS; i ++)
	{
		irqTable[i].handler = irqDummy;
		irqTable[i].mask = 0;
	}

#ifdef ARM7
	if (isDSiMode()) {
		irqSetAUX(IRQ_I2C, i2cIRQHandler);
		irqEnableAUX(IRQ_I2C);
	}
#endif
	REG_IME = 1;			// enable global interrupt
}

//this will be removed once I update devkitarm.
#ifdef ARM7

#ifndef isDSiMode
//!	Checks whether the application is running in DSi mode.
inline bool isDSiMode() {
	extern bool __dsimode;
	return __dsimode;
}
#endif

#endif