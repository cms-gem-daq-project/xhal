#ifndef VFAT3_H
#define VFAT3_H

#include "xhal/XHALDevice.h"

namespace xhal {
  namespace rpc {
    class VFAT3 : public xhal::XHALDevice {
      public:
      /**
       * @brief Default constructor
       *
       * Parses XML file and loads required modules
       * @param board_domain_name domain name of CTP7
       * @param address_table_filename XML address table file name
       */
      VFAT3(const std::string& board_domain_name, const std::string& address_table_filename);

      //FIXME provide docs
      /**
       * @brief load configuration parameters to VFAT3 chips
       */
      uint32_t configureVFAT3s(uint32_t ohN, uint32_t vfatMask);

       /**
        *  @brief configures all unmasked VFATs on ohN for ADC Monitoring of the DAC specified by dacSelect.  See the VFAT3 manual for possible values of dacSelect.
        *  @param ohN Optohybrid optical link number
        *  @param vfatMask Bitmask of chip positions determining which chips to use
        *  @param dacSelect the monitoring selection for the VFAT3 ADC, possible values are [0,16] and [32,41].  See VFAT3 manual for details
        */
      uint32_t configureVFAT3DacMonitor(uint32_t ohN, uint32_t vfatMask, uint32_t dacSelect);

      /**
       *  @brief configures all unmasked VFATs on ohN for ADC Monitoring of the DAC specified by dacSelect.  See the VFAT3 manual for possible values of dacSelect.
       *  @param ohMask A 12 bit number which specifies which optohybrids to read from.  Having a value of 1 in the n^th bit indicates that the n^th optohybrid should be considered.
       *  @param ohVfatMaskArray Pointer to an array of length 12.  Each element is the bitmask of chip positions determining which chips to use for the optohybrid number corresponding to the element index.
       *  @param dacSelect the monitoring selection for the VFAT3 ADC, possible values are [0,16] and [32,41].  See VFAT3 manual for details
       */
      uint32_t configureVFAT3DacMonitorMultiLink(uint32_t ohMask, uint32_t *ohVfatMaskArray, uint32_t dacSelect);

      /**
       *  @brief reads channel registers of all unmasked vfats on ohN
       *  @param ohN Optohybrid optical link number
       *  @param vfatMask Bitmask of chip positions determining which chips to use
       *  @param chanRegData array pointer for channel register data with 3072 entries, the (vfat,chan) pairing determines the array index via: idx = vfat*128 + chan
       */
      uint32_t getChannelRegistersVFAT3(uint32_t ohN, uint32_t vfatMask, uint32_t *chanRegData);

      /**
       *  @brief Reads the ADC value from all unmasked VFATs
       *  @param adcData pointer to the array containing the ADC results; length of array is expected to be 24
       *  @param ohN Optohybrid optical link number
       *  @param useExtRefADC true (false) read the ADC1 (ADC0) which uses an external (internal) reference
       *  @param vfatMask Bitmask of chip positions determining which chips to use
       */
      uint32_t readVFAT3ADC(uint32_t ohN, uint32_t *adcData, bool useExtRefADC=false, uint32_t vfatMask=0xFF000000);

      /**
       *  @brief As readVFAT3ADC(...) but for all optical links specified in ohMask on the AMC
       *  @param ohMask A 12 bit number which specifies which optohybrids to read from.  Having a value of 1 in the n^th bit indicates that the n^th optohybrid should be considered.
       *  @param ohVfatMaskArray Pointer to an array of length 12.  Each element is the bitmask of chip positions determining which chips to use for the optohybrid number corresponding to the element index.
       *  @param adcDataAll pointer to the array containing the ADC results; length of array is expected to be 12*24=288
       *  @param useExtRefADC true (false) read the ADC1 (ADC0) which uses an external (internal) reference
       */
      uint32_t readVFAT3ADCMultiLink(uint32_t ohMask, uint32_t *ohVfatMaskArray, uint32_t *adcDataAll, bool useExtRefADC=false);

      /**
       *  @brief sets all vfat3 channel registers
       *  @param ohN Optohybrid optical link number
       *  @param vfatMask Bitmask of chip positions determining which chips to use
       *  @param calEnable array pointer for calEnable with 3072 entries, the (vfat,chan) pairing determines the array index via: idx = vfat*128 + chan
       *  @param masks as calEnable but for channel masks
       *  @param trimARM as calEnable but for arming comparator trim value
       *  @param trimARMPol as calEnable but for arming comparator trim polarity
       *  @param trimZCC as calEnable but for zero crossing comparator trim value
       *  @param trimZCCPol as calEnable but for zero crossing comparator trim polarity
       */
      uint32_t setChannelRegistersVFAT3(uint32_t ohN, uint32_t vfatMask, uint32_t *calEnable, uint32_t *masks, uint32_t *trimARM, uint32_t *trimARMPol, uint32_t *trimZCC, uint32_t *trimZCCPol);

      /**
       *  @brief sets all vfat3 channel registers using a single channel register array
       *  @param ohN Optohybrid optical link number
       *  @param vfatMask Bitmask of chip positions determining which chips to use
       *  @param chanRegData array pointer for channel register data with 3072 entries, the (vfat,chan) pairing determines the array index via: idx = vfat*128 + chan
       */
      uint32_t setChannelRegistersVFAT3Simple(uint32_t ohN, uint32_t vfatMask, uint32_t *chanRegData);
    };//end class VFAT3
  }//end namespace rpc
}//end namespace xhal

#endif
