#include "errno.h" //See: http://www.virtsync.com/c-error-codes-include-errno
#include <fstream>
#include <string>
#include <vector>
#include "xhal/rpc/amc.h"

xhal::rpc::AMC3::AMC3(const std::string& board_domain_name, const std::string& address_table_filename):
  xhal::XHALDevice(board_domain_name, address_table_filename)
{
  this->loadModule("amc","amc v1.0.1");
}

uint32_t xhal::rpc::AMC::getOHVFATMask(uint32_t ohN){
    req = wisc::RPCMsg("amc.getOHVFATMask");

    req.set_word("ohN",ohN);

    try {
        rsp = rpc.call_method(req);
    }
    STANDARD_CATCH;

    if (rsp.get_key_exists("error")) {
        printf("Caught an error: %s\n", (rsp.get_string("error")).c_str());
        return 0xffffffff;
    }

    return rsp.get_word("vfatMask");
} //End getOHVFATMask(...)

uint32_t xhal::rpc::AMC::getOHVFATMaskMultiLink(uint32_t ohMask, uint32_t * ohVfatMaskArray){
    req = wisc::RPCMsg("amc.getOHVFATMaskMultiLink");

    req.set_word("ohMask", ohMask);

    try {
        rsp = rpc.call_method(req);
    }
    STANDARD_CATCH;

    if (rsp.get_key_exists("error")) {
        printf("Caught an error: %s\n", (rsp.get_string("error")).c_str());
        return 1;
    }
    const uint32_t size = 12;
    if (rsp.get_key_exists("ohVfatMaskArray")) {
        ASSERT(rsp.get_word_array_size("ohVfatMaskArray") == size);
        rsp.get_word_array("ohVfatMaskArray", ohVfatMaskArray);
    } else {
        printf("No ohVfatMaskArray key found");
        return 1;
    }

    return 0;
} //End getOHVFATMaskMultiLink(...)

uint32_t xhal::rpc::AMC::sbitReadOut(uint32_t ohN, uint32_t acquireTime, char * outFilePath){
    req = wisc::RPCMsg("amc.sbitReadOut");

    req.set_word("ohN",ohN);
    req.set_word("acquireTime",acquireTime);

    uint32_t netTime = 0;
    int runNum = 1;

    //Acquire data
    printf("sbitReadOut(): Beginning acquisition of trigger data\n");
    while(netTime < acquireTime){ //Acquisition Loop
        printf("sbitReadOut(): acquired data for %i seconds of requested %i seconds, data taking continues\n", netTime, acquireTime);

        //Open output file for this acquisition
        std::string strFileName(outFilePath);
        strFileName = strFileName+"/sbitReadOut_run"+std::to_string(runNum)+".dat";
        std::fstream fileTrigData;
        fileTrigData.open(strFileName, std::ios::out);
        if (!fileTrigData.is_open()){
            printf("sbitReadOut(): Error while trying to open file %s\n",outFilePath);
            printf("sbitReadOut(): Perhaps you do not have write permissions or the filepath does not exist?\n");
            printf("sbitReadOut(): Exiting\n");
            return EIO;
        }

        //Call RPC Method
        try {
            rsp = rpc.call_method(req);
        }
        STANDARD_CATCH;

        //Check for RPC Error
        if (rsp.get_key_exists("error")) {
            printf("sbitReadOut(): Caught an error: %s\n", (rsp.get_string("error")).c_str());
            fileTrigData.close();
            return 1;
        }

        //If max network size reached before acquireTime was reached
        //increment netTime and we will take more data in the next loop
        if(rsp.get_key_exists("maxNetworkSizeReached")){
            netTime += rsp.get_word("approxLiveTime");
        }
        else{
            netTime += acquireTime;
        }

        //Write data to file
        std::vector<uint32_t> vec_sbitData;
        if (rsp.get_key_exists("storedSbits")) {
            vec_sbitData = rsp.get_word_array("storedSbits");
        } else {
            printf("sbitReadOut(): No sbit data found");
            return 1;
        }

        fileTrigData<<"evtNum/i:";
        for(int cluster=0; cluster < 8; ++cluster){
            fileTrigData<<"sbitClusterData" << cluster << "/i:";
        }
        fileTrigData<<std::endl;

        uint32_t sbitPos = 1;
        uint32_t evtNum = 0;
        for(auto iterSBIT = vec_sbitData.begin(); iterSBIT != vec_sbitData.end(); ++iterSBIT){ //Loop over stored sbits
            if(iterSBIT == vec_sbitData.begin()){
                fileTrigData << evtNum << "\t" << (*iterSBIT) << "\t";
                evtNum++;
            }
            else{
                if( 0 == (sbitPos % 8)){ //Last cluster of current event
                    fileTrigData << (*iterSBIT) << "\n";
                }
                else if( 1 == (sbitPos % 8)){ //New Event
                    fileTrigData << evtNum << "\t" << (*iterSBIT) << "\t";
                    evtNum++;
                }
                else{ //2nd through 7th cluster of current evet
                    fileTrigData << (*iterSBIT) << "\t";
                }
            }
            sbitPos++;
        } //End loop over stored sbits
        fileTrigData.close();

        runNum++;
    } //End Acquisition Loop

    return 0;
} //End sbitReadOut(...)
