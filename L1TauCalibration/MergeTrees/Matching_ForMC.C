#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <iostream>
#include <TLorentzVector.h>
#include <TH1.h>
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

void Matching_ForMC(TString Input_file = "")
{
  TFile File(Input_file.Data(),"READ");
  TTree * Tree = (TTree*)File.Get("Ntuplizer_TagAndProbe");
  
  int m_run;
  unsigned long long int m_event;
  int m_lumi;
  float m_tauPt;
  float m_tauEta;
  float m_tauPhi;
  bool m_hasTriggerMuonType;
  bool m_hasTriggerTauType;
  bool m_isMatched;
  bool m_isOS;
  int m_foundJet;
  float m_muonPt;
  float m_muonEta;
  float m_muonPhi;
  int m_Nvtx;
  
  std::vector<int>* m_l1tQual= 0;
  std::vector<float>* m_l1tPt= 0;
  std::vector<float>* m_l1tEta= 0;
  std::vector<float>* m_l1tPhi= 0;
  std::vector<int>* m_l1tIso= 0;
  std::vector<int>* m_l1tEmuQual= 0;
  std::vector<float>* m_l1tEmuPt= 0;
  std::vector<float>* m_l1tEmuEta= 0;
  std::vector<float>* m_l1tEmuPhi= 0;
  std::vector<int>* m_l1tEmuIso= 0;
  std::vector<int>* m_l1tEmuNTT= 0;
  std::vector<int>* m_l1tEmuHasEM= 0;
  std::vector<int>* m_l1tEmuIsMerged= 0;
  std::vector<int>* m_l1tEmuTowerIEta= 0;
  std::vector<int>* m_l1tEmuTowerIPhi= 0;
  std::vector<int>* m_l1tEmuRawEt= 0;
  std::vector<int>* m_l1tEmuIsoEt= 0;  

  Tree->SetBranchAddress("RunNumber",&m_run);
  Tree->SetBranchAddress("EventNumber",&m_event);
  Tree->SetBranchAddress("lumi", &m_lumi);
  Tree->SetBranchAddress("tauPt", &m_tauPt);
  Tree->SetBranchAddress("tauEta", &m_tauEta);
  Tree->SetBranchAddress("tauPhi", &m_tauPhi);
  Tree->SetBranchAddress("hasTriggerMuonType", &m_hasTriggerMuonType);
  Tree->SetBranchAddress("hasTriggerTauType", &m_hasTriggerTauType);
  Tree->SetBranchAddress("isMatched", &m_isMatched);
  Tree->SetBranchAddress("isOS", &m_isOS);
  Tree->SetBranchAddress("foundJet", &m_foundJet);
  Tree->SetBranchAddress("muonPt", &m_muonPt);
  Tree->SetBranchAddress("muonEta", &m_muonEta);
  Tree->SetBranchAddress("muonPhi", &m_muonPhi);
  Tree->SetBranchAddress("Nvtx", &m_Nvtx);
  Tree->SetBranchAddress("l1tPt", &m_l1tPt);
  Tree->SetBranchAddress("l1tEta", &m_l1tEta);
  Tree->SetBranchAddress("l1tPhi", &m_l1tPhi);
  Tree->SetBranchAddress("l1tQual", &m_l1tQual);
  Tree->SetBranchAddress("l1tIso", &m_l1tIso);
  Tree->SetBranchAddress("l1tEmuPt",  &m_l1tEmuPt);
  Tree->SetBranchAddress("l1tEmuEta", &m_l1tEmuEta);
  Tree->SetBranchAddress("l1tEmuPhi", &m_l1tEmuPhi);
  Tree->SetBranchAddress("l1tEmuQual", &m_l1tEmuQual);
  Tree->SetBranchAddress("l1tEmuIso", &m_l1tEmuIso);
  Tree->SetBranchAddress("l1tEmuNTT", &m_l1tEmuNTT);
  Tree->SetBranchAddress("l1tEmuHasEM", &m_l1tEmuHasEM);
  Tree->SetBranchAddress("l1tEmuIsMerged", &m_l1tEmuIsMerged);
  Tree->SetBranchAddress("l1tEmuTowerIEta", &m_l1tEmuTowerIEta);
  Tree->SetBranchAddress("l1tEmuTowerIPhi", &m_l1tEmuTowerIPhi);
  Tree->SetBranchAddress("l1tEmuRawEt", &m_l1tEmuRawEt);
  Tree->SetBranchAddress("l1tEmuIsoEt", &m_l1tEmuIsoEt);


  cout<<"Tree->GetEntries() = "<<Tree->GetEntries()<<endl;


  
  TString temp = Input_file;
  Ssiz_t pos = temp.Index("_0.root");
  Ssiz_t length = 7;
  temp.Replace(pos,length,"_Out.root");

  TString outFileName = temp;
  cout<<outFileName<<endl;

  TFile outFile(outFileName.Data(),"RECREATE");
  TTree outTree("MC_withMatch","MC_withMatch");

  int out_run;
  unsigned long long int out_event;
  int out_lumi;
  float out_tauPt;
  float out_tauEta;
  float out_tauPhi;
  bool out_hasTriggerMuonType;
  bool out_hasTriggerTauType;
  bool out_isMatched;
  bool out_isOS;
  int out_foundJet;
  float out_muonPt;
  float out_muonEta;
  float out_muonPhi;
  int out_Nvtx;
  int out_l1tEmuQual= 0;
  float out_l1tEmuPt= 0;
  float out_l1tEmuEta= 0;
  float out_l1tEmuPhi= 0;
  int out_l1tEmuIso= 0;
  int out_l1tEmuNTT= 0;
  int out_l1tEmuHasEM= 0;
  int out_l1tEmuIsMerged= 0;
  int out_l1tEmuTowerIEta= 0;
  int out_l1tEmuTowerIPhi= 0;
  int out_l1tEmuRawEt= 0;
  int out_l1tEmuIsoEt= 0; 
  // int out_l1tQual= 0;
  // float out_l1tPt= 0;
  // float out_l1tEta= 0;
  // float out_l1tPhi= 0;
  // int out_l1tIso= 0;

  outTree.Branch("RunNumber",&out_run,"RunNumber/I");
  outTree.Branch("EventNumber",&out_event,"EventNumber/I");
  outTree.Branch("lumi",&out_lumi,"lumi/I");
  outTree.Branch("tauPt",&out_tauPt,"tauPt/F");
  outTree.Branch("tauEta",&out_tauEta,"tauEta/F");
  outTree.Branch("tauPhi",&out_tauPhi,"tauPhi/F");
  outTree.Branch("hasTriggerMuonType",&out_hasTriggerMuonType,"hasTriggerMuonType/O");
  outTree.Branch("hasTriggerTauType",&out_hasTriggerTauType,"hasTriggerTauType/O");
  outTree.Branch("isMatched",&out_isMatched,"isMatched/O");
  outTree.Branch("isOS",&out_isOS,"isOS/O");
  outTree.Branch("foundJet",&out_foundJet,"foundJet/I");
  outTree.Branch("muonPt",&out_muonPt,"muonPt/F");
  outTree.Branch("muonEta",&out_muonEta,"muonEta/F");
  outTree.Branch("muonPhi",&out_muonPhi,"muonPhi/F");
  outTree.Branch("Nvtx",&out_Nvtx,"Nvtx/I");
  outTree.Branch("l1tEmuQual",&out_l1tEmuQual,"l1tEmuQual/I");
  outTree.Branch("l1tEmuPt",&out_l1tEmuPt,"l1tEmuPt/F");
  outTree.Branch("l1tEmuEta",&out_l1tEmuEta,"l1tEmuEta/F");
  outTree.Branch("l1tEmuPhi",&out_l1tEmuPhi,"l1tEmuPhi/F");
  outTree.Branch("l1tEmuIso",&out_l1tEmuIso,"l1tEmuIso/I");
  outTree.Branch("l1tEmuNTT",&out_l1tEmuNTT,"l1tEmuNTT/I");
  outTree.Branch("l1tEmuHasEM",&out_l1tEmuHasEM,"l1tEmuHasEM/I");
  outTree.Branch("l1tEmuIsMerged",&out_l1tEmuIsMerged,"l1tEmuIsMerged/I");
  outTree.Branch("l1tEmuTowerIEta",&out_l1tEmuTowerIEta,"l1tEmuTowerIEta/I");
  outTree.Branch("l1tEmuTowerIPhi",&out_l1tEmuTowerIPhi,"l1tEmuTowerIPhi/I");
  outTree.Branch("l1tEmuRawEt",&out_l1tEmuRawEt,"l1tEmuRawEt/I");
  outTree.Branch("l1tEmuIsoEt",&out_l1tEmuIsoEt,"l1tEmuIsoEt/I"); 

  for(UInt_t i = 0 ; i < Tree->GetEntries() ; ++i)
    {
      Tree->GetEntry(i);

      TLorentzVector RecoTau;
      RecoTau.SetPtEtaPhiM(m_tauPt,m_tauEta,m_tauPhi,0.);

      float minDR = 0.5;

      bool foundMatch = false;
      
      for(UInt_t iL1Tau = 0 ; iL1Tau < m_l1tEmuIsoEt->size() ; iL1Tau++)
	{
	  TLorentzVector L1Tau;
	  L1Tau.SetPtEtaPhiM(m_l1tEmuPt->at(iL1Tau),m_l1tEmuEta->at(iL1Tau),m_l1tEmuPhi->at(iL1Tau),0.);
	  if(fabs(m_l1tEmuEta->at(iL1Tau))>2.1) continue;
	  float dR = RecoTau.DeltaR(L1Tau);

	  if(dR < minDR)
	    {

	      minDR = dR;
	      out_run = m_run;
	      out_event = m_event;
	      out_lumi =  m_lumi;
	      out_tauPt = m_tauPt;
	      out_tauEta = m_tauEta;
	      out_tauPhi = m_tauPhi;
	      out_hasTriggerMuonType = m_hasTriggerMuonType;
	      out_hasTriggerTauType = m_hasTriggerTauType;
	      out_isMatched = true;
	      out_isOS = m_isOS;
	      out_foundJet = m_foundJet;
	      out_muonPt = m_muonPt;
	      out_muonEta = m_muonEta;
	      out_muonPhi = m_muonPhi;
	      out_Nvtx = m_Nvtx;
	      out_l1tEmuQual = m_l1tEmuQual->at(iL1Tau);

	      out_l1tEmuPt = m_l1tEmuPt->at(iL1Tau);
	      out_l1tEmuEta = m_l1tEmuEta->at(iL1Tau);
	      out_l1tEmuPhi = m_l1tEmuPhi->at(iL1Tau);
	      out_l1tEmuIso = m_l1tEmuIso->at(iL1Tau);
	      out_l1tEmuNTT = m_l1tEmuNTT->at(iL1Tau);

	      // out_l1tEmuHasEM = m_l1tEmuHasEM->at(iL1Tau);

	      out_l1tEmuIsMerged = m_l1tEmuIsMerged->at(iL1Tau);
	      out_l1tEmuTowerIEta = m_l1tEmuTowerIEta->at(iL1Tau);

	      out_l1tEmuTowerIPhi = m_l1tEmuTowerIPhi->at(iL1Tau);
	      out_l1tEmuRawEt = m_l1tEmuRawEt->at(iL1Tau);
	      out_l1tEmuIsoEt = m_l1tEmuIsoEt->at(iL1Tau); 
	      

	      foundMatch = true;
	    }
	  
	}

      if(foundMatch) outTree.Fill();
      
    }

  outTree.Write();
  

  return;
}
