#include <nds.h>
#include <nds/system.h>
#include <nds/interrupts.h>

#include "../../../common/common.h"

#include "fifo_handler.h"
#include "interrupts.h"

#include "../touch.h"
#include "../wireless/wifi_arm7.h"


void hblank(){
}

void vblank(){	
	Wifi_Update();
}

void vcounter(){
	updateMyIPC();	
}