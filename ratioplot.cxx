/*
    ratioplot.cxx
*/
#include "TF2.h"
#include "TH2.h"
#include "TH1.h"
#include "TH1D.h"
#include "TMath.h"

void ratioplot(/*const string& inputFile*/) {

    //string finname = inputFile;
    string finname = "../data/merged_18_3.hist.root";

    //file open
    TFile* fin = TFile::Open(finname.c_str(), "READ");
    if (!fin) {
        cout << " input file:" << finname.c_str() << " does not exist"<< endl;
        return;
    }
    cout << " input data file:" << finname.c_str() << " open..." << endl;

    //get histograms
    TH1F *h1 = (TH1F*)fin->Get("events"); 
    TH1F *h2 = (TH1F*)fin->Get("eventsAC"); 
    TH1F *h3 = (TH1F*)fin->Get("eventsCA"); 

    //new histograms
    //TH1F *h_ratio = new TH1F("h_ratio", "ratio of events w/ BCM_AC_UI trig ; Run Number; ratio", 16340, 348150.5, 364490.5);
    TH1F *h_ratio = new TH1F("h_ratio", "asymmetry of event with trigger ; Run Number; ratio", 16340, 348150.5, 364490.5);

    //get 
    double a,b,c;
    const int n = h1->GetNbinsX()+1;
    //double x[n] = {};
    //double y[n] = {};
    for (int i=0; i< n; i++){
        double z = 0.;
        double w = 0.;
        //x[i] = i;
        a  = h1->GetBinContent(i);
        b  = h2->GetBinContent(i);
        c  = h3->GetBinContent(i);
        if( a != 0 ) z = b/a;
        if( a != 0 ) w = c/a;
        //if ( z != 0 ){
         //   h_ratio->SetBinContent(i,z);
        //}
        double m = 0;
        if ( b != 0 ){
        if ( c != 0 ){
                m = (b-c)/(b+c);
                std::cout << "m= " << m << std::endl;
            if(m != 0.){
                h_ratio->SetBinContent(i,m);
            }
        }
        }
        //if(i == 363910-348150) {
        //    std::cout << "i= " << i << std::endl;
        //    std::cout << "nEvents= " << a << std::endl;
        //    std::cout << "AC= " << b << std::endl;
        //    std::cout << "CA= " << c << std::endl;
        //    std::cout << "z= " << z << std::endl;
        //}
        //y[i] = z;
    }

    TCanvas *c1 = new TCanvas("c1", "c1");
    h_ratio->GetYaxis()->SetRangeUser(-1.0,1.1);
    h_ratio->Draw("P");
    h_ratio->SetLineColor(3); //5
    h_ratio->SetMarkerColor(2);
    h_ratio->SetMarkerStyle(21);
    h_ratio->SetMarkerSize(0.3);

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
    
    return;

}

