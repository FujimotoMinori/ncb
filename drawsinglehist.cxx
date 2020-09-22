/*
    drawhists.cxx
    read histogram and fit by 2Dgaussian
*/
#include "TF2.h"
#include "TH2.h"
#include "TH1.h"
#include "TH1D.h"
#include "TMath.h"


void drawsinglehist(/*const string& inputFile*/) {

    //string finname = inputFile;
    string finname = "../data/sample.root";

    //file open
    TFile* fin = TFile::Open(finname.c_str(), "READ");
    if (!fin) {
        cout << " input file:" << finname.c_str() << " does not exist"<< endl;
        return;
    }
    cout << " input data file:" << finname.c_str() << " open..." << endl;

    //TFile* fin2 = TFile::Open(finname2.c_str(), "READ");
    //if (!fin2) {
    //    cout << " input file:" << finname2.c_str() << " does not exist"<< endl;
    //    return;
    //}
    //cout << " input data file:" << finname2.c_str() << " open..." << endl;

    //get histogram
    TH1F *h1 = (TH1F*)fin->Get("nRDOwoSH"); 
    TH1F *h2 = (TH1F*)fin->Get("nRDOwSH"); 

    cout << h1->GetEntries() << endl;
    cout << h1->GetBinContent(2) << endl;
    cout << h1->GetBinContent(2)/h1->GetEntries() << endl;
    cout << h2->GetEntries() << endl;
    cout << h2->GetBinContent(2) << endl;
    cout << h2->GetBinContent(2)/h2->GetEntries() << endl;
    //h1->SetLineColor(kGreen);
    //draw histogram
    TCanvas *c1 = new TCanvas("c1", "c1");
    //h1->SetTitle("NPixels");
    h1->GetXaxis()->SetTitle("nRDO");
    h1->Draw();
    TCanvas *c2 = new TCanvas("c2", "c2");
    //h2->SetLineColor(kRed);
    h2->GetXaxis()->SetTitle("nRDO");
    h2->Draw();
    //c1->Update();

    //TPaveStats *st1 = (TPaveStats*)h1->FindObject("stats");
    //st1->SetTextColor(kGreen);
    //TPaveStats *st2 = (TPaveStats*)h2->FindObject("stats");
    //st2->SetTextColor(kRed);
    //c1->Modified();

    //c1->SaveAs("test0804.pdf");
    
    return;

}


