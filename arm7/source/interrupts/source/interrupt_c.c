#include <nds.h>
#include <nds/system.h>
#include <nds/interrupts.h>

#include "common_shared.h"
#include "interrupts.h"
#include "touch.h"
#include "wifi_arm7.h"


void hblank(){
}

void vblank(){	
	Wifi_Update();
}

void vcounter(){
	updateMyIPC();	
}