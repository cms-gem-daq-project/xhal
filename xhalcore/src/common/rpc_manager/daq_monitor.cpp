#include "xhal/rpc/daq_monitor.h"

PyListUint32 xhal::rpc::DaqMonitor::getmonTTCmain()
{
    PyListUint32 result;
    req = wisc::RPCMsg("amc.getmonTTCmain");
    try {
    	rsp = rpc.call_method(req);
    }
    STANDARD_CATCH;

    try{
        if (rsp.get_key_exists("error")) {
            throw xhal::utils::XHALRPCException(strcat("RPC exception: ", rsp.get_string("error").c_str()));
        } else {
            result.clear();
            result.push_back(rsp.get_word("MMCM_LOCKED"));
            result.push_back(rsp.get_word("TTC_SINGLE_ERROR_CNT"));
            result.push_back(rsp.get_word("BC0_LOCKED"));
            result.push_back(rsp.get_word("L1A_ID"));
            result.push_back(rsp.get_word("L1A_RATE"));
        }
    }
    STANDARD_CATCH;
    return result;
}

PyListUint32 xhal::rpc::DaqMonitor::getmonTRIGGERmain(uint32_t noh)
{
    PyListUint32 result;
    req = wisc::RPCMsg("amc.getmonTRIGGERmain");
    req.set_word("NOH",noh);
    try {
        rsp = rpc.call_method(req);
    }
    STANDARD_CATCH;

    try{
        if (rsp.get_key_exists("error")) {
            throw xhal::utils::XHALRPCException(strcat("RPC exception: ", rsp.get_string("error").c_str()));
        } else {
            std::string t;
            result.push_back(rsp.get_word("OR_TRIGGER_RATE"));
            for (unsigned int i = 0; i < noh; i++) {
                t = "OH"+std::to_string(i)+".TRIGGER_RATE";
                result.push_back(rsp.get_word(t));
            }
        }
    }
    STANDARD_CATCH;
    return result;
}

PyListUint32 xhal::rpc::DaqMonitor::getmonTRIGGEROHmain(uint32_t noh)
{
    PyListUint32 result(8*noh,0);
    req = wisc::RPCMsg("amc.getmonTRIGGEROHmain");
    req.set_word("NOH",noh);
    try {
        rsp = rpc.call_method(req);
    }
    STANDARD_CATCH;

    try{
        if (rsp.get_key_exists("error")) {
            throw xhal::utils::XHALRPCException(strcat("RPC exception: ", rsp.get_string("error").c_str()));
        }else {
            std::string t;
            for (unsigned int i = 0; i < noh; i++) {
                t = "OH"+std::to_string(i)+".LINK0_MISSED_COMMA_CNT";
                result[i] = rsp.get_word(t);
                t = "OH"+std::to_string(i)+".LINK1_MISSED_COMMA_CNT";
                result[i+noh] = rsp.get_word(t);
                t = "OH"+std::to_string(i)+".LINK0_OVERFLOW_CNT";
                result[i+2*noh] = rsp.get_word(t);
                t = "OH"+std::to_string(i)+".LINK1_OVERFLOW_CNT";
                result[i+3*noh] = rsp.get_word(t);
                t = "OH"+std::to_string(i)+".LINK0_UNDERFLOW_CNT";
                result[i+4*noh] = rsp.get_word(t);
                t = "OH"+std::to_string(i)+".LINK1_UNDERFLOW_CNT";
                result[i+5*noh] = rsp.get_word(t);
                 t = "OH"+std::to_string(i)+".LINK0_SBIT_OVERFLOW_CNT";
                result[i+6*noh] = rsp.get_word(t);
                t = "OH"+std::to_string(i)+".LINK1_SBIT_OVERFLOW_CNT";
                result[i+7*noh] = rsp.get_word(t);
            }
        }
    }
    STANDARD_CATCH;
    return result;
}

PyListUint32 xhal::rpc::DaqMonitor::getmonDAQmain()
{
    PyListUint32 result;
    req = wisc::RPCMsg("amc.getmonDAQmain");
    try {
        rsp = rpc.call_method(req);
    }
    STANDARD_CATCH;

    try{
        if (rsp.get_key_exists("error")) {
            throw xhal::utils::XHALRPCException(strcat("RPC exception: ", rsp.get_string("error").c_str()));
        } else {
            result.push_back(rsp.get_word("DAQ_ENABLE"));
            result.push_back(rsp.get_word("DAQ_LINK_READY"));
            result.push_back(rsp.get_word("DAQ_LINK_AFULL"));
            result.push_back(rsp.get_word("DAQ_OFIFO_HAD_OFLOW"));
            result.push_back(rsp.get_word("L1A_FIFO_HAD_OFLOW"));
            result.push_back(rsp.get_word("L1A_FIFO_DATA_COUNT"));
            result.push_back(rsp.get_word("DAQ_FIFO_DATA_COUNT"));
            result.push_back(rsp.get_word("EVENT_SENT"));
            result.push_back(rsp.get_word("TTS_STATE"));
        }
    }
    STANDARD_CATCH;
    return result;
}

PyListUint32 xhal::rpc::DaqMonitor::getmonDAQOHmain(uint32_t noh)
{
    PyListUint32 result(6*noh,0);
    req = wisc::RPCMsg("amc.getmonDAQOHmain");
    req.set_word("NOH",noh);
    try {
        rsp = rpc.call_method(req);
    }
    STANDARD_CATCH;

    try{
        if (rsp.get_key_exists("error")) {
            throw xhal::utils::XHALRPCException(strcat("RPC exception: ", rsp.get_string("error").c_str()));
        }else {
            std::string t;
            for (unsigned int i = 0; i < noh; i++) {
                t = "OH"+std::to_string(i)+".STATUS.EVT_SIZE_ERR";
                result[i] = rsp.get_word(t);
                t = "OH"+std::to_string(i)+".STATUS.EVENT_FIFO_HAD_OFLOW";
                result[i+noh] = rsp.get_word(t);
                t = "OH"+std::to_string(i)+".STATUS.INPUT_FIFO_HAD_OFLOW";
                result[i+2*noh] = rsp.get_word(t);
                t = "OH"+std::to_string(i)+".STATUS.INPUT_FIFO_HAD_UFLOW";
                result[i+3*noh] = rsp.get_word(t);
                t = "OH"+std::to_string(i)+".STATUS.VFAT_TOO_MANY";
                result[i+4*noh] = rsp.get_word(t);
                t = "OH"+std::to_string(i)+".STATUS.VFAT_NO_MARKER";
                result[i+5*noh] = rsp.get_word(t);
            }
        }
    }
    STANDARD_CATCH;
    return result;
}

PyListUint32 xhal::rpc::DaqMonitor::getmonOHmain(uint32_t noh)
{
    PyListUint32 result(7*noh,0);
    req = wisc::RPCMsg("amc.getmonOHmain");
    req.set_word("NOH",noh);
    try {
        rsp = rpc.call_method(req);
    }
    STANDARD_CATCH;

    try{
        if (rsp.get_key_exists("error")) {
            throw xhal::utils::XHALRPCException(strcat("RPC exception: ", rsp.get_string("error").c_str()));
        } else {
            std::string t;
            for (unsigned int i = 0; i < noh; i++) {
                t = "OH"+std::to_string(i)+".FW_VERSION";
                result[i] = rsp.get_word(t);
                t = "OH"+std::to_string(i)+".EVENT_COUNTER";
                result[i+noh] = rsp.get_word(t);
                t = "OH"+std::to_string(i)+".EVENT_RATE";
                result[i+2*noh] = rsp.get_word(t);
                t = "OH"+std::to_string(i)+".GTX.TRK_ERR";
                result[i+3*noh] = rsp.get_word(t);
                t = "OH"+std::to_string(i)+".GTX.TRG_ERR";
                result[i+4*noh] = rsp.get_word(t);
                t = "OH"+std::to_string(i)+".GBT.TRK_ERR";
                result[i+5*noh] = rsp.get_word(t);
                t = "OH"+std::to_string(i)+".CORR_VFAT_BLK_CNT";
                result[i+6*noh] = rsp.get_word(t);
            }
        }
    }
    STANDARD_CATCH;
    return result;
}

NestedPyDict<int,PyDictUint32<std::string> > xhal::rpc::DaqMonitor::getmonOHSCAmain(uint32_t noh, uint32_t ohMask){
    req = wisc::RPCMsg("amc.getmonOHSCAmain");

    req.set_word("NOH",noh);
    req.set_word("ohMask",ohMask);
    try {
        rsp = rpc.call_method(req);
    }
    STANDARD_CATCH;

    //PyDictVecUint32<int> ret_Dict; //Key is ohN, value is a list
    NestedPyDict<int,PyDictUint32<std::string> > ret_nestedDict;
    try{
        if (rsp.get_key_exists("error")) { //Case Error Exists
            throw xhal::utils::XHALRPCException(strcat("RPC exception: ", rsp.get_string("error").c_str()));
        } //End Case: Error Exists
        else { //Case: No Error
            for(int ohN = 0; ohN < noh; ++ohN){ //Loop over number of optohybrids
                // If this Optohybrid is masked skip it
                if(((ohMask >> ohN) & 0x0)){
                    continue;
                }

                PyDictUint32<std::string> scaVals4ohN;
                //std::string strKeyName;
                std::string strOhN = std::to_string(ohN);

                //SCA Temperature
                scaVals4ohN["SCA_TEMP"] = rsp.get_word("OH" + strOhN + "SCA_TEMP");

                //OH Temperature Sensors
                for(int tempVal=1; tempVal <= 9; ++tempVal){ //Loop over optohybrid temperature sensors
                    std::string strTempVal = std::to_string(tempVal);
                    scaVals4ohN["BOARD_TEMP"+strTempVal]=rsp.get_word("OH" + strOhN + "BOARD_TEMP" + strTempVal);
                } //End Loop over optohybrid temperature sensors

                //Voltage Monitor - AVCCN
                scaVals4ohN["AVCCN"] = rsp.get_word("OH" + strOhN + "AVCCN");

                //Voltage Monitor - AVTTN
                scaVals4ohN["AVTTN"] = rsp.get_word("OH" + strOhN + "AVTTN");

                //Voltage Monitor - 1V0_INT
                scaVals4ohN["1V0_INT"] = rsp.get_word("OH" + strOhN + "1V0_INT");

                //Voltage Monitor - 1V8F
                scaVals4ohN["1V8F"] = rsp.get_word("OH" + strOhN + "1V8F");

                //Voltage Monitor - 1V5
                scaVals4ohN["1V5"] = rsp.get_word("OH" + strOhN + "1V5");

                //Voltage Monitor - 2V5_IO
                scaVals4ohN["2V5_IO"] = rsp.get_word("OH" + strOhN + "2V5_IO");

                //Voltage Monitor - 3V0
                scaVals4ohN["3V0"] = rsp.get_word("OH" + strOhN + "3V0");

                //Voltage Monitor - 1V8
                scaVals4ohN["1V8"] = rsp.get_word("OH" + strOhN + "1V8");

                //Voltage Monitor - VTRX_RSSI2
                scaVals4ohN["VTRX_RSSI2"] = rsp.get_word("OH" + strOhN + "VTRX_RSSI2");

                //Voltage Monitor - VTRX_RSSI1
                scaVals4ohN["VTRX_RSSI1"] = rsp.get_word("OH" + strOhN + "VTRX_RSSI1");

                //Store this in output map
                ret_nestedDict[ohN] = scaVals4ohN;
            } // End loop over number of optohybrids
        } //End Case: No Error
    }
    STANDARD_CATCH;

    return ret_nestedDict;
} //End xhal::rpc::DaqMonitor::getmonOHSCAmain
