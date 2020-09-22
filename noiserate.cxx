/*
    noiserate.cxx
    read histogram and fit by 2Dgaussian
*/
#include "TF2.h"
#include "TH2.h"
#include "TH1.h"
#include "TH1D.h"
#include "TMath.h"


void noiserate(/*const string& inputFile*/) {

    //string finname = inputFile;
    //string finname = "../data/merged_18_1003.root";
    string finname = "../data/merged0921.hist.root";

    //file open
    TFile* fin = TFile::Open(finname.c_str(), "READ");
    if (!fin) {
        cout << " input file:" << finname.c_str() << " does not exist"<< endl;
        return;
    }
    cout << " input data file:" << finname.c_str() << " open..." << endl;

    //get histogram
    //TH1F *h1 = (TH1F*)fin->Get("noiserateAcluster"); 
    TH1F *h1 = (TH1F*)fin->Get("noiserate"); 
    TH1F *h2 = (TH1F*)fin->Get("noiserateall"); 

    //for(int i = 0;i< h2->GetEntries();i++){
    //    cout << "i= " << i << endl;
    //    if (h2->GetBinError(i) != 0. ) cout << "bincontent= " << (h2->GetBinError(i))*(h2->GetBinError(i)) << endl;
    //}

    //draw histogram
    gStyle->SetOptStat(0);
    TCanvas *c1 = new TCanvas("c1", "c1");
    //h1->SetTitle("NPixels");
    //h1->GetXaxis()->SetTitle("NPixels");
    h1->SetMarkerColor(kBlue);
    h1->SetMarkerSize(20);
    h1->SetMarkerStyle(7);
    h1->Draw("e2");
    c1->Update();
    TCanvas *c2 = new TCanvas("c2", "c2");
    h2->SetMarkerColor(kBlue);
    h2->SetMarkerSize(20);
    h2->SetMarkerStyle(7);
    h2->Draw("e2");
    c2->Update();
    //h2->SetLineColor(kRed);
    //h2->Draw("sames");
    //c1->Update();

    //TPaveStats *st1 = (TPaveStats*)h1->FindObject("stats");
    //st1->SetTextColor(kGreen);
    //TPaveStats *st2 = (TPaveStats*)h2->FindObject("stats");
    //st2->SetTextColor(kRed);
    //c1->Modified();

    //c1->SaveAs("noiserate.pdf");
    
    return;

}


