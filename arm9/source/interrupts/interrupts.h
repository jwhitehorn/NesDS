
//these just extend libnds interrupt libraries
#ifndef nds_interrupt_headers
#define nds_interrupt_headers


#include <nds.h>

#include <nds/interrupts.h>
#include <nds/system.h>
#include <nds/ipc.h>
#ifdef ARM7
#include <nds/arm7/i2c.h>
#endif


#endif
#ifdef __cplusplus
extern "C"{
#endif

//external (usermode)
extern void vcounter();
extern void Vblank();
extern void Hblank();
extern void initirqs();
extern void refreshNESjoypads();

//internal code (kernel)
extern void IntrMainExt();

//libnds
extern void irqDummy(void);
extern struct IntTable irqTable[MAX_INTERRUPTS];
//extern struct IntTable irqTable[MAX_INTERRUPTS] INT_TABLE_SECTION;

#ifdef INT_TABLE_SECTION
#else
extern struct IntTable irqTable[MAX_INTERRUPTS];
#endif

extern void irqInitExt(IntFn handler);

#ifdef __cplusplus
}
#endif
