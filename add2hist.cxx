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

    //string finname = inputFile;
    string finname = "/Users/fujimoto/QTtask/ncb/data/output0405.root";

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
    TH1F *h1 = (TH1F*)fin->Get("mHist_NPixelsunpaired1and"); 
    TH1F *h2 = (TH1F*)fin->Get("mHist_NPixelsunpaired16"); 
    TH1F *h3 = (TH1F*)fin->Get("mHist_BCMACNUItrigwpv"); 
    TH1F *h4 = (TH1F*)fin->Get("mHist_BCMCANUItrigwpv"); 
    TH1F *h5 = (TH1F*)fin->Get("mHist_BCMACNUItrigwopv"); 
    TH1F *h6 = (TH1F*)fin->Get("mHist_BCMCANUItrigwopv"); 
    //TH1F *h3 = (TH1F*)fin->Get("mHist_BCMACNUItrigwopv"); 
    //TH1F *h4 = (TH1F*)fin->Get("mHist_BCMCANUItrigwopv"); 
    //TH1F *h5 = (TH1F*)fin->Get("mHist_unpaired1wopvorg"); 
    //TH1F *h6 = (TH1F*)fin->Get("mHist_unpaired2wopvorg"); 

    h2->SetLineColor(kRed);
    //draw histogram
    TCanvas *c1 = new TCanvas("c1", "c1");
    //h1->GetYaxis()->SetRangeUser(0,2800);
    h1->SetTitle("NPixels");
    h1->GetXaxis()->SetTitle("NPixels");
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
    h5->GetYaxis()->SetRangeUser(0,2800);
    h5->SetTitle("BCMUI");
    h5->GetXaxis()->SetTitle("z-asymmetry");
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
    h3->GetYaxis()->SetRangeUser(0,2800);
    h3->SetTitle("BCMUI");
    h3->GetXaxis()->SetTitle("z-asymmetry");
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

    c1->SaveAs("mHist_BCMUItrigwoPV.pdf");
    c2->SaveAs("mHist_unpairedwoPV.pdf");
    c3->SaveAs("mHist_BCMUNItrigwoPV.pdf");
    
    return;

}

