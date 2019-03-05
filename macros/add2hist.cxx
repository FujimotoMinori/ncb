/*
    add2hist.cxx
    read histogram and fit by 2Dgaussian
*/
#include "TF2.h"
#include "TH2.h"
#include "TH1.h"
#include "TH1D.h"
#include "TMath.h"


void add2hist(/*const string& inputFile*/) {
    std::cout << "#-----start beamfitfromdata.cxx-----" << std::endl;

    //string finname = inputFile;
    string finname = "/Users/fujimoto/QTtask/ncb/submitDir_5/hist-data.root";
    string finname2 = "/Users/fujimoto/QTtask/ncb/submitDir_6/hist-data.root";

    //file open
    TFile* fin = TFile::Open(finname.c_str(), "READ");
    if (!fin) {
        cout << " input file:" << finname.c_str() << " does not exist"<< endl;
        return;
    }
    cout << " input data file:" << finname.c_str() << " open..." << endl;

    TFile* fin2 = TFile::Open(finname2.c_str(), "READ");
    if (!fin2) {
        cout << " input file:" << finname2.c_str() << " does not exist"<< endl;
        return;
    }
    cout << " input data file:" << finname2.c_str() << " open..." << endl;
    //get histogram
    TH1F *h1 = (TH1F*)fin->Get("mHist_charge"); 
    TH1F *h2 = (TH1F*)fin2->Get("mHist_charge"); 
    h2->SetLineColor(kRed);
    //draw histogram
    TCanvas *c1 = new TCanvas("c1", "c1");
    //h1->GetYaxis()->SetRangeUser(0,2000);
    h1->Draw();
    h2->Draw("sames");
    c1->Update();
    TPaveStats *st1 = (TPaveStats*)h1->FindObject("stats");
    st1->SetTextColor(kRed);
    TPaveStats *st2 = (TPaveStats*)h2->FindObject("stats");
    st2->SetTextColor(kBlue);
    st2->SetX1NDC(0.18);
    st2->SetX2NDC(0.38);
    c1->Modified();

    return;

}

