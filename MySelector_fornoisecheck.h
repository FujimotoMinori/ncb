//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat May 11 11:07:23 2019 by ROOT version 6.16/00
// from TTree tree/tree
// found on file: /eos/atlas/unpledged/group-tokyo/users/mfujimot/NCB/condorDir/output30run.root
//////////////////////////////////////////////////////////

#ifndef MySelector_fornoisecheck_h
#define MySelector_fornoisecheck_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector
#include <vector>



class MySelector_fornoisecheck : public TSelector {
private:
   std::string outputfile_;
   std::string inputfile_;
public :
   TFile *outputFile = 0;
   TString *inputFile = 0;
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain
   //std::multimap<int,std::pair<int,int>> dmodule;
   bool dead[2048] = {false};
   bool deadopposite[2048] = {false};
   fstream findata;
   std::string strdata;
   //int nevents = 0;


   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Int_t> fEventNumber = {fReader, "EventNumber"};
   TTreeReaderValue<Int_t> fRunNumber = {fReader, "RunNumber"};
   TTreeReaderValue<Int_t> ftimeStamp = {fReader, "timeStamp"};
   TTreeReaderValue<Int_t> fLBNumber = {fReader, "LBNumber"};
   TTreeReaderValue<Int_t> fbcid = {fReader, "bcid"};
   TTreeReaderValue<Int_t> fpvs = {fReader, "pvs"};
   TTreeReaderValue<Bool_t> fpassesACTrigger = {fReader, "passesACTrigger"};
   TTreeReaderValue<Bool_t> fpassesCATrigger = {fReader, "passesCATrigger"};
   TTreeReaderArray<int> fHitsOnDisks = {fReader, "HitsOnDisks"};
   TTreeReaderArray<int> fsideDiskA = {fReader, "sideDiskA"};
   TTreeReaderArray<int> fsideDiskC = {fReader, "sideDiskC"};
   TTreeReaderValue<Float_t> fBCMprescale = {fReader, "BCMprescale"};
   TTreeReaderValue<Bool_t> fTriggerISO = {fReader, "TriggerISO"};
   TTreeReaderValue<Bool_t> fTriggerEmpty = {fReader, "TriggerEmpty"};
   TTreeReaderValue<Bool_t> fGoodLB = {fReader, "GoodLB"};
   TTreeReaderValue<Bool_t> fpassesHLT = {fReader, "passesHLT"};
   TTreeReaderValue<Float_t> fHLTprescale = {fReader, "HLTprescale"};
   TTreeReaderValue<Int_t> fPixelHits = {fReader, "PixelHits"};
   TTreeReaderValue<Int_t> fHitsPixelECA = {fReader, "HitsPixelECA"};
   TTreeReaderValue<Int_t> fHitsPixelECC = {fReader, "HitsPixelECC"};
   TTreeReaderValue<Int_t> fHitsTRTECA = {fReader, "HitsTRTECA"};
   TTreeReaderValue<Int_t> fHitsTRTECC = {fReader, "HitsTRTECC"};
   TTreeReaderValue<Float_t> fZAsymmetryTRT = {fReader, "ZAsymmetryTRT"};
   TTreeReaderValue<Bool_t> fwithPrimaryVertex = {fReader, "withPrimaryVertex"};
   TTreeReaderArray<int> fpbecV = {fReader, "pbecV"};
   TTreeReaderArray<int> fplayerV = {fReader, "playerV"};
   TTreeReaderArray<int> fpnRDOV = {fReader, "pnRDOV"};
   TTreeReaderArray<int> fpToTV = {fReader, "pToTV"};
   //TTreeReaderArray<int> fpphiV = {fReader, "pphiV"};
   //TTreeReaderArray<int> fpsizeZV = {fReader, "psizeZV"};
   //TTreeReaderArray<int> fpsizePhiV = {fReader, "psizePhiV"};
   TTreeReaderValue<Float_t> fZAsymmetryPixel = {fReader, "ZAsymmetryPixel"};


   MySelector_fornoisecheck(TTree * /*tree*/ =0) { 
	   //fNumberOfEvents(0),
		   //fChain(0) { }

   }

   virtual ~MySelector_fornoisecheck() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();
  
   // Histograms
   std::vector<TH2F*> ListTH2F;
   std::vector<TH1F*> ListTH1F;

   TH1F* h_events;
   TH1F* h_events_AC;
   TH1F* h_events_CA;
   TH1F* h_events_ACwoPV;
   TH1F* h_events_CAwoPV;
   TH1F* h_ratioAC;
   TH1F* h_ratioCA;

   //TH2F* h_nHitsA_beam2_bcid;
   //TH2F* h_nHitsC_beam2_bcid;
   //TH2F* h_nHitsA_empty;
   //TH2F* h_nHitsC_empty;
   //TH2F* h_nHitsA_beam1;
   //TH2F* h_nHitsC_beam1;
   //TH2F* h_nHitsA_beam2;
   //TH2F* h_nHitsC_beam2;
   //TH2F* h_nHitsA_beam1_woSmallHits;
   //TH2F* h_nHitsC_beam1_woSmallHits;
   //TH2F* h_nHitsA_beam2_woSmallHits;
   //TH2F* h_nHitsC_beam2_woSmallHits;
   //TH2F* h_nHitsA_beam1_wSmallHits;
   //TH2F* h_nHitsC_beam1_wSmallHits;
   //TH2F* h_nHitsA_beam2_wSmallHits;
   //TH2F* h_nHitsC_beam2_wSmallHits;

   //TH2F* h_nHitsA_beam1_3;
   //TH2F* h_nHitsC_beam1_3;
   //TH2F* h_nHitsA_beam2_3;
   //TH2F* h_nHitsC_beam2_3;
   //TH2F* h_nHitsA_beam1_not3;
   //TH2F* h_nHitsC_beam1_not3;
   //TH2F* h_nHitsA_beam2_not3;
   //TH2F* h_nHitsC_beam2_not3;
   //TH2F* h_nHitsA_beam1_6;
   //TH2F* h_nHitsC_beam1_6;
   //TH2F* h_nHitsA_beam2_6;
   //TH2F* h_nHitsC_beam2_6;
   //TH2F* h_nHitsA_beam1_not6;
   //TH2F* h_nHitsC_beam1_not6;
   //TH2F* h_nHitsA_beam2_not6;
   //TH2F* h_nHitsC_beam2_not6;

   //TH2F* h_zasym_AC_bcid;
   //TH2F* h_zasym_CA_bcid;
   //TH2F* h_zasym_AC;
   //TH2F* h_zasym_CA;
   //TH2F* h_zasym_AC_woSmallHits;
   //TH2F* h_zasym_CA_woSmallHits;
   TH2F* h_zasym_AC_woSmallHitsnew;
   TH2F* h_zasym_CA_woSmallHitsnew;
   //TH2F* h_zasym_AC_wSmallHits;
   //TH2F* h_zasym_CA_wSmallHits;
   //TH2F* h_zasymtrack_AC;
   //TH2F* h_zasymtrack_CA;
   //TH2F* h_p_AC_woSmallHits;
   //TH2F* h_p_CA_woSmallHits;

   ClassDef(MySelector_fornoisecheck,0);

};

#endif

#ifdef MySelector_fornoisecheck_cxx
void MySelector_fornoisecheck::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
   // Set object pointer
   //HitsOnDisks = 0;
   // Set branch addresses and branch pointers
   //if (!tree) return;
   //fChain = tree;
   //fChain->SetMakeClass(1);

   //fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   //fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   //fChain->SetBranchAddress("timeStamp", &timeStamp, &b_timeStamp);
   //fChain->SetBranchAddress("LBNumber", &LBNumber, &b_LBNumber);
   //fChain->SetBranchAddress("bcid", &bcid, &b_bcid);
   //fChain->SetBranchAddress("passesACTrigger", &passesACTrigger, &b_passesACTrigger);
   //fChain->SetBranchAddress("passesCATrigger", &passesCATrigger, &b_passesCATrigger);
   //fChain->SetBranchAddress("HitsOnDisks", &HitsOnDisks, &b_HitsOnDisks);
   //fChain->SetBranchAddress("BCMACprescale", &BCMACprescale, &b_BCMACprescale);
   //fChain->SetBranchAddress("BCMCAprescale", &BCMCAprescale, &b_BCMCAprescale);
   //fChain->SetBranchAddress("withPrimaryVertex", &withPrimaryVertex, &b_withPrimaryVertex);
   //fChain->SetBranchAddress("PixelHitsOnDisksA", &PixelHitsOnDisksA, &b_PixelHitsOnDisksA);
   //fChain->SetBranchAddress("PixelHitsOnDisksC", &PixelHitsOnDisksC, &b_PixelHitsOnDisksC);

}

Bool_t MySelector_fornoisecheck::Notify()
{
	// The Notify() function is called when a new file is opened. This
	// can be either for a new TTree in a TChain or when when a new TTree
	// is started when using PROOF. It is normally not necessary to make changes
	// to the generated code, but the routine can be extended by the
	// user if needed. The return value is currently not used.

	return kTRUE;
}


#endif // #ifdef MySelector_fornoisecheck_cxx

