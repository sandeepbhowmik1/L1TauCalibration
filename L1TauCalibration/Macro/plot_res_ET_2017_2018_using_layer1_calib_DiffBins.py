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

fMC_2017 = TFile.Open("/home/sbhowmik/L1TauTrigger_NTuple/Calibration_2018data_180911/outputForCalibration_Ntuple_MC_VBFHToTauTau_L1_RECO_reEmulTPs_2017calib_180917.root")
fMC_2018 = TFile.Open("/home/sbhowmik/L1TauTrigger_NTuple/Calibration_2018data_180911/outputForCalibration_Ntuple_MC_VBFHToTauTau_L1_RECO_reEmulTPs_2018calib_180917.root")
#fMC = TFile.Open("/home/sbhowmik/L1TauTrigger_NTuple/Calibration_2018data_180503/calibratedOutput_Ntuple_MC_VBF_180505.root")
#fData = TFile.Open("/home/sbhowmik/L1TauTrigger_NTuple/Calibration_2018data_180503/calibratedOutput_Ntuple_SingleMu_180503.root")

tMC_2017 = fMC_2017.Get("outTreeForCalibration")
tMC_2018 = fMC_2018.Get("outTreeForCalibration")
#tMC = fMC.Get("outTreeForCalibration")
#tData = fData.Get("outTreeForCalibration")

PtBins = [20, 25, 30, 35, 40, 45, 50, 60, 80, 120, 180, 255, 1000]
PtBinsName = ["Pt_20_25", "Pt_25_30", "Pt_30_35", "Pt_35_40", "Pt_40_45", "Pt_45_50", "Pt_50_60", "Pt_60_80", "Pt_80_120", "Pt_120_180", "Pt_180_255", "Pt_255_1000"]
EtaBins =[0.0, 0.5, 1.0, 1.5, 2.1]
EtaBinsName =["Eta_0p0_0p5", "Eta_0p5_1p0", "Eta_1p0_1p5", "Eta_1p5_2p1"]

for i in range (0, len(PtBinsName)):

    for j in range (0, len(EtaBinsName)):

        hEt_raw_MC = TH1F ("hEt_raw_MC" + PtBinsName[i] + "_" + EtaBinsName[j], "hEt_raw_MC" + PtBinsName[i] + "_" + EtaBinsName[j], 60, 0, 3)
        hEt_calib_MC_17 = TH1F ( "hEt_calib_MC_17" + PtBinsName[i] + "_" + EtaBinsName[j], "hEt_calib_MC_17" + PtBinsName[i] + "_" + EtaBinsName[j], 60, 0, 3)
        hEt_calib_MC_18 = TH1F ( "hEt_calib_MC_18" + PtBinsName[i] + "_" + EtaBinsName[j], "hEt_calib_MC_18" + PtBinsName[i] + "_" + EtaBinsName[j], 60, 0, 3)

        nEv = tMC_2018.GetEntries()
        for iEv in range (0, nEv):
            tMC_2018.GetEntry(iEv)
            tMC_2017.GetEntry(iEv)
            if iEv % 100000 == 0 : print iEv , "/" , nEv

            if tMC_2018.OfflineTau_pt < PtBins[i] or tMC_2018.OfflineTau_pt >= PtBins[i+1] :
                continue

            if abs(tMC_2018.OfflineTau_eta) < EtaBins[j] or abs(tMC_2018.OfflineTau_eta) >= EtaBins[j+1] :
                continue

            hEt_raw_MC.Fill(tMC_2018.L1Tau_RawIEt/2 / tMC_2018.OfflineTau_pt)
            hEt_calib_MC_17.Fill(tMC_2017.L1Tau_pt / tMC_2017.OfflineTau_pt)
            hEt_calib_MC_18.Fill(tMC_2018.L1Tau_pt / tMC_2018.OfflineTau_pt)

        leg = TLegend (0.48, 0.555, 0.8, 0.85)
            
        Mean_raw_MC = str(round(hEt_raw_MC.GetMean(),3))
        Mean_calib_MC_18 = str(round(hEt_calib_MC_18.GetMean(),3))
        Mean_calib_MC_17 = str(round(hEt_calib_MC_17.GetMean(),3))

        RMS_raw_MC = str(round(hEt_raw_MC.GetRMS(),3))
        RMS_calib_MC_18 = str(round(hEt_calib_MC_18.GetRMS(),3))
        RMS_calib_MC_17 = str(round(hEt_calib_MC_17.GetRMS(),3))

        leg.AddEntry(hEt_raw_MC, "Raw L1", "l")
        leg.AddEntry(0,"Mean = "+Mean_raw_MC+", RMS = "+RMS_raw_MC, "");

        leg.AddEntry(hEt_calib_MC_18, "Calibrated L1, 2018 Layer1", "l")
        leg.AddEntry(0,"Mean = "+Mean_calib_MC_18+", RMS = "+RMS_calib_MC_18, "");
        
        leg.AddEntry(hEt_calib_MC_17, "Calibrated L1, 2017 Layer1", "l")
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

        extraTextBox1 = ROOT.TLatex  (0.6, 0.4, PtBinsName[i]  )
        extraTextBox2 = ROOT.TLatex  (0.6, 0.3, EtaBinsName[j] )
        extraTextBox1.SetNDC()
        extraTextBox2.SetNDC()
        extraTextBox1.SetTextSize(0.76*0.05)
        extraTextBox2.SetTextSize(0.76*0.05)
        extraTextBox1.SetTextFont(42)
        extraTextBox2.SetTextFont(42)
        extraTextBox1.SetTextColor(ROOT.kBlack)
        extraTextBox2.SetTextColor(ROOT.kBlack)
        extraTextBox1.SetTextAlign(13)
        extraTextBox2.SetTextAlign(13)
        extraTextBox1.Draw()
        extraTextBox2.Draw()

        c1.Print("/home/sbhowmik/L1TauTrigger_NTuple/Calibration_2018data_180911/Plots/resolution_ET_MC_" + PtBinsName[i] + "_" + EtaBinsName[j] + "_180917.pdf", "pdf") 
        c1.Print("/home/sbhowmik/L1TauTrigger_NTuple/Calibration_2018data_180911/Plots/resolution_ET_MC_" + PtBinsName[i] + "_" + EtaBinsName[j] + "_180917.png", "png")

c1.Update()
c1.Close()

raw_input()
