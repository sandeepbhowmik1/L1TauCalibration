/**
 *  @file  Manager.h
 *  @brief  
 *
 *
 *  @author  Jean-Baptiste Sauvan <sauvan@llr.in2p3.fr>
 *
 *  @date    07/15/2014
 *
 *  @internal
 *     Created :  07/15/2014
 * Last update :  07/15/2014 11:51:11 AM
 *          by :  JB Sauvan
 *
 * =====================================================================================
 */



#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include <string>

#include "TFile.h"

#include "ITrees.h"



class Manager
{
    public:
        Manager(){};
        ~Manager();

        bool initialize(const std::string& config);
        bool merge();

    private:
        ITrees* m_treeManager;

        std::vector<std::string> m_mainFiles;
        std::string m_mainTreeName;
        TFile* m_mainFile;
        TTree* m_mainTree;
        std::vector<TChain*> m_secondaryTrees;
        std::string m_outputFileName;
        TFile* m_outputFile;
        TTree* m_outputTree;

};


#endif
