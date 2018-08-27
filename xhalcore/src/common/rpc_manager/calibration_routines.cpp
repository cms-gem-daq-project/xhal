#include <stdexcept>
#include "xhal/rpc/calibration_routines.h"

PyListUint32 xhal::rpc::CalRoutines::checkSbitMappingWithCalPulse(xhal::ParamScan &scanParams, xhal::ParamCalPulse &calPulseParams, xhal::ParamTtcGen &ttcGenParams)
{
    req = wisc::RPCMsg("calibration_routines.checkSbitMappingWithCalPulse");

    req.set_word("ohN", scanParams.ohN);
    req.set_word("vfatN", scanParams.vfatN);
    req.set_word("mask", scanParams.vfatMask);
    req.set_word("nevts", scanParams.nevts);

    req.set_word("useCalPulse", calPulseParams.enable);
    req.set_word("currentPulse", calPulseParams.isCurrent);
    req.set_word("calScaleFactor", calPulseParams.scaleFactor);

    req.set_word("L1Ainterval", ttcGenParams.L1Ainterval);
    req.set_word("pulseDelay", ttcGenParams.pulseDelay);

    try {
        rsp = rpc.call_method(req);
    }
    STANDARD_CATCH;

    if (rsp.get_key_exists("error")) {
        throw xhal::utils::Exception(strcat("RPC exception: ", rsp.get_string("error").c_str()));
    }

    PyListUint32 data;
    if (rsp.get_key_exists("data")){
        data = rsp.get_word_array("data");
    }
    else{
        throw xhal::utils::Exception("RPC exception: no SBIT mapping data found");
    }

    return data;
} //End checkSbitMappingWithCalPulse()

PyDictVecUint32<std::string> xhal::rpc::CalRoutines::checkSbitRateWithCalPulse(xhal::ParamScan &scanParams, xhal::ParamCalPulse &calPulseParams, xhal::ParamTtcGen &ttcGenParams)
{
    req = wisc::RPCMsg("calibration_routines.checkSbitRateWithCalPulse");

    req.set_word("ohN", scanParams.ohN);
    req.set_word("vfatN", scanParams.vfatN);
    req.set_word("mask", scanParams.vfatMask);
    req.set_word("waitTime", scanParams.waitTime);

    req.set_word("useCalPulse", calPulseParams.enable);
    req.set_word("currentPulse", calPulseParams.isCurrent);
    req.set_word("calScaleFactor", calPulseParams.scaleFactor);

    req.set_word("pulseRate", ttcGenParams.pulseRate);
    req.set_word("pulseDelay", ttcGenParams.pulseDelay);

    try {
        rsp = rpc.call_method(req);
    }
    STANDARD_CATCH;

    if (rsp.get_key_exists("error")) {
        throw xhal::utils::Exception(strcat("RPC exception: ", rsp.get_string("error").c_str()));
    }

    PyDictVecUint32<std::string> ret_dictRateData;
    if (rsp.get_key_exists("outDataCTP7Rate")) {
        ret_dictRateData["CTP7"]=rsp.get_word_array("outDataCTP7Rate");
    }
    else{
        throw xhal::utils::Exception("RPC exception: no SBIT rate data from CTP7 found");
    }

    if (rsp.get_key_exists("outDataFPGAClusterCntRate")) {
        ret_dictRateData["FPGA"]=rsp.get_word_array("outDataFPGARate");
    }
    else{
        throw xhal::utils::Exception("RPC exception: no SBIT rate data from FPGA found");
    }

    if (rsp.get_key_exists("outDataVFATSBits")) {
        ret_dictRateData["VFAT"]=rsp.get_word_array("outDataVFATRate");
    }
    else{
        throw xhal::utils::Exception("RPC exception: no SBIT rate data from VFAT found");
    }

    return ret_dictRateData;
} //End checkSbitRateWithCalPulse()

PyListUint32 xhal::rpc::CalRoutines::genScan(xhal::ParamScan &scanParams, xhal::ParamCalPulse &calPulseParams)
{
    req = wisc::RPCMsg("calibration_routines.genScan");

    req.set_word("nevts",scanParams.nevts);
    req.set_word("ohN",scanParams.ohN);
    req.set_word("dacMin",scanParams.dacMin);
    req.set_word("dacMax",scanParams.dacMax);
    req.set_word("dacStep",scanParams.dacStep);
    req.set_word("ch",scanParams.chan);
    req.set_word("mask",scanParams.vfatMask);
    if(scanParams.useUltra){
        req.set_word("useUltra",scanParams.useUltra);
    }
    req.set_word("useExtTrig",scanParams.useExtTrig);
    req.set_string("scanReg",scanParams.scanReg);

    req.set_word("useCalPulse", calPulseParams.enable);
    req.set_word("currentPulse", calPulseParams.isCurrent);
    req.set_word("calScaleFactor", calPulseParams.scaleFactor);

    try {
        rsp = rpc.call_method(req);
    }
    STANDARD_CATCH;

    if (rsp.get_key_exists("error")) {
        throw xhal::utils::Exception(strcat("RPC exception: ", rsp.get_string("error").c_str()));
    }

    PyListUint32 data;
    if (rsp.get_key_exists("data")) {
        data = rsp.get_word_array("data");
    } else {
        throw xhal::utils::Exception("RPC exception: no data from generic scan found");
    }

    return data;
}

PyListUint32 xhal::rpc::CalRoutines::genChannelScan(xhal::ParamScan &scanParams, xhal::ParamCalPulse &calPulseParams)
{
    req = wisc::RPCMsg("calibration_routines.genChannelScan");

    req.set_word("nevts",scanParams.nevts);
    req.set_word("ohN",scanParams.ohN);
    req.set_word("mask",scanParams.vfatMask);
    req.set_word("dacMin",scanParams.dacMin);
    req.set_word("dacMax",scanParams.dacMax);
    req.set_word("dacStep",scanParams.dacStep);
    if(scanParams.useUltra){
        req.set_word("useUltra",scanParams.useUltra);
    }
    req.set_word("useExtTrig",scanParams.useExtTrig);
    req.set_string("scanReg",scanParams.scanReg);

    req.set_word("useCalPulse", calPulseParams.enable);
    req.set_word("currentPulse", calPulseParams.isCurrent);
    req.set_word("calScaleFactor", calPulseParams.scaleFactor);

    uint32_t dataSize = sizeof(uint32_t)*24*128*(scanParams.dacMax-scanParams.dacMin+1)/scanParams.dacStep;
    if(dataSize > 65535){
        throw std::length_error("dataSize for generic channel scan exceeds TCP/IP maximum packet size, please try to run again for a smaller scan range");
    }

    try {
        rsp = rpc.call_method(req);
    }
    STANDARD_CATCH;

    if (rsp.get_key_exists("error")) {
        throw xhal::utils::Exception(strcat("RPC exception: ", rsp.get_string("error").c_str()));
    }

    PyListUint32 data;
    if (rsp.get_key_exists("data")) {
        data = rsp.get_word_array("data");
    } else {
        throw xhal::utils::Exception("RPC exception: no data from generic channel scan found");
    }

    return data;
} //End genChannelScan()

PyDictVecUint32<std::string> xhal::rpc::CalRoutines::sbitRateScan(xhal::ParamScan &scanParams, bool invertVFATPos, bool isParallel)
{
    req = wisc::RPCMsg("calibration_routines.sbitRateScan");


    req.set_word("ohN",scanParams.ohN);
    req.set_word("mask",scanParams.vfatMask);
    req.set_word("dacMin",scanParams.dacMin);
    req.set_word("dacMax",scanParams.dacMax);
    req.set_word("dacStep",scanParams.dacStep);
    req.set_word("ch",scanParams.chan);
    req.set_string("scanReg",scanParams.scanReg);
    req.set_word("waitTime",scanParams.waitTime);

    req.set_word("invertVFATPos", invertVFATPos);
    req.set_word("isParallel", isParallel);

    //Check to make sure (dacMax-dacMin+1)/dacStep is an integer!
    if( 0 != ((scanParams.dacMax - scanParams.dacMin + 1) % scanParams.dacStep) ){
        throw std::logic_error("Caught an error: (dacMax - dacMin + 1)/dacStep must be an integer!");
    }

    try {
        rsp = rpc.call_method(req);
    }
    STANDARD_CATCH;

    PyDictVecUint32<std::string> ret_dictRateData;
    if (rsp.get_key_exists("error")) {
        throw xhal::utils::Exception(strcat("RPC exception: ", rsp.get_string("error").c_str()));
    }

    if (rsp.get_key_exists("outDataDacValue")) {
        ret_dictRateData["DACVAL"] = rsp.get_word_array("outDataDacValue");
    } else {
        throw xhal::utils::Exception("RPC exception: no dac values from sbit rate scan found");
    }

    if (rsp.get_key_exists("outDataCTP7Rate")) {
        ret_dictRateData["CTP7Rate"] = rsp.get_word_array("outDataCTP7Rate");
    } else {
        throw xhal::utils::Exception("RPC exception: no data for CTP7 rate from sbit rate scan found");
    }

    if(isParallel){
        if (rsp.get_key_exists("outDataVFATRate")) {
            ret_dictRateData["VFATRate"] = rsp.get_word_array("outDataVFATRate");
        }
        else{
            throw xhal::utils::Exception("RPC exception: no data for VFAT rate from sbit rate scan found");
        }
    }

    return ret_dictRateData;
} //End sbitRateScan(...)

void xhal::rpc::CalRoutines::ttcGenConf(uint32_t ohN, xhal::ParamTtcGen &ttcGenParams)
{

    req = wisc::RPCMsg("calibration_routines.ttcGenConf");

    req.set_word("ohN", ohN);

    req.set_word("mode",ttcGenParams.mode);
    req.set_word("type",ttcGenParams.type);
    req.set_word("pulseDelay",ttcGenParams.pulseDelay);
    req.set_word("L1Ainterval",ttcGenParams.L1Ainterval);
    req.set_word("nPulses",ttcGenParams.nPulses);
    req.set_word("enable",ttcGenParams.enable);

    try {
        rsp = rpc.call_method(req);
    }
    STANDARD_CATCH;

    if (rsp.get_key_exists("error")) {
        throw xhal::utils::Exception(strcat("RPC exception: ", rsp.get_string("error").c_str()));
    }

    return;
}

void xhal::rpc::CalRoutines::ttcGenToggle(uint32_t ohN, bool enable)
{
    req = wisc::RPCMsg("calibration_routines.ttcGenToggle");
    req.set_word("ohN", ohN);
    req.set_word("enable", enable);
    try {
        rsp = rpc.call_method(req);
    }
    STANDARD_CATCH;

    if (rsp.get_key_exists("error")) {
        throw xhal::utils::Exception(strcat("RPC exception: ", rsp.get_string("error").c_str()));
    }

    return;
} //End ttcGenToggle(...)
