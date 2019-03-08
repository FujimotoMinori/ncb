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
    string finname = "/Users/fujimoto/QTtask/ncb/data/output0306.root";
    //string finname2 = "/Users/fujimoto/QTtask/ncb/submitDir_6/hist-data.root";

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
    TH1F *h1 = (TH1F*)fin->Get("mHist_BCMACUItrig"); 
    TH1F *h2 = (TH1F*)fin->Get("mHist_BCMCAUItrig"); 
    TH1F *h3 = (TH1F*)fin->Get("mHist_BCMACNUItrig"); 
    TH1F *h4 = (TH1F*)fin->Get("mHist_BCMCANUItrig"); 
    TH1F *h5 = (TH1F*)fin->Get("mHist_unpaired1"); 
    TH1F *h6 = (TH1F*)fin->Get("mHist_unpaired2"); 

    h2->SetLineColor(kRed);
    //draw histogram
    TCanvas *c1 = new TCanvas("c1", "c1");
    //h1->GetYaxis()->SetRangeUser(0,2000);
    h1->Draw();
    h2->Draw("sames");
    c1->Update();
    TPaveStats *st1 = (TPaveStats*)h1->FindObject("stats");
    st1->SetTextColor(kBlue);
    TPaveStats *st2 = (TPaveStats*)h2->FindObject("stats");
    st2->SetTextColor(kRed);
    st2->SetX1NDC(0.18);
    st2->SetX2NDC(0.38);
    c1->Modified();

    h6->SetLineColor(kRed);
    //draw histogram
    TCanvas *c2 = new TCanvas("c2", "c2");
    //h1->GetYaxis()->SetRangeUser(0,2000);
    h5->Draw();
    h6->Draw("sames");
    c2->Update();
    TPaveStats *st5 = (TPaveStats*)h5->FindObject("stats");
    st5->SetTextColor(kBlue);
    TPaveStats *st6 = (TPaveStats*)h6->FindObject("stats");
    st6->SetTextColor(kRed);
    st6->SetX1NDC(0.18);
    st6->SetX2NDC(0.38);
    c2->Modified();
    
    h4->SetLineColor(kRed);
    //draw histogram
    TCanvas *c3 = new TCanvas("c3", "c3");
    //h1->GetYaxis()->SetRangeUser(0,2000);
    h3->Draw();
    h4->Draw("sames");
    c3->Update();
    TPaveStats *st3 = (TPaveStats*)h3->FindObject("stats");
    st3->SetTextColor(kBlue);
    TPaveStats *st4 = (TPaveStats*)h4->FindObject("stats");
    st4->SetTextColor(kRed);
    st4->SetX1NDC(0.18);
    st4->SetX2NDC(0.38);
    c3->Modified();

    c1->SaveAs("mHist_BCMUItrig2.pdf");
    c2->SaveAs("mHist_unpaired2.pdf");
    c3->SaveAs("mHist_BCMUNItrig2.pdf");
    
    return;

}

