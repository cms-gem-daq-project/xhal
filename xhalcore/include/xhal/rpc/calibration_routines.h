#ifndef CALIBRATION_ROUTINES_H
#define CALIBRATION_ROUTINES_H

#include "xhal/utils/CalParamTypes.h"
#include "xhal/utils/PyTypes.h"
#include "xhal/XHALInterface.h"

namespace xhal {
  namespace rpc {
    /**
    * @class CalRoutines
    * @brief Provides interface to call remote utility methods
    */
    class CalRoutines : public XHALInterface
    {
      public:
        /**
         * @brief Default constructor
         *
         * Loads the neccessary remote modules
         * @param board_domain_name domain name of CTP7
         */
        CalRoutines(const std::string& board_domain_name):xhal::XHALInterface(board_domain_name){
            m_map_modName_modVer["calibration_routines"]="calibration_routines v1.0.1";
            this->loadModule("calibration_routines", "calibration_routines v1.0.1");
        }

        ~CalRoutines(){}

        /**
         * @brief investigates the sbit mapping with the calpulse, can also be used to observe which channels send sbits when the calpulse is not used
         * @param scanParams an instance of xhal::ParamScan which specifies the scan parameters
         * @param calPulseParams an instance of xhal::ParamCalPulse which specifies the configuration of the calibration module
         * @param ttcGenParams an instance of xhal::ParamTtcGen which specifies the configuration of the CTP7 TTC Generator
         */
        PyListUint32 checkSbitMappingWithCalPulse(xhal::ParamScan &scanParams, xhal::ParamCalPulse &calPulseParams, xhal::ParamTtcGen &ttcGenParams);

        /**
         * @brief compares the sbit rate with a known pulse rate with the calpulse, can also be used to measure the sbit rate when the calpulse is not used
         * @param scanParams an instance of xhal::ParamScan which specifies the scan parameters
         * @param calPulseParams an instance of xhal::ParamCalPulse which specifies the configuration of the calibration module
         * @param ttcGenParams an instance of xhal::ParamTtcGen which specifies the configuration of the CTP7 TTC Generator
         */
        PyDictVecUint32<std::string> checkSbitRateWithCalPulse(xhal::ParamScan &scanParams, xhal::ParamCalPulse &calPulseParams, xhal::ParamTtcGen &ttcGenParams);

        /**
         * @brief Runs a generic scan routine for a specific channel of a VFAT chip
         * @param scanParams an instance of xhal::ParamScan which specifies the scan parameters
         * @param calPulseParams an instance of xhal::ParamCalPulse which specifies the configuration of the calibration module
         * @returns A PyListUint32 container holding the scan results
         */
        PyListUint32 genScan(xhal::ParamScan &scanParams, xhal::ParamCalPulse &calPulseParams);

        /**
         * @brief Runs a generic scan routine on all channels of a VFAT chip
         * @param scanParams an instance of xhal::ParamScan which specifies the scan parameters
         * @param calPulseParams an instance of xhal::ParamCalPulse which specifies the configuration of the calibration module
         * @returns A PyListUint32 container holding the scan results
         */
        PyListUint32 genChannelScan(xhal::ParamScan &scanParams, xhal::ParamCalPulse &calPulseParams);

        /**
         * @brief Measures sbit rate as a function of scanParams.scanReg and reports the trigger rate observed
         * @param scanParams an instance of xhal::ParamScan which specifies the scan parameters
         * @param invertVFATPos true (false) firmware uses software (hardware) numbering for VFAT position
         * @param isParallel true (false) run scan in parallel (series)
         * @returns A PyDictVecUint32<std::string> container with the keys {"DACVAL","CTP7Rate","VFATRate"} where each key maps to a value of PyListUint32 of all the same length and each element represents respectively the dac value, the rate measured by the CTP7, and the rate measured per VFAT.
         */
        PyDictVecUint32<std::string> sbitRateScan(xhal::ParamScan &scanParams, bool invertVFATPos=false, bool isParallel=true);

        /**
         * @brief configure TTC generator
         *
         * v3  electronics Behavior:
         *      pulseDelay (only for enable = true), delay between CalPulse and L1A
         *      L1Ainterval (only for enable = true), how often to repeat signals
         *      enable = true (false) ignore (take) ttc commands from backplane for this AMC (affects all links)
         * v2b electronics behavior:
         *      Configure the T1 controller
         *      mode: 0 (Single T1 signal),
         *            1 (CalPulse followed by L1A),
         *            2 (pattern)
         *      type (only for mode 0, type of T1 signal to send):
         *            0 L1A
         *            1 CalPulse
         *            2 Resync
         *            3 BC0
         *      pulseDelay (only for mode 1), delay between CalPulse and L1A
         *      L1Ainterval (only for mode 0,1), how often to repeat signals
         *      nPulses how many signals to send (0 is continuous)
         *      enable = true (false) start (stop) the T1Controller for link ohN
         *
         * @param ohN Optohybrid optical link number
         * @param ttcGenParams an instance of xhal::ParamTtcGen which specifies the configuration of the CTP7 TTC Generator
         */
        void ttcGenConf(uint32_t ohN, xhal::ParamTtcGen &ttcGenParams);

        /**
         * @brief Toggles TTC behavior
         *
         * v3  electronics: enable = true (false) ignore (take) ttc commands from backplane for this AMC
         * v2b electronics: enable = true (false) start (stop) the T1Controller for link ohN
         */
        void ttcGenToggle(uint32_t ohN, bool enable);
    };
  }
}
#endif
