/*
    drawhists.cxx
    read histogram and fit by 2Dgaussian
*/
#include "TF2.h"
#include "TH2.h"
#include "TH1.h"
#include "TH1D.h"
#include "TMath.h"


void drawhists(/*const string& inputFile*/) {

    //string finname = inputFile;
    string finname = "../data/output0804.root";

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
    TH1F *h1 = (TH1F*)fin->Get("all"); 
    TH1F *h2 = (TH1F*)fin->Get("hits3"); 
    TH1F *h3 = (TH1F*)fin->Get("hits6"); 
    TH1F *h4 = (TH1F*)fin->Get("woSmallHits"); 
    TH1F *h5 = (TH1F*)fin->Get("ECA_beam1");

    h1->SetLineColor(kGreen);
    //draw histogram
    TCanvas *c1 = new TCanvas("c1", "c1");
    //h1->SetTitle("NPixels");
    //h1->GetXaxis()->SetTitle("NPixels");
    h1->Draw();
    h2->SetLineColor(kRed);
    h2->Draw("sames");
    c1->Update();
    h4->SetLineColor(kBlack);
    h4->Draw("sames");
    h3->SetLineColor(kBlue);
    h3->Draw("sames");
    c1->Update();
    h5->SetLineColor(kPink);
    h5->Draw("sames");
    c1->Update();

    TPaveStats *st1 = (TPaveStats*)h1->FindObject("stats");
    st1->SetTextColor(kGreen);
    TPaveStats *st2 = (TPaveStats*)h2->FindObject("stats");
    st2->SetTextColor(kRed);
    c1->Modified();
    TPaveStats *st4 = (TPaveStats*)h4->FindObject("stats");
    st4->SetTextColor(kBlack);
    c1->Modified();
    TPaveStats *st3 = (TPaveStats*)h3->FindObject("stats");
    c1->Modified();
    st3->SetTextColor(kBlue);
    c1->Modified();
    TPaveStats *st5 = (TPaveStats*)h5->FindObject("stats");
    st5->SetTextColor(kPink);
    c1->Modified();


    //c1->SaveAs("test0804.pdf");
    
    return;

}


