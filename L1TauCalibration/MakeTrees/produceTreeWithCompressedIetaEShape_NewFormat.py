import ROOT
import array
import math
import operator

compressedIetaFile = "./compressionLuts/tauCompressEtaLUT_2bit_v8.txt"
compressedEFile = "./compressionLuts/tauCompressELUT_5bit_v8.txt"
compressednTTFile = "./compressionLuts/tauCompressnTTLUT_5bit_v8.txt"

inputFileName = "/home/sbhowmik/RootTree/L1TauTrigger/Run3/L1TauCalibration_20210727/rootTree_forCalibration_MC_VBFHToTauTau_L1_RECO_reEmulTPs_20210727.root"

outputFileName = "/home/sbhowmik/RootTree/L1TauTrigger/Run3/L1TauCalibration_20210727/rootTree_forCalibration_compressed_MC_VBFHToTauTau_L1_RECO_reEmulTPs_20210727.root"

treeName = "outTreeForCalibration"

def readLUT(lutFileName):
    lut = {}
    i=0
    print lutFileName
    with open(lutFileName, 'r') as f:
        lines = f.readlines()
        for line in lines:
            print "line #",i," content = ",line
            if line[0]=='#': continue
            if line[0]=="" : continue
            tokens = line.split()
            print "tokens = ",tokens
            if len(tokens)<2: continue
            print tokens[0]
            lut[int(tokens[0])] = int(tokens[1])
            print "lut content",lut[int(tokens[0])]
            ++i
    return lut

## Read Ieta,E,shape compression mapping
compressedIeta  = readLUT(compressedIetaFile)
compressedE     = readLUT(compressedEFile)
compressednTT = readLUT(compressednTTFile)

print len(compressedIeta)

## Reading input trees 
## + filling compressed shape histo
inputFile = ROOT.TFile.Open(inputFileName)
inputTree = inputFile.Get(treeName)
inputTree.__class__ = ROOT.TTree

data = {"RunNumber"     :array.array('i',[0]),
        "EventNumber"   :array.array('i',[0]),
        "L1Tau_IEt"       :array.array('i',[0]),
        "L1Tau_IEta"       :array.array('i',[0]),
        "L1Tau_eta"       :array.array('f',[0]),
        "Target"  :array.array('f',[0.]),
        "OfflineTau_pt"   :array.array('f',[0.]),
        "OfflineTau_eta"   :array.array('f',[0.]),
        "OfflineTau_isMatched"   :array.array('i',[0]),
        "L1Tau_pt"    :array.array('f',[0.]),
        "L1Tau_isMerged"    :array.array('i',[0]),
        "L1Tau_hasEM"    :array.array('i',[0]),
        "L1Tau_Qual"     :array.array('i',[0]),
        "L1Tau_nTT"      :array.array('i',[0]),
        "Nvtx"      :array.array('i',[0]),
        "L1Tau_Iso"      :array.array('i',[0]),
        "L1Tau_IsoFlag"      :array.array('i',[0]),
        "compressedieta" :array.array('i',[0]),
        "compressedE" :array.array('i',[0]),
        "compressednTT" :array.array('i',[0]),
       }

nentries = inputTree.GetEntriesFast()
for e in xrange(nentries):
    if inputTree.OfflineTau_isMatched!=1: continue
    inputTree.GetEntry(e)
    data["RunNumber"][0]    = int(inputTree.RunNumber)
    data["EventNumber"][0]  =  int(inputTree.EventNumber)
    data["L1Tau_IEt"][0]      =  int(inputTree.L1Tau_RawIEt)
    data["L1Tau_IEta"][0]      =  int(inputTree.L1Tau_IEta)
    data["L1Tau_eta"][0]      =  inputTree.L1Tau_eta
    data["Target"][0] =  inputTree.Target
    data["OfflineTau_pt"][0]  =  inputTree.OfflineTau_pt
    data["OfflineTau_eta"][0]  =  inputTree.OfflineTau_eta
    data["OfflineTau_isMatched"][0]  =  inputTree.OfflineTau_isMatched
    data["L1Tau_pt"][0]   =  inputTree.L1Tau_pt
    data["L1Tau_isMerged"][0] =  int(inputTree.L1Tau_isMerged)
    data["L1Tau_hasEM"][0] =   int(inputTree.L1Tau_hasEM)
    data["L1Tau_Qual"][0] =   int(inputTree.L1Tau_Qual)
    data["L1Tau_nTT"][0] =   int(inputTree.L1Tau_nTT)
    data["Nvtx"][0] =   int(inputTree.Nvtx)
    data["L1Tau_Iso"][0] =   int(inputTree.L1Tau_Iso)
    data["L1Tau_IsoFlag"][0] =   int(inputTree.L1Tau_IsoFlag)
    data["compressedieta"][0]  = int(math.copysign(compressedIeta[abs(data["L1Tau_IEta"][0])], data["L1Tau_IEta"][0]))
    data["compressedE"][0]     = compressedE[min(data["L1Tau_IEt"][0],255)]
    data["compressednTT"][0] = compressednTT[data["L1Tau_nTT"][0]]

## TODO
## Reading and filling tree with compressed and sorted values
outputFile = ROOT.TFile.Open(outputFileName, "RECREATE")
outputTree = ROOT.TTree(treeName, treeName)
for name, a in data.items():
    outputTree.Branch(name, a, "{0}/{1}".format(name, a.typecode.upper()))

print "Second pass: reading tree for filling output tree"
for e in xrange(nentries):
    inputTree.GetEntry(e)
    if inputTree.OfflineTau_isMatched!=1: continue
    data["RunNumber"][0]    = int(inputTree.RunNumber)
    data["EventNumber"][0]  =  int(inputTree.EventNumber)
    data["L1Tau_IEt"][0]      =  int(inputTree.L1Tau_RawIEt)
    data["L1Tau_IEta"][0]      =  int(inputTree.L1Tau_IEta)
    data["L1Tau_eta"][0]      =  inputTree.L1Tau_eta
    data["Target"][0] =  inputTree.Target
    data["OfflineTau_pt"][0]  =  inputTree.OfflineTau_pt
    data["OfflineTau_eta"][0]  =  inputTree.OfflineTau_eta
    data["OfflineTau_isMatched"][0]  =  inputTree.OfflineTau_isMatched
    data["L1Tau_pt"][0]   =  inputTree.L1Tau_pt
    data["L1Tau_isMerged"][0]   =  inputTree.L1Tau_isMerged
    data["L1Tau_hasEM"][0]   =  inputTree.L1Tau_hasEM
    data["L1Tau_Qual"][0]   =  inputTree.L1Tau_Qual
    data["L1Tau_nTT"][0]   =  inputTree.L1Tau_nTT
    data["Nvtx"][0]   =  inputTree.Nvtx
    data["L1Tau_Iso"][0]   =  inputTree.L1Tau_Iso
    data["L1Tau_IsoFlag"][0]   =  inputTree.L1Tau_IsoFlag
    data["compressedieta"][0]  = int(math.copysign(compressedIeta[abs(data["L1Tau_IEta"][0])], data["L1Tau_IEta"][0]))
    data["compressedE"][0]     = compressedE[min(data["L1Tau_IEt"][0],255)]
    data["compressednTT"][0] = compressednTT[data["L1Tau_nTT"][0]]
    outputTree.Fill()

outputFile.cd()
outputTree.Write()
outputFile.Close()
inputFile.Close()



