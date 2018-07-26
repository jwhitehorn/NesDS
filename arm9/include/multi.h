#ifndef _multi_nesds__
#define _multi_nesds__

#include "../../common/wifi_shared.h"
#endif

#ifdef __cplusplus
extern "C"{
#endif

extern Wifi_MainStruct Wifi_Data_Struct;
extern volatile Wifi_MainStruct * WifiData;
extern WifiPacketHandler packethandler;
extern WifiSyncHandler synchandler;
extern int Wifi_RawTxFrameNIFI(u16 datalen, u16 rate, u16 * data);

#ifdef __cplusplus
}
#endif
