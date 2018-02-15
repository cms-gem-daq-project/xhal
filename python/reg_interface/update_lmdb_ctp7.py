#!/usr/bin/env python
import xml.etree.ElementTree as xml
import sys, os, subprocess
from time import sleep
from ctypes import *
import timeit
from rw_reg import parseXML, readReg

lib = CDLL(os.getenv("XHAL_ROOT")+"/lib/x86_64/librpcman.so")

nodes = parseXML()

rpc_connect = lib.init
rpc_connect.argtypes = [c_char_p]
rpc_connect.restype = c_uint

update_atdb = lib.update_atdb
update_atdb.argtypes = [c_char_p]
update_atdb.restype = c_uint

DEBUG = True

def updateLMDB(cardName):
    print "attempting to connect to %s"%(cardName)
    rpc_connect(cardName)
    print "Connection to %s successful"%(cardName)
    
    print "updating address table to: %s"%(addrTable_CTP7)
    addrTable_CTP7 = "/mnt/persistent/texas/gem_amc_top.xml"
    update_atdb(addrTable_CTP7)
    
    #print "updating address table to: %s"%(addrTable_OHv3) 
    #addrTable_OHv3 = "/mnt/persistent/texas/optohybrid_registers.xml"
    #update_atdb(addrTable_OHv3)
    
    print "Address tables updated"

    return

if __name__ == '__main__':
    from optparse import OptionParser

    parser = OptionParser()
    parser.add_option("-c","--cardName", type="string", dest="cardName",
                      help="Name of CTP7 to be updated", metavar="cardName")

    updateLMDB(options.cardName)

    return
