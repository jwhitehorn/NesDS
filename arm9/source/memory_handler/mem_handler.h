#include <nds.h>


#ifdef __cplusplus
extern "C"{
#endif

extern __attribute__((section(".dtcm"))) u32 * this_heap_ptr;
extern __attribute__((section(".dtcm"))) int free_allocable_mem;

extern int calc_remaining_kernel_mem();
extern u32 * sbrk_init();
extern u32 * sbrk_alloc(int size);
extern u32 * sbrk_dealloc(int size);

//ld variables
//linker script hardware address setup (get map addresses from linker file)
extern int __ewram_start;
extern int __dtcm_start;

extern int __gbarom_start;
extern int __gbarom_end;

extern int __gbaew_start;
extern int __gbaew_end;

extern int __itcm_start;

//top NDS EWRAM used memory by libnds
extern int __end__;

#ifdef __cplusplus
}
#endif
