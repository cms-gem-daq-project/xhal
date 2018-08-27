#ifndef VFAT3_H
#define VFAT3_H

#include "xhal/XHALDevice.h"
#include "xhal/utils/PyTypes.h"

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
      void configureVFAT3s(uint32_t ohN, uint32_t vfatMask);

       /**
        *  @brief configures all unmasked VFATs on ohN for ADC Monitoring of the DAC specified by dacSelect.  See the VFAT3 manual for possible values of dacSelect.
        *  @param ohN Optohybrid optical link number
        *  @param vfatMask Bitmask of chip positions determining which chips to use
        *  @param dacSelect the monitoring selection for the VFAT3 ADC, possible values are [0,16] and [32,41].  See VFAT3 manual for details
        */
      void configureVFAT3DacMonitor(uint32_t ohN, uint32_t vfatMask, uint32_t dacSelect);

      /**
       *  @brief configures all unmasked VFATs on ohN for ADC Monitoring of the DAC specified by dacSelect.  See the VFAT3 manual for possible values of dacSelect.
       *  @param ohMask A 12 bit number which specifies which optohybrids to read from.  Having a value of 1 in the n^th bit indicates that the n^th optohybrid should be considered.
       *  @param ohVfatMaskArray PyListUint32 of size 12.  Each element is the bitmask of chip positions determining which chips to use for the optohybrid number corresponding to the element index.
       *  @param dacSelect the monitoring selection for the VFAT3 ADC, possible values are [0,16] and [32,41].  See VFAT3 manual for details
       */
      void configureVFAT3DacMonitorMultiLink(uint32_t ohMask, PyListUint32 &ohVfatMaskArray, uint32_t dacSelect);

      /**
       *  @brief reads channel registers of all unmasked vfats on ohN
       *  @param ohN Optohybrid optical link number
       *  @param vfatMask Bitmask of chip positions determining which chips to use
       *  @returns A PyListUint32 of size 3072 containing channel register data, the (vfat,chan) pairing determines the index via: idx = vfat*128 + chan
       */
      PyListUint32 getChannelRegistersVFAT3(uint32_t ohN, uint32_t vfatMast);

      /**
       *  @brief Reads the ADC value from all unmasked VFATs
       *  @param ohN Optohybrid optical link number
       *  @param useExtRefADC true (false) read the ADC1 (ADC0) which uses an external (internal) reference
       *  @param vfatMask Bitmask of chip positions determining which chips to use
       *  @returns PyListUint32 of size 24 containing the ADC results
       */
      PyListUint32 readVFAT3ADC(uint32_t ohN, bool useExtRefADC=false, uint32_t vfatMask=0xFF000000);

      /**
       *  @brief As readVFAT3ADC(...) but for all optical links specified in ohMask on the AMC
       *  @param ohMask A 12 bit number which specifies which optohybrids to read from.  Having a value of 1 in the n^th bit indicates that the n^th optohybrid should be considered.
       *  @param ohVfatMaskArray PyListUint32 of size 12.  Each element is the bitmask of chip positions determining which chips to use for the optohybrid number corresponding to the element index.
       *  @param useExtRefADC true (false) read the ADC1 (ADC0) which uses an external (internal) reference
       *  @returns PyListUint32 of size 12*24=288 containing the ADC results
       */
      PyListUint32 readVFAT3ADCMultiLink(uint32_t ohMask, PyListUint32 &ohVfatMaskArray, bool useExtRefADC=false);

      /**
       *  @brief sets all vfat3 channel registers
       *  @param ohN Optohybrid optical link number
       *  @param vfatMask Bitmask of chip positions determining which chips to use
       *  @param calEnable PyListUint32 for calEnable with 3072 entries, the (vfat,chan) pairing determines the index via: idx = vfat*128 + chan
       *  @param masks as calEnable but for channel masks
       *  @param trimARM as calEnable but for arming comparator trim value
       *  @param trimARMPol as calEnable but for arming comparator trim polarity
       *  @param trimZCC as calEnable but for zero crossing comparator trim value
       *  @param trimZCCPol as calEnable but for zero crossing comparator trim polarity
       */
      void setChannelRegistersVFAT3(uint32_t ohN, uint32_t vfatMask, PyListUint32 &calEnable, PyListUint32 &masks, PyListUint32 &trimARM, PyListUint32 &trimARMPol, PyListUint32 &trimZCC, PyListUint32 &trimZCCPol);

      /**
       *  @brief sets all vfat3 channel registers using a single channel register array
       *  @param ohN Optohybrid optical link number
       *  @param vfatMask Bitmask of chip positions determining which chips to use
       *  @param chanRegData PyListUint32 of size 3072 containing channel register data, the (vfat,chan) pairing determines the index via: idx = vfat*128 + chan
       */
      void setChannelRegistersVFAT3Simple(uint32_t ohN, uint32_t vfatMask, PyListUint32 &chanRegData);
    };//end class VFAT3
  }//end namespace rpc
}//end namespace xhal

#endif
