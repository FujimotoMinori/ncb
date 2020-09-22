#define MySelector_fornoisecheck_cxx
// The class definition in MySelector_fornoisecheck.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("MySelector_fornoisecheck.C")
// root> T->Process("MySelector_fornoisecheck.C","some options")
// root> T->Process("MySelector_fornoisecheck.C+")
//


#include "MySelector_fornoisecheck.h"
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <map>
#include "pixelMapping.h"
//#include <stdio.h>
#include <string>

void MySelector_fornoisecheck::Begin(TTree * /*tree*/)
{
	// The Begin() function is called at the start of the query.
	// When running with PROOF Begin() is only called on the client.
	// The tree argument is deprecated (on PROOF 0 is passed).

	//TString option = GetOption();
}

void MySelector_fornoisecheck::SlaveBegin(TTree * /*tree*/)
{
	// The SlaveBegin() function is called after the Begin() function.
	// When running with PROOF SlaveBegin() is called on each slave server.
	// The tree argument is deprecated (on PROOF 0 is passed).

	outputfile_ = "outputofornoise.root";

	//TH1F
	h_events= new TH1F("events", "; Run Number; Events", 16340, 348150.5, 364490.5);
	h_events_AC= new TH1F("eventsAC", "; Run Number; Events", 16340, 348150.5, 364490.5);
	h_events_CA= new TH1F("eventsCA", "; Run Number; Events", 16340, 348150.5, 364490.5);
	h_events_ACwoPV= new TH1F("eventsACwoPV", "; Run Number; Events", 16340, 348150.5, 364490.5);
	h_events_CAwoPV= new TH1F("eventsCAwoPV", "; Run Number; Events", 16340, 348150.5, 364490.5);

	ListTH1F.push_back(h_events);
	ListTH1F.push_back(h_events_AC);
	ListTH1F.push_back(h_events_CA);
	ListTH1F.push_back(h_events_ACwoPV);
	ListTH1F.push_back(h_events_CAwoPV);

	//for dead module
	h_zasym_AC_woSmallHitsnew = new TH2F("zasym_AC_woSmallHitsnew", "; Run Number; Events", 16340, 348150.5, 364490.5,100,-1,1.1);
	h_zasym_CA_woSmallHitsnew = new TH2F("zasym_CA_woSmallHitsnew", "; Run Number; Events", 16340, 348150.5, 364490.5,100,-1,1.1);

	//for dead module
	ListTH2F.push_back(h_zasym_AC_woSmallHitsnew);
	ListTH2F.push_back(h_zasym_CA_woSmallHitsnew);

	//for output
	cout << "outputfile_:" << outputfile_ << endl;
	outputFile = new TFile(outputfile_.c_str(), "RECREATE");

}

Bool_t MySelector_fornoisecheck::Process(Long64_t entry)
{
	// The Process() function is called for each entry in the tree (or possibly
	// keyed object in the case of PROOF) to be processed. The entry argument
	// specifies which entry in the currently loaded tree is to be processed.
	// When processing keyed objects with PROOF, the object is already loaded
	// and is available via the fObject pointer.
	//
	// This function should contain the \"body\" of the analysis. It can contain
	// simple or elaborate selection criteria, run algorithms on the data
	// of the event and typically fill histograms.
	//
	// The processing can be stopped by calling Abort().
	//
	// Use fStatus to set the return value of TTree::Process().
	//
	// The return value is currently not used.

	fReader.SetEntry(entry);
	h_events->Fill(*fRunNumber);
        //nevents++;
        //std::cout << "nevents= " << nevents << std::endl;

	double scale = 0.;
	double zasym = 1000;

	int bcid = *fbcid;
	int hitA = 0;
	int hitC = 0;
	hitA = *fHitsPixelECA;
	hitC = *fHitsPixelECC;
	int hitsECA = 0;
	int hitsECC = 0;
	int hitsnoise1 = 0;
	int hitsnoise2 = 0;
	int hitsnoise3 = 0;
	double ratio = 1000;

	if(*fwithPrimaryVertex == false) { //w/o PV ; BIB events

		for(int i = 0;i<*fPixelHits;i++){ //pixel cluster loop
			if(abs(fpbecV[i]) == 2){ //only endcap
					if(/*fpchargeV[i] < 10000 && */fpnRDOV[i] == 1) hitsnoise++;

			} //only endcap
		} //end of pixelcluster loop

		if ( hitA != 0) ratio = ((double)hitsECA)/((double)hitA);

	} //end bool PrimaryVertex

	if ((hitA+hitC) != 0) zasym = (double)( hitA - hitC )/( hitA + hitC );
	if (hitC != 0) pA = (double) hitA/hitC;
	if (hitA != 0) pC = (double) hitC/hitA;


	//empty trigger
	if(*fTriggerEmpty == true){ //empty trig
		if(*fwithPrimaryVertex == false){ //w/o PV ; BIB events
		}
	}

	// selection with trigger
	if(*fpassesACTrigger == true) { // BCMAC
		if(*fTriggerISO == true){ //ISO
			h_events_AC->Fill(*fRunNumber);

			if(*fwithPrimaryVertex == false) { //w/o PV ; BIB events
				if(hitA > 50) {
				}
				if(hitC > 50) {
				}
				//if(hitA <= 50) h_nHitsA_beam1_wSmallHits->Fill(*fRunNumber,hitA);
				//if(hitC <= 50) h_nHitsC_beam1_wSmallHits->Fill(*fRunNumber,hitC);
				h_events_ACwoPV->Fill(*fRunNumber);
				if(hitA>50 && hitC>50) {
					//for dead module
					h_zasym_AC_woSmallHitsnew->Fill(*fRunNumber,zasymnew);
				}
				//if(hitA<=50 && hitC<=50) h_zasym_AC_wSmallHits->Fill(*fRunNumber,zasym);
			}
		}
	}

	if(*fpassesCATrigger == true) { // BCMCA
		if(*fTriggerISO == true){ //ISO
			h_events_CA->Fill(*fRunNumber);
			if(*fwithPrimaryVertex == false) { //w/o PV ; BIB events
				if(hitA > 50) {
				}
				if(hitC > 50) {
				}
				//if(hitA <= 50) h_nHitsA_beam2_wSmallHits->Fill(*fRunNumber,hitA);
				//if(hitC <= 50) h_nHitsC_beam2_wSmallHits->Fill(*fRunNumber,hitC);
				h_events_CAwoPV->Fill(*fRunNumber);
				if(hitA>50 && hitC>50) {
					//for dead module
					h_zasym_CA_woSmallHitsnew->Fill(*fRunNumber,zasymnew);
				}
				//if(hitA<=50 && hitC<=50) h_zasym_CA_wSmallHits->Fill(*fRunNumber,zasym);
			}
		}
	}
	return kTRUE;
}

void MySelector_fornoisecheck::SlaveTerminate()
{
	// The SlaveTerminate() function is called after all entries or objects
	// have been processed. When running with PROOF SlaveTerminate() is called
	// on each slave server.

}

void MySelector_fornoisecheck::Terminate()
{
	// The Terminate() function is the last function to be called during
	// a query. It always runs on the client, it can be used to present
	// the results graphically or save the results to file.
	for ( TH1F* th1f : ListTH1F) th1f->Write();
	for ( TH2F* th2f : ListTH2F) th2f->Write();
	outputFile->Close();
}


