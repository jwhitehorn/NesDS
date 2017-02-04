/*---------------------------------------------------------------------------------
	derived from the default ARM7 core
---------------------------------------------------------------------------------*/
#include <nds.h>
#include <dswifi7.h>
//#include <maxmod7.h>
#include "ds_misc.h"
#include "c_defs.h"

#include "arm7.h"
#include "interrupts/fifo_handler.h"
#include "interrupts/interrupts.h"

#include "../../common/common.h"

void nesmain();

volatile s16 buffer[MIXBUFSIZE*20];


volatile bool exitflag = false;

u8 *bootstub;
u32 ndstype;
typedef void (*type_void)();
type_void bootstub_arm7;
static void sys_exit(){
	if(!bootstub_arm7){
		if(ndstype>=2)writePowerManagement(0x10, 1);
		else writePowerManagement(0, PM_SYSTEM_PWR);
	}
	bootstub_arm7(); //won't return
}

extern int APU_paused;
void dealrawpcm(unsigned char *out);

//ori
/*
//---------------------------------------------------------------------------------
int main() {
//---------------------------------------------------------------------------------
	readUserSettings();

	irqInit();
	fifoInit();
	// Start the RTC tracking IRQ
	initClockIRQ();

	installSystemFIFO();
	installWifiFIFO();
	//irqSet(IRQ_VCOUNT, VcountHandler);
	irqSet(IRQ_VBLANK, VblankHandler);

	irqEnable(IRQ_TIMER1 | IRQ_VBLANK | IRQ_NETWORK);
	
	{
		ndstype=0;
		u32 myself = readPowerManagement(4); //(PM_BACKLIGHT_LEVEL);
		if(myself & (1<<6))
			ndstype=(myself==readPowerManagement(5))?1:2;
	}

	bootstub=(u8*)0x02ff4000;
	bootstub_arm7=(*(u64*)bootstub==0x62757473746F6F62ULL)?(*(type_void*)(bootstub+0x0c)):0;
	setPowerButtonCB(sys_exit); 

	while(!fifoCheckValue32(FIFO_USER_06))		//wait for the value of ipc_region
		swiWaitForVBlank();				
	ipc_region = fifoGetValue32(FIFO_USER_06);

	nesmain();

	// Keep the ARM7 mostly idle
	while (1) {
		if ( 0 == (REG_KEYINPUT & (KEY_SELECT | KEY_START | KEY_L | KEY_R))) {
			sys_exit();
		}
		inputGetAndSend();
		swiWaitForVBlank();
	}
	//return 0;
}
*/

//ARM9 maps this ipc_region
int ipc_region = 0;
u32 interrupts_to_wait_arm7 = 0;

//---------------------------------------------------------------------------------
int main() {
//---------------------------------------------------------------------------------
	readUserSettings();
	
    int i   = 0;
	REG_IME = 0;

	// Reset the clock if needed
    rtcReset();

    interrupts_to_wait_arm7 = IRQ_TIMER1 | IRQ_HBLANK | IRQ_VBLANK | IRQ_VCOUNT | IRQ_FIFO_NOT_EMPTY;    
	
    irqInit();
    fifoInit();
    
	installWifiFIFO();
	
    irqSet(IRQ_HBLANK,hblank);
	irqSet(IRQ_VBLANK, vblank);
	irqSet(IRQ_VCOUNT,vcounter);
    irqSet(IRQ_TIMER1, soundinterrupt);
    
	irqSet(IRQ_FIFO_NOT_EMPTY,HandleFifoNotEmpty);
    //irqSet(IRQ_FIFO_EMPTY,HandleFifoEmpty);
    
	irqEnable(interrupts_to_wait_arm7);
    
    REG_IPC_SYNC = 0;
    REG_IPC_FIFO_CR = IPC_FIFO_RECV_IRQ;			//10    R/W  Receive Fifo Not Empty IRQ  (0=Disable, 1=Enable)
	//REG_IPC_FIFO_CR |= (1<<2);  					//send empty irq
    REG_IPC_FIFO_CR |= IPC_FIFO_ENABLE;
	
	
    //set up ppu: do irq on hblank/vblank/vcount/and vcount line is 159
    REG_DISPSTAT = REG_DISPSTAT | DISP_HBLANK_IRQ | DISP_VBLANK_IRQ | DISP_YTRIGGER_IRQ | (VCOUNT_LINE_INTERRUPT << 15);
    
	{
		ndstype=0;
		u32 myself = readPowerManagement(4); //(PM_BACKLIGHT_LEVEL);
		if(myself & (1<<6))
			ndstype=(myself==readPowerManagement(5))?1:2;
	}

	bootstub=(u8*)0x02ff4000;
	bootstub_arm7=(*(u64*)bootstub==0x62757473746F6F62ULL)?(*(type_void*)(bootstub+0x0c)):0;
	setPowerButtonCB(sys_exit); 
	
	REG_IF = ~0;
    REG_IME = 1;
	
	//wait for APU to be setup
	while(MyIPC->apu_ready != true){}
	ipc_region = (int)(u32*)MyIPC->IPC_ADDR;
	
	nesmain();
	
	while(1){
		swiWaitForVBlank();
	}
}