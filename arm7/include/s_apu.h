#ifndef S_APU_H__
#define S_APU_H__

#ifdef __cplusplus
extern "C" {
#endif

extern void APUSoundInstall(void);
extern void APU4015Reg(void);
extern void APUSoundWrite(Uint address, Uint value);
#ifdef __cplusplus
}
#endif

#endif /* S_APU_H__ */
