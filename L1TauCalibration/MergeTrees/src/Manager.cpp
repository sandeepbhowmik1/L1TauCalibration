/**
 *  @file  Manager.cpp
 *  @brief  
 *
 *
 *  @author  Jean-Baptiste Sauvan <sauvan@llr.in2p3.fr>
 *
 *  @date    07/15/2014
 *
 *  @internal
 *     Created :  07/15/2014
 * Last update :  07/15/2014 11:51:19 AM
 *          by :  JB Sauvan
 *
 * =====================================================================================
 */



#include "TEnv.h"
#include "TChain.h"
#include "TSystem.h"

#include "Manager.h"
#include "treeDefinitions.h"
#include "Utilities.h"

using namespace std;


/*****************************************************************/
Manager::~Manager()
/*****************************************************************/
{
    for(auto itr=m_secondaryTrees.begin();itr!=m_secondaryTrees.end();itr++)  
    {
        (*itr)->Delete();
    }
    
}

/*****************************************************************/
bool Manager::initialize(const std::string& config)
/*****************************************************************/
{
    gSystem->Load("obj/libDictionary_C.so");
    TEnv params;
    int status = params.ReadFile(config.c_str(),EEnvLevel(0));
    if(status!=0) 
    {
        cout<<"[ERROR] Cannot read configuration file "<<config<<"\n";
        return false;
    }

    string treeClass = params.GetValue("TreeClass", "Trees");

    cout<<"[INFO] Tree class: "<<treeClass<<"\n";

    string mainFiles= params.GetValue("MainFiles", "");
    Utilities::tokenize(mainFiles, m_mainFiles, " ");
    m_mainTreeName = params.GetValue("MainTree", "dummyTree");

    cout<<"[INFO] Main tree: "<<m_mainTreeName<<"\n";

    int nSecondaryTrees = params.GetValue("SecondaryTrees.N", 1);
    for(int i=0;i<nSecondaryTrees;i++)
    {
        stringstream keyTree;
        keyTree << "SecondaryTrees." << i << ".Tree";
        string tree = params.GetValue(keyTree.str().c_str(), "");

        cout<<"[INFO] Secondary tree: "<<tree<<"\n";

        stringstream keyFiles;
        keyFiles << "SecondaryTrees." << i << ".Files";
        string fileNames = params.GetValue(keyFiles.str().c_str(), "");
        vector<string> files;
        Utilities::tokenize(fileNames, files, " ");
        TChain* chain = new TChain(tree.c_str());
        for(auto itr=files.begin();itr!=files.end();itr++)
        {
            chain->Add(itr->c_str());
        }
        m_secondaryTrees.push_back(chain);
    }
    m_outputFileName = params.GetValue("OutputFile", "output.root");

    createFactory();
    m_treeManager = g_factory->createTrees(treeClass);
    m_treeManager->setSecondaryTrees(m_secondaryTrees);
    m_treeManager->linkSecondaryVariables();

    return true;

}



/*****************************************************************/
bool Manager::merge()
/*****************************************************************/
{
    int counter = 0;
    for(auto itr=m_mainFiles.begin();itr!=m_mainFiles.end();itr++)
    {
        // retrieve main tree
        string mainFileName = *itr;
        cout<<"[INFO] Merging "<<mainFileName<<"\n";
        m_mainFile = TFile::Open(mainFileName.c_str());
        m_mainTree = (TTree*)m_mainFile->Get(m_mainTreeName.c_str());
        if(!m_mainTree)
        {
            std::cerr<<"[ERROR] Cannot find tree "<<m_mainTreeName<<" in "<<mainFileName<<"\n";
            return 0;
        }
        m_treeManager->setMainTree(m_mainTree);
        m_treeManager->linkMainVariables();

        // create ouput file and tree
        string fileName = m_outputFileName; 
        stringstream replacement;
        replacement << "_" << counter << ".root";
        Utilities::findAndReplace(fileName, ".root", replacement.str());
        TFile* outputFile = TFile::Open(fileName.c_str(), "RECREATE");
        outputFile->cd();
        string outputTreeName(m_mainTreeName);
        Utilities::findAndReplace(outputTreeName, "/", "_");
        m_outputTree = new TTree(outputTreeName.c_str(), outputTreeName.c_str());
        m_treeManager->setOutputTree(m_outputTree);
        m_treeManager->linkOutputVariables();
        
        // merge trees
        m_treeManager->mergeTrees();

        outputFile->Close();
        m_mainFile->Close();
        //m_outputTree->Delete();
        counter++;
    }
    return true;
}
