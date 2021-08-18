


#include "TauStage2Trees.h"

#include "TTree.h"
#include "TChain.h"

#include <iostream>


/*****************************************************************/
void TauStage2Trees::linkMainVariables()
/*****************************************************************/
{
    // main tree: offline and truth variable
    m_mainTree->SetBranchStatus("RunNumber"         , true);
    m_mainTree->SetBranchStatus("EventNumber"       , true);
    m_mainTree->SetBranchStatus("lumi"       , true);
    m_mainTree->SetBranchStatus("tauTriggerBits"       , true);
    m_mainTree->SetBranchStatus("tauPt"       , true);
    m_mainTree->SetBranchStatus("tauEta"       , true);
    m_mainTree->SetBranchStatus("tauPhi"       , true);
    //m_mainTree->SetBranchStatus("tauCharge"       , true);
    //m_mainTree->SetBranchStatus("tauDecayMode"       , true);
    // m_mainTree->SetBranchStatus("muonPt"       , true);
    // m_mainTree->SetBranchStatus("muonEta"       , true);
    // m_mainTree->SetBranchStatus("muonPhi"       , true);
    m_mainTree->SetBranchStatus("hasTriggerMuonType"       , true);
    m_mainTree->SetBranchStatus("hasTriggerTauType"       , true);
    m_mainTree->SetBranchStatus("isMatched"       , true);
    m_mainTree->SetBranchStatus("isOS"       , true);
    m_mainTree->SetBranchStatus("foundJet"       , true);
    m_mainTree->SetBranchStatus("Nvtx"       , true);


    m_mainTree->SetBranchAddress("RunNumber"         , &m_run);
    m_mainTree->SetBranchAddress("EventNumber"       , &m_event);
    m_mainTree->SetBranchAddress("lumi"         , &m_lumi);
    m_mainTree->SetBranchAddress("tauPt"         , &m_tauPt);
    m_mainTree->SetBranchAddress("tauEta"         , &m_tauEta);
    m_mainTree->SetBranchAddress("tauPhi"         , &m_tauPhi);
    //m_mainTree->SetBranchAddress("tauCharge"         , &m_tauCharge);
    //m_mainTree->SetBranchAddress("tauDecayMode"         , &m_tauDecayMode);
    m_mainTree->SetBranchAddress("hasTriggerMuonType"         , &m_hasTriggerMuonType);
    m_mainTree->SetBranchAddress("hasTriggerTauType"         , &m_hasTriggerTauType);
    m_mainTree->SetBranchAddress("isMatched"         , &m_isMatched);
    m_mainTree->SetBranchAddress("isOS"         , &m_isOS);
    m_mainTree->SetBranchAddress("foundJet"         , &m_foundJet);
    // m_mainTree->SetBranchAddress("muonPt"         , &m_muonPt);
    // m_mainTree->SetBranchAddress("muonEta"         , &m_muonEta);
    // m_mainTree->SetBranchAddress("muonPhi"         , &m_muonPhi);
    m_mainTree->SetBranchAddress("Nvtx"         , &m_Nvtx);

}

/*****************************************************************/
void TauStage2Trees::linkSecondaryVariables()
/*****************************************************************/
{
    // Stage-2 secondary tree 
    m_secondaryTrees[0]->SetBranchStatus("RunNumber"         , true);
    m_secondaryTrees[0]->SetBranchStatus("EventNumber"       , true);
    m_secondaryTrees[0]->SetBranchStatus("l1tPt",  true);
    m_secondaryTrees[0]->SetBranchStatus("l1tEta", true);
    m_secondaryTrees[0]->SetBranchStatus("l1tPhi", true);
    m_secondaryTrees[0]->SetBranchStatus("l1tQual", true);
    m_secondaryTrees[0]->SetBranchStatus("l1tIso", true);
    m_secondaryTrees[0]->SetBranchStatus("l1tEmuPt",  true);
    m_secondaryTrees[0]->SetBranchStatus("l1tEmuEta", true);
    m_secondaryTrees[0]->SetBranchStatus("l1tEmuPhi", true);
    m_secondaryTrees[0]->SetBranchStatus("l1tEmuQual", true);
    m_secondaryTrees[0]->SetBranchStatus("l1tEmuIso", true);
    m_secondaryTrees[0]->SetBranchStatus("l1tEmuNTT", true);
    m_secondaryTrees[0]->SetBranchStatus("l1tEmuHasEM", true);
    m_secondaryTrees[0]->SetBranchStatus("l1tEmuIsMerged", true);
    m_secondaryTrees[0]->SetBranchStatus("l1tEmuTowerIEta", true);
    m_secondaryTrees[0]->SetBranchStatus("l1tEmuTowerIPhi", true);
    m_secondaryTrees[0]->SetBranchStatus("l1tEmuRawEt", true);
    m_secondaryTrees[0]->SetBranchStatus("l1tEmuIsoEt", true);

    m_secondaryTrees[0]->SetBranchAddress("l1tPt", &m_l1tPt);
    m_secondaryTrees[0]->SetBranchAddress("l1tEta", &m_l1tEta);
    m_secondaryTrees[0]->SetBranchAddress("l1tPhi", &m_l1tPhi);
    m_secondaryTrees[0]->SetBranchAddress("l1tQual", &m_l1tQual);
    m_secondaryTrees[0]->SetBranchAddress("l1tIso", &m_l1tIso);
    m_secondaryTrees[0]->SetBranchAddress("l1tEmuPt",  &m_l1tEmuPt);
    m_secondaryTrees[0]->SetBranchAddress("l1tEmuEta", &m_l1tEmuEta);
    m_secondaryTrees[0]->SetBranchAddress("l1tEmuPhi", &m_l1tEmuPhi);
    m_secondaryTrees[0]->SetBranchAddress("l1tEmuQual", &m_l1tEmuQual);
    m_secondaryTrees[0]->SetBranchAddress("l1tEmuIso", &m_l1tEmuIso);
    m_secondaryTrees[0]->SetBranchAddress("l1tEmuNTT", &m_l1tEmuNTT);
    m_secondaryTrees[0]->SetBranchAddress("l1tEmuHasEM", &m_l1tEmuHasEM);
    m_secondaryTrees[0]->SetBranchAddress("l1tEmuIsMerged", &m_l1tEmuIsMerged);
    m_secondaryTrees[0]->SetBranchAddress("l1tEmuTowerIEta", &m_l1tEmuTowerIEta);
    m_secondaryTrees[0]->SetBranchAddress("l1tEmuTowerIPhi", &m_l1tEmuTowerIPhi);
    m_secondaryTrees[0]->SetBranchAddress("l1tEmuRawEt", &m_l1tEmuRawEt);
    m_secondaryTrees[0]->SetBranchAddress("l1tEmuIsoEt", &m_l1tEmuIsoEt);

    // Build event indices for secondary trees
    for(auto itr=m_secondaryTrees.begin(); itr!=m_secondaryTrees.end(); itr++)
    {
        (*itr)->BuildIndex("RunNumber", "EventNumber");
    }

}

/*****************************************************************/
void TauStage2Trees::linkOutputVariables()
/*****************************************************************/
{

  m_lumi=0;
  m_tauPt=0;
  m_tauEta=0;
  m_tauPhi=0;
  m_tauCharge=0;
  m_tauDecayMode=0;
  m_hasTriggerMuonType=0;
  m_hasTriggerTauType=0;
  m_isMatched=0;
  m_isOS=0;
  m_foundJet=0;
  // m_muonPt=0;
  // m_muonEta=0;
  // m_muonPhi=0;
  m_Nvtx=0;

  m_l1tQual=0;
  m_l1tPt=0;
  m_l1tEta=0;
  m_l1tPhi=0;
  m_l1tIso=0;
  m_l1tEmuQual=0;
  m_l1tEmuPt=0;
  m_l1tEmuEta=0;
  m_l1tEmuPhi=0;
  m_l1tEmuIso=0;
  m_l1tEmuNTT=0;
  m_l1tEmuHasEM=0;
  m_l1tEmuIsMerged=0;
  m_l1tEmuTowerIEta=0;
  m_l1tEmuTowerIPhi=0;
  m_l1tEmuRawEt=0;
  m_l1tEmuIsoEt=0;


  // m_l1tQual->clear();
  // m_l1tPt->clear();
  // m_l1tEta->clear();
  // m_l1tPhi->clear();
  // m_l1tIso->clear();
  // m_l1tEmuQual->clear();
  // m_l1tEmuPt->clear();
  // m_l1tEmuEta->clear();
  // m_l1tEmuPhi->clear();
  // m_l1tEmuIso->clear();
  // m_l1tEmuNTT->clear();
  // m_l1tEmuHasEM->clear();
  // m_l1tEmuIsMerged->clear();
  // m_l1tEmuTowerIEta->clear();
  // m_l1tEmuTowerIPhi->clear();
  // m_l1tEmuRawEt->clear();
  // m_l1tEmuIsoEt->clear();

  // Output tree
  m_outputTree->Branch("RunNumber",  &m_run,        "RunNumber/I");
  m_outputTree->Branch("EventNumber", &m_event,     "EventNumber/l");

  m_outputTree->Branch("lumi"         , &m_lumi);
  m_outputTree->Branch("tauPt"         , &m_tauPt);
  m_outputTree->Branch("tauEta"         , &m_tauEta);
  m_outputTree->Branch("tauPhi"         , &m_tauPhi);
  m_outputTree->Branch("tauCharge"         , &m_tauCharge);
  m_outputTree->Branch("tauDecayMode"         , &m_tauDecayMode);
  m_outputTree->Branch("hasTriggerMuonType"         , &m_hasTriggerMuonType);
  m_outputTree->Branch("hasTriggerTauType"         , &m_hasTriggerTauType);
  m_outputTree->Branch("isMatched"         , &m_isMatched);
  m_outputTree->Branch("isOS"         , &m_isOS);
  m_outputTree->Branch("foundJet"         , &m_foundJet);
  // m_outputTree->Branch("muonPt"         , &m_muonPt);
  // m_outputTree->Branch("muonEta"         , &m_muonEta);
  // m_outputTree->Branch("muonPhi"         , &m_muonPhi);
  m_outputTree->Branch("Nvtx"         , &m_Nvtx);
  m_outputTree->Branch("l1tPt", &m_l1tPt);
  m_outputTree->Branch("l1tEta", &m_l1tEta);
  m_outputTree->Branch("l1tPhi", &m_l1tPhi);
  m_outputTree->Branch("l1tQual", &m_l1tQual);
  m_outputTree->Branch("l1tIso", &m_l1tIso);
  m_outputTree->Branch("l1tEmuPt",  &m_l1tEmuPt);
  m_outputTree->Branch("l1tEmuEta", &m_l1tEmuEta);
  m_outputTree->Branch("l1tEmuPhi", &m_l1tEmuPhi);
  m_outputTree->Branch("l1tEmuQual", &m_l1tEmuQual);
  m_outputTree->Branch("l1tEmuIso", &m_l1tEmuIso);
  m_outputTree->Branch("l1tEmuNTT", &m_l1tEmuNTT);
  m_outputTree->Branch("l1tEmuHasEM", &m_l1tEmuHasEM);
  m_outputTree->Branch("l1tEmuIsMerged", &m_l1tEmuIsMerged);
  m_outputTree->Branch("l1tEmuTowerIEta", &m_l1tEmuTowerIEta);
  m_outputTree->Branch("l1tEmuTowerIPhi", &m_l1tEmuTowerIPhi);
  m_outputTree->Branch("l1tEmuRawEt", &m_l1tEmuRawEt);
  m_outputTree->Branch("l1tEmuIsoEt", &m_l1tEmuIsoEt);

}



/*****************************************************************/
void TauStage2Trees::resetVariables()
/*****************************************************************/
{
  ITrees::resetVariables();

  m_lumi=0;
  m_tauPt=0;
  m_tauEta=0;
  m_tauPhi=0;
  m_tauCharge=0;
  m_tauDecayMode=0;
  m_hasTriggerMuonType=0;
  m_hasTriggerTauType=0;
  m_isMatched=0;
  m_isOS=0;
  m_foundJet=0;
  // m_muonPt=0;
  // m_muonEta=0;
  // m_muonPhi=0;
  m_Nvtx=0;

  m_l1tQual->clear();
  m_l1tPt->clear();
  m_l1tEta->clear();
  m_l1tPhi->clear();
  m_l1tIso->clear();
  m_l1tEmuQual->clear();
  m_l1tEmuPt->clear();
  m_l1tEmuEta->clear();
  m_l1tEmuPhi->clear();
  m_l1tEmuIso->clear();
  m_l1tEmuNTT->clear();
  m_l1tEmuHasEM->clear();
  m_l1tEmuIsMerged->clear();
  m_l1tEmuTowerIEta->clear();
  m_l1tEmuTowerIPhi->clear();
  m_l1tEmuRawEt->clear();
  m_l1tEmuIsoEt->clear();

}
