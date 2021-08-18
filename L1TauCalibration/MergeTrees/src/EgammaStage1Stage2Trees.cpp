


#include "EgammaStage1Stage2Trees.h"

#include "TTree.h"
#include "TChain.h"

#include <iostream>


/*****************************************************************/
void EgammaStage1Stage2Trees::linkMainVariables()
/*****************************************************************/
{


    // main tree: offline and truth variable
    m_mainTree->SetBranchStatus("run"         , true);
    m_mainTree->SetBranchStatus("event"       , true);
    m_mainTree->SetBranchStatus("npv"         , true);
    m_mainTree->SetBranchStatus("npu"         , true);
    m_mainTree->SetBranchStatus("rho"         , true);

    m_mainTree->SetBranchStatus("ele_n"            , true);
    m_mainTree->SetBranchStatus("ele_pt"           , true);
    m_mainTree->SetBranchStatus("ele_et"           , true);
    m_mainTree->SetBranchStatus("ele_E"            , true);
    m_mainTree->SetBranchStatus("ele_eta"          , true);
    m_mainTree->SetBranchStatus("ele_phi"          , true);
    m_mainTree->SetBranchStatus("ele_charge"       , true);
    m_mainTree->SetBranchStatus("ele_sc_E"         , true);
    m_mainTree->SetBranchStatus("ele_sc_eta"       , true);
    m_mainTree->SetBranchStatus("ele_sc_phi"       , true);
    m_mainTree->SetBranchStatus("ele_ncl"          , true);
    m_mainTree->SetBranchStatus("ele_class"        , true);
    m_mainTree->SetBranchStatus("ele_isEB"         , true);
    m_mainTree->SetBranchStatus("ele_isEE"         , true);
    m_mainTree->SetBranchStatus("ele_isEBEEGap"    , true);
    m_mainTree->SetBranchStatus("ele_isEBGap"      , true);
    m_mainTree->SetBranchStatus("ele_isEEGap"      , true);
    m_mainTree->SetBranchStatus("ele_bdt"          , true);
    m_mainTree->SetBranchStatus("ele_pass"         , true);
    m_mainTree->SetBranchStatus("ele_seedtt_ieta"  , true);
    m_mainTree->SetBranchStatus("ele_seedtt_iphi"  , true);
    m_mainTree->SetBranchStatus("ele_tt_ieta"      , true);
    m_mainTree->SetBranchStatus("ele_tt_iphi"      , true);
    m_mainTree->SetBranchStatus("ele_tt_E"         , true);
    m_mainTree->SetBranchStatus("ele_rct_ieta"     , true);
    m_mainTree->SetBranchStatus("ele_rct_iphi"     , true);

    m_mainTree->SetBranchStatus("truthele_n"            , true);
    m_mainTree->SetBranchStatus("truthele_pt"           , true);
    m_mainTree->SetBranchStatus("truthele_E"            , true);
    m_mainTree->SetBranchStatus("truthele_eta"          , true);
    m_mainTree->SetBranchStatus("truthele_phi"          , true);
    m_mainTree->SetBranchStatus("truthele_charge"       , true);
    m_mainTree->SetBranchStatus("truthele_recoMatch"    , true);


    m_mainTree->SetBranchAddress("run"         , &m_run);
    m_mainTree->SetBranchAddress("event"       , &m_event);
    m_mainTree->SetBranchAddress("npv"         , &m_npv);
    m_mainTree->SetBranchAddress("npu"         , &m_npu);
    m_mainTree->SetBranchAddress("rho"         , &m_rho);

    m_mainTree->SetBranchAddress("ele_n"            , &m_ele_n);
    m_mainTree->SetBranchAddress("ele_pt"           , &m_ele_pt);
    m_mainTree->SetBranchAddress("ele_et"           , &m_ele_et);
    m_mainTree->SetBranchAddress("ele_E"            , &m_ele_E);
    m_mainTree->SetBranchAddress("ele_eta"          , &m_ele_eta);
    m_mainTree->SetBranchAddress("ele_phi"          , &m_ele_phi);
    m_mainTree->SetBranchAddress("ele_charge"       , &m_ele_charge);
    m_mainTree->SetBranchAddress("ele_sc_E"         , &m_ele_sc_E);
    m_mainTree->SetBranchAddress("ele_sc_eta"       , &m_ele_sc_eta);
    m_mainTree->SetBranchAddress("ele_sc_phi"       , &m_ele_sc_phi);
    m_mainTree->SetBranchAddress("ele_ncl"          , &m_ele_ncl);
    m_mainTree->SetBranchAddress("ele_class"        , &m_ele_class);
    m_mainTree->SetBranchAddress("ele_isEB"         , &m_ele_isEB);
    m_mainTree->SetBranchAddress("ele_isEE"         , &m_ele_isEE);
    m_mainTree->SetBranchAddress("ele_isEBEEGap"    , &m_ele_isEBEEGap);
    m_mainTree->SetBranchAddress("ele_isEBGap"      , &m_ele_isEBGap);
    m_mainTree->SetBranchAddress("ele_isEEGap"      , &m_ele_isEEGap);
    m_mainTree->SetBranchAddress("ele_bdt"          , &m_ele_bdt);
    m_mainTree->SetBranchAddress("ele_pass"         , &m_ele_pass);
    m_mainTree->SetBranchAddress("ele_seedtt_ieta"  , &m_ele_seedtt_ieta);
    m_mainTree->SetBranchAddress("ele_seedtt_iphi"  , &m_ele_seedtt_iphi);
    m_mainTree->SetBranchAddress("ele_tt_ieta"      , &m_ele_tt_ieta);
    m_mainTree->SetBranchAddress("ele_tt_iphi"      , &m_ele_tt_iphi);
    m_mainTree->SetBranchAddress("ele_tt_E"         , &m_ele_tt_E);
    m_mainTree->SetBranchAddress("ele_rct_ieta"     , &m_ele_rct_ieta);
    m_mainTree->SetBranchAddress("ele_rct_iphi"     , &m_ele_rct_iphi);

    m_mainTree->SetBranchAddress("truthele_n"            , &m_truthele_n);
    m_mainTree->SetBranchAddress("truthele_pt"           , &m_truthele_pt);
    m_mainTree->SetBranchAddress("truthele_E"            , &m_truthele_E);
    m_mainTree->SetBranchAddress("truthele_eta"          , &m_truthele_eta);
    m_mainTree->SetBranchAddress("truthele_phi"          , &m_truthele_phi);
    m_mainTree->SetBranchAddress("truthele_charge"       , &m_truthele_charge);
    m_mainTree->SetBranchAddress("truthele_recoMatch"    , &m_truthele_recoMatch);

}

/*****************************************************************/
void EgammaStage1Stage2Trees::linkSecondaryVariables()
/*****************************************************************/
{

    //m_l1t_stage2_tower_hwEta     = 0;
    //m_l1t_stage2_tower_hwPt      = 0;
    //m_l1t_stage2_tower_hwEtEm    = 0;
    //m_l1t_stage2_tower_hwEtHad   = 0;
    //m_l1t_stage2_tower_hwEtRatio = 0;
    //m_l1t_stage2_tower_hwQual    = 0;

    // Stage-2 secondary tree 
    m_secondaryTrees[0]->SetBranchStatus("run"         , true);
    m_secondaryTrees[0]->SetBranchStatus("event"       , true);

    m_secondaryTrees[0]->SetBranchStatus("l1t_stage2_tower_n"         , true);
    m_secondaryTrees[0]->SetBranchStatus("l1t_stage2_tower_hwEta"     , true);
    m_secondaryTrees[0]->SetBranchStatus("l1t_stage2_tower_hwPhi"     , true);
    m_secondaryTrees[0]->SetBranchStatus("l1t_stage2_tower_hwEtEm"    , true);
    m_secondaryTrees[0]->SetBranchStatus("l1t_stage2_tower_hwEtHad"   , true);
    m_secondaryTrees[0]->SetBranchStatus("l1t_stage2_tower_hwEtRatio" , true);
    m_secondaryTrees[0]->SetBranchStatus("l1t_stage2_tower_hwQual"    , true);

    m_secondaryTrees[0]->SetBranchStatus("l1t_stage2_eg_n"     , true);
    m_secondaryTrees[0]->SetBranchStatus("l1t_stage2_eg_pt"    , true);
    m_secondaryTrees[0]->SetBranchStatus("l1t_stage2_eg_eta"   , true);
    m_secondaryTrees[0]->SetBranchStatus("l1t_stage2_eg_phi"   , true);
    m_secondaryTrees[0]->SetBranchStatus("l1t_stage2_eg_hwPt"  , true);
    m_secondaryTrees[0]->SetBranchStatus("l1t_stage2_eg_hwEta" , true);
    m_secondaryTrees[0]->SetBranchStatus("l1t_stage2_eg_hwPhi" , true);
    m_secondaryTrees[0]->SetBranchStatus("l1t_stage2_eg_hwQual", true);
    m_secondaryTrees[0]->SetBranchStatus("l1t_stage2_eg_hwIso" , true);


    m_secondaryTrees[0]->SetBranchAddress("l1t_stage2_tower_n"         , &m_l1t_stage2_tower_n);
    m_secondaryTrees[0]->SetBranchAddress("l1t_stage2_tower_hwEta"     , &m_l1t_stage2_tower_hwEta);
    m_secondaryTrees[0]->SetBranchAddress("l1t_stage2_tower_hwPhi"     , &m_l1t_stage2_tower_hwPhi);
    m_secondaryTrees[0]->SetBranchAddress("l1t_stage2_tower_hwEtEm"    , &m_l1t_stage2_tower_hwEtEm);
    m_secondaryTrees[0]->SetBranchAddress("l1t_stage2_tower_hwEtHad"   , &m_l1t_stage2_tower_hwEtHad);
    m_secondaryTrees[0]->SetBranchAddress("l1t_stage2_tower_hwEtRatio" , &m_l1t_stage2_tower_hwEtRatio);
    m_secondaryTrees[0]->SetBranchAddress("l1t_stage2_tower_hwQual"    , &m_l1t_stage2_tower_hwQual);

    m_secondaryTrees[0]->SetBranchAddress("l1t_stage2_eg_n"     , &m_l1t_stage2_eg_n);
    m_secondaryTrees[0]->SetBranchAddress("l1t_stage2_eg_pt"    , &m_l1t_stage2_eg_pt);
    m_secondaryTrees[0]->SetBranchAddress("l1t_stage2_eg_eta"   , &m_l1t_stage2_eg_eta);
    m_secondaryTrees[0]->SetBranchAddress("l1t_stage2_eg_phi"   , &m_l1t_stage2_eg_phi);
    m_secondaryTrees[0]->SetBranchAddress("l1t_stage2_eg_hwPt"  , &m_l1t_stage2_eg_hwPt);
    m_secondaryTrees[0]->SetBranchAddress("l1t_stage2_eg_hwEta" , &m_l1t_stage2_eg_hwEta);
    m_secondaryTrees[0]->SetBranchAddress("l1t_stage2_eg_hwPhi" , &m_l1t_stage2_eg_hwPhi);
    m_secondaryTrees[0]->SetBranchAddress("l1t_stage2_eg_hwQual", &m_l1t_stage2_eg_hwQual);
    m_secondaryTrees[0]->SetBranchAddress("l1t_stage2_eg_hwIso" , &m_l1t_stage2_eg_hwIso);

    // Stage-1 secondary tree 
    m_secondaryTrees[1]->SetBranchStatus("run"         , true);
    m_secondaryTrees[1]->SetBranchStatus("event"       , true);

    m_secondaryTrees[1]->SetBranchStatus("l1t_stage1_eg_n"     , true);
    m_secondaryTrees[1]->SetBranchStatus("l1t_stage1_eg_pt"    , true);
    m_secondaryTrees[1]->SetBranchStatus("l1t_stage1_eg_eta"   , true);
    m_secondaryTrees[1]->SetBranchStatus("l1t_stage1_eg_phi"   , true);
    m_secondaryTrees[1]->SetBranchStatus("l1t_stage1_eg_hwPt"  , true);
    m_secondaryTrees[1]->SetBranchStatus("l1t_stage1_eg_hwEta" , true);
    m_secondaryTrees[1]->SetBranchStatus("l1t_stage1_eg_hwPhi" , true);
    m_secondaryTrees[1]->SetBranchStatus("l1t_stage1_eg_hwQual", true);
    m_secondaryTrees[1]->SetBranchStatus("l1t_stage1_eg_hwIso" , true);

    m_secondaryTrees[1]->SetBranchAddress("l1t_stage1_eg_n"     , &m_l1t_stage1_eg_n);
    m_secondaryTrees[1]->SetBranchAddress("l1t_stage1_eg_pt"    , &m_l1t_stage1_eg_pt);
    m_secondaryTrees[1]->SetBranchAddress("l1t_stage1_eg_eta"   , &m_l1t_stage1_eg_eta);
    m_secondaryTrees[1]->SetBranchAddress("l1t_stage1_eg_phi"   , &m_l1t_stage1_eg_phi);
    m_secondaryTrees[1]->SetBranchAddress("l1t_stage1_eg_hwPt"  , &m_l1t_stage1_eg_hwPt);
    m_secondaryTrees[1]->SetBranchAddress("l1t_stage1_eg_hwEta" , &m_l1t_stage1_eg_hwEta);
    m_secondaryTrees[1]->SetBranchAddress("l1t_stage1_eg_hwPhi" , &m_l1t_stage1_eg_hwPhi);
    m_secondaryTrees[1]->SetBranchAddress("l1t_stage1_eg_hwQual", &m_l1t_stage1_eg_hwQual);
    m_secondaryTrees[1]->SetBranchAddress("l1t_stage1_eg_hwIso" , &m_l1t_stage1_eg_hwIso);

    // Build event indices for secondary trees
    for(auto itr=m_secondaryTrees.begin(); itr!=m_secondaryTrees.end(); itr++)
    {
        (*itr)->BuildIndex("run", "event");
    }

}

/*****************************************************************/
void EgammaStage1Stage2Trees::linkOutputVariables()
/*****************************************************************/
{
    m_ele_pt          = 0;
    m_ele_et          = 0;
    m_ele_E           = 0;
    m_ele_eta         = 0;
    m_ele_phi         = 0;
    m_ele_charge      = 0;
    m_ele_sc_E        = 0;
    m_ele_sc_eta      = 0;
    m_ele_sc_phi      = 0;
    m_ele_ncl         = 0;
    m_ele_class       = 0;
    m_ele_isEB        = 0;
    m_ele_isEE        = 0;
    m_ele_isEBEEGap   = 0;
    m_ele_isEBGap     = 0;
    m_ele_isEEGap     = 0;
    m_ele_bdt         = 0;
    m_ele_pass        = 0;
    m_ele_seedtt_ieta = 0;
    m_ele_seedtt_iphi = 0;
    m_ele_tt_ieta     = 0;
    m_ele_tt_iphi     = 0;
    m_ele_tt_E        = 0;
    m_ele_rct_ieta    = 0;
    m_ele_rct_iphi    = 0;

    m_truthele_pt          = 0;
    m_truthele_E           = 0;
    m_truthele_eta         = 0;
    m_truthele_phi         = 0;
    m_truthele_charge      = 0;
    m_truthele_recoMatch   = 0;

    m_l1t_stage2_tower_hwEta     = 0;
    m_l1t_stage2_tower_hwPhi     = 0;
    m_l1t_stage2_tower_hwEtEm    = 0;
    m_l1t_stage2_tower_hwEtHad   = 0;
    m_l1t_stage2_tower_hwEtRatio = 0;
    m_l1t_stage2_tower_hwQual    = 0;

    m_l1t_stage2_eg_pt     = 0;
    m_l1t_stage2_eg_eta    = 0;
    m_l1t_stage2_eg_phi    = 0;
    m_l1t_stage2_eg_hwPt   = 0;
    m_l1t_stage2_eg_hwEta  = 0;
    m_l1t_stage2_eg_hwPhi  = 0;
    m_l1t_stage2_eg_hwQual = 0;
    m_l1t_stage2_eg_hwIso  = 0;

    m_l1t_stage1_eg_pt     = 0;
    m_l1t_stage1_eg_eta    = 0;
    m_l1t_stage1_eg_phi    = 0;
    m_l1t_stage1_eg_hwPt   = 0;
    m_l1t_stage1_eg_hwEta  = 0;
    m_l1t_stage1_eg_hwPhi  = 0;
    m_l1t_stage1_eg_hwQual = 0;
    m_l1t_stage1_eg_hwIso  = 0;

    // Output tree
    m_outputTree->Branch("run",  &m_run,        "run/I");
    m_outputTree->Branch("event", &m_event,     "event/I");
    m_outputTree->Branch("rho",  &m_rho,        "rho/D");
    m_outputTree->Branch("npv",  &m_npv,        "npv/I");
    m_outputTree->Branch("npu",  &m_npu,        "npu/I");

    m_outputTree->Branch("ele_n"            , &m_ele_n, "ele_n/I");
    m_outputTree->Branch("ele_pt"           , &m_ele_pt);
    m_outputTree->Branch("ele_et"           , &m_ele_et);
    m_outputTree->Branch("ele_E"            , &m_ele_E);
    m_outputTree->Branch("ele_eta"          , &m_ele_eta);
    m_outputTree->Branch("ele_phi"          , &m_ele_phi);
    m_outputTree->Branch("ele_charge"       , &m_ele_charge);
    m_outputTree->Branch("ele_sc_E"         , &m_ele_sc_E);
    m_outputTree->Branch("ele_sc_eta"       , &m_ele_sc_eta);
    m_outputTree->Branch("ele_sc_phi"       , &m_ele_sc_phi);
    m_outputTree->Branch("ele_ncl"          , &m_ele_ncl);
    m_outputTree->Branch("ele_class"        , &m_ele_class);
    m_outputTree->Branch("ele_isEB"         , &m_ele_isEB);
    m_outputTree->Branch("ele_isEE"         , &m_ele_isEE);
    m_outputTree->Branch("ele_isEBEEGap"    , &m_ele_isEBEEGap);
    m_outputTree->Branch("ele_isEBGap"      , &m_ele_isEBGap);
    m_outputTree->Branch("ele_isEEGap"      , &m_ele_isEEGap);
    m_outputTree->Branch("ele_bdt"          , &m_ele_bdt);
    m_outputTree->Branch("ele_pass"         , &m_ele_pass);
    m_outputTree->Branch("ele_seedtt_ieta"  , &m_ele_seedtt_ieta);
    m_outputTree->Branch("ele_seedtt_iphi"  , &m_ele_seedtt_iphi);
    m_outputTree->Branch("ele_tt_ieta"      , &m_ele_tt_ieta);
    m_outputTree->Branch("ele_tt_iphi"      , &m_ele_tt_iphi);
    m_outputTree->Branch("ele_tt_E"         , &m_ele_tt_E);
    m_outputTree->Branch("ele_rct_ieta"     , &m_ele_rct_ieta);
    m_outputTree->Branch("ele_rct_iphi"     , &m_ele_rct_iphi);

    m_outputTree->Branch("truthele_n"            , &m_truthele_n, "truthele_n/I");
    m_outputTree->Branch("truthele_pt"           , &m_truthele_pt);
    m_outputTree->Branch("truthele_E"            , &m_truthele_E);
    m_outputTree->Branch("truthele_eta"          , &m_truthele_eta);
    m_outputTree->Branch("truthele_phi"          , &m_truthele_phi);
    m_outputTree->Branch("truthele_charge"       , &m_truthele_charge);
    m_outputTree->Branch("truthele_recoMatch"    , &m_truthele_recoMatch);

    m_outputTree->Branch("l1t_stage2_tower_n"         , &m_l1t_stage2_tower_n,   "l1t_stage2_tower_n/I");
    m_outputTree->Branch("l1t_stage2_tower_hwEta"     , &m_l1t_stage2_tower_hwEta);
    m_outputTree->Branch("l1t_stage2_tower_hwPhi"     , &m_l1t_stage2_tower_hwPhi);
    m_outputTree->Branch("l1t_stage2_tower_hwEtEm"    , &m_l1t_stage2_tower_hwEtEm);
    m_outputTree->Branch("l1t_stage2_tower_hwEtHad"   , &m_l1t_stage2_tower_hwEtHad);
    m_outputTree->Branch("l1t_stage2_tower_hwEtRatio" , &m_l1t_stage2_tower_hwEtRatio);
    m_outputTree->Branch("l1t_stage2_tower_hwQual"    , &m_l1t_stage2_tower_hwQual);


    m_outputTree->Branch("l1t_stage2_eg_n"     , &m_l1t_stage2_eg_n, "l1t_stage2_eg_n/I");
    m_outputTree->Branch("l1t_stage2_eg_pt"    , &m_l1t_stage2_eg_pt);
    m_outputTree->Branch("l1t_stage2_eg_eta"   , &m_l1t_stage2_eg_eta);
    m_outputTree->Branch("l1t_stage2_eg_phi"   , &m_l1t_stage2_eg_phi);
    m_outputTree->Branch("l1t_stage2_eg_hwPt"  , &m_l1t_stage2_eg_hwPt);
    m_outputTree->Branch("l1t_stage2_eg_hwEta" , &m_l1t_stage2_eg_hwEta);
    m_outputTree->Branch("l1t_stage2_eg_hwPhi" , &m_l1t_stage2_eg_hwPhi);
    m_outputTree->Branch("l1t_stage2_eg_hwQual", &m_l1t_stage2_eg_hwQual);
    m_outputTree->Branch("l1t_stage2_eg_hwIso" , &m_l1t_stage2_eg_hwIso);

    m_outputTree->Branch("l1t_stage1_eg_n"     , &m_l1t_stage1_eg_n, "l1t_stage1_eg_n/I");
    m_outputTree->Branch("l1t_stage1_eg_pt"    , &m_l1t_stage1_eg_pt);
    m_outputTree->Branch("l1t_stage1_eg_eta"   , &m_l1t_stage1_eg_eta);
    m_outputTree->Branch("l1t_stage1_eg_phi"   , &m_l1t_stage1_eg_phi);
    m_outputTree->Branch("l1t_stage1_eg_hwPt"  , &m_l1t_stage1_eg_hwPt);
    m_outputTree->Branch("l1t_stage1_eg_hwEta" , &m_l1t_stage1_eg_hwEta);
    m_outputTree->Branch("l1t_stage1_eg_hwPhi" , &m_l1t_stage1_eg_hwPhi);
    m_outputTree->Branch("l1t_stage1_eg_hwQual", &m_l1t_stage1_eg_hwQual);
    m_outputTree->Branch("l1t_stage1_eg_hwIso" , &m_l1t_stage1_eg_hwIso);
}



/*****************************************************************/
void EgammaStage1Stage2Trees::resetVariables()
/*****************************************************************/
{
    ITrees::resetVariables();

    m_npv       = 0;
    m_npu       = 0;
    m_rho       = 0.;


    m_ele_n       = 0;
    m_ele_pt          ->clear();
    m_ele_et          ->clear();
    m_ele_E           ->clear();
    m_ele_eta         ->clear();
    m_ele_phi         ->clear();
    m_ele_charge      ->clear();
    m_ele_sc_E        ->clear();
    m_ele_sc_eta      ->clear();
    m_ele_sc_phi      ->clear();
    m_ele_ncl         ->clear();
    m_ele_class       ->clear();
    m_ele_isEB        ->clear();
    m_ele_isEE        ->clear();
    m_ele_isEBEEGap   ->clear();
    m_ele_isEBGap     ->clear();
    m_ele_isEEGap     ->clear();
    m_ele_bdt         ->clear();
    m_ele_pass        ->clear();
    m_ele_seedtt_ieta ->clear();
    m_ele_seedtt_iphi ->clear();
    m_ele_tt_ieta     ->clear();
    m_ele_tt_iphi     ->clear();
    m_ele_tt_E        ->clear();
    m_ele_rct_ieta    ->clear();
    m_ele_rct_iphi    ->clear();

    m_truthele_n       = 0;
    m_truthele_pt          ->clear();
    m_truthele_E           ->clear();
    m_truthele_eta         ->clear();
    m_truthele_phi         ->clear();
    m_truthele_charge      ->clear();
    m_truthele_recoMatch   ->clear();

    m_l1t_stage2_tower_n = 0;
    m_l1t_stage2_tower_hwEta    ->clear();
    m_l1t_stage2_tower_hwPhi    ->clear();
    m_l1t_stage2_tower_hwEtEm   ->clear();
    m_l1t_stage2_tower_hwEtHad  ->clear();
    m_l1t_stage2_tower_hwEtRatio->clear();
    m_l1t_stage2_tower_hwQual   ->clear();

    m_l1t_stage2_eg_n = 0;
    m_l1t_stage2_eg_pt          ->clear();
    m_l1t_stage2_eg_eta         ->clear();
    m_l1t_stage2_eg_phi         ->clear();
    m_l1t_stage2_eg_hwPt        ->clear();
    m_l1t_stage2_eg_hwEta       ->clear();
    m_l1t_stage2_eg_hwPhi       ->clear();
    m_l1t_stage2_eg_hwQual      ->clear();
    m_l1t_stage2_eg_hwIso       ->clear();

    m_l1t_stage1_eg_n = 0;
    m_l1t_stage1_eg_pt          ->clear();
    m_l1t_stage1_eg_eta         ->clear();
    m_l1t_stage1_eg_phi         ->clear();
    m_l1t_stage1_eg_hwPt        ->clear();
    m_l1t_stage1_eg_hwEta       ->clear();
    m_l1t_stage1_eg_hwPhi       ->clear();
    m_l1t_stage1_eg_hwQual      ->clear();
    m_l1t_stage1_eg_hwIso       ->clear();


}
