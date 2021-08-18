/**
 *  @file  EgammaStage1Stage2Trees.h
 *  @brief  
 *
 *
 *  @author  Jean-Baptiste Sauvan <sauvan@llr.in2p3.fr>
 *
 *  @date    07/16/2014
 *
 *  @internal
 *     Created :  07/16/2014
 * Last update :  07/16/2014 03:35:25 PM
 *          by :  JB Sauvan
 *
 * =====================================================================================
 */


#ifndef EGAMMASTAGE1STAGE2TREES_H
#define EGAMMASTAGE1STAGE2TREES_H

#include "ITrees.h"

class EgammaStage1Stage2Trees:public ITrees
{
    public:
        EgammaStage1Stage2Trees():ITrees(){};
        ~EgammaStage1Stage2Trees(){};

        void linkMainVariables();
        void linkSecondaryVariables();
        void linkOutputVariables();
        void resetVariables();

    protected:
        // offline and truth variables
        int   m_npv;
        int   m_npu;
        double m_rho;

        int                                m_ele_n;
        std::vector<double>                *m_ele_pt;
        std::vector<double>                *m_ele_et;
        std::vector<double>                *m_ele_E;
        std::vector<double>                *m_ele_eta;
        std::vector<double>                *m_ele_phi;
        std::vector<int>                   *m_ele_charge;
        std::vector<double>                *m_ele_sc_E;
        std::vector<double>                *m_ele_sc_eta;
        std::vector<double>                *m_ele_sc_phi;
        std::vector<int>                   *m_ele_ncl;
        std::vector<int>                   *m_ele_class;
        std::vector<bool>                  *m_ele_isEB;
        std::vector<bool>                  *m_ele_isEE;
        std::vector<bool>                  *m_ele_isEBEEGap;
        std::vector<bool>                  *m_ele_isEBGap;
        std::vector<bool>                  *m_ele_isEEGap;
        std::vector<double>                *m_ele_bdt;
        std::vector<bool>                  *m_ele_pass;
        std::vector<int>                   *m_ele_seedtt_ieta;
        std::vector<int>                   *m_ele_seedtt_iphi;
        std::vector< std::vector<int> >    *m_ele_tt_ieta;
        std::vector< std::vector<int> >    *m_ele_tt_iphi;
        std::vector< std::vector<float> >  *m_ele_tt_E;
        std::vector< std::vector<int> >    *m_ele_rct_ieta;
        std::vector< std::vector<int> >    *m_ele_rct_iphi;

        int                                m_truthele_n;
        std::vector<double>                *m_truthele_pt;
        std::vector<double>                *m_truthele_E;
        std::vector<double>                *m_truthele_eta;
        std::vector<double>                *m_truthele_phi;
        std::vector<int>                   *m_truthele_charge;
        std::vector<int>                   *m_truthele_recoMatch;

        int                                m_l1t_stage2_tower_n;
        std::vector<int>                   *m_l1t_stage2_tower_hwEta;
        std::vector<int>                   *m_l1t_stage2_tower_hwPhi;
        std::vector<int>                   *m_l1t_stage2_tower_hwEtEm;
        std::vector<int>                   *m_l1t_stage2_tower_hwEtHad;
        std::vector<int>                   *m_l1t_stage2_tower_hwEtRatio;
        std::vector<int>                   *m_l1t_stage2_tower_hwQual;

        int                                m_l1t_stage2_eg_n;
        std::vector<double>                *m_l1t_stage2_eg_pt;
        std::vector<double>                *m_l1t_stage2_eg_eta;
        std::vector<double>                *m_l1t_stage2_eg_phi;
        std::vector<int>                   *m_l1t_stage2_eg_hwPt;
        std::vector<int>                   *m_l1t_stage2_eg_hwEta;
        std::vector<int>                   *m_l1t_stage2_eg_hwPhi;
        std::vector<int>                   *m_l1t_stage2_eg_hwQual;
        std::vector<int>                   *m_l1t_stage2_eg_hwIso;

        int                                m_l1t_stage1_eg_n;
        std::vector<double>                *m_l1t_stage1_eg_pt;
        std::vector<double>                *m_l1t_stage1_eg_eta;
        std::vector<double>                *m_l1t_stage1_eg_phi;
        std::vector<int>                   *m_l1t_stage1_eg_hwPt;
        std::vector<int>                   *m_l1t_stage1_eg_hwEta;
        std::vector<int>                   *m_l1t_stage1_eg_hwPhi;
        std::vector<int>                   *m_l1t_stage1_eg_hwQual;
        std::vector<int>                   *m_l1t_stage1_eg_hwIso;

};


#endif
