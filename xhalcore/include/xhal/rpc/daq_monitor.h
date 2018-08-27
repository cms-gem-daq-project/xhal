#ifndef DAQ_MONITOR_H
#define DAQ_MONITOR_H

#include "xhal/XHALInterface.h"
#include "xhal/utils/PyTypes.h"

namespace xhal {
  namespace rpc {
    /**
    * @class DaqMonitor
    * @brief Provides interface to call remote utility methods
    */
    class DaqMonitor : public XHALInterface
    {
      public:
        /**
         * @brief Default constructor
         *
         * Loads the neccessary remote modules
         * @param board_domain_name domain name of CTP7
         */
        DaqMonitor(const std::string& board_domain_name):xhal::XHALInterface(board_domain_name){this->loadModule("amc", "amc v1.0.1");}

        ~DaqMonitor(){}

        /**
         * @brief get an array of values for TTC main monitoring table
         *
         * @return an array of monitoring values
         */
        //uint32_t getmonTTCmain(uint32_t* result);
        PyListUint32 getmonTTCmain();

        /**
         * @brief get an array of values for TRIGGER main monitoring table
         *
         * @param noh Number of expected optical links, default value 12
         * @return an array of monitoring values
         */
        PyListUint32 getmonTRIGGERmain(uint32_t noh = 12);

        /**
         * @brief get an array of values for TRIGGER OH main monitoring table
         *
         * @param noh Number of expected optical links, default value 12
         * @return an array of monitoring values
         */
        PyListUint32 getmonTRIGGEROHmain(uint32_t noh = 12);

        /**
         * @brief get an array of values for DAQ main monitoring table
         *
         * @return an array of monitoring values
         */
        PyListUint32 getmonDAQmain();

        /**
         * @brief get an array of values for DAQ OH main monitoring table
         *
         * @param noh Number of expected optical links, default value 12
         * @return an array of monitoring values
         */
        PyListUint32 getmonDAQOHmain(uint32_t noh = 12);

        /**
         * @brief get an array of values for OH main monitoring table
         *
         * @param noh Number of expected optical links, default value 12
         * @return an array of monitoring values
         */
        PyListUint32 getmonOHmain(uint32_t noh = 12);

        /**
         * @brief get an array of values for OH SCA monitoring table
         *
         * @param noh Number of expected optical links, default value 12
         * @param ohMask A 12 bit number which specifies which optohybrids to read from.  Having a value of 1 in the n^th bit indicates that the n^th optohybrid should be considered.
         * @return a nested map of monitoring values, outer key is ohN, value is a PyDictUint32<std::string> which maps register to value
         */
        NestedPyDict<int,PyDictUint32<std::string> > getmonOHSCAmain(uint32_t noh = 12, uint32_t ohMask = 0xfff);
    };
  }
}

#endif
