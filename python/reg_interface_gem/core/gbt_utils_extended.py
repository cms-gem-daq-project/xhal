from xhal.reg_interface_gem.core.reg_extra_ops import rpc_connect, scanGBTPhases, writeGBTConfig, writeGBTPhase

from ctypes import *
import os

def configGBT(cardName, listOfconfigFiles, ohMask = 0xfff, nOHs=12):
    """
    Configures all GBT's for OH's defined in ohMask on cardName

    cardName            - network alias of backend AMC
    listOfconfigFiles   - List of config filenames to be used for all OH's, 
                          index of element should match GBTx number on OH, max length of 3
    ohMask              - ohMask to apply, a 1 in the n^th bit indicates the n^th OH should be considered
    nOHs                - Number of OH's on this AMC
    """

    rpc_connect(cardName)
    
    if len(listOfconfigFiles) > 3:
        # FIXME less generic exception
        raise RuntimeError("Too many GBT filenames provided, at most 3 files should be given",os.EX_USAGE)

    for ohN in range(nOHs):
        # Skip masked OH's
        if( not ((ohMask >> ohN) & 0x1)):
            continue

        # Program all requested GBT's on this OH
        for gbtN,configFile in enumerate(listOfconfigFiles):
            config = readGBTConfigFile(configFile)
            configBlob = (c_uint8 * len(config))(*config)

            rpcRsp = writeGBTConfig(ohN, gbtN, len(config), configBlob)
            if rpcRsp > 0:
                # Not sure if this should print a warning and skip or raise an exception...for now an exception
                raise RuntimeError("Failed to configured GBT{0} of OH{1}".format(gbtN,ohN))
            pass
        pass

    return

def printGBTPhaseScanResults(phasesBlob):
    from tabulate import tabulate

    # Create a table with the scan results
    table = []
    for phase in range(16):
        row = []
        row.append(phase)
        for vfatN in range(24):
            row.append(phasesBlob[vfatN*16+phase])

        table.append(row)

    # Create header for the table
    header = ["Phase"]
    for vfatN in range(24):
        header.append("VFAT" + str(vfatN))

    # Print the table
    print tabulate(table, headers=header)

def readGBTConfigFile(filename):
    # Read and parse the configuration file
    with open(filename, "r") as f:
        content = [int(line, 16) for line in f.readlines()]

    # GBTX configuration is 366 registers long
    if len(content) < 366:
        raise ValueError("The configuration file you provided is too short.", filename)
    else:
        return content[:366]

def saveGBTPhaseScanResults(filename, ohN, phasesBlob, nOfRepetitions=100):
    import csv

    # Header for the ROOT file
    header = "ohN/I;"
    header += "vfatN/I:"
    header += "phase/I:"
    header += "nRepetitions/I:"
    header += "nSuccesses/I"

    # Parse the data
    data = []
    for vfatN in range(24):
        for phase in range(16):
            nOfSuccesses = phasesBlob[vfatN*16+phase]
            data.append([ohN, vfatN, phase, nOfRepetitions, nOfSuccesses])

    # Write the file
    with open(filename, 'wb') as f:
        f.write(header)
        writer = csv.writer(f, delimiter = ' ')
        writer.writerows(data)

def scanGBTPhases(cardName, ohMask = 0xfff, nOHs=12, nOfRepetitions=100, silent=True, outputFile=None):
    """
    Scan the VFAT phases for all optohybrids defined in ohMask.

    cardName            - network alias of backend AMC
    ohMask              - ohMask to apply, a 1 in the n^th bit indicates the n^th OH should be considered
    nOHs                - Number of OH's on this AMC
    nOfRepetitions      - Number of times the scan is performed.
    outputFile          - If provided creates a text file with this name and writes phase scan results to the file
    """
        
    rpc_connect(cardName)

    dict_phaseScanResults = {}
    for ohN in range(nOHs):
        # Skip masked OH's
        if( not ((ohMask >> ohN) & 0x1)):
            continue

        # Scan phases
        phasesBlob = (c_uint32 * (24*16))()
        scanGBTPhases(phasesBlob, ohN, nOfRepetitions, 0, 15, 1)
        dict_phaseScanResults[ohN] = phasesBlob

        # stdout output
        if not silent:
            printGBTPhaseScanResults(phasesBlob)
            pass

        # File output
        if outputFile is not None:
            saveGBTPhaseScanResults(outputFile, ohN, phasesBlob, nOfRepetitions)
            pass
        pass

    return dict_phaseScanResults

def setPhase(cardName, ohN, vfatN, phase):
    """
    Write the RX phase of one VFAT of one OptoHybrid.

    V3 electronics only.

    ohN - OptoHybrid to configure.
    vaftN - VFAT to configure.
    phase - Phase value to write. (Min = 0; max = 15).
    """

    rpc_connect(cardName)

    rpcRsp = writeGBTPhase(ohN, vfatN, phase)
    if rpcRsp > 0:
        raise RuntimeError("Failed to write phase {0} to VFAT{1} of OH{2}".format(phase,vfatN,ohN))
    
    return

def setPhaseAllOHs(cardName, vfatN, phase, ohMask=0xfff, nOHs=12):
    """
    For all OH's in ohMask writes the phase to the specified vfat
    """

    rpc_connect(cardName)

    for ohN in range(nOHs):
        # Skip masked OH's
        if( not ((ohMask >> ohN) & 0x1)):
            continue

        rpcRsp = writeGBTPhase(ohN, vfatN, phase)
        if rpcRsp > 0:
            raise RuntimeError("Failed to write phase {0} to VFAT{1} of OH{2}".format(phase,vfatN,ohN))
        pass

    return
