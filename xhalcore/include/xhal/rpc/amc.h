#ifndef AMC_H
#define AMC_H

#include "xhal/XHALDevice.h"

namespace xhal {
    namespace rpc {
        class AMC : public xhal::XHALDevice {
            public:
                /**
                 * @brief Default constructor
                 *
                 * Parses XML file and loads required modules
                 * @param board_domain_name domain name of CTP7
                 * @param address_table_filename XML address table file name
                 */
                AMC(const std::string& board_domain_name, const std::string& address_table_filename);

                /**
                 *  @brief Determines the vfatMask for optohybrid ohN.
                 *  @details Reads the SYNC_ERR_CNT counter for each VFAT on ohN.  If for a given VFAT the counter returns a non-zero value the given VFAT will be masked.
                 *  @param ohN Optohybrid optical link number
                 *  @returns uint32_t where bits [23:0] represent the vfat mask.  If the "error" key exists in the RPC response returns instead overflow (0xFFFFFFFF)
                 */
                uint32_t getOHVFATMask(uint32_t ohN);

                /**
                 *  @brief As getOHVFATMask(...) but for all optohybrids specified in ohMask
                 *  @param ohMask A 12 bit number which specifies which optohybrids to read from.  Having a value of 1 in the n^th bit indicates that the n^th optohybrid should be considered.
                 *  @param ohVfatMaskArray Pointer to an array of length 12.  After the call completes each element will be the bitmask of chip positions determining which chips to use for the optohybrid number corresponding to the element index.
                 */
                uint32_t getOHVFATMaskMultiLink(uint32_t ohMask, uint32_t * ohVfatMaskArray);

                /**
                 *  @brief SBIT readout from optohybrid ohN for a number of seconds given by acquireTime; data is written to a file directory specified by outFilePath
                 *  @param ohN Optohybrid optical link number
                 *  @param acquireTime acquisition time on the wall clock in seconds
                 *  @return An integer from the set {0, 1, EIO}; where 0 indicates successful completion, 1 indicates an RPC error, and EIO is a platform dependent error code representing a file IO error
                 */
                uint32_t sbitReadOut(uint32_t ohN, uint32_t acquireTime, char * outFilePath);
        } //End class AMC
    } //End namespace rpc
} //End namespace xhal

#endif
