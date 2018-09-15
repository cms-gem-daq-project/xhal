#ifndef DAQ_MONITOR_H
#define DAQ_MONITOR_H

#include "xhal/rpc/utils.h"

struct SCAMonitor{
    //Temperature Data
    uint32_t ohBoardTemp[9];
    uint32_t ohFPGACoreTemp;
    uint32_t scaTemp;

    //Voltages
    uint32_t AVCCN;
    uint32_t AVTTN;
    uint32_t voltage1V0_INT;
    uint32_t voltage1V8F;
    uint32_t voltage1V5;
    uint32_t voltage2V5_IO;
    uint32_t voltage3V0;
    uint32_t voltage1V8;
    uint32_t VTRX_RSSI2;
    uint32_t VTRX_RSSI1;
};

DLLEXPORT uint32_t getmonTTCmain(uint32_t* result);
DLLEXPORT uint32_t getmonTRIGGERmain(uint32_t* result, uint32_t noh = 12);
DLLEXPORT uint32_t getmonTRIGGEROHmain(uint32_t* result, uint32_t noh = 12);
DLLEXPORT uint32_t getmonDAQmain(uint32_t* result);
DLLEXPORT uint32_t getmonDAQOHmain(uint32_t* result, uint32_t noh = 12);
DLLEXPORT uint32_t getmonOHmain(uint32_t* result, uint32_t noh = 12);

DLLEXPORT uint32_t getmonOHSCAmain(struct SCAMonitor *scaMon, uint32_t noh = 12, uint32_t ohMask = 0xfff);

#endif
