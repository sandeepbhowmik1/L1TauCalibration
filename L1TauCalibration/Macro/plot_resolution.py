from ROOT import *

fileName_In = "/home/sbhowmik/RootTree/L1TauTrigger/Run3/L1TauCalibration_20210727/rootTree_calibratedOutput_MC_VBF_20210727.root"
treeName_In = "outTreeForCalibration"
fileName_Out = "/home/sbhowmik/RootTree/L1TauTrigger/Run3/L1TauCalibration_20210727/plots/plot_resolution_for_ET_MC_VBF_20210727"

fileIn = TFile (fileName_In)
treeIn = fileIn.Get(treeName_In)

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
    LS.SetPadGridY(1);
    LS.SetPadGridX(1);
    #LS.SetPadTopMargin(0.05)
    #LS.SetPadBottomMargin(0.13)
    LS.SetPadLeftMargin(0.16)

    LS.SetCanvasDefH(800)
    LS.SetCanvasDefW(800)

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

hist_Et_Reso_raw = TH1F ("hist_Et_Reso_raw", "hist_Et_Reso_raw", 60, 0, 3)
hist_Et_Reso_calib = TH1F ( "hist_Et_Reso_calib", "hist_Et_Reso_calib", 60, 0, 3)
hist_Et_Reso_default = TH1F ( "hist_Et_Reso_default", "hist_Et_Reso_default", 60, 0, 3)


treeIn.Draw("L1Tau_IEt/2 / OfflineTau_pt >> hist_Et_Reso_raw","OfflineTau_isMatched == 1", "OfflineTau_pt > 20")
treeIn.Draw("L1Tau_CalibPt / OfflineTau_pt >> hist_Et_Reso_calib", "OfflineTau_isMatched == 1", "OfflineTau_pt > 20")
treeIn.Draw("L1Tau_pt / OfflineTau_pt >> hist_Et_Reso_default", "OfflineTau_isMatched == 1", "OfflineTau_pt > 20")

#####

leg = TLegend (0.48, 0.555, 0.8, 0.85)

Mean_raw_MC = str(round(hist_Et_Reso_raw.GetMean(),3))
Mean_calib_MC = str(round(hist_Et_Reso_calib.GetMean(),3))
Mean_default_MC = str(round(hist_Et_Reso_default.GetMean(),3))

RMS_raw_MC = str(round(hist_Et_Reso_raw.GetRMS(),3))
RMS_calib_MC = str(round(hist_Et_Reso_calib.GetRMS(),3))
RMS_default_MC = str(round(hist_Et_Reso_default.GetRMS(),3))

leg.AddEntry(hist_Et_Reso_raw, "Raw L1, MC", "l")
leg.AddEntry(0,"Mean = "+Mean_raw_MC+", RMS = "+RMS_raw_MC, "");

leg.AddEntry(hist_Et_Reso_calib, "Calibrated L1, MC", "l")
leg.AddEntry(0,"Mean = "+Mean_calib_MC+", RMS = "+RMS_calib_MC, "");

leg.AddEntry(hist_Et_Reso_default, "Default L1, MC", "l")
leg.AddEntry(0,"Mean = "+Mean_default_MC+", RMS = "+RMS_default_MC, "");

hist_Et_Reso_raw.SetLineWidth(2)
hist_Et_Reso_calib.SetLineWidth(2)
hist_Et_Reso_default.SetLineWidth(2)

hist_Et_Reso_raw.SetLineColor(kBlue)
hist_Et_Reso_calib.SetLineColor(kRed)
hist_Et_Reso_default.SetLineColor(kGreen)

hist_Et_Reso_calib.SetTitle(";E_{T}^{#tau, L1} / p_{T}^{#tau, offline}; a.u.")

hist_Et_Reso_calib.DrawNormalized("")
hist_Et_Reso_raw.DrawNormalized("same")
hist_Et_Reso_default.DrawNormalized("same")


leg.Draw()

c1.Print(fileName_Out + ".pdf", "pdf")
c1.Print(fileName_Out + ".png", "png")
c1.Print(fileName_Out + ".root", "root")

c1.Update()
c1.Close()

raw_input()
