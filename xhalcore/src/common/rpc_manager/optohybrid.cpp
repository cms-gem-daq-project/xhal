#include "xhal/rpc/optohybrid.h"

xhal::rpc::Optohybrid::Optohybrid(const std::string& board_domain_name, const std::string& address_table_filename):
  xhal::XHALDevice(board_domain_name, address_table_filename)
{
  m_map_modName_modVer["optohybrid"]="optohybrid v1.0.1";
  this->loadModule("optohybrid","optohybrid v1.0.1");
}

PyListUint32 xhal::rpc::Optohybrid::broadcastRead(uint32_t ohN, std::string &regName, uint32_t vfatMask)
{
    /* User supplies the VFAT node name as reg_name, examples:
     *
     *    v2b electronics: reg_name = "VThreshold1" to get VT1
     *    v3 electronics: reg_name = "CFG_THR_ARM_DAC"
     *
     *    Supplying only a substr of VFAT Node name will crash
     */

    req = wisc::RPCMsg("optohybrid.broadcastRead");

    req.set_string("reg_name",regName);
    req.set_word("ohN",ohN);
    req.set_word("mask",vfatMask);

    try {
        rsp = rpc.call_method(req);
    }
    STANDARD_CATCH;

    PyListUint32 data;
    if (rsp.get_key_exists("error")) {
        throw xhal::utils::XHALRPCException(strcat("RPC exception: ", rsp.get_string("error").c_str()));
    }
    else if (rsp.get_key_exists("data")) {
        data = rsp.get_word_array("data");
    } else {
        throw xhal::utils::XHALRPCException("RPC exception: no data found from broadcast read");
    }

    return data;
} //End broadcastRead

void xhal::rpc::Optohybrid::broadcastWrite(uint32_t ohN, std::string &regName, uint32_t value, uint32_t vfatMask)
{
    /* User supplies the VFAT node name as reg_name, examples:
     *
     *    v2b electronics: reg_name = "VThreshold1" to get VT1
     *    v3 electronics: reg_name = "CFG_THR_ARM_DAC"
     *
     *    Supplying only a substr of VFAT Node name will crash
     */

    req = wisc::RPCMsg("optohybrid.broadcastWrite");

    req.set_string("reg_name",regName);
    req.set_word("ohN",ohN);
    req.set_word("value",value);
    req.set_word("mask",vfatMask);

    try {
        rsp = rpc.call_method(req);
    }
    STANDARD_CATCH;

    if (rsp.get_key_exists("error")) {
        throw xhal::utils::XHALRPCException(strcat("RPC exception: ", rsp.get_string("error").c_str()));
    }

    return;
}

void xhal::rpc::Optohybrid::configureScanModule(xhal::ParamScan &scanParams, uint32_t scanmode)
{
    req = wisc::RPCMsg("optohybrid.configureScanModule");

    req.set_word("ohN",scanParams.ohN);
    req.set_word("scanmode",scanmode);
    if (scanParams.useUltra){
        req.set_word("useUltra",scanParams.useUltra);
        req.set_word("mask",scanParams.vfatMask);
    }
    else{
        req.set_word("vfatN",scanParams.vfatN);
    }
    req.set_word("ch",scanParams.chan); //channel
    req.set_word("nevts",scanParams.nevts);
    req.set_word("dacMin",scanParams.dacMin);
    req.set_word("dacMax",scanParams.dacMax);
    req.set_word("dacStep",scanParams.dacStep);

    try {
        rsp = rpc.call_method(req);
    }
    STANDARD_CATCH;

    if (rsp.get_key_exists("error")) {
        throw xhal::utils::XHALRPCException(strcat("RPC exception: ", rsp.get_string("error").c_str()));
    }

    return;
} //End configureScanModule(...)

void xhal::rpc::Optohybrid::printScanConfiguration(uint32_t ohN, bool useUltra)
{
    req = wisc::RPCMsg("optohybrid.printScanConfiguration");

    req.set_word("ohN",ohN);
    if (useUltra){
        req.set_word("useUltra",useUltra);
    }

    try {
        rsp = rpc.call_method(req);
    }
    STANDARD_CATCH;

    if (rsp.get_key_exists("error")) {
        throw xhal::utils::XHALRPCException(strcat("RPC exception: ", rsp.get_string("error").c_str()));
    }

    return;
} //End printScanConfiguration(...)

void xhal::rpc::Optohybrid::startScanModule(uint32_t ohN, bool useUltra)
{
    req = wisc::RPCMsg("optohybrid.startScanModule");

    req.set_word("ohN",ohN);
    if (useUltra){
        req.set_word("useUltra",useUltra);
    }

    try {
        rsp = rpc.call_method(req);
    }
    STANDARD_CATCH;

    if (rsp.get_key_exists("error")) {
        throw xhal::utils::XHALRPCException(strcat("RPC exception: ", rsp.get_string("error").c_str()));
    }

    return;
} //End startScanModule(...)

PyListUint32 xhal::rpc::Optohybrid::getUltraScanResults(xhal::ParamScan &scanParams)
{
    req = wisc::RPCMsg("optohybrid.getUltraScanResults");

    req.set_word("ohN",scanParams.ohN);
    req.set_word("nevts",scanParams.nevts);
    req.set_word("dacMin",scanParams.dacMin);
    req.set_word("dacMax",scanParams.dacMax);
    req.set_word("dacStep",scanParams.dacStep);

    try {
        rsp = rpc.call_method(req);
    }
    STANDARD_CATCH;

    if (rsp.get_key_exists("error")) {
        throw xhal::utils::XHALRPCException(strcat("RPC exception: ", rsp.get_string("error").c_str()));
    }

    PyListUint32 data;
    if (rsp.get_key_exists("data")) {
        data = rsp.get_word_array("data");
    } else {
        throw xhal::utils::XHALRPCException("RPC exception: no data found in ultra scan results");
    }

    return data;
} //End getUltraScanResults(...)

void xhal::rpc::Optohybrid::stopCalPulse2AllChannels(uint32_t ohN, uint32_t mask, uint32_t ch_min, uint32_t ch_max)
{
    req = wisc::RPCMsg("optohybrid.stopCalPulse2AllChannels");

    req.set_word("ohN",ohN);
    req.set_word("mask",mask);
    req.set_word("ch_min",ch_min);
    req.set_word("ch_max",ch_max);

    try {
        rsp = rpc.call_method(req);
    }
    STANDARD_CATCH;

    if (rsp.get_key_exists("error")) {
        throw xhal::utils::XHALRPCException(strcat("RPC exception: ", rsp.get_string("error").c_str()));
    }

    return;
}
