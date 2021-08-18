#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <iostream>
#include <TLorentzVector.h>
#include <TH1.h>
#include <TProfile.h>
#include <TH2.h>
#include <TH3.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TPaveText.h>
#include <TStyle.h>
#include <TROOT.h>
#include <sstream>
#include <TBranchElement.h>
#include <fstream>
#include <TGraphAsymmErrors.h>
#include <TMultiGraph.h>
//#include "myIncludes.h"

using namespace std;

void DrawIsoEnergies(TString FileName1 = "", TString FileName2 = "", TString FileName3 = "", TString FileName4 = "")
{
  gStyle->SetOptStat(0000);

  TFile plots_6x9(FileName1.Data(),"READ");
  TFile plots_9x9(FileName2.Data(),"READ");
  
  // - E(6x9) iso sig/bkg in bins of pt
  // - E(9x9) iso sig/bkg in bins of pt
  TH1F* Eiso_20_30_sig_6x9 = (TH1F*)plots_6x9.Get("Eiso_20_30_sig");
  TH1F* Eiso_20_30_bkg_6x9 = (TH1F*)plots_6x9.Get("Eiso_20_30_bkg");
  TH1F* Eiso_20_30_sig_9x9 = (TH1F*)plots_9x9.Get("Eiso_20_30_sig");
  TH1F* Eiso_20_30_bkg_9x9 = (TH1F*)plots_9x9.Get("Eiso_20_30_bkg");

  TCanvas c1("c1","c1",800.,800.);
  Eiso_20_30_sig_6x9->SetLineColor(kRed);
  Eiso_20_30_bkg_6x9->SetLineColor(kRed);
  Eiso_20_30_bkg_6x9->SetLineStyle(7);
  Eiso_20_30_sig_6x9->SetLineWidth(3);
  Eiso_20_30_bkg_6x9->SetLineWidth(3);
  Eiso_20_30_sig_6x9->SetTitle("");
  Eiso_20_30_sig_6x9->GetXaxis()->SetRangeUser(0.,35.);
  Eiso_20_30_sig_6x9->GetXaxis()->SetTitle("E_{T}^{iso} [GeV]");
  Eiso_20_30_sig_6x9->GetYaxis()->SetTitle("a.u.");
  Eiso_20_30_sig_6x9->GetYaxis()->SetTitleOffset(1.5);

  Eiso_20_30_sig_9x9->SetLineColor(kBlue);
  Eiso_20_30_bkg_9x9->SetLineColor(kBlue);
  Eiso_20_30_bkg_9x9->SetLineStyle(7);
  Eiso_20_30_sig_9x9->SetLineWidth(3);
  Eiso_20_30_bkg_9x9->SetLineWidth(3);

  Eiso_20_30_bkg_6x9->SetFillStyle(3002);
  Eiso_20_30_bkg_9x9->SetFillStyle(3003);

  Eiso_20_30_bkg_6x9->SetFillColorAlpha(kRed, 0.5);
  Eiso_20_30_bkg_9x9->SetFillColorAlpha(kBlue, 0.5);

  // Eiso_20_30_bkg_6x9->SetFillColor(kRed);
  // Eiso_20_30_bkg_9x9->SetFillColor(kBlue);

  Eiso_20_30_sig_6x9->DrawNormalized();
  // Eiso_20_30_bkg_6x9->DrawNormalized("same");
  Eiso_20_30_sig_9x9->DrawNormalized("same");
  Eiso_20_30_bkg_6x9->DrawNormalized("same");
  Eiso_20_30_bkg_9x9->DrawNormalized("same");

  TLegend* leg1 = new TLegend(0.56,0.57,0.88,0.87);
  leg1->SetBorderSize(0);
  leg1->AddEntry(Eiso_20_30_sig_6x9,"6x9: ggF signal","L");
  leg1->AddEntry(Eiso_20_30_bkg_6x9,"6x9: ZeroBias","LF");
  leg1->AddEntry(Eiso_20_30_sig_9x9,"9x9: ggF signal","L");
  leg1->AddEntry(Eiso_20_30_bkg_9x9,"9x9: ZeroBias","LF");
  leg1->Draw("same");

  TPaveText* texl1 = new TPaveText(0.20,0.89,0.70,0.96,"NDC");
  texl1->AddText("CMS Internal, #sqrt{s}=13 TeV");

  texl1->SetTextSize(0.03);
  texl1->SetFillStyle(0);
  texl1->SetBorderSize(0);
  texl1->Draw("same");

  cout<<"6x9: mean signal = "<<Eiso_20_30_sig_6x9->GetMean()<<endl;
  cout<<"6x9: mean bkg    = "<<Eiso_20_30_bkg_6x9->GetMean()<<endl;
  cout<<"9x9: mean signal = "<<Eiso_20_30_sig_9x9->GetMean()<<endl;
  cout<<"9x9: mean bkg    = "<<Eiso_20_30_bkg_9x9->GetMean()<<endl;

  cout<<"6x9: RMS/mean signal = "<<Eiso_20_30_sig_6x9->GetRMS()/Eiso_20_30_sig_6x9->GetMean()<<endl;
  cout<<"6x9: RMS/mean bkg    = "<<Eiso_20_30_bkg_6x9->GetRMS()/Eiso_20_30_bkg_6x9->GetMean()<<endl;
  cout<<"9x9: RMS/mean signal = "<<Eiso_20_30_sig_9x9->GetRMS()/Eiso_20_30_sig_9x9->GetMean()<<endl;
  cout<<"9x9: RMS/mean bkg    = "<<Eiso_20_30_bkg_9x9->GetRMS()/Eiso_20_30_bkg_9x9->GetMean()<<endl;

  c1.SaveAs("Eiso_6x9_vs_9x9.pdf");
  c1.SaveAs("Eiso_6x9_vs_9x9.root");

  //Compare ROCs
  TFile f3(FileName3.Data(),"READ");
  TFile f4(FileName4.Data(),"READ");

  TGraph* g3 = (TGraph*)f3.Get("gr");
  TGraph* g4 = (TGraph*)f4.Get("gr");

  TMultiGraph *mg = new TMultiGraph();
  mg->Add(g3,"l");  
  mg->Add(g4,"l");  

  TCanvas c2("c2","c2",800.,800.);
  g3->SetLineColor(kRed);
  g3->SetLineWidth(3);
  g4->SetLineColor(kBlue);
  g4->SetLineWidth(3);

  Eiso_20_30_sig_9x9->SetLineColor(kBlue);
  Eiso_20_30_bkg_9x9->SetLineColor(kBlue);
  Eiso_20_30_bkg_9x9->SetLineStyle(7);
  Eiso_20_30_sig_9x9->SetLineWidth(3);
  Eiso_20_30_bkg_9x9->SetLineWidth(3);

  mg->Draw("ALP");
  mg->SetTitle("");
  mg->GetXaxis()->SetRangeUser(0.,35.);
  mg->GetXaxis()->SetTitle("Signal efficiency");
  mg->GetYaxis()->SetTitle("Background rejection");
  mg->GetYaxis()->SetTitleOffset(1.35);

  TLegend* leg2 = new TLegend(0.46,0.67,0.88,0.87);
  leg2->SetBorderSize(0);
  leg2->AddEntry(g3,"6x9 iso. window","L");
  leg2->AddEntry(g4,"9x9 iso. window","L");
  leg2->Draw("same");

  TPaveText* texl2 = new TPaveText(0.20,0.89,0.70,0.96,"NDC");
  texl2->AddText("CMS Internal, #sqrt{s}=13 TeV");

  texl2->SetTextSize(0.03);
  texl2->SetFillStyle(0);
  texl2->SetBorderSize(0);
  texl2->Draw("same");

  c2.SaveAs("ROC_6x9_vs_9x9.pdf");
  c2.SaveAs("ROC_6x9_vs_9x9.root");


  // E(6x9) iso sig/bkg w/ and w/o merging (to be put side by side)
  TH1F* Eiso_20_30_sig_wMerging    = (TH1F*)plots_6x9.Get("EisoMerged_30_40_sig");
  TH1F* Eiso_20_30_bkg_wMerging    = (TH1F*)plots_6x9.Get("EisoMerged_30_40_bkg");
  TH1F* Eiso_20_30_sig_woMerging   = (TH1F*)plots_6x9.Get("EisoNotMerged_30_40_sig");
  TH1F* Eiso_20_30_bkg_woMerging   = (TH1F*)plots_6x9.Get("EisoNotMerged_30_40_bkg");

  TCanvas c3("c3","c3",800.,800.);
  Eiso_20_30_sig_wMerging->SetLineColor(kRed);
  Eiso_20_30_bkg_wMerging->SetLineColor(kRed);
  Eiso_20_30_bkg_wMerging->SetLineStyle(7);
  Eiso_20_30_sig_wMerging->SetLineWidth(3);
  Eiso_20_30_bkg_wMerging->SetLineWidth(3);
  Eiso_20_30_sig_wMerging->SetTitle("");
  Eiso_20_30_sig_wMerging->GetXaxis()->SetRangeUser(0.,35.);
  Eiso_20_30_sig_wMerging->GetXaxis()->SetTitle("E_{T}^{iso} [GeV]");
  Eiso_20_30_sig_wMerging->GetYaxis()->SetTitle("a.u.");
  Eiso_20_30_sig_wMerging->GetYaxis()->SetTitleOffset(1.5);

  Eiso_20_30_sig_woMerging->SetLineColor(kBlue);
  Eiso_20_30_bkg_woMerging->SetLineColor(kBlue);
  Eiso_20_30_bkg_woMerging->SetLineStyle(7);
  Eiso_20_30_sig_woMerging->SetLineWidth(3);
  Eiso_20_30_bkg_woMerging->SetLineWidth(3);

  Eiso_20_30_bkg_wMerging->SetFillStyle(3002);
  Eiso_20_30_bkg_woMerging->SetFillStyle(3003);
  Eiso_20_30_bkg_wMerging->SetFillColorAlpha(kRed, 0.5);
  Eiso_20_30_bkg_woMerging->SetFillColorAlpha(kBlue, 0.5);

  Eiso_20_30_sig_wMerging->DrawNormalized();
  // Eiso_20_30_bkg_wMerging->DrawNormalized("same");
  Eiso_20_30_sig_woMerging->DrawNormalized("same");
  Eiso_20_30_bkg_wMerging->DrawNormalized("same");
  Eiso_20_30_bkg_woMerging->DrawNormalized("same");

  TLegend* leg3 = new TLegend(0.56,0.57,0.88,0.87);
  leg3->SetBorderSize(0);
  leg3->AddEntry(Eiso_20_30_sig_wMerging,"Unmerged: ggF signal","L");
  leg3->AddEntry(Eiso_20_30_bkg_wMerging,"Unmerged: ZeroBias","L");
  leg3->AddEntry(Eiso_20_30_sig_woMerging,"Merged: ggF signal","L");
  leg3->AddEntry(Eiso_20_30_bkg_woMerging,"Merged: ZeroBias","L");
  leg3->Draw("same");

  TPaveText* texl3 = new TPaveText(0.20,0.89,0.70,0.96,"NDC");
  texl3->AddText("CMS Internal, #sqrt{s}=13 TeV");

  texl3->SetTextSize(0.03);
  texl3->SetFillStyle(0);
  texl3->SetBorderSize(0);
  texl3->Draw("same");

  c3.SaveAs("Eiso_NotMerged_Merged.pdf");
  c3.SaveAs("Eiso_NotMerged_Merged.root");


  // Fraction of merged clusters as function of pT for sig and bkg.
  TH1F* numerator_sig    = (TH1F*)plots_6x9.Get("rawEtMerged_sig");
  TH1F* tot_sig          = (TH1F*)plots_6x9.Get("rawEt_sig");
  TH1F* numerator_bkg    = (TH1F*)plots_6x9.Get("rawEtMerged_bkg");
  TH1F* tot_bkg          = (TH1F*)plots_6x9.Get("rawEt_bkg");

  numerator_sig->Sumw2();
  numerator_bkg->Sumw2();
  tot_sig->Sumw2();
  tot_bkg->Sumw2();

  numerator_sig->Rebin(2);
  numerator_bkg->Rebin(2);
  tot_sig->Rebin(2);
  tot_bkg->Rebin(2);

  numerator_sig->Divide(tot_sig);
  numerator_bkg->Divide(tot_bkg);

  numerator_sig->Scale(100.);
  numerator_bkg->Scale(100.);

  TCanvas c4("c4","c4",800.,800.);
  numerator_sig->SetLineColor(kBlack);
  numerator_sig->SetMaximum(70.);
  numerator_bkg->SetLineColor(kGreen+1);
  numerator_sig->SetLineWidth(3);
  numerator_bkg->SetLineWidth(3);
  numerator_sig->SetTitle("");
  numerator_sig->GetXaxis()->SetRangeUser(20.,120.);
  numerator_sig->GetXaxis()->SetTitle("E_{T}^{L1} [GeV]");
  numerator_sig->GetYaxis()->SetTitle("Fraction of merged candidates [%]");
  numerator_sig->GetYaxis()->SetTitleOffset(1.5);

  numerator_sig->Draw();
  numerator_bkg->Draw("same");

  TLegend* leg4 = new TLegend(0.56,0.65,0.88,0.87);
  leg4->SetBorderSize(0);
  leg4->AddEntry(numerator_sig,"ggF signal","L");
  leg4->AddEntry(numerator_bkg,"ZeroBias","L");
  leg4->Draw("same");

  TPaveText* texl4 = new TPaveText(0.20,0.89,0.70,0.96,"NDC");
  texl4->AddText("CMS Internal, #sqrt{s}=13 TeV");

  texl4->SetTextSize(0.03);
  texl4->SetFillStyle(0);
  texl4->SetBorderSize(0);
  texl4->Draw("same");

  c4.SaveAs("FractionMerged_vs_rawEt.pdf");
  c4.SaveAs("FractionMerged_vs_rawEt.root");

  //Calibrated pT of L1 tau candidates as function of nTT, for signal.
  TProfile* profile1 = (TProfile*)plots_6x9.Get("calibEt_nvtx_sig");

  TCanvas c5("c5","c5",800.,800.);
  profile1->SetLineColor(kBlue);
  profile1->SetMaximum(50.);
  profile1->SetMinimum(10.);
  profile1->SetLineWidth(3);
  profile1->SetTitle("");
  profile1->GetXaxis()->SetRangeUser(0.,100.);
  profile1->GetXaxis()->SetTitle("nVtx");
  profile1->GetYaxis()->SetTitle("Average L1-#tau calibrated energy [GeV]");
  profile1->GetYaxis()->SetTitleOffset(1.5);

  profile1->Draw();

  TLegend* leg5 = new TLegend(0.56,0.25,0.88,0.47);
  leg5->SetBorderSize(0);
  leg5->AddEntry(profile1,"ggF signal","L");
  leg5->Draw("same");

  TPaveText* texl5 = new TPaveText(0.20,0.89,0.70,0.96,"NDC");
  texl5->AddText("CMS Internal, #sqrt{s}=13 TeV");

  texl5->SetTextSize(0.03);
  texl5->SetFillStyle(0);
  texl5->SetBorderSize(0);
  texl5->Draw("same");

  c5.SaveAs("calibEt_vs_nVtx.pdf");
  c5.SaveAs("calibEt_vs_nVtx.root");

  //Calibrated pT of L1 tau candidates as function of nTT, for signal.
  TProfile* profile2 = (TProfile*)plots_6x9.Get("calibEt_nTT_sig");
  profile2->Rebin(2);
  // profile2->Scale(0.5);

  TCanvas c6("c6","c6",800.,800.);
  profile2->SetLineColor(kBlue);
  profile2->SetMaximum(50.);
  profile2->SetMinimum(10.);
  profile2->SetLineWidth(3);
  profile2->SetTitle("");
  profile2->GetXaxis()->SetRangeUser(0.,100.);
  profile2->GetXaxis()->SetTitle("nTT");
  profile2->GetYaxis()->SetTitle("Average L1-#tau calibrated energy [GeV]");
  profile2->GetYaxis()->SetTitleOffset(1.5);

  profile2->Draw();

  TLegend* leg6 = new TLegend(0.56,0.25,0.88,0.47);
  leg6->SetBorderSize(0);
  leg6->AddEntry(profile2,"ggF signal","L");
  leg6->Draw("same");

  TPaveText* texl6 = new TPaveText(0.20,0.89,0.70,0.96,"NDC");
  texl6->AddText("CMS Internal, #sqrt{s}=13 TeV");

  texl6->SetTextSize(0.03);
  texl6->SetFillStyle(0);
  texl6->SetBorderSize(0);
  texl6->Draw("same");

  c6.SaveAs("calibEt_vs_nTT.pdf");
  c6.SaveAs("calibEt_vs_nTT.root");

  //In case of merged, ratio of energy of second cluster to primary cluster as function of pT, for sig and bkg.
  TProfile* profile3 = (TProfile*)plots_6x9.Get("secToMainRatio_sig");
  TProfile* profile4 = (TProfile*)plots_6x9.Get("secToMainRatio_bkg");

  profile3->SetLineWidth(3);
  profile4->SetLineWidth(3);

  profile3->SetLineColor(kBlack);
  profile4->SetLineColor(kGreen+1);

  TCanvas c7("c7","c7",800.,800.);
  // profile3->SetMaximum(50.);
  // profile3->SetMinimum(10.);
  profile3->SetLineWidth(3);
  profile3->SetTitle("");
  profile3->GetXaxis()->SetRangeUser(20.,100.);
  profile3->GetXaxis()->SetTitle("raw E_{T}^{L1} [GeV]");
  profile3->GetYaxis()->SetTitle("E_{T}^{secondary}/E_{T}^{main}");
  profile3->GetYaxis()->SetTitleOffset(1.3);

  profile3->Draw();
  profile4->Draw("same");

  TLegend* leg7 = new TLegend(0.45,0.66,0.77,0.88);
  leg7->SetBorderSize(0);
  leg7->AddEntry(profile3,"ggF signal","L");
  leg7->AddEntry(profile4,"ZeroBias","L");
  leg7->Draw("same");

  TPaveText* texl7 = new TPaveText(0.20,0.89,0.70,0.96,"NDC");
  texl7->AddText("CMS Internal, #sqrt{s}=13 TeV");

  texl7->SetTextSize(0.03);
  texl7->SetFillStyle(0);
  texl7->SetBorderSize(0);
  texl7->Draw("same");

  c7.SaveAs("secToMainRatio.pdf");
  c7.SaveAs("secToMainRatio.root");

  //Calibrated pT of L1 tau candidates as function of nTT, for signal.
  TProfile* profile5 = (TProfile*)plots_6x9.Get("nTT_vtx_sig");

  TCanvas c8("c8","c8",800.,800.);
  profile5->SetLineColor(kBlue);
  // profile5->SetMaximum(50.);
  // profile5->SetMinimum(10.);
  profile5->SetLineWidth(3);
  profile5->SetTitle("");
  profile5->GetXaxis()->SetRangeUser(0.,100.);
  profile5->GetXaxis()->SetTitle("nVtx");
  profile5->GetYaxis()->SetTitle("Average nTT");
  profile5->GetYaxis()->SetTitleOffset(1.3);

  profile5->Draw();

  TLegend* leg8 = new TLegend(0.56,0.25,0.88,0.47);
  leg8->SetBorderSize(0);
  leg8->AddEntry(profile5,"ggF signal","L");
  leg8->Draw("same");

  TPaveText* texl8 = new TPaveText(0.20,0.89,0.70,0.96,"NDC");
  texl8->AddText("CMS Internal, #sqrt{s}=13 TeV");

  texl8->SetTextSize(0.03);
  texl8->SetFillStyle(0);
  texl8->SetBorderSize(0);
  texl8->Draw("same");

  c8.SaveAs("nVtx_vs_nTT.pdf");
  c8.SaveAs("nVtx_vs_nTT.root");


  // Fraction of merged clusters as function of nVtx
  TH1F* numerator_sig2    = (TH1F*)plots_6x9.Get("NvtxMerged_sig");
  TH1F* tot_sig2          = (TH1F*)plots_6x9.Get("Nvtx_sig");

  numerator_sig2->Sumw2();
  tot_sig2->Sumw2();

  numerator_sig2->Divide(tot_sig2);
  numerator_sig2->Scale(100.);

  TCanvas c9("c9","c9",800.,800.);
  numerator_sig2->SetLineColor(kBlack);
  numerator_sig2->SetMaximum(70.);
  numerator_sig2->SetLineWidth(3);
  numerator_sig2->SetTitle("");
  numerator_sig2->GetXaxis()->SetRangeUser(20.,80.);
  numerator_sig2->GetXaxis()->SetTitle("nVtx");
  numerator_sig2->GetYaxis()->SetTitle("Average fraction of merged candidates [%]");
  numerator_sig2->GetYaxis()->SetTitleOffset(1.5);

  numerator_sig2->Draw();

  TLegend* leg9 = new TLegend(0.56,0.65,0.88,0.87);
  leg9->SetBorderSize(0);
  leg9->AddEntry(numerator_sig2,"ggF signal","L");
  leg9->Draw("same");

  TPaveText* texl9 = new TPaveText(0.20,0.89,0.70,0.96,"NDC");
  texl9->AddText("CMS Internal, #sqrt{s}=13 TeV");

  texl9->SetTextSize(0.03);
  texl9->SetFillStyle(0);
  texl9->SetBorderSize(0);
  texl9->Draw("same");

  c9.SaveAs("FractionMerged_vs_nVtx.pdf");
  c9.SaveAs("FractionMerged_vs_nVtx.root");

  // secRawEtDivMainEt sig vs. bkg in bin 30-40
  TH1F* secRawEtDivMainEt_sig    = (TH1F*)plots_6x9.Get("SecToMainRatio_30_40_sig");
  TH1F* secRawEtDivMainEt_bkg    = (TH1F*)plots_6x9.Get("SecToMainRatio_30_40_bkg");

  TCanvas c10("c10","c10",800.,800.);
  secRawEtDivMainEt_sig->SetLineColor(kBlack);
  //secRawEtDivMainEt_sig->SetMaximum(70.);
  secRawEtDivMainEt_sig->SetLineWidth(3);
  secRawEtDivMainEt_bkg->SetLineWidth(3);
  secRawEtDivMainEt_bkg->SetLineColor(kGreen+1);
  secRawEtDivMainEt_sig->SetTitle("");
  secRawEtDivMainEt_sig->GetXaxis()->SetRangeUser(0.,2.);
  secRawEtDivMainEt_sig->GetXaxis()->SetTitle("E_{T}^{secondary}/E_{T}^{main}");
  secRawEtDivMainEt_sig->GetYaxis()->SetTitle("a.u.");
  secRawEtDivMainEt_sig->GetYaxis()->SetTitleOffset(1.5);

  secRawEtDivMainEt_sig->DrawNormalized();
  secRawEtDivMainEt_bkg->DrawNormalized("same");

  TLegend* leg10 = new TLegend(0.56,0.65,0.88,0.87);
  leg10->SetBorderSize(0);
  leg10->AddEntry(secRawEtDivMainEt_sig,"ggF signal","L");
  leg10->AddEntry(secRawEtDivMainEt_bkg,"ZeroBias","L");
  leg10->Draw("same");

  TPaveText* texl10 = new TPaveText(0.20,0.89,0.70,0.96,"NDC");
  texl10->AddText("CMS Internal, #sqrt{s}=13 TeV");

  texl10->SetTextSize(0.03);
  texl10->SetFillStyle(0);
  texl10->SetBorderSize(0);
  texl10->Draw("same");

  c10.SaveAs("secRawEtDivMainEt.pdf");
  c10.SaveAs("secRawEtDivMainEt.root");
  
}
