#include <array>
#include <cstring>
#include <stdexcept>
#include <string>
#include "xhal/rpc/vfat3.h"

xhal::rpc::VFAT3::VFAT3(const std::string& board_domain_name, const std::string& address_table_filename):
  xhal::XHALDevice(board_domain_name, address_table_filename)
{
  m_map_modName_modVer["vfat3"]="vfat3 v1.0.1";
  this->loadModule("vfat3","vfat3 v1.0.1");
}

void xhal::rpc::VFAT3::configureVFAT3s(uint32_t ohN, uint32_t vfatMask)
{
    req = wisc::RPCMsg("vfat3.configureVFAT3s");
    req.set_word("vfatMask",vfatMask);
    req.set_word("ohN",ohN);

    try {
        rsp = rpc.call_method(req);
    }
    STANDARD_CATCH;

    if (rsp.get_key_exists("error")) {
        throw xhal::utils::XHALRPCException(strcat("RPC exception: ", rsp.get_string("error").c_str()));
    }
    return;
}

void xhal::rpc::VFAT3::configureVFAT3DacMonitor(uint32_t ohN, uint32_t vfatMask, uint32_t dacSelect){
    req = wisc::RPCMsg("vfat3.configureVFAT3DacMonitor");

    req.set_word("ohN",ohN);
    req.set_word("vfatMask",vfatMask);
    req.set_word("dacSelect",dacSelect);

    try {
        rsp = rpc.call_method(req);
    }
    STANDARD_CATCH;

    if (rsp.get_key_exists("error")) {
        throw xhal::utils::XHALRPCException(strcat("RPC exception: ", rsp.get_string("error").c_str()));
    }
    return;
} //End configureVFAT3DacMonitor(...)

void xhal::rpc::VFAT3::configureVFAT3DacMonitorMultiLink(uint32_t ohMask, PyListUint32 &ohVfatMaskArray, uint32_t dacSelect){
    req = wisc::RPCMsg("vfat3.configureVFAT3DacMonitorMultiLink");

    if(ohVfatMaskArray.size() != 12){
        throw std::length_error("ohVfatMaskArray size is " + std::to_string(ohVfatMaskArray.size()) + " but expected to be 12");
    }

    req.set_word("ohMask",ohMask);
    req.set_word_array("ohVfatMaskArray",ohVfatMaskArray);
    req.set_word("dacSelect",dacSelect);

    try {
        rsp = rpc.call_method(req);
    }
    STANDARD_CATCH;

    if (rsp.get_key_exists("error")) {
        throw xhal::utils::XHALRPCException(strcat("RPC exception: ", rsp.get_string("error").c_str()));
    }
    return;
} //End configureVFAT3DacMonitor(...)

PyListUint32 xhal::rpc::VFAT3::getChannelRegistersVFAT3(uint32_t ohN, uint32_t vfatMask)
{
    req = wisc::RPCMsg("vfat3.getChannelRegistersVFAT3");
    req.set_word("ohN",ohN);
    req.set_word("vfatMask",vfatMask);

    try {
        rsp = rpc.call_method(req);
    }
    STANDARD_CATCH;

    if (rsp.get_key_exists("error")) {
        throw xhal::utils::XHALRPCException(strcat("RPC exception: ", rsp.get_string("error").c_str()));
    }

    PyListUint32 chanRegData;
    if (rsp.get_key_exists("chanRegData")) {
        chanRegData = rsp.get_word_array("chanRegData");
    } else {
        throw xhal::utils::XHALRPCException("RPC exception: no channel register data found");
    }

    return chanRegData;
}

PyListUint32 xhal::rpc::VFAT3::readVFAT3ADC(uint32_t ohN, bool useExtRefADC, uint32_t vfatMask){
    req = wisc::RPCMsg("vfat3.readVFAT3ADC");

    req.set_word("ohN",ohN);
    req.set_word("useExtRefADC", useExtRefADC);
    req.set_word("vfatMask",vfatMask);

    try {
        rsp = rpc.call_method(req);
    }
    STANDARD_CATCH;

    if (rsp.get_key_exists("error")) {
        throw xhal::utils::XHALRPCException(strcat("RPC exception: ", rsp.get_string("error").c_str()));
    }

    PyListUint32 adcData;
    if (rsp.get_key_exists("adcData")) {
        adcData = rsp.get_word_array("adcData");
    } else {
        throw xhal::utils::XHALRPCException("RPC exception: no ADC data found");
    }

    return adcData;
} //End readVFAT3ADC(...)

PyListUint32 xhal::rpc::VFAT3::readVFAT3ADCMultiLink(uint32_t ohMask, PyListUint32 &ohVfatMaskArray, bool useExtRefADC){
    req = wisc::RPCMsg("vfat3.readVFAT3ADCMultiLink");

    req.set_word("ohMask",ohMask);
    req.set_word_array("ohVfatMaskArray",ohVfatMaskArray);
    req.set_word("useExtRefADC", useExtRefADC);

    try {
        rsp = rpc.call_method(req);
    }
    STANDARD_CATCH;

    if (rsp.get_key_exists("error")) {
        throw xhal::utils::XHALRPCException(strcat("RPC exception: ", rsp.get_string("error").c_str()));
    }

    PyListUint32 adcDataAll;
    if (rsp.get_key_exists("adcDataAll")) {
        adcDataAll = rsp.get_word_array("adcDataAll");
    } else {
        throw xhal::utils::XHALRPCException("RPC exception: no ADC data found");
    }

    return adcDataAll;
} //End readVFAT3ADCMultiLink(...)

void xhal::rpc::VFAT3::setChannelRegistersVFAT3(uint32_t ohN, uint32_t vfatMask, PyListUint32 &calEnable, PyListUint32 &masks, PyListUint32 &trimARM, PyListUint32 &trimARMPol, PyListUint32 &trimZCC, PyListUint32 &trimZCCPol)
{
    req = wisc::RPCMsg("vfat3.setChannelRegistersVFAT3");
    req.set_word("ohN",ohN);
    req.set_word("vfatMask",vfatMask);

    req.set_word_array("calEnable",calEnable);
    req.set_word_array("masks",masks);
    req.set_word_array("trimARM",trimARM);
    req.set_word_array("trimARMPol",trimARMPol);
    req.set_word_array("trimZCC",trimZCC);
    req.set_word_array("trimZCCPol",trimZCCPol);

    try {
        rsp = rpc.call_method(req);
    }
    STANDARD_CATCH;

    if (rsp.get_key_exists("error")) {
        throw xhal::utils::XHALRPCException(strcat("RPC exception: ", rsp.get_string("error").c_str()));
    }
    return;
}

void xhal::rpc::VFAT3::setChannelRegistersVFAT3Simple(uint32_t ohN, uint32_t vfatMask, PyListUint32 &chanRegData)
{
    req = wisc::RPCMsg("vfat3.setChannelRegistersVFAT3");
    req.set_word("ohN",ohN);
    req.set_word("vfatMask",vfatMask);
    req.set_word("simple",true);

    req.set_word_array("chanRegData",chanRegData);

    try {
        rsp = rpc.call_method(req);
    }
    STANDARD_CATCH;

    if (rsp.get_key_exists("error")) {
        throw xhal::utils::XHALRPCException(strcat("RPC exception: ", rsp.get_string("error").c_str()));
    }
    return;
}
