/**
 *  @file  TauStage2Trees.h
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


#ifndef TAUSTAGE2TREES_H
#define TAUSTAGE2TREES_H

#include "ITrees.h"

class TauStage2Trees:public ITrees
{
    public:
        TauStage2Trees():ITrees(){};
        ~TauStage2Trees(){};

        void linkMainVariables();
        void linkSecondaryVariables();
        void linkOutputVariables();
        void resetVariables();

    protected:
        // offline and truth variables
        int m_lumi;
        float m_tauPt;
        float m_tauEta;
        float m_tauPhi;
	int   m_tauCharge;
	int   m_tauDecayMode;
        bool m_hasTriggerMuonType;
        bool m_hasTriggerTauType;
        bool m_isMatched;
        bool m_isOS;
        int m_foundJet;
        /* float m_muonPt; */
        /* float m_muonEta; */
        /* float m_muonPhi; */
        int m_Nvtx;

        std::vector<int>* m_l1tQual;
        std::vector<float>* m_l1tPt;
        std::vector<float>* m_l1tEta;
        std::vector<float>* m_l1tPhi;
        std::vector<int>* m_l1tIso;
        std::vector<int>* m_l1tEmuQual;
        std::vector<float>* m_l1tEmuPt;
        std::vector<float>* m_l1tEmuEta;
        std::vector<float>* m_l1tEmuPhi;
        std::vector<int>* m_l1tEmuIso;
        std::vector<int>* m_l1tEmuNTT;
        std::vector<int>* m_l1tEmuHasEM;
        std::vector<int>* m_l1tEmuIsMerged;
        std::vector<int>* m_l1tEmuTowerIEta;
        std::vector<int>* m_l1tEmuTowerIPhi;
        std::vector<int>* m_l1tEmuRawEt;
        std::vector<int>* m_l1tEmuIsoEt;

};


#endif
