#ifndef CAL_UTILS_H
#define CAL_UTILS_H

namespace xhal {
    struct ParamScan{
        //Hardware selection
        uint32_t ohN;
        uint32_t ohMask;
        uint32_t vfatN;
        uint32_t vfatMask;
        uint32_t chan;      //channel of interest

        //Params
        bool useUltra;
        bool useExtTrig;

        uint32_t dacMax;    //Maximum dac value
        uint32_t dacMin;    //Minimum dac value
        uint32_t dacSelect; //DAC to use for Monitoring
        uint32_t dacStep;   //step size for dac
        uint32_t nevts;     //Number of events
        uint32_t waitTime;  //unit of time; uints depend on function

        string scanReg;     //Register to scan against

        ParamScan(){
            useUltra = true;
            useExtTrig = false;

            dacMax=254;
            dacMin=0;
            dacStep=1;
            nevts=100;
        }
    }; //End ParamScan

    struct ParamCalPulse{
        bool enable; //true (false) turn on (off) calpulse
        bool isCurrent; //true (false) is current injection (voltage pulse)

        uint32_t duration; //duration in BX's (CFG_CAL_DUR)
        uint32_t extVoltStep; //External voltage step 0->disable; 1->enable (CFG_CAL_EXT)
        uint32_t height; //height of calpulse (CFG_CAL_DAC)
        uint32_t phase; //phase of calpulse (CFG_CAL_PHI)
        uint32_t polarity; //polarity of calpulse 0->pos; 1->neg (CFG_CAL_SEL_POL)
        uint32_t scaleFactor; //current pulse scale factor (CFG_CAL_FS)

        SetupCalPulse(){
            enable = false;
            isCurrent = false;

            duration = 0x1ff;
            extVoltStep = 0x0;
            height = 0x0;
            phase = 0x0;
            polarity = 0x0;
            scaleFactor = 0x0;
        }
    }; //End ParamCalPulse

    struct ParamTtcGen{
        bool enable;

        uint32_t L1Ainterval;
        uint32_t mode;
        uint32_t nPulses;
        uint32_t pulseDelay;
        uint32_t pulseRate;
        uint32_t type;

        ParamTtcGen(){
            enable = false;

            L1Ainterval = 250;
            pulseDelay = 40;
            pulseRate = 0;
        }
    }; //End ParamTtcGen

} //End namespace xhal
#endif
