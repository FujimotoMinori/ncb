/*
    getandrebin.cxx
*/
#include "TF2.h"
#include "TH2.h"
#include "TH1.h"
#include "TH1D.h"
#include "TMath.h"


void getandrebin(/*const string& inputFile*/) {

    //string finname = inputFile;
    string finname = "/Users/fujimoto/QTtask/ncb/data/sample.root";

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
    TH2F *hA0woSH = (TH2F*)fin->Get("radiusA0woSH"); 
    TH2F *hA1woSH = (TH2F*)fin->Get("radiusA1woSH"); 
    TH2F *hA2woSH = (TH2F*)fin->Get("radiusA2woSH"); 
    TH2F *hC0woSH = (TH2F*)fin->Get("radiusC0woSH"); 
    TH2F *hC1woSH = (TH2F*)fin->Get("radiusC0woSH"); 
    TH2F *hC2woSH = (TH2F*)fin->Get("radiusC0woSH"); 
    hA0woSH->Rebin(4);
    hA1woSH->Rebin(4);
    hA2woSH->Rebin(4);

    TH2F *hA0wSH = (TH2F*)fin->Get("radiusA0wSH"); 
    TH2F *hA1wSH = (TH2F*)fin->Get("radiusA1wSH"); 
    TH2F *hA2wSH = (TH2F*)fin->Get("radiusA2wSH"); 
    hA0wSH->Rebin(4);
    hA1wSH->Rebin(4);
    hA2wSH->Rebin(4);

    //draw histogram
    TCanvas *c1 = new TCanvas("c1", "c1");
    hA0woSH->GetZaxis()->SetRangeUser(0,1500);
    hA0woSH->SetStats(0);
    hA0woSH->Draw("h");
    TCanvas *c2 = new TCanvas("c2", "c2");
    hA1woSH->GetZaxis()->SetRangeUser(0,1500);
    hA1woSH->SetStats(0);
    hA1woSH->Draw("h");
    TCanvas *c3 = new TCanvas("c3", "c3");
    hA2woSH->GetZaxis()->SetRangeUser(0,1500);
    hA2woSH->SetStats(0);
    hA2woSH->Draw("h");

    TCanvas *c4 = new TCanvas("c4", "c4");
    hA0wSH->GetZaxis()->SetRangeUser(0,15);
    hA0wSH->SetStats(0);
    hA0wSH->Draw("h");
    TCanvas *c5 = new TCanvas("c5", "c5");
    hA1wSH->GetZaxis()->SetRangeUser(0,15);
    hA1wSH->SetStats(0);
    hA1wSH->Draw("h");
    TCanvas *c6 = new TCanvas("c6", "c6");
    hA2wSH->GetZaxis()->SetRangeUser(0,15);
    hA2wSH->SetStats(0);
    hA2wSH->Draw("h");

    c1->Print("A0woSH.pdf");
    c2->Print("A1woSH.pdf");
    c3->Print("A2woSH.pdf");
    c4->Print("A0wSH.pdf");
    c5->Print("A1wSH.pdf");
    c6->Print("A2wSH.pdf");
    
    return;

}


