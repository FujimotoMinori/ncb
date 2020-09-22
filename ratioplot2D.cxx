/*
    ratioplot.cxx
*/
#include "TF2.h"
#include "TH2.h"
#include "TH1.h"
#include "TH1D.h"
#include "TMath.h"

void ratioplot2D(/*const string& inputFile*/) {

    //string finname = inputFile;
    string finname = "../data/merged.hist.root";

    //file open
    TFile* fin = TFile::Open(finname.c_str(), "READ");
    if (!fin) {
        cout << " input file:" << finname.c_str() << " does not exist"<< endl;
        return;
    }
    cout << " input data file:" << finname.c_str() << " open..." << endl;

    //get histograms
    TH2F *h1 = (TH2F*)fin->Get("zasym_ACvalid"); 
    TH2F *h2 = (TH2F*)fin->Get("zasym_CAvalid"); 

    //new histograms
    TH1F *h_mean = new TH1F("h_mean", "; Run Number; ratio", 16340, 348150.5, 364490.5);
    
    TProfile *pf = h1->ProfileX();
    TCanvas *c1 = new TCanvas("c1", "c1");
    pf->Draw();
    TProfile *pf2 = h2->ProfileX();
    TCanvas *c2 = new TCanvas("c2", "c2");
    pf2->Draw();
     

    /*
    //get 
    double a,b,c;
    const int n = h2->GetNbinsX()+1;
    for (int i=0; i< n; i++){
        double z = 0.;
        //x[i] = i;
        a  = h1->GetBinContent(i);
        h_ratio->SetBinContent(i,z);
        std::cout << "z= " << z << std::endl;
    }

    TCanvas *c1 = new TCanvas("c1", "c1");
    h_ratio->GetYaxis()->SetRangeUser(0.,1.1);
    h_ratio->Draw("");

    //TGraph *gr = new TGraph(n,x,y);
    //TCanvas *c2 = new TCanvas("c2", "c2");
    //gr->Draw("AP");


    //draw histogram
    //h2->SetLineColor(kRed);
    //TCanvas *c1 = new TCanvas("c1", "c1");
    ////h1->GetYaxis()->SetRangeUser(0,2800);
    //h1->SetTitle("NPixels");
    //h1->GetXaxis()->SetTitle("NPixels");
    //h1->Draw();
    //h2->Draw("sames");
    //c1->Update();
    //TPaveStats *st1 = (TPaveStats*)h1->FindObject("stats");
    //st1->SetTextColor(kBlue);
    //TPaveStats *st2 = (TPaveStats*)h2->FindObject("stats");
    //st2->SetTextColor(kRed);
    //st2->SetX1NDC(0.18);
    //st2->SetX2NDC(0.38);
    //c1->Modified();

    //c1->SaveAs("mHist_ratio.pdf");
    */
    
    return;

}

