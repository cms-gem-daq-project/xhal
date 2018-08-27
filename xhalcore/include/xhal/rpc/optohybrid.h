#ifndef OPTOHYBRID_H
#define OPTOHYBRID_H

#include <string>
#include "xhal/utils/CalParamTypes.h"
#include "xhal/utils/PyTypes.h"
#include "xhal/XHALDevice.h"

namespace xhal {
  namespace rpc {
    class Optohybrid : public xhal::XHALDevice {
      public:
      /**
       * @brief Default constructor
       *
       * Parses XML file and loads required modules
       * @param board_domain_name domain name of CTP7
       * @param address_table_filename XML address table file name
       */
      Optohybrid(const std::string& board_domain_name, const std::string& address_table_filename);

      //FIXME provide documentation
      PyListUint32 broadcastRead(uint32_t ohN, std::string &regName, uint32_t vfatMask);
      void broadcastWrite(uint32_t ohN, std::string &regName, uint32_t value, uint32_t vfatMask);
      void configureScanModule(xhal::ParamScan &scanParams, uint32_t scanmode);
      void printScanConfiguration(uint32_t ohN, bool useUltra);
      void startScanModule(uint32_t ohN, bool useUltra);
      PyListUint32 getUltraScanResults(xhal::ParamScan &scanParams);
      void stopCalPulse2AllChannels(uint32_t ohN, uint32_t mask, uint32_t ch_min, uint32_t ch_max);
    };//end class Optohybrid
  }//end namespace rpc
}//end namespace xhal

#endif
