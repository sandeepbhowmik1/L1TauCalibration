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

void MakeTau_Calib_LUT(Bool_t withLayer1 = kTRUE)
{
  TString fileName_In = "/home/sbhowmik/RootTree/L1TauTrigger/Run3/L1TauCalibration_20210727/corrections_Trigger_Stage2_2021_compressedieta_compressedE_hasEM_isMerged_20210727.root";
  TString histName_In_0 = "LUT_isMerged0_GBRFullLikelihood_Trigger_Stage2_2021_compressedieta_compressedE_hasEM_isMerged_20210727";
  TString histName_In_1 = "LUT_isMerged1_GBRFullLikelihood_Trigger_Stage2_2021_compressedieta_compressedE_hasEM_isMerged_20210727";
  TString fileName_Out = "/home/sbhowmik/RootTree/L1TauTrigger/Run3/L1TauCalibration_20210727/Tau_Calibration_LUT_MC_VBF_20210727.txt";

  TFile fileIn(fileName_In.Data(),"READ");
  TH3F* histIn_0 = (TH3F*)fileIn.Get(histName_In_0);
  TH3F* histIn_1 = (TH3F*)fileIn.Get(histName_In_1);
  ofstream fileOut(fileName_Out.Data());

  cout << "LUT name: " << histIn_0->GetName() << endl;
  cout << "LUT name: " << histIn_1->GetName() << endl;
  cout << "Max LUT calib factor: " << histIn_0->GetMaximum() << endl;

  const Float_t hardcodedIetaBins[] = {0, 6, 12, 18, 33};
  const Float_t hardcodedIetBins[]  = {0, 15, 18, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 50, 53, 56, 59, 62, 65, 69, 73, 77, 82, 88, 95, 105, 120, 157, 255};
  const Float_t hardcodedhasEMBins[] = {0, 1, 2};

  int neta = sizeof(hardcodedIetaBins) / sizeof(int) -1 ;
  int nEt  = sizeof(hardcodedIetBins) / sizeof(int)-1;
  int nhasEM = sizeof(hardcodedhasEMBins) / sizeof(int)-1;

  TH3F* binning = new TH3F ("binning", "binning", neta, hardcodedIetaBins, nEt, hardcodedIetBins, nhasEM, hardcodedhasEMBins);

  float maxeta = binning->GetXaxis()->GetBinLowEdge(histIn_0->GetNbinsX()+1);
  float maxEt  = binning->GetYaxis()->GetBinLowEdge(histIn_0->GetNbinsY()+1);
  float maxhasEM = binning->GetZaxis()->GetBinLowEdge(histIn_0->GetNbinsZ()+1);

  cout << maxeta << " " << maxEt << " " << maxhasEM << endl;

  cout << "Output cmpr bins: " << nEt << " " << neta << " " << nhasEM << " 1 "<< endl;

  ////////////////////////////////////////////////////////////////////////////
  //// print compression block on top of the LUT /////////////////////////////

  int etaBits = 6;
  int etBits  = 13;
  int hasEMBits = 10;

  int TotalIDX = 0;

  ////////////////////////////////////////////////////////////////////////////
  ///// print header
  ////////////////////////////////////////////////////////////////////////////
  //# comments...
  //#<header> V1 12 7 </header>
  // eta compr bits: 2
  // Et compr bits:  3
  // hasEM compr bits: 3
  // input bits: 2**6 + 2**13 + 2**10 + 2**(2+3+3) = 271k ==> stays on 14 bits
    
  int cmprEta = 2;
  //int cmprEt = 3;
  int cmprEt = 5;
  int cmprhasEM = 1;

  // int cmprEta = 2;
  // //int cmprEt = 3;
  // int cmprEt = 4;
  // int cmprhasEM = 3;

  //int totInBits  = 12 ;
  int totInBits  = 9 ;
  int totOutBits = 10 ;  // i.e. cut max 127, but it is largely overestimated: max in LUT is 27 --> 5 bits are enough
  // int totOutBits = 9 ;  // i.e. cut max 127, but it is largely overestimated: max in LUT is 27 --> 5 bits are enough
  fileOut << "# Tau calibration LUT"<<endl;
  fileOut << "# Calibration vs |ieta|,iEt,hasEM,isMerged: derived from 13 TeV MC (VBF) using loose tau ID selection, with semi-parametric regression"<<endl;
  fileOut << "# The LUT output is (ET_off/ET_L1) between 0 and 4, encoded on 10 bits: corr = LUT_output/256. <-> pt_calib = ((LUT_output*pt_raw)>>8)"<<endl;
  fileOut << "# Iso LUT structure is ieta --> iEt -->  hasEM --> isMerged" << endl;
  // fileOut << "# Iso LUT structure is Et --> eta -->  hasEM --> isMerged" << endl;
  fileOut << "# Compr bits: ieta: " << cmprEta << " iEt: " << cmprEt << " hasEM: " << cmprhasEM << " isMerged : 1" << endl;
  // fileOut << "# Compr bits: et: " << cmprEt << " eta: " << cmprEta << " hasEM: " << cmprhasEM << " isMerged : 1" << endl;
  fileOut << "# Index is (ieta<<7)+(iEt<<2)+(hasEM<<1)+isMerged"<<endl;
  // fileOut << "# Index is (et<<4)+(eta<<2)+(hasEM<<1)+isMerged"<<endl;
  fileOut << "# anything after # is ignored with the exception of the header"<<endl;
  fileOut << "# the header is first valid line starting with #<header> versionStr(unused but may be in future) </header>"<<endl;
  fileOut << "#<header> V13.0 " << totInBits << " " << totOutBits << " </header>"<<endl;

  ////////////////////////////////////////////////////////////////////////////
  //// print isolation LUT ///////////////////////////////////////////////////

  // structure: Et -- eta -- hasEM
  int onlyIsoAddr = 0;
  for (int ieta = 0; ieta < pow(2, cmprEta); ieta++)
    {
      for (int iEt = 0; iEt < pow(2, cmprEt); iEt++)
	{
	  for (int ihasEM = 0; ihasEM < pow(2, cmprhasEM); ihasEM++)
            {
	      for(int iisMerged = 0 ; iisMerged < 2 ; ++iisMerged)
		{
		  int binEt = iEt;
		  int bineta = ieta;
		  int binhasEM = ihasEM;
                
		  if (binEt >= nEt)   binEt  = nEt -1;   // these are never used -- values that are outside the compression
		  if (bineta >= neta) bineta = neta -1;
		  if (binhasEM >= nhasEM) binhasEM = nhasEM -1;
		  
		  float thr_f ;
		  if(iisMerged==0) thr_f = histIn_0->GetBinContent(bineta+1,binEt+1,binhasEM+1);
		  else thr_f = histIn_1->GetBinContent(bineta+1,binEt+1,binhasEM+1);
		  // if(iisMerged==0) thr_f = histIn->GetBinContent(binEt+1,bineta+1,binhasEM+1);
		  // else thr_f = LUT_isMerged1->GetBinContent(binEt+1,bineta+1,binhasEM+1);

		  if(thr_f>1.7 && withLayer1) thr_f=1.7;
		  else if(thr_f>2.1 && !withLayer1) thr_f=2.1;
		  // cout<<"iEt+1 = "<<iEt+1<<", iEta+1 = "<<ieta+1<<", iisMerged+1 = "<<iisMerged+1<<", corr = "<<thr_f<<endl;

		  // thr_f = thr_f-0.5;
		  // if(thr>=pow(2,totOutBits)-1) thr=pow(2,totOutBits)-1;
		  int thr = int(round(thr_f/4.*1024));
		  //yint = int(round(y/2.*512))

		  fileOut << TotalIDX << " " << thr*2;
		  if (iEt == 0 && ieta == 0 && ihasEM == 0 && iisMerged==0) fileOut << " # start of calibration LUT -- ieta : iEt : ihasEM : isMerged = " << ieta << " : " << iEt << " : " << ihasEM << " : "<<iisMerged; 
		  else fileOut << " # ieta : iEt : ihasEM : iisMerged = " << ieta << " : " << iEt << " : " << ihasEM << " : "<<iisMerged; 

		  fileOut << endl;
		  cout << onlyIsoAddr << " ieta : iEt : ihasEM : iisMerged = " << ieta << " : " << iEt << " : " << ihasEM << " : " << iisMerged << " --> calib: " << thr*2 << endl; 
		  TotalIDX++;
		  onlyIsoAddr++;
		}
            }
        }
    }

  int totIDXexpected = pow(2,etaBits) + pow(2,etBits) + pow (2, hasEMBits) + pow (2, cmprEta+cmprEt+cmprhasEM);
  cout << "TOTAL IDX " << TotalIDX << " expected: " << totIDXexpected << endl;
  cout << "Max allowed by input LUT bits: " << pow(2, totInBits) << endl;
  if (TotalIDX >= pow(2, totInBits))
    {
      cout << " **** WARNING!!! too few input bits " << totInBits << " , please increase value in header" << endl;
    } 


}
