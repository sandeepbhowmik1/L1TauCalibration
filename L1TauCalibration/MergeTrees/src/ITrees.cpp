

#include "ITrees.h"
#include "TChain.h"
#include "TTree.h"

#include <iostream>

using namespace std;

/*****************************************************************/
void ITrees::setMainTree(TTree* mainTree)
/*****************************************************************/
{
    m_mainTree = mainTree;
}


/*****************************************************************/
void ITrees::setSecondaryTrees(std::vector<TChain*>& secondaryTrees)
/*****************************************************************/
{
    m_secondaryTrees = secondaryTrees;
}

/*****************************************************************/
void ITrees::setOutputTree(TTree* outputTree)
/*****************************************************************/
{
    m_outputTree = outputTree;
}


/*****************************************************************/
void ITrees::resetVariables()
/*****************************************************************/
{
    m_run   = 0;
    m_event = 0;
}


/*****************************************************************/
void ITrees::mergeTrees()
/*****************************************************************/
{
    resetVariables();
    Long64_t nNotFound = 0;
    Long64_t nentries = m_mainTree->GetEntries();
    //std::cerr<<"N secondary entries = "<<m_secondaryTrees[0]->GetEntries()<<"\n";
    for(Long64_t entry=0;entry<nentries;entry++)
    {
      //cout<<"entry = "<<entry<<endl;
        if(entry%10000==0) std::cout<<"[INFO]   Entry "<<entry<<"/"<<nentries<<"\n";
        m_mainTree->GetEntry(entry);
        bool fill = true;
        for(auto itr=m_secondaryTrees.begin();itr!=m_secondaryTrees.end();itr++)
        {
	  //cout<<"m_run = "<<m_run<<endl;
	  //cout<<"m_event = "<<m_event<<endl;
            if( (*itr)->GetEntryWithIndex(m_run, m_event)<=0 ) 
            {
                fill = false;
                //cout<<"[WARN] Cannot find event "<<m_run<<","<<m_event<<" in secondary tree "<<(*itr)->GetName()<<"\n";
            }
        }
        if(fill) m_outputTree->Fill();
        else nNotFound++;
    }
    if(nNotFound>0)
    {
        cout<<"[WARN] "<<nNotFound<<" events were not found in secondary trees \n";
    }
    m_outputTree->Write();
}
