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
//#include "myIncludes.h"

using namespace std;

void CompareIsoEnergies(TString FileName1 = "", TString FileName2 = "", TString FileName3 = "", TString FileName4 = "")
{
  TFile File1(FileName1.Data(),"READ");
  TTree * Tree1 = (TTree*)File1.Get("MC_withMatch");
  
  int MC_run;
  int MC_event;
  int MC_lumi;
  float MC_tauPt;
  float MC_tauEta;
  float MC_tauPhi;
  bool MC_hasTriggerMuonType;
  bool MC_hasTriggerTauType;
  bool MC_isMatched;
  bool MC_isOS;
  int MC_foundJet;
  float MC_muonPt;
  float MC_muonEta;
  float MC_muonPhi;
  int MC_Nvtx;
  int MC_l1tEmuQual= 0;
  float MC_l1tEmuPt= 0;
  float MC_l1tEmuEta= 0;
  float MC_l1tEmuPhi= 0;
  int MC_l1tEmuIso= 0;
  int MC_l1tEmuNTT= 0;
  int MC_l1tEmuHasEM= 0;
  int MC_l1tEmuIsMerged= 0;
  int MC_l1tEmuTowerIEta= 0;
  int MC_l1tEmuTowerIPhi= 0;
  int MC_l1tEmuRawEt= 0;
  int MC_l1tEmuIsoEt= 0; 

  Tree1->SetBranchAddress("RunNumber",&MC_run);
  Tree1->SetBranchAddress("EventNumber",&MC_event);
  Tree1->SetBranchAddress("lumi",&MC_lumi);
  Tree1->SetBranchAddress("tauPt",&MC_tauPt);
  Tree1->SetBranchAddress("tauEta",&MC_tauEta);
  Tree1->SetBranchAddress("tauPhi",&MC_tauPhi);
  Tree1->SetBranchAddress("hasTriggerMuonType",&MC_hasTriggerMuonType);
  Tree1->SetBranchAddress("hasTriggerTauType",&MC_hasTriggerTauType);
  Tree1->SetBranchAddress("isMatched",&MC_isMatched);
  Tree1->SetBranchAddress("isOS",&MC_isOS);
  Tree1->SetBranchAddress("foundJet",&MC_foundJet);
  Tree1->SetBranchAddress("muonPt",&MC_muonPt);
  Tree1->SetBranchAddress("muonEta",&MC_muonEta);
  Tree1->SetBranchAddress("muonPhi",&MC_muonPhi);
  Tree1->SetBranchAddress("Nvtx",&MC_Nvtx);
  Tree1->SetBranchAddress("l1tEmuQual",&MC_l1tEmuQual);
  Tree1->SetBranchAddress("l1tEmuPt",&MC_l1tEmuPt);
  Tree1->SetBranchAddress("l1tEmuEta",&MC_l1tEmuEta);
  Tree1->SetBranchAddress("l1tEmuPhi",&MC_l1tEmuPhi);
  Tree1->SetBranchAddress("l1tEmuIso",&MC_l1tEmuIso);
  Tree1->SetBranchAddress("l1tEmuNTT",&MC_l1tEmuNTT);
  // Tree1->SetBranchAddress("l1tEmuHasEM",&MC_l1tEmuHasEM);
  Tree1->SetBranchAddress("l1tEmuIsMerged",&MC_l1tEmuIsMerged);
  Tree1->SetBranchAddress("l1tEmuTowerIEta",&MC_l1tEmuTowerIEta);
  Tree1->SetBranchAddress("l1tEmuTowerIPhi",&MC_l1tEmuTowerIPhi);
  Tree1->SetBranchAddress("l1tEmuRawEt",&MC_l1tEmuRawEt);
  Tree1->SetBranchAddress("l1tEmuIsoEt",&MC_l1tEmuIsoEt);

  TH1F* pt1 = new TH1F("pt1","pt1",40,20.,100.);
  TH1F* Iso1 = new TH1F("Iso1","Iso1",30,0.,15.);
  TH1F* Iso1_NotMerged = new TH1F("Iso1_NotMerged","Iso1_NotMerged",30,0.,15.);
  TH1F* Iso1_Merged = new TH1F("Iso1_Merged","Iso1_Merged",30,0.,15.);
  
  TH1F* isMerged1 = new TH1F("isMerged1","isMerged1",2,0.,2.);
  TH1F* isMerged1_20_25 = new TH1F("isMerged1_20_25","isMerged1_20_25",2,0.,2.);
  TH1F* isMerged1_25_30 = new TH1F("isMerged1_25_30","isMerged1_25_30",2,0.,2.);
  TH1F* isMerged1_30_35 = new TH1F("isMerged1_30_35","isMerged1_30_35",2,0.,2.);
  TH1F* isMerged1_35_40 = new TH1F("isMerged1_35_40","isMerged1_35_40",2,0.,2.);
  TH1F* isMerged1_40_45 = new TH1F("isMerged1_40_45","isMerged1_40_45",2,0.,2.);
  TH1F* Merged1_vs_pt = new TH1F("Merged1_vs_pt","Merged1_vs_pt",20,20.,100.);
  TH1F* FractionOfMerged1_vs_pt = new TH1F("FractionOfMerged1_vs_pt","FractionOfMerged1_vs_pt",20,20.,100.);
  TH2F* Iso1_vs_pt = new TH2F("Iso1_vs_pt","Iso1_vs_pt",20,20.,100.,30,0.,15.);

  for(UInt_t i = 0 ; i < Tree1->GetEntries() ; ++i)
    {
      Tree1->GetEntry(i);
      if(MC_l1tEmuPt>=20. && MC_l1tEmuPt<30. && fabs(MC_l1tEmuEta)<2.1)
	{
	  Iso1->Fill(MC_l1tEmuIsoEt/2.);
	  if(MC_l1tEmuIsMerged) Iso1_NotMerged->Fill(MC_l1tEmuIsoEt/2.);
	  else Iso1_Merged->Fill(MC_l1tEmuIsoEt/2.);
	}
      if(MC_l1tEmuPt>=20. && fabs(MC_l1tEmuEta)<2.1)
	{
	  pt1->Fill(MC_l1tEmuPt);
	  isMerged1->Fill(MC_l1tEmuIsMerged);
	  if(MC_l1tEmuPt>=20. && MC_l1tEmuPt<25.) isMerged1_20_25->Fill(MC_l1tEmuIsMerged);
	  if(MC_l1tEmuPt>=25. && MC_l1tEmuPt<30.) isMerged1_25_30->Fill(MC_l1tEmuIsMerged);
	  if(MC_l1tEmuPt>=30. && MC_l1tEmuPt<35.) isMerged1_30_35->Fill(MC_l1tEmuIsMerged);
	  if(MC_l1tEmuPt>=35. && MC_l1tEmuPt<40.) isMerged1_35_40->Fill(MC_l1tEmuIsMerged);
	  if(MC_l1tEmuPt>=40. && MC_l1tEmuPt<45.) isMerged1_40_45->Fill(MC_l1tEmuIsMerged);

	  FractionOfMerged1_vs_pt->Fill(MC_l1tEmuPt);
	  if(MC_l1tEmuIsMerged==1) Merged1_vs_pt->Fill(MC_l1tEmuPt);

	  Iso1_vs_pt->Fill(MC_l1tEmuPt,MC_l1tEmuIsoEt/2.);
	}
      
    }


  TFile File2(FileName2.Data(),"READ");
  TTree * Tree2 = (TTree*)File2.Get("ZeroBias/ZeroBias");

  int ZeroBias_run;
  unsigned long long int ZeroBias_event;
  int ZeroBias_lumi;
  std::vector<int>* ZeroBias_l1tEmuQual= 0;
  std::vector<float>* ZeroBias_l1tEmuPt= 0;
  std::vector<float>* ZeroBias_l1tEmuEta= 0;
  std::vector<float>* ZeroBias_l1tEmuPhi= 0;
  std::vector<int>* ZeroBias_l1tEmuIso= 0;
  std::vector<int>* ZeroBias_l1tEmuNTT= 0;
  std::vector<int>* ZeroBias_l1tEmuHasEM= 0;
  std::vector<int>* ZeroBias_l1tEmuIsMerged= 0;
  std::vector<int>* ZeroBias_l1tEmuTowerIEta= 0;
  std::vector<int>* ZeroBias_l1tEmuTowerIPhi= 0;
  std::vector<int>* ZeroBias_l1tEmuRawEt= 0;
  std::vector<int>* ZeroBias_l1tEmuIsoEt= 0; 

  Tree2->SetBranchAddress("RunNumber",&ZeroBias_run);
  Tree2->SetBranchAddress("EventNumber",&ZeroBias_event);
  Tree2->SetBranchAddress("lumi",&ZeroBias_lumi);
  Tree2->SetBranchAddress("l1tEmuQual",&ZeroBias_l1tEmuQual);
  Tree2->SetBranchAddress("l1tEmuPt",&ZeroBias_l1tEmuPt);
  Tree2->SetBranchAddress("l1tEmuEta",&ZeroBias_l1tEmuEta);
  Tree2->SetBranchAddress("l1tEmuPhi",&ZeroBias_l1tEmuPhi);
  Tree2->SetBranchAddress("l1tEmuIso",&ZeroBias_l1tEmuIso);
  Tree2->SetBranchAddress("l1tEmuNTT",&ZeroBias_l1tEmuNTT);
  // Tree2->SetBranchAddress("l1tEmuHasEM",&ZeroBias_l1tEmuHasEM);
  Tree2->SetBranchAddress("l1tEmuIsMerged",&ZeroBias_l1tEmuIsMerged);
  Tree2->SetBranchAddress("l1tEmuTowerIEta",&ZeroBias_l1tEmuTowerIEta);
  Tree2->SetBranchAddress("l1tEmuTowerIPhi",&ZeroBias_l1tEmuTowerIPhi);
  Tree2->SetBranchAddress("l1tEmuRawEt",&ZeroBias_l1tEmuRawEt);
  Tree2->SetBranchAddress("l1tEmuIsoEt",&ZeroBias_l1tEmuIsoEt);

  TH1F* pt2 = new TH1F("pt2","pt2",40,20.,100.);
  TH1F* Iso2 = new TH1F("Iso2","Iso2",30,0.,15.);
  TH1F* Iso2_NotMerged = new TH1F("Iso2_NotMerged","Iso2_NotMerged",30,0.,15.);
  TH1F* Iso2_Merged = new TH1F("Iso2_Merged","Iso2_Merged",30,0.,15.);

  TH1F* isMerged2 = new TH1F("isMerged2","isMerged2",2,0.,2.);
  TH1F* isMerged2_20_25 = new TH1F("isMerged2_20_25","isMerged2_20_25",2,0.,2.);
  TH1F* isMerged2_25_30 = new TH1F("isMerged2_25_30","isMerged2_25_30",2,0.,2.);
  TH1F* isMerged2_30_35 = new TH1F("isMerged2_30_35","isMerged2_30_35",2,0.,2.);
  TH1F* isMerged2_35_40 = new TH1F("isMerged2_35_40","isMerged2_35_40",2,0.,2.);
  TH1F* isMerged2_40_45 = new TH1F("isMerged2_40_45","isMerged2_40_45",2,0.,2.);
  TH1F* Merged2_vs_pt = new TH1F("Merged2_vs_pt","Merged2_vs_pt",20,20.,100.);
  TH1F* FractionOfMerged2_vs_pt = new TH1F("FractionOfMerged2_vs_pt","FractionOfMerged2_vs_pt",20,20.,100.);
  TH2F* Iso2_vs_pt = new TH2F("Iso2_vs_pt","Iso2_vs_pt",20,20.,100.,30,0.,15.);

  for(UInt_t i = 0 ; i < Tree2->GetEntries() ; ++i)
    {
      Tree2->GetEntry(i);
      for(UInt_t iL1Tau = 0 ; iL1Tau < ZeroBias_l1tEmuIsoEt->size() ; ++iL1Tau)
	{
	  if(ZeroBias_l1tEmuPt->at(iL1Tau)>=20. && ZeroBias_l1tEmuPt->at(iL1Tau)<30. && fabs(ZeroBias_l1tEmuEta->at(iL1Tau))<2.1)
	    {
	      Iso2->Fill(ZeroBias_l1tEmuIsoEt->at(iL1Tau)/2.);
	      if(ZeroBias_l1tEmuIsMerged->at(iL1Tau)) Iso2_NotMerged->Fill(ZeroBias_l1tEmuIsoEt->at(iL1Tau)/2.);
	      else Iso2_Merged->Fill(ZeroBias_l1tEmuIsoEt->at(iL1Tau)/2.);
	    }
	  if(ZeroBias_l1tEmuPt->at(iL1Tau)>=20. && fabs(ZeroBias_l1tEmuEta->at(iL1Tau))<2.1)
	    {
	      pt2->Fill(ZeroBias_l1tEmuPt->at(iL1Tau));
	      isMerged2->Fill(ZeroBias_l1tEmuIsMerged->at(iL1Tau));
	      if(ZeroBias_l1tEmuPt->at(iL1Tau)>=20. && ZeroBias_l1tEmuPt->at(iL1Tau)<25.) isMerged2_20_25->Fill(ZeroBias_l1tEmuIsMerged->at(iL1Tau));
	      if(ZeroBias_l1tEmuPt->at(iL1Tau)>=25. && ZeroBias_l1tEmuPt->at(iL1Tau)<30.) isMerged2_25_30->Fill(ZeroBias_l1tEmuIsMerged->at(iL1Tau));
	      if(ZeroBias_l1tEmuPt->at(iL1Tau)>=30. && ZeroBias_l1tEmuPt->at(iL1Tau)<35.) isMerged2_30_35->Fill(ZeroBias_l1tEmuIsMerged->at(iL1Tau));
	      if(ZeroBias_l1tEmuPt->at(iL1Tau)>=35. && ZeroBias_l1tEmuPt->at(iL1Tau)<40.) isMerged2_35_40->Fill(ZeroBias_l1tEmuIsMerged->at(iL1Tau));
	      if(ZeroBias_l1tEmuPt->at(iL1Tau)>=40. && ZeroBias_l1tEmuPt->at(iL1Tau)<45.) isMerged2_40_45->Fill(ZeroBias_l1tEmuIsMerged->at(iL1Tau));

	      FractionOfMerged2_vs_pt->Fill(ZeroBias_l1tEmuPt->at(iL1Tau));
	      if(ZeroBias_l1tEmuIsMerged->at(iL1Tau)==1) Merged2_vs_pt->Fill(ZeroBias_l1tEmuPt->at(iL1Tau));

	      Iso2_vs_pt->Fill(ZeroBias_l1tEmuPt->at(iL1Tau),ZeroBias_l1tEmuIsoEt->at(iL1Tau)/2.);

	    }
	}
    }

  TString HistogramFileName = "histograms_MC_ZeroBias_";
  if(FileName2.Contains("6x9")) HistogramFileName += "6x9.root";
  if(FileName2.Contains("9x9")) HistogramFileName += "9x9.root";
 
  TFile FileHistograms(HistogramFileName.Data(),"RECREATE");
  Iso1->Write();
  Iso1_NotMerged->Write();
  Iso1_Merged->Write();
  isMerged1->Write();
  isMerged1_20_25->Write();
  isMerged1_25_30->Write();
  isMerged1_30_35->Write();
  isMerged1_35_40->Write();
  isMerged1_40_45->Write();
  Merged1_vs_pt->Divide(FractionOfMerged1_vs_pt);
  Merged1_vs_pt->Write();
  pt1->Write(),
  Iso1_vs_pt->Write();
  TProfile *AverageIso1_vs_pt = Iso1_vs_pt->ProfileX("AverageIso1_vs_pt");
  AverageIso1_vs_pt->Write();

  Iso2->Write();
  Iso2_NotMerged->Write();
  Iso2_Merged->Write();
  isMerged2->Write();
  isMerged2_20_25->Write();
  isMerged2_25_30->Write();
  isMerged2_30_35->Write();
  isMerged2_35_40->Write();
  isMerged2_40_45->Write();
  Merged2_vs_pt->Divide(FractionOfMerged2_vs_pt);
  Merged2_vs_pt->Write();
  pt2->Write();
  Iso2_vs_pt->Write();
  TProfile *AverageIso2_vs_pt = Iso2_vs_pt->ProfileX("AverageIso2_vs_pt");
  AverageIso2_vs_pt->Write();

  return;
}
