#define MySelector_18_3_cxx
// The class definition in MySelector_18_3.h has been generated automatically
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
// root> T->Process("MySelector_18_3.C")
// root> T->Process("MySelector_18_3.C","some options")
// root> T->Process("MySelector_18_3.C+")
//


#include "MySelector_18_3.h"
#include <TH2.h>
#include <TStyle.h>
#include <map>

void MySelector_18_3::Begin(TTree * /*tree*/)
{
	// The Begin() function is called at the start of the query.
	// When running with PROOF Begin() is only called on the client.
	// The tree argument is deprecated (on PROOF 0 is passed).

	TString option = GetOption();
}

void MySelector_18_3::SlaveBegin(TTree * /*tree*/)
{
	// The SlaveBegin() function is called after the Begin() function.
	// When running with PROOF SlaveBegin() is called on each slave server.
	// The tree argument is deprecated (on PROOF 0 is passed).

	TString option = GetOption();
	outputfile_ = "output.root";

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

        //TH2F
	h_nHitsA_beam1 = new TH2F("nHitsA_beam1", "; Run Number; Events", 16340, 348150.5, 364490.5,5000,0,5000);
	h_nHitsC_beam1 = new TH2F("nHitsC_beam1", "; Run Number; Events", 16340, 348150.5, 364490.5,5000,0,5000);
	h_nHitsA_beam2 = new TH2F("nHitsA_beam2", "; Run Number; Events", 16340, 348150.5, 364490.5,5000,0,5000);
	h_nHitsC_beam2 = new TH2F("nHitsC_beam2", "; Run Number; Events", 16340, 348150.5, 364490.5,5000,0,5000);
	h_nHitsA_beam1_3 = new TH2F("nHitsA_beam1_3", "; Run Number; Events", 16340, 348150.5, 364490.5,5000,0,5000);
	h_nHitsC_beam1_3 = new TH2F("nHitsC_beam1_3", "; Run Number; Events", 16340, 348150.5, 364490.5,5000,0,5000);
	h_nHitsA_beam2_3 = new TH2F("nHitsA_beam2_3", "; Run Number; Events", 16340, 348150.5, 364490.5,5000,0,5000);
	h_nHitsC_beam2_3 = new TH2F("nHitsC_beam2_3", "; Run Number; Events", 16340, 348150.5, 364490.5,5000,0,5000);
	h_nHitsA_beam1_6 = new TH2F("nHitsA_beam1_6", "; Run Number; Events", 16340, 348150.5, 364490.5,5000,0,5000);
	h_nHitsC_beam1_6 = new TH2F("nHitsC_beam1_6", "; Run Number; Events", 16340, 348150.5, 364490.5,5000,0,5000);
	h_nHitsA_beam2_6 = new TH2F("nHitsA_beam2_6", "; Run Number; Events", 16340, 348150.5, 364490.5,5000,0,5000);
	h_nHitsC_beam2_6 = new TH2F("nHitsC_beam2_6", "; Run Number; Events", 16340, 348150.5, 364490.5,5000,0,5000);
	h_nHitsA_beam1_woSmallHits = new TH2F("nHitsA_beam1_woSmallHits", "; Run Number; Events", 16340, 348150.5, 364490.5,5000,0,5000);
	h_nHitsC_beam1_woSmallHits = new TH2F("nHitsC_beam1_woSmallHits", "; Run Number; Events", 16340, 348150.5, 364490.5,5000,0,5000);
	h_nHitsA_beam2_woSmallHits = new TH2F("nHitsA_beam2_woSmallHits", "; Run Number; Events", 16340, 348150.5, 364490.5,5000,0,5000);
	h_nHitsC_beam2_woSmallHits = new TH2F("nHitsC_beam2_woSmallHits", "; Run Number; Events", 16340, 348150.5, 364490.5,5000,0,5000);
	h_nHitsA_beam1_wSmallHits = new TH2F("nHitsA_beam1_wSmallHits", "; Run Number; Events", 16340, 348150.5, 364490.5,5000,0,5000);
	h_nHitsC_beam1_wSmallHits = new TH2F("nHitsC_beam1_wSmallHits", "; Run Number; Events", 16340, 348150.5, 364490.5,5000,0,5000);
	h_nHitsA_beam2_wSmallHits = new TH2F("nHitsA_beam2_wSmallHits", "; Run Number; Events", 16340, 348150.5, 364490.5,5000,0,5000);
	h_nHitsC_beam2_wSmallHits = new TH2F("nHitsC_beam2_wSmallHits", "; Run Number; Events", 16340, 348150.5, 364490.5,5000,0,5000);
	h_nTrackA_beam1 = new TH2F("nTrackA_beam1", "; Run Number; Events", 16340, 348150.5, 364490.5,50,0,50);
	h_nTrackC_beam1 = new TH2F("nTrackC_beam1", "; Run Number; Events", 16340, 348150.5, 364490.5,50,0,50);
	h_nTrack6_beam1 = new TH2F("nTrack6_beam1", "; Run Number; Events", 16340, 348150.5, 364490.5,50,0,50);
	h_nTrackA_beam2 = new TH2F("nTrackA_beam2", "; Run Number; Events", 16340, 348150.5, 364490.5,50,0,50);
	h_nTrackC_beam2 = new TH2F("nTrackC_beam2", "; Run Number; Events", 16340, 348150.5, 364490.5,50,0,50);
	h_nTrack6_beam2 = new TH2F("nTrack6_beam2", "; Run Number; Events", 16340, 348150.5, 364490.5,50,0,50);
	h_zasymtrack_AC = new TH2F("zasymtrack_AC", "; Run Number; Events", 16340, 348150.5, 364490.5,100,-1,1.1);
	h_zasymtrack_CA = new TH2F("zasymtrack_CA", "; Run Number; Events", 16340, 348150.5, 364490.5,100,-1,1.1);
	h_zasym_AC = new TH2F("zasym_AC", "; Run Number; Events", 16340, 348150.5, 364490.5,100,-1,1.1);
	h_zasym_CA = new TH2F("zasym_CA", "; Run Number; Events", 16340, 348150.5, 364490.5,100,-1,1.1);
	h_zasym_AC_woSmallHits = new TH2F("zasym_AC_woSmallHits", "; Run Number; Events", 16340, 348150.5, 364490.5,100,-1,1.1);
	h_zasym_CA_woSmallHits = new TH2F("zasym_CA_woSmallHits", "; Run Number; Events", 16340, 348150.5, 364490.5,100,-1,1.1);
	h_zasym_AC_wSmallHits = new TH2F("zasym_AC_wSmallHits", "; Run Number; Events", 16340, 348150.5, 364490.5,100,-1,1.1);
	h_zasym_CA_wSmallHits = new TH2F("zasym_CA_wSmallHits", "; Run Number; Events", 16340, 348150.5, 364490.5,100,-1,1.1);

	ListTH2F.push_back(h_nHitsA_beam1);
	ListTH2F.push_back(h_nHitsC_beam1);
	ListTH2F.push_back(h_nHitsA_beam2);
	ListTH2F.push_back(h_nHitsC_beam2);
	ListTH2F.push_back(h_nHitsA_beam1_3);
	ListTH2F.push_back(h_nHitsC_beam1_3);
	ListTH2F.push_back(h_nHitsA_beam2_3);
	ListTH2F.push_back(h_nHitsC_beam2_3);
	ListTH2F.push_back(h_nHitsA_beam1_6);
	ListTH2F.push_back(h_nHitsC_beam1_6);
	ListTH2F.push_back(h_nHitsA_beam2_6);
	ListTH2F.push_back(h_nHitsC_beam2_6);
	ListTH2F.push_back(h_nHitsA_beam1_woSmallHits);
	ListTH2F.push_back(h_nHitsC_beam1_woSmallHits);
	ListTH2F.push_back(h_nHitsA_beam2_woSmallHits);
	ListTH2F.push_back(h_nHitsC_beam2_woSmallHits);
	ListTH2F.push_back(h_nHitsA_beam1_wSmallHits);
	ListTH2F.push_back(h_nHitsC_beam1_wSmallHits);
	ListTH2F.push_back(h_nHitsA_beam2_wSmallHits);
	ListTH2F.push_back(h_nHitsC_beam2_wSmallHits);
	ListTH2F.push_back(h_nTrackA_beam1);
	ListTH2F.push_back(h_nTrackC_beam1);
	ListTH2F.push_back(h_nTrack6_beam1);
	ListTH2F.push_back(h_nTrackA_beam2);
	ListTH2F.push_back(h_nTrackC_beam2);
	ListTH2F.push_back(h_nTrack6_beam2);
	ListTH2F.push_back(h_zasymtrack_AC);
	ListTH2F.push_back(h_zasymtrack_CA);
	ListTH2F.push_back(h_zasym_AC);
	ListTH2F.push_back(h_zasym_CA);
	ListTH2F.push_back(h_zasym_AC_woSmallHits);
	ListTH2F.push_back(h_zasym_CA_woSmallHits);
	ListTH2F.push_back(h_zasym_AC_wSmallHits);
	ListTH2F.push_back(h_zasym_CA_wSmallHits);

	//for output
	cout << "outputfile_:" << outputfile_ << endl;
	outputFile = new TFile(outputfile_.c_str(), "RECREATE");


}

Bool_t MySelector_18_3::Process(Long64_t entry)
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

        double scale = 0.;
        double zasym = 1000;
        double zasymtrack = 1000;
        
        int hitA = 0;
        int hitC = 0;
        hitA = *fHitsPixelECA;
	hitC = *fHitsPixelECC;
        int ntrackA = 0;
        int ntrackC = 0;
        int ntrack6 = 0;
        bool threehitsA = false;
        bool threehitsC = false;
        bool sixhits = false;

        //for tracks...
	if(*fwithPrimaryVertex == false) { //w/o PV ; BIB events
		std::map<int,unsigned int> pattern;
		std::map<int,unsigned int> pattern6;
		unsigned int flag = 0; 
		unsigned int flag6 = 0; 

		for(int i = 0;i<*fPixelHits;i++){ //pixel cluster loop
			int mybec=0;
			int mylayer=0;
			int mybecphi=0;
			int myphi=0;
			if(abs(fpbecV[i]) == 2){
				if(fpbecV[i] == 2 ) mybec = 1;
				if(fpbecV[i] == -2 ) mybec = 0;
				mylayer = fplayerV[i];
				mybecphi = mybec*100+fpphiV[i];
				myphi = fpphiV[i];

				auto itr = pattern.find(mybecphi);        
				if( itr != pattern.end() ) {
					flag = itr->second;
					pattern[mybecphi] = (flag | (1 << mylayer));
				} else {
					pattern.insert(make_pair(mybec*100+fpphiV[i],(1 << mylayer)));
				}

				auto itr6 = pattern6.find(myphi);        
				if( itr6 != pattern6.end() ) {
					flag6 = itr6->second;
					if(mybec == 0) pattern6[myphi] = (flag6 | (1 << mylayer));
					if(mybec == 1) pattern6[myphi] = (flag6 | (1 << (mylayer+3)));
				} else {
					if(mybec == 0) pattern6.insert(make_pair(myphi,(1 << mylayer)));
					if(mybec == 1) pattern6.insert(make_pair(myphi,(1 << (mylayer+3))));
				}
			}
		} //end of pixelcluster loop

		//std::cout<< "************************pattern size= " << pattern.size() << std::endl;
		auto begin = pattern.begin(), end = pattern.end();
		for (auto iter = begin; iter != end; iter++) {
			if(iter->second == 7){ 
				//if(iter->first == 100) std::cout << "flag= " << iter->second << "becphi= " << iter->first << std::endl;
				if(iter->first>=100) ++ntrackA;
				else ++ntrackC;
			}
		}
		pattern.clear();

		auto begin6 = pattern6.begin(), end6 = pattern6.end();
		for (auto iter6 = begin6; iter6 != end6; iter6++) {
			if(iter6->second == 63){ 
				//std::cout << "flag= " << iter6->second << " phi= " << iter6->first << std::endl;
				++ntrack6;
			}
		}
		pattern6.clear();
	}//end bool PrimaryVertex

	if ((hitA+hitC) != 0) zasym = (double)( hitA - hitC )/( hitA + hitC );
	if ((ntrackA+ntrackC) != 0) zasymtrack = (double)( ntrackA - ntrackC )/( ntrackA + ntrackC );
        if (ntrackA > 0) threehitsA = true;
        if (ntrackC > 0) threehitsC = true;
        if (ntrack6 > 0) sixhits = true;

	// selection with trigger
	if(*fpassesACTrigger == true) { // BCMAC
		if(*fTriggerISO == true){ //ISO
			h_events_AC->Fill(*fRunNumber);
			h_nTrackA_beam1->Fill(*fRunNumber,ntrackA);
			h_nTrackC_beam1->Fill(*fRunNumber,ntrackC);
			h_nTrack6_beam1->Fill(*fRunNumber,ntrack6);

			if(*fwithPrimaryVertex == false) { //w/o PV ; BIB events
				h_nHitsA_beam1->Fill(*fRunNumber,hitA);
				h_nHitsC_beam1->Fill(*fRunNumber,hitC);
				if(threehitsA) h_nHitsA_beam1_3->Fill(*fRunNumber,hitA);
				if(threehitsC) h_nHitsC_beam1_3->Fill(*fRunNumber,hitC);
				if(sixhits) h_nHitsA_beam1_6->Fill(*fRunNumber,hitA);
				if(sixhits) h_nHitsC_beam1_6->Fill(*fRunNumber,hitC);
                                if(hitA > 50) h_nHitsA_beam1_woSmallHits->Fill(*fRunNumber,hitA);
                                if(hitC > 50) h_nHitsC_beam1_woSmallHits->Fill(*fRunNumber,hitC);
                                if(hitA <= 50) h_nHitsA_beam1_wSmallHits->Fill(*fRunNumber,hitA);
                                if(hitC <= 50) h_nHitsC_beam1_wSmallHits->Fill(*fRunNumber,hitC);
				h_events_ACwoPV->Fill(*fRunNumber);
				h_zasym_AC->Fill(*fRunNumber,zasym);
				if(hitA>50 && hitC>50) h_zasym_AC_woSmallHits->Fill(*fRunNumber,zasym);
				if(hitA<=50 && hitC<=50) h_zasym_AC_wSmallHits->Fill(*fRunNumber,zasym);
				h_zasymtrack_AC->Fill(*fRunNumber,zasymtrack);
			}
		}
	}

	if(*fpassesCATrigger == true) { // BCMCA
		if(*fTriggerISO == true){ //ISO
			h_events_CA->Fill(*fRunNumber);
			h_nTrackA_beam2->Fill(*fRunNumber,ntrackA);
			h_nTrackC_beam2->Fill(*fRunNumber,ntrackC);
			h_nTrack6_beam2->Fill(*fRunNumber,ntrack6);
			if(*fwithPrimaryVertex == false) { //w/o PV ; BIB events
				h_nHitsA_beam2->Fill(*fRunNumber,hitA);
				h_nHitsC_beam2->Fill(*fRunNumber,hitC);
				if(threehitsA) h_nHitsA_beam2_3->Fill(*fRunNumber,hitA);
				if(threehitsC) h_nHitsC_beam2_3->Fill(*fRunNumber,hitC);
				if(sixhits) h_nHitsA_beam2_6->Fill(*fRunNumber,hitA);
				if(sixhits) h_nHitsC_beam2_6->Fill(*fRunNumber,hitC);
                                if(hitA > 50) h_nHitsA_beam2_woSmallHits->Fill(*fRunNumber,hitA);
                                if(hitC > 50) h_nHitsC_beam2_woSmallHits->Fill(*fRunNumber,hitC);
                                if(hitA <= 50) h_nHitsA_beam2_wSmallHits->Fill(*fRunNumber,hitA);
                                if(hitC <= 50) h_nHitsC_beam2_wSmallHits->Fill(*fRunNumber,hitC);
				h_events_CAwoPV->Fill(*fRunNumber);
				h_zasym_CA->Fill(*fRunNumber,zasym);
				if(hitA>50 && hitC>50) h_zasym_CA_woSmallHits->Fill(*fRunNumber,zasym);
				if(hitA<=50 && hitC<=50) h_zasym_CA_wSmallHits->Fill(*fRunNumber,zasym);
				h_zasymtrack_CA->Fill(*fRunNumber,zasymtrack);
			}
		}
	}

	return kTRUE;
}

void MySelector_18_3::SlaveTerminate()
{
	// The SlaveTerminate() function is called after all entries or objects
	// have been processed. When running with PROOF SlaveTerminate() is called
	// on each slave server.

}

void MySelector_18_3::Terminate()
{
	// The Terminate() function is the last function to be called during
	// a query. It always runs on the client, it can be used to present
	// the results graphically or save the results to file.
	for ( TH1F* th1f : ListTH1F) th1f->Write();
	for ( TH2F* th2f : ListTH2F) th2f->Write();
	outputFile->Close();
}


