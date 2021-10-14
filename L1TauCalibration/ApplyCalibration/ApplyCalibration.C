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
#include <stdio.h>
#include <math.h>

using namespace std;

const Int_t NbinsIEta = 4+1;
const Int_t NbinsIEt = 17+1;
const Int_t NbinsnTT = 15+1; //new nTT CMP
//const Int_t NbinsIEt = 16+1;
//const Int_t NbinsnTT = 11+1;//Acceptable LUT Thomas
//const Int_t NbinsnTT = 23+1;//Cristina
//const Int_t NbinsnTT = 20+1;//Sandeep

const Int_t NbinsIEt2 = 32+1;
const Int_t NbinsnTT2 = 32+1;

const Int_t hardcodedIetaBins[NbinsIEta] = {0, 6, 12, 18, 33};
//const Int_t hardcodedIetBins[NbinsIEt]    = {0, 19, 23, 27, 31, 35, 39, 43, 47, 53, 59, 65, 73, 82, 95, 120, 157, 255};
const Int_t hardcodedIetBins[NbinsIEt]    = {0, 23, 27, 31, 35, 39, 43, 47, 53, 59, 65, 73, 82, 95, 105, 120, 157, 255}; //Olivier
//const Int_t hardcodedIetBins[NbinsIEt]    = {0, 23, 27, 31, 35, 39, 43, 47, 53, 59, 65, 73, 82, 95, 120, 157, 255};
const Int_t hardcodedIetBins2[NbinsIEt2]  = {0, 15, 18, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 50, 53, 56, 59, 62, 65, 69, 73, 77, 82, 88, 95, 105, 120, 157, 255};
const Double_t hardcodedIetBins2double[NbinsIEt2]  = {0, 15, 18, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 50, 53, 56, 59, 62, 65, 69, 73, 77, 82, 88, 95, 105, 120, 157, 255};

//const Int_t hardcodednTTBins[NbinsnTT] =   {0, 26, 31, 36, 41, 46, 51, 56, 61, 66, 76, 86, 101, 121, 255};//Acceptable LUT Thomas
const Int_t hardcodednTTBins[NbinsnTT] =   {0, 26, 31, 36, 41, 46, 51, 56, 61, 66, 71, 76, 81, 91, 106, 255 }; //Olivier
//const Int_t hardcodednTTBins[NbinsnTT] = {0,61,66,71,76,81,86,91,96,101,111,121,131,141,161,255};
//const Int_t hardcodednTTBins[NbinsnTT] =   {0, 26, 31, 36, 41, 46, 51, 56, 61, 66, 76, 255};//Acceptable LUT Thomas
//const Int_t hardcodednTTBins[NbinsnTT] = {0,26,31,36,41,46,51,56,61,66,71,76,81,86,91,96,101,106,111,131,151,171,201,255 }; //Cristina
//const Int_t hardcodednTTBins[NbinsnTT] = {0,61,66,71,76,81,86,91,96,101,106,111,116,121,126,131,136,141,146,161,255};//Sandeep  


// const Int_t hardcodednTTBins[NbinsnTT] =   {0, 11, 16, 21, 26, 31, 36, 41, 46, 51, 56, 255};//Acceptable LUT Thomas
const Int_t hardcodednTTBins2[NbinsnTT2] = {0, 6, 11, 16, 21, 26, 31, 36, 41, 46, 51, 56, 61, 66, 71, 76, 81, 86, 91, 96, 101, 106, 111, 116, 121, 126, 131, 136, 141, 146, 161, 161, 255};//Acceptable LUThomas

bool CheckBit (short int number, int bitpos)
{
  bool res = number & (1 << bitpos);
  return res;
}

void SetBit (short int& number, int bitpos, bool val)
{
  if (val)
    number |= (1 << bitpos);
  else
    number &= ~(1 << bitpos);
}

Int_t FindBinIEt(Int_t IEt)
{
  for(UInt_t i = 0 ; i < NbinsIEt2-1 ; ++i)
    {
      if(IEt>=157) return NbinsIEt2-2;
      if(IEt>= hardcodedIetBins2[i] && IEt < hardcodedIetBins2[i+1]) return i;
    }
  return -1;
}

Int_t FindBinnTT(Int_t nTT)
{
  for(UInt_t i = 0 ; i < NbinsnTT2-1 ; ++i)
    {
      if(nTT>=161) return NbinsnTT2-2;
      if(nTT>= hardcodednTTBins2[i] && nTT < hardcodednTTBins2[i+1]) return i;
    }
  return -1;
}

Int_t FindBinCorrespondenceIEt(Int_t IEt_fine)
{
  for(UInt_t i = 0 ; i < NbinsIEt-1 ; ++i)
    {
      if(IEt_fine>=157) return NbinsIEt-2;
      // if(IEt_fine>=120) return NbinsIEt-2;
      if(IEt_fine>= hardcodedIetBins[i] && IEt_fine < hardcodedIetBins[i+1]) return i;
    }
  return -1;
}

Int_t FindBinCorrespondencenTT(Int_t nTT_fine)
{
  for(UInt_t i = 0 ; i < NbinsnTT-1 ; ++i)
    {
      //if(nTT_fine>=76) return NbinsnTT-2;
      // if(nTT_fine>=106) return NbinsnTT-2;
      // if(nTT_fine>=56) return NbinsnTT-2;
      if(nTT_fine>=161) return NbinsnTT-2;
      if(nTT_fine>= hardcodednTTBins[i] && nTT_fine < hardcodednTTBins[i+1]) return i;
    }
  return -1;
}

void ApplyCalibration()
{
  TString fileName_In = "/home/sbhowmik/RootTree/L1TauTrigger/Run3/L1TauCalibration_20210727/rootTree_forCalibration_compressed_MC_VBFHToTauTau_L1_RECO_reEmulTPs_20210727.root";
  //TString fileName_In = "/hdfs/local/sbhowmik/L1TauTrigger_NTuple/Calibration_2018data_180503/outputForCalibration_compressed_Ntuple_MC_VBFHToTauTau_L1_RECO_Jets_reEmulTPs_180503_v1_0.root";
  TString treeName_In = "outTreeForCalibration";
  TString fileName_LUT = "/home/sbhowmik/RootTree/L1TauTrigger/Run3/L1TauCalibration_20211009/corrections_Trigger_Stage2_2021_compressedieta_compressedE_hasEM_isMerged_20211009.root";
  TString histName_LUT_0 = "LUT_isMerged0_GBRFullLikelihood_Trigger_Stage2_2021_compressedieta_compressedE_hasEM_isMerged_20211009";
  TString histName_LUT_1 = "LUT_isMerged1_GBRFullLikelihood_Trigger_Stage2_2021_compressedieta_compressedE_hasEM_isMerged_20211009";
  //TString fileName_Out = "/home/sbhowmik/RootTree/L1TauTrigger/Run3/L1TauCalibration_20210727/rootTree_calibratedOutput_MC_VBF_20210727.root";
  TString fileName_Out = "/home/sbhowmik/RootTree/L1TauTrigger/Run3/L1TauCalibration_20211009/rootTree_calibratedOutput_MC_VBF_20211009.root";

  //TString fileName_LUT = "/home/sbhowmik/RootTree/L1TauTrigger/Run3/L1TauCalibration_20211008/corrections_Trigger_Stage2_2018_compressedieta_compressedE_hasEM_isMerged_20211008.root";
  //TString histName_LUT_0 = "LUT_isMerged0_GBRFullLikelihood_Trigger_Stage2_2018_compressedieta_compressedE_hasEM_isMerged_20211008";
  //TString histName_LUT_1 = "LUT_isMerged1_GBRFullLikelihood_Trigger_Stage2_2018_compressedieta_compressedE_hasEM_isMerged_20211008";
  //TString fileName_Out = "/home/sbhowmik/RootTree/L1TauTrigger/Run3/L1TauCalibration_20211008/rootTree_calibratedOutput_MC_VBF_20211008.root";
  TString treeName_Out = "outTreeForCalibration";

  TFile fileIn(fileName_In.Data(),"READ");
  TTree* treeIn = (TTree*)fileIn.Get(treeName_In);
  TFile fileLUT(fileName_LUT.Data(),"READ");
  TH3F* histLUT_0 = (TH3F*)fileLUT.Get(histName_LUT_0);
  TH3F* histLUT_1 = (TH3F*)fileLUT.Get(histName_LUT_1);
  TFile fileOut(fileName_Out, "RECREATE");
  TTree* treeOut = new TTree(treeName_Out, treeName_Out);

  TH2F* isolation_vs_pt = new TH2F("isolation_vs_pt","isolation_vs_pt",100,0,100,NbinsIEt2-1,hardcodedIetBins2double);
  // TH2F* isolation_vs_pt = new TH2F("isolation_vs_pt","isolation_vs_pt",100,0.,100.,200,0.,200.);
  isolation_vs_pt->Clear();

  const UInt_t nIsolation = 101;
  const Double_t isolationBins[nIsolation] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100};
 
  Int_t           L1Tau_IEta;
  Int_t           L1Tau_hasEM;
  Float_t         Target;
  Int_t           L1Tau_IEt;
  Int_t           L1Tau_RawIEt;
  Int_t           EventNumber;
  Int_t           RunNumber;
  Int_t           L1Tau_nTT;
  Int_t           Nvtx;
  Float_t         L1Tau_pt;
  Float_t         OfflineTau_pt;
  Float_t         OfflineTau_eta;
  Int_t           L1Tau_Iso;
  Int_t           OfflineTau_isMatched;
  Int_t           L1Tau_isMerged;
  Int_t           compressedieta;
  Int_t           compressedE;
  Int_t           compressednTT;
  Int_t           supercompressedE;
  Int_t           supercompressednTT;
  Int_t           L1Tau_Qual;
    
  treeIn->SetBranchAddress("L1Tau_IEta", &L1Tau_IEta);
  treeIn->SetBranchAddress("L1Tau_hasEM", &L1Tau_hasEM);
  treeIn->SetBranchAddress("Target", &Target);
  treeIn->SetBranchAddress("L1Tau_IEt", &L1Tau_IEt);
  //treeIn->SetBranchAddress("L1Tau_RawIEt", &L1Tau_RawIEt);
  treeIn->SetBranchAddress("EventNumber", &EventNumber);
  treeIn->SetBranchAddress("RunNumber", &RunNumber);
  treeIn->SetBranchAddress("L1Tau_nTT", &L1Tau_nTT);
  //  treeIn->SetBranchAddress("Nvtx", &Nvtx);
  treeIn->SetBranchAddress("L1Tau_pt", &L1Tau_pt);
  treeIn->SetBranchAddress("OfflineTau_pt", &OfflineTau_pt);
  treeIn->SetBranchAddress("OfflineTau_eta", &OfflineTau_eta);
  treeIn->SetBranchAddress("compressedieta", &compressedieta);
  treeIn->SetBranchAddress("compressedE", &compressedE);
  treeIn->SetBranchAddress("L1Tau_Iso", &L1Tau_Iso);
  treeIn->SetBranchAddress("compressednTT", &compressednTT);
  treeIn->SetBranchAddress("OfflineTau_isMatched", &OfflineTau_isMatched);
  treeIn->SetBranchAddress("L1Tau_isMerged", &L1Tau_isMerged);
  treeIn->SetBranchAddress("L1Tau_Qual",&L1Tau_Qual);

  Int_t           out_L1Tau_IEta;
  Int_t           out_L1Tau_hasEM;
  Float_t         out_Target;
  Int_t           out_L1Tau_IEt;
  Int_t           out_L1Tau_RawIEt;
  Int_t           out_EventNumber;
  Int_t           out_RunNumber;
  Int_t           out_L1Tau_nTT;
  Int_t           out_Nvtx;
  Float_t         out_L1Tau_pt;
  Float_t         out_L1Tau_CalibPt;
  Float_t         out_OfflineTau_pt;
  Float_t         out_OfflineTau_eta;
  Int_t           out_compressedieta;
  Int_t           out_compressedE;
  Int_t           out_L1Tau_Iso;
  Int_t           out_compressednTT;
  Int_t           out_OfflineTau_isMatched;
  Int_t           out_L1Tau_isMerged;
  Int_t           out_supercompressedE;
  Int_t           out_supercompressednTT;
  Int_t           out_L1Tau_Qual;
  Float_t         out_L1Tau_CalibConstant;

  treeOut->Branch("L1Tau_IEta", &out_L1Tau_IEta,"L1Tau_IEta/I");
  treeOut->Branch("L1Tau_hasEM", &L1Tau_hasEM, "L1Tau_hasEM/I");
  treeOut->Branch("Target", &out_Target, "Target/F");
  treeOut->Branch("L1Tau_IEt", &out_L1Tau_IEt, "L1Tau_IEt/I");
  //  treeOut->Branch("L1Tau_RawIEt", &out_L1Tau_RawIEt, "L1Tau_RawIEt/I");
  treeOut->Branch("EventNumber", &out_EventNumber, "EventNumber/I");
  treeOut->Branch("RunNumber", &out_RunNumber, "RunNumber/I");
  treeOut->Branch("L1Tau_nTT", &out_L1Tau_nTT, "L1Tau_nTT/I");
  //  treeOut->Branch("Nvtx", &out_Nvtx, "Nvtx/I");
  treeOut->Branch("L1Tau_pt", &out_L1Tau_pt, "L1Tau_pt/F");
  treeOut->Branch("L1Tau_CalibPt", &out_L1Tau_CalibPt, "L1Tau_CalibPt/F");
  treeOut->Branch("L1Tau_CalibConstant", &out_L1Tau_CalibConstant, "L1Tau_CalibConstant/F");
  treeOut->Branch("OfflineTau_pt", &out_OfflineTau_pt, "OfflineTau_pt/F");
  treeOut->Branch("OfflineTau_eta", &out_OfflineTau_eta, "OfflineTau_eta/F");
  treeOut->Branch("compressedieta", &out_compressedieta, "compressedieta/I");
  treeOut->Branch("compressedE", &out_compressedE, "compressedE/I");
  treeOut->Branch("L1Tau_Iso", &out_L1Tau_Iso, "L1Tau_Iso/I");
  treeOut->Branch("compressednTT", &out_compressednTT, "compressednTT/I");
  treeOut->Branch("OfflineTau_isMatched", &out_OfflineTau_isMatched, "OfflineTau_isMatched/I");
  treeOut->Branch("L1Tau_isMerged", &out_L1Tau_isMerged, "L1Tau_isMerged/I");
  treeOut->Branch("supercompressedE", &out_supercompressedE, "supercompressedE/I");
  treeOut->Branch("supercompressednTT", &out_supercompressednTT, "supercompressednTT/I");
  treeOut->Branch("L1Tau_Qual",&out_L1Tau_Qual, "out_L1Tau_Qual/I");

  map<int, int> remap;
  remap[0] = 6 ;
  remap[1] = 5 ;
  remap[2] = 1 ;
  remap[3] = 0 ;
  remap[4] = 4 ;
  remap[5] = 3 ;
  remap[6] = 2 ;

  // pt in 20-30
  vector<int> veto_set_20 = {0,4,99,8,20};
  // pt in 30-40
  vector<int> veto_set_30 = {127, 119, 99, 111, 103, 23, 55, 20, 31, 27, 63, 107, 19, 51, 28};
  // pt in 40-50
  vector<int> veto_set_40 = {127, 119, 99, 103, 20, 111, 23, 19, 27, 4, 55};

  for(UInt_t i = 0 ; i < treeIn->GetEntries() ; ++i)
    {
      treeIn->GetEntry(i);
      if(i%10000==0) cout<<"Entry #"<<i<<endl;
      out_L1Tau_IEta = abs(L1Tau_IEta);
      out_L1Tau_hasEM = L1Tau_hasEM;
      out_Target = Target;
      out_L1Tau_IEt = L1Tau_IEt;
      //      out_L1Tau_RawIEt = L1Tau_RawIEt;
      out_EventNumber = EventNumber;
      out_RunNumber = RunNumber;
      out_L1Tau_nTT = L1Tau_nTT;
      //      out_Nvtx = Nvtx;
      out_L1Tau_pt = L1Tau_pt;
      out_OfflineTau_pt = OfflineTau_pt;
      out_OfflineTau_eta = OfflineTau_eta;
      out_compressedieta = abs(compressedieta);
      out_compressedE = compressedE;
      out_L1Tau_Iso = L1Tau_Iso;
      out_compressednTT = compressednTT;
      out_OfflineTau_isMatched = OfflineTau_isMatched;
      out_L1Tau_isMerged = L1Tau_isMerged;
      for(Int_t ie = 0 ; ie < NbinsIEt ; ++ie)
	{
	  if(L1Tau_IEt>=255)
	    {
	      out_supercompressedE = NbinsIEt-2;
	      break;
	    }
	  else if(L1Tau_IEt >= hardcodedIetBins[ie] && L1Tau_IEt < hardcodedIetBins[ie+1])
	    {
	      out_supercompressedE = ie;
	      break;
	    }
	}
      for(Int_t inTT = 0 ; inTT < NbinsnTT ; ++inTT)
	{
	  if(L1Tau_nTT>=255)
	    {
	      out_supercompressednTT = NbinsnTT-2;
	      break;
	    }
	  else if(L1Tau_nTT >= hardcodednTTBins[inTT] && L1Tau_nTT < hardcodednTTBins[inTT+1])
	    {
	      out_supercompressednTT = inTT;
	      break;
	    }
	}
      if(!out_L1Tau_isMerged)
	{
	  out_L1Tau_CalibConstant = histLUT_0->GetBinContent(abs(compressedieta)+1,compressedE+1,L1Tau_hasEM+1);
	  if(out_L1Tau_CalibConstant>1.3) out_L1Tau_CalibConstant = 1.3;
	  // if(out_L1Tau_CalibConstant>1.7) out_L1Tau_CalibConstant = 1.7;
	  out_L1Tau_CalibPt = out_L1Tau_CalibConstant*L1Tau_IEt/2.;
	}
      else
	{
	  out_L1Tau_CalibConstant = histLUT_1->GetBinContent(abs(compressedieta)+1,compressedE+1,L1Tau_hasEM+1);
	  if(out_L1Tau_CalibConstant>1.3) out_L1Tau_CalibConstant = 1.3;
	  // if(out_L1Tau_CalibConstant>1.7) out_L1Tau_CalibConstant = 1.7;
	  out_L1Tau_CalibPt = out_L1Tau_CalibConstant*L1Tau_IEt/2.;
	}
      out_L1Tau_Qual = L1Tau_Qual;
      isolation_vs_pt->Fill(L1Tau_Iso,out_L1Tau_IEt);

      treeOut->Fill();
    }
  treeOut->Write();
}
