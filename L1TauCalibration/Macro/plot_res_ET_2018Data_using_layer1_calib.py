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

fData = TFile.Open("/home/sbhowmik/L1TauTrigger_NTuple/Performance_2018data_181009/outputForCalibration_NTuple_SingleMu_Run2018B_v1_L1_RECO_181112.root")

tData = fData.Get("outTreeForCalibration")

hEt_raw_Data      = TH1F ("hEt_raw_Data",      "hEt_raw_Data", 60, 0, 3)
hEt_calib_Data_18 = TH1F ("hEt_calib_Data_18", "hEt_calib_Data_18", 60, 0, 3)

tData.Draw("L1Tau_RawIEt/2 / OfflineTau_pt >> hEt_raw_Data", "abs(OfflineTau_eta)<= 1.305")
tData.Draw("L1Tau_pt / OfflineTau_pt >> hEt_calib_Data_18", "abs(OfflineTau_eta) <= 1.305")
#tData.Draw("L1Tau_RawIEt/2 / OfflineTau_pt >> hEt_raw_Data", "abs(OfflineTau_eta) > 1.479")
#tData.Draw("L1Tau_pt / OfflineTau_pt >> hEt_calib_Data_18", "abs(OfflineTau_eta) > 1.479")

#####

leg = TLegend (0.48, 0.555, 0.8, 0.85)

Mean_raw_Data = str(round(hEt_raw_Data.GetMean(),3))
Mean_calib_Data_18 = str(round(hEt_calib_Data_18.GetMean(),3))

RMS_raw_Data = str(round(hEt_raw_Data.GetRMS(),3))
RMS_calib_Data_18 = str(round(hEt_calib_Data_18.GetRMS(),3))

leg.AddEntry(hEt_raw_Data, "Raw L1 with Layer1 correction", "l")
leg.AddEntry(0,"Mean = "+Mean_raw_Data+", RMS = "+RMS_raw_Data, "");

leg.AddEntry(hEt_calib_Data_18, "Calibrated L1, Layer1 + Layer2 correction", "l")
leg.AddEntry(0,"Mean = "+Mean_calib_Data_18+", RMS = "+RMS_calib_Data_18, "");

hEt_raw_Data.SetLineWidth(2)
hEt_calib_Data_18.SetLineWidth(2)

hEt_raw_Data.SetLineColor(kBlue)
hEt_calib_Data_18.SetLineColor(kRed)

hEt_calib_Data_18.SetTitle(";E_{T}^{#tau, L1} / p_{T}^{#tau, offline}; a.u.")

hEt_calib_Data_18.DrawNormalized("")
hEt_raw_Data.DrawNormalized("same")

leg.Draw()

c1.Print("/home/sbhowmik/L1TauTrigger_NTuple/Performance_2018data_181009/plots/resolution_ET_Data_Run2018B_181119_barrel.pdf", "pdf")
c1.Print("/home/sbhowmik/L1TauTrigger_NTuple/Performance_2018data_181009/plots/resolution_ET_Data_Run2018B_181119_barrel.png", "png")
#c1.Print("/home/sbhowmik/L1TauTrigger_NTuple/Performance_2018data_181009/plots/resolution_ET_Data_Run2018B_181119_endcap.pdf", "pdf")
#c1.Print("/home/sbhowmik/L1TauTrigger_NTuple/Performance_2018data_181009/plots/resolution_ET_Data_Run2018B_181119_endcap.png", "png")

c1.Update()
c1.Close()

raw_input()
