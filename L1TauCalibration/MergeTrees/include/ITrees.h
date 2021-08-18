/**
 *  @file  ITrees.h
 *  @brief  
 *
 *
 *  @author  Jean-Baptiste Sauvan <sauvan@llr.in2p3.fr>
 *
 *  @date    07/15/2014
 *
 *  @internal
 *     Created :  07/15/2014
 * Last update :  07/15/2014 11:10:39 AM
 *          by :  JB Sauvan
 *
 * =====================================================================================
 */



#ifndef ITREES_H
#define ITREES_H

#include <vector>

class TTree;
class TChain;

class ITrees
{
    public:
        ITrees():m_run(0),m_event(0){};
        virtual ~ITrees() {};

        void setMainTree(TTree* mainTree);
        void setSecondaryTrees(std::vector<TChain*>& secondaryTrees);
        void setOutputTree(TTree* outputTree);

        virtual void linkMainVariables() = 0;
        virtual void linkSecondaryVariables() = 0;
        virtual void linkOutputVariables() = 0;
        void resetVariables();

        void mergeTrees();

    protected:
        TTree* m_mainTree;
        std::vector<TChain*> m_secondaryTrees;
        TTree* m_outputTree;

        int m_run;
        unsigned long long int m_event;
        /* ULong64_t m_event; */
};

#endif
