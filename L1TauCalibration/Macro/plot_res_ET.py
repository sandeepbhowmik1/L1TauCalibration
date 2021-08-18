from ROOT import *
import ROOT
import operator
import array
import os

ROOT.gSystem.Load('libRooFit')

# global style for nice plots!
# histoType = 0: histos with errors via sumw2() ==> set markers, not lines!
def PlotStyle ():
    #global LS
    LS = TStyle (gStyle) #copy some of the basics of defualt style...
    LS.SetName("PlotStyle")
    LS.SetTitle("PlotStyle")

    # pad
    LS.SetOptStat(0)
    LS.SetTickLength(0.02,"X")
    LS.SetTickLength(0.02,"Y")
    LS.SetPadTickY(1)
    LS.SetPadTickX(1)
    #LS.SetPadGridY(1);
    #LS.SetPadGridX(1);
    #LS.SetPadTopMargin(0.05)
    #LS.SetPadBottomMargin(0.13)
    LS.SetPadLeftMargin(0.16)

    LS.SetCanvasDefH(600)
    LS.SetCanvasDefW(600)

    # axis
    LS.SetTitleYOffset(1.4)
    LS.SetTitleXOffset(0.9)
    LS.SetLabelOffset(0.009, "XYZ")
    LS.SetTitleSize(0.050, "XYZ")

    # legend
    LS.SetLegendBorderSize(0)
    LS.SetLegendFont(62)
    LS.SetLegendTextSize(0.028)
    #LS.SetLegendFillStyle(0) #NOT IMPLEMENTED in root

    # if histoType == 0:
    #     LS.SetMarkerStyle(8);
    #     LS.SetMarkerSize(0.8);

    LS.cd()
    return LS

gROOT.SetBatch(True)

styl = PlotStyle()
c1 = TCanvas ("c1", "c1", 800, 800)

fMC = TFile.Open("/home/sbhowmik/RootTree/L1TauTrigger/Run3/L1TauCalibration_20210727/rootTree_calibratedOutput_MC_VBF_20210727.root")
#fData = TFile.Open("/home/sbhowmik/L1TauTrigger_NTuple/Calibration_180409/calibratedOutput_Ntuple_SingleMu_180409.root")

tMC = fMC.Get("outTreeForCalibration")
#tData = fData.Get("outTreeForCalibration")

hEt_raw_MC = TH1F ("hEt_raw_MC", "hEt_raw_MC", 60, 0, 3)
hEt_calib_MC = TH1F ( "hEt_calib_MC", "hEt_calib_MC", 60, 0, 3)
hEt_default_MC = TH1F ( "hEt_default_MC", "hEt_default_MC", 60, 0, 3)
hEt_raw_Data = TH1F ("hEt_raw_Data", "hEt_raw_Data", 60, 0, 3)
hEt_calib_Data = TH1F ( "hEt_calib_Data", "hEt_calib_Data", 60, 0, 3)

tMC.Draw("L1Tau_IEt/2 / OfflineTau_pt >> hEt_raw_MC","OfflineTau_isMatched == 1", "OfflineTau_pt > 20")
tMC.Draw("L1Tau_CalibPt / OfflineTau_pt >> hEt_calib_MC", "OfflineTau_isMatched == 1", "OfflineTau_pt > 20")
tMC.Draw("L1Tau_pt / OfflineTau_pt >> hEt_default_MC", "OfflineTau_isMatched == 1", "OfflineTau_pt > 20")
#tData.Draw("L1Tau_IEt/2 / OfflineTau_pt >> hEt_raw_Data","OfflineTau_isMatched == 1", "OfflineTau_pt > 20")
#tData.Draw("L1Tau_CalibPt / OfflineTau_pt >> hEt_calib_Data", "OfflineTau_isMatched == 1", "OfflineTau_pt > 20")

#####

leg = TLegend (0.48, 0.555, 0.8, 0.85)

Mean_raw_MC = str(round(hEt_raw_MC.GetMean(),3))
#Mean_raw_Data = str(round(hEt_raw_Data.GetMean(),3))
Mean_calib_MC = str(round(hEt_calib_MC.GetMean(),3))
Mean_default_MC = str(round(hEt_default_MC.GetMean(),3))
#Mean_calib_Data = str(round(hEt_calib_Data.GetMean(),3))

RMS_raw_MC = str(round(hEt_raw_MC.GetRMS(),3))
#RMS_raw_Data = str(round(hEt_raw_Data.GetRMS(),3))
RMS_calib_MC = str(round(hEt_calib_MC.GetRMS(),3))
RMS_default_MC = str(round(hEt_default_MC.GetRMS(),3))
#RMS_calib_Data = str(round(hEt_calib_Data.GetRMS(),3))

leg.AddEntry(hEt_raw_MC, "Raw L1, MC", "l")
leg.AddEntry(0,"Mean = "+Mean_raw_MC+", RMS = "+RMS_raw_MC, "");
#leg.AddEntry(hEt_raw_Data, "Raw L1, Data", "l")
#leg.AddEntry(0,"Mean = "+Mean_raw_Data+", RMS = "+RMS_raw_Data, "");

leg.AddEntry(hEt_calib_MC, "Calibrated L1, MC", "l")
leg.AddEntry(0,"Mean = "+Mean_calib_MC+", RMS = "+RMS_calib_MC, "");
#leg.AddEntry(hEt_calib_Data, "Calibrated L1, Data", "l")
#leg.AddEntry(0,"Mean = "+Mean_calib_Data+", RMS = "+RMS_calib_Data, "");

leg.AddEntry(hEt_default_MC, "Defaul L1, MC", "l")
leg.AddEntry(0,"Mean = "+Mean_default_MC+", RMS = "+RMS_default_MC, "");

hEt_raw_MC.SetLineWidth(2)
hEt_calib_MC.SetLineWidth(2)
hEt_default_MC.SetLineWidth(2)
hEt_raw_Data.SetLineWidth(2)
hEt_calib_Data.SetLineWidth(2)

#hEt_raw_MC.SetLineStyle(3)
#hEt_raw_Data.SetLineStyle(3)

hEt_raw_MC.SetLineColor(kBlue)
hEt_raw_Data.SetLineColor(kBlack)
hEt_calib_MC.SetLineColor(kRed)
hEt_default_MC.SetLineColor(kGreen)
hEt_calib_Data.SetLineColor(kGreen)

hEt_calib_MC.SetTitle(";E_{T}^{#tau, L1} / p_{T}^{#tau, offline}; a.u.")

hEt_calib_MC.DrawNormalized("")
hEt_raw_MC.DrawNormalized("same")
hEt_default_MC.DrawNormalized("same")
#hEt_raw_Data.DrawNormalized("same")
#hEt_calib_Data.DrawNormalized("same")


leg.Draw()

c1.Print("/home/sbhowmik/RootTree/L1TauTrigger/Run3/L1TauCalibration_20210727/plots/resolution_ET_MC_VBF_20210727_test.pdf", "pdf")
c1.Print("/home/sbhowmik/RootTree/L1TauTrigger/Run3/L1TauCalibration_20210727/plots/resolution_ET_MC_VBF_20210727_test.png", "png")


c1.Update()
c1.Close()

raw_input()
