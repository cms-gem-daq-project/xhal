#ifndef CALIBRATION_ROUTINES_H
#define CALIBRATION_ROUTINES_H

#include "xhal/rpc/utils.h"

struct vfat3DACSize{
    uint32_t max[41];

    vfat3DACSize(){
        //ADC Measures Current
        //I wonder if this dacMin and dacMax info could be added to the LMDB...?
        max[0] = 0x3f; //CFG_IREF
        //max[1] = ???
        max[2] = 0xff; //CFG_BIAS_PRE_I_BIT
        max[3] = 0x3f; //CFG_BIAS_PRE_I_BLCC
        //max[4] = ???
        max[5] = 0xff; //CFG_BIAS_SH_I_BFCAS
        max[6] = 0xff; //CFG_BIAS_SH_I_BDIFF
        max[7] = 0xff; //CFG_BIAS_SD_I_BDIFF
        max[8] = 0xff; //CFG_BIAS_SD_I_BFCAS
        max[9] = 0x3f; //CFG_BIAS_SD_I_BSF
        max[10] = 0x3f; //CFG_BIAS_CFD_DAC_1
        max[11] = 0x3f; //CFG_BIAS_CFD_DAC_2
        max[12] = 0x3f; //CFG_HYST
        //max[13] = ???
        max[14] = 0xff; //CFG_THR_ARM_DAC
        max[15] = 0xff; //CFG_THR_ZCC_DAC
        //max[16] = ???

        //ADC Measures Voltage
        //max[32] = ???
        //max[33] = ???
        max[34] = 0xff; //CFG_BIAS_PRE_VREF
        max[35] = 0xff; //CFG_THR_ARM_DAC
        max[36] = 0xff; //CFG_THR_ZCC_DAC
        max[39] = 0x3; //CFG_ADC_VREF
        //max[40] = ???
        //max[41] = ???
    }
};

DLLEXPORT uint32_t checkSbitMappingWithCalPulse(uint32_t ohN, uint32_t vfatN, uint32_t mask, bool useCalPulse, bool currentPulse, uint32_t calScaleFactor, uint32_t nevts, uint32_t L1Ainterval, uint32_t pulseDelay, uint32_t *data);
DLLEXPORT uint32_t checkSbitRateWithCalPulse(uint32_t ohN, uint32_t vfatN, uint32_t mask, bool useCalPulse, bool currentPulse, uint32_t calScaleFactor, uint32_t waitTime, uint32_t pulseRate, uint32_t pulseDelay, uint32_t *outDataCTP7Rate, uint32_t *outDataFPGAClusterCntRate, uint32_t *outDataVFATSBits);
DLLEXPORT uint32_t dacScan(uint32_t ohN, uint32_t dacSelect, uint32_t dacStep, uint32_t mask, bool useExtRefADC, uint32_t * results);
DLLEXPORT uint32_t dacScanMultiLink(uint32_t ohMask, uint32_t NOH, uint32_t dacSelect, uint32_t dacStep, bool useExtRefADC, uint32_t * results);
DLLEXPORT uint32_t genScan(uint32_t nevts, uint32_t ohN, uint32_t dacMin, uint32_t dacMax, uint32_t dacStep,
        uint32_t ch, bool useCalPulse, bool currentPulse, uint32_t calScaleFactor, uint32_t mask, char * scanReg, bool useUltra, bool useExtTrig,
        uint32_t * result);
DLLEXPORT uint32_t genChannelScan(uint32_t nevts, uint32_t ohN, uint32_t mask, uint32_t dacMin, uint32_t dacMax, uint32_t dacStep, bool useCalPulse, bool currentPulse, uint32_t calScaleFactor, bool useExtTrig, char * scanReg, bool useUltra, uint32_t * result);
DLLEXPORT uint32_t sbitRateScan(uint32_t ohN, uint32_t dacMin, uint32_t dacMax, uint32_t dacStep, uint32_t ch, uint32_t maskOh,
        bool invertVFATPos, char * scanReg, uint32_t waitTime, uint32_t * resultDacVal, uint32_t * resultTrigRate,
        uint32_t * resultTrigRatePerVFAT, bool isParallel);
DLLEXPORT uint32_t ttcGenConf(uint32_t ohN, uint32_t mode, uint32_t type, uint32_t pulseDelay,
        uint32_t L1Ainterval, uint32_t nPulses, bool enable);
DLLEXPORT uint32_t ttcGenToggle(uint32_t ohN, bool enable);

#endif
