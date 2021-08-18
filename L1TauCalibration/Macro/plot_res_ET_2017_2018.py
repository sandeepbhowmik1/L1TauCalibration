from ROOT import *

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


fMC = TFile.Open("/home/sbhowmik/L1TauTrigger_NTuple/Calibration_2018data_180503/calibratedOutput_Ntuple_MC_VBF_180505.root")
#fData = TFile.Open("/home/sbhowmik/L1TauTrigger_NTuple/Calibration_2018data_180503/calibratedOutput_Ntuple_SingleMu_180503.root")

tMC = fMC.Get("outTreeForCalibration")
#tData = fData.Get("outTreeForCalibration")

hEt_raw_MC = TH1F ("hEt_raw_MC", "hEt_raw_MC", 60, 0, 3)
hEt_calib_MC_18 = TH1F ( "hEt_calib_MC_18", "hEt_calib_MC_18", 60, 0, 3)
hEt_calib_MC_17 = TH1F ( "hEt_calib_MC_17", "hEt_calib_MC_17", 60, 0, 3)


tMC.Draw("L1Tau_IEt/2 / OfflineTau_pt >> hEt_raw_MC","OfflineTau_isMatched == 1", "OfflineTau_pt > 20")
tMC.Draw("L1Tau_CalibPt / OfflineTau_pt >> hEt_calib_MC_18", "OfflineTau_isMatched == 1", "OfflineTau_pt > 20")
tMC.Draw("L1Tau_pt / OfflineTau_pt >> hEt_calib_MC_17", "OfflineTau_isMatched == 1", "OfflineTau_pt > 20")


#####

leg = TLegend (0.48, 0.555, 0.8, 0.85)

Mean_raw_MC = str(round(hEt_raw_MC.GetMean(),3))
Mean_calib_MC_18 = str(round(hEt_calib_MC_18.GetMean(),3))
Mean_calib_MC_17 = str(round(hEt_calib_MC_17.GetMean(),3))


RMS_raw_MC = str(round(hEt_raw_MC.GetRMS(),3))
RMS_calib_MC_18 = str(round(hEt_calib_MC_18.GetRMS(),3))
RMS_calib_MC_17 = str(round(hEt_calib_MC_17.GetRMS(),3))


leg.AddEntry(hEt_raw_MC, "Raw L1", "l")
leg.AddEntry(0,"Mean = "+Mean_raw_MC+", RMS = "+RMS_raw_MC, "");

leg.AddEntry(hEt_calib_MC_18, "Calibrated L1, 2018 LUT", "l")
leg.AddEntry(0,"Mean = "+Mean_calib_MC_18+", RMS = "+RMS_calib_MC_18, "");

leg.AddEntry(hEt_calib_MC_17, "Calibrated L1, 2017 LUT", "l")
leg.AddEntry(0,"Mean = "+Mean_calib_MC_17+", RMS = "+RMS_calib_MC_17, "");


hEt_raw_MC.SetLineWidth(2)
hEt_calib_MC_18.SetLineWidth(2)
hEt_calib_MC_17.SetLineWidth(2)


hEt_raw_MC.SetLineColor(kBlue)
hEt_calib_MC_18.SetLineColor(kRed)
hEt_calib_MC_17.SetLineColor(kGreen)


hEt_calib_MC_18.SetTitle(";E_{T}^{#tau, L1} / p_{T}^{#tau, offline}; a.u.")

hEt_calib_MC_18.DrawNormalized("")
hEt_calib_MC_17.DrawNormalized("same")
hEt_raw_MC.DrawNormalized("same")




leg.Draw()

c1.Print("/home/sbhowmik/L1TauTrigger_NTuple/Calibration_2018data_180503/resolution_ET_MC_VBF_180505.pdf", "pdf")
c1.Print("/home/sbhowmik/L1TauTrigger_NTuple/Calibration_2018data_180503/resolution_ET_MC_VBF_180505.png", "png")


c1.Update()
c1.Close()

raw_input()
