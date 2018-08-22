#ifndef AMC_H
#define AMC_H

#include "xhal/rpc/utils.h"

/*! \fn DLLEXPORT uint32_t sbitReadOut(uint32_t ohN, uint32_t acquireTime, uint32_t * approxLiveTime, bool * maxNetworkSizeReached, uint32_t * storedSbits)
 *  \brief SBIT readout from optohybrid ohN for a number of seconds given by acquireTime; data is written to a file directory specified by outFilePath
 *  \param ohN Optohybrid optical link number
 *  \param acquireTime acquisition time on the wall clock in seconds
 */
DLLEXPORT uint32_t sbitReadOut(uint32_t ohN, uint32_t acquireTime, char * outFilePath);

#endif
