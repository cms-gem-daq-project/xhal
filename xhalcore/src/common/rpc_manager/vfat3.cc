#include <array>
#include "xhal/rpc/vfat3.h"

/***
 * @brief load configuration parameters to VFAT3 chips
 */
DLLEXPORT uint32_t configureVFAT3s(uint32_t ohN, uint32_t vfatMask)
{
    req = wisc::RPCMsg("vfat3.configureVFAT3s");

    req.set_word("vfatMask",vfatMask);
    req.set_word("ohN",ohN);
    wisc::RPCSvc* rpc_loc = getRPCptr();

    try {
        rsp = rpc_loc->call_method(req);
    }
    STANDARD_CATCH;

    if (rsp.get_key_exists("error")) {
        printf("Caught an error: %s\n", (rsp.get_string("error")).c_str());
        return 1;
    }
    return 0;
}

DLLEXPORT uint32_t getChannelRegistersVFAT3(uint32_t ohN, uint32_t vfatMask, uint32_t *chanRegData){
    req = wisc::RPCMsg("vfat3.getChannelRegistersVFAT3");

    req.set_word("ohN",ohN);
    req.set_word("vfatMask",vfatMask);

    wisc::RPCSvc* rpc_loc = getRPCptr();

    try {
        rsp = rpc_loc->call_method(req);
    }
    STANDARD_CATCH;

    if (rsp.get_key_exists("error")) {
        printf("Caught an error: %s\n", (rsp.get_string("error")).c_str());
        return 1;
    }

    const uint32_t size = 3072;
    if (rsp.get_key_exists("chanRegData")) {
        ASSERT(rsp.get_word_array_size("chanRegData") == size);
        rsp.get_word_array("chanRegData", chanRegData);
    } else {
        printf("No channel register data found");
        return 1;
    }

    return 0;
}

DLLEXPORT uint32_t setChannelRegistersVFAT3(uint32_t ohN, uint32_t vfatMask, uint32_t *calEnable, uint32_t *masks, uint32_t *trimARM, uint32_t *trimARMPol, uint32_t *trimZCC, uint32_t *trimZCCPol){
    req = wisc::RPCMsg("vfat3.setChannelRegistersVFAT3");

    req.set_word("ohN",ohN);
    req.set_word("vfatMask",vfatMask);

    req.set_word_array("calEnable",calEnable,3072);
    req.set_word_array("masks",masks,3072);
    req.set_word_array("trimARM",trimARM,3072);
    req.set_word_array("trimARMPol",trimARMPol,3072);
    req.set_word_array("trimZCC",trimZCC,3072);
    req.set_word_array("trimZCCPol",trimZCCPol,3072);

    wisc::RPCSvc* rpc_loc = getRPCptr();

    try {
        rsp = rpc_loc->call_method(req);
    }
    STANDARD_CATCH;

    if (rsp.get_key_exists("error")) {
        printf("Caught an error: %s\n", (rsp.get_string("error")).c_str());
        return 1;
    }
    return 0;
}


DLLEXPORT uint32_t setChannelRegistersVFAT3Simple(uint32_t ohN, uint32_t vfatMask, uint32_t *chanRegData){
    req = wisc::RPCMsg("vfat3.setChannelRegistersVFAT3");

    req.set_word("ohN",ohN);
    req.set_word("vfatMask",vfatMask);
    req.set_word("simple",true);

    req.set_word_array("chanRegData",chanRegData,3072);

    wisc::RPCSvc* rpc_loc = getRPCptr();

    try {
        rsp = rpc_loc->call_method(req);
    }
    STANDARD_CATCH;

    if (rsp.get_key_exists("error")) {
        printf("Caught an error: %s\n", (rsp.get_string("error")).c_str());
        return 1;
    }
    return 0;
}
