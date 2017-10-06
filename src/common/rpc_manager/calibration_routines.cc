#include "xhal/rpc/calibration_routines.h"

/***
 * @brief configure TTC generator
 */
DLLEXPORT uint32_t ttcGenConf(uint32_t L1Ainterval, uint32_t pulseDelay)
{
    wisc::RPCSvc* rpc_loc = getRPCptr();
    //wisc::RPCMsg req_loc, rsp_loc;
    //req_loc = wisc::RPCMsg("calibration_routines.ttcGenConf");
    req = wisc::RPCMsg("calibration_routines.ttcGenConf");
    req.set_word("L1Ainterval", L1Ainterval);
    req.set_word("pulseDelay", pulseDelay);
    try {
        rsp = rpc_loc->call_method(req);
    }
    STANDARD_CATCH;

    if (rsp.get_key_exists("error")) {
        return 1;
    }
    return 0;
}

/***
 * @brief run a generic scan routine
 */
DLLEXPORT uint32_t genScan(uint32_t nevts, uint32_t ohN, uint32_t dacMin, uint32_t dacMax, uint32_t dacStep, uint32_t ch, uint32_t enCal, uint32_t mask, char * scanReg)
{
    req = wisc::RPCMsg("calibration_routines.genScan");

    req.set_word("nevts", nevts);
    req.set_word("ohN", ohN);
    req.set_word("dacMin", dacMin);
    req.set_word("dacMax", dacMax);
    req.set_word("dacStep", dacStep);
    req.set_word("ch", ch);
    req.set_word("enCal", enCal);
    req.set_word("mask", mask);
    req.set_string("scanReg", std::string(scanReg));

    //std::shared_ptr<wisc::RPCSvc> rpc_loc = getRPCptr();
    wisc::RPCSvc* rpc_loc = getRPCptr();

    try {
        rsp = rpc_loc->call_method(req);
    }
    STANDARD_CATCH;

    if (rsp.get_key_exists("error")) {
        printf("Caught an error: %s\n", (rsp.get_string("error")).c_str());
        return 1;
    }
    const uint32_t size = (dacMax - dacMin+1)*24/dacStep;
    uint32_t* result = new uint32_t[size];
    if (rsp.get_key_exists("data")) {
        ASSERT(rsp.get_word_array_size("data") == size);
        rsp.get_word_array("data", result); 
    } else {
        printf("No data key found");
        return 1;
    } 
    FILE *f = fopen("file.txt", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(f, "vfatN/I:nEvents/I:dacVal/I:nHits/I\n");
    uint32_t vfatSize = (dacMax-dacMin+1)/dacStep;
    for (unsigned int i = 0; i<24; i++)
    {
        for (unsigned int j = 0; j<vfatSize; j++)
        {
            fprintf(f,"%d    %d    %d    %d\n",i,result[i*vfatSize+j]&0xFFFF,dacMin+j*dacStep,(result[i*vfatSize+j]>>16)&0xFFFF);
        } 
    }
    return 0;
}
