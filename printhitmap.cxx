/*
    printhitmap.cxx
    read histogram and fit by 2Dgaussian
*/
#include "TF2.h"
#include "TH2.h"
#include "TH1.h"
#include "TH1D.h"
#include "TMath.h"


void printhitmap(/*const string& inputFile*/) {

    //string finname = inputFile;
    string finname = "/Users/fujimoto/QTtask/ncb/data/merged0701.root";

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
    TH2F *hA0woSH = (TH2F*)fin->Get("hitmapA0woSH"); 
    TH2F *hA1woSH = (TH2F*)fin->Get("hitmapA1woSH"); 
    TH2F *hA2woSH = (TH2F*)fin->Get("hitmapA2woSH"); 
    TH2F *hC0woSH = (TH2F*)fin->Get("hitmapC0woSH"); 
    TH2F *hC1woSH = (TH2F*)fin->Get("hitmapC1woSH"); 
    TH2F *hC2woSH = (TH2F*)fin->Get("hitmapC2woSH"); 

    TH2F *hA0wSH = (TH2F*)fin->Get("hitmapA0wSH"); 
    TH2F *hA1wSH = (TH2F*)fin->Get("hitmapA1wSH"); 
    TH2F *hA2wSH = (TH2F*)fin->Get("hitmapA2wSH"); 
    TH2F *hC0wSH = (TH2F*)fin->Get("hitmapC0wSH"); 
    TH2F *hC1wSH = (TH2F*)fin->Get("hitmapC1wSH"); 
    TH2F *hC2wSH = (TH2F*)fin->Get("hitmapC2wSH"); 

    //draw histogram
    TCanvas *c1 = new TCanvas("c1", "c1");
    hC0woSH->GetZaxis()->SetRangeUser(0,1500);
    hC0woSH->SetStats(0);
    hC0woSH->Draw("colz");
    TCanvas *c2 = new TCanvas("c2", "c2");
    hC1woSH->GetZaxis()->SetRangeUser(0,1500);
    hC1woSH->SetStats(0);
    hC1woSH->Draw("colz");
    TCanvas *c3 = new TCanvas("c3", "c3");
    hC2woSH->GetZaxis()->SetRangeUser(0,1500);
    hC2woSH->SetStats(0);
    hC2woSH->Draw("colz");

    TCanvas *c4 = new TCanvas("c4", "c4");
    hC0wSH->GetZaxis()->SetRangeUser(0,15);
    hC0wSH->SetStats(0);
    hC0wSH->Draw("colz");
    TCanvas *c5 = new TCanvas("c5", "c5");
    hC1wSH->GetZaxis()->SetRangeUser(0,15);
    hC1wSH->SetStats(0);
    hC1wSH->Draw("colz");
    TCanvas *c6 = new TCanvas("c6", "c6");
    hC2wSH->GetZaxis()->SetRangeUser(0,15);
    hC2wSH->SetStats(0);
    hC2wSH->Draw("colz");

    c1->Print("C0woSH.pdf");
    c2->Print("C1woSH.pdf");
    c3->Print("C2woSH.pdf");
    c4->Print("C0wSH.pdf");
    c5->Print("C1wSH.pdf");
    c6->Print("C2wSH.pdf");
    
    return;

}

