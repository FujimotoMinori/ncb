/*
    ratioratioplot.cxx
*/
#include "TF2.h"
#include "TH2.h"
#include "TH1.h"
#include "TH1D.h"
#include "TMath.h"

void ratioratioplot(/*const string& inputFile*/) {

    //string finname = inputFile;
    string finname = "../data/merged_17_0616.hist.root";

    //file open
    TFile* fin = TFile::Open(finname.c_str(), "READ");
    if (!fin) {
        cout << " input file:" << finname.c_str() << " does not exist"<< endl;
        return;
    }
    cout << " input data file:" << finname.c_str() << " open..." << endl;

    //get histograms
    TH1F *h1 = (TH1F*)fin->Get("eventsAC"); 
    TH1F *h2 = (TH1F*)fin->Get("eventsACwoPV"); 
    TH1F *h3 = (TH1F*)fin->Get("eventsCA"); 
    TH1F *h4 = (TH1F*)fin->Get("eventsCAwoPV"); 

    //new histograms
    //TH1F *h_ratioAC = new TH1F("h_ratioAC", "ratio of events w/ BCM_AC_UI trig ; Run Number; ratio", 16340, 348150.5, 364490.5);
    //TH1F *h_ratioCA = new TH1F("h_ratioCA", "ratioCA of events w/ BCM_CA_UI trig ; Run Number; ratio", 16340, 348150.5, 364490.5);
    //TH1F *h_ratioratio = new TH1F("h_ratioratio", "comparison of ratio (AC/CA) ; Run Number; ratio", 16340, 348150.5, 364490.5);
    TH1F *h_ratioAC = new TH1F("h_ratioAC", "ratio of events w/ BCM_AC_UI trig ; Run Number; ratio", 17345, 324310.5, 341655.5);
    TH1F *h_ratioCA = new TH1F("h_ratioCA", "ratioCA of events w/ BCM_CA_UI trig ; Run Number; ratio", 17345, 324310.5, 341655.5);
    TH1F *h_ratioratio = new TH1F("h_ratioratio", "comparison of ratio (AC/CA) ; Run Number; ratio", 17345, 324310.5, 341655.5);

    //get 
    double a,b,c,d;
    vector<Double_t> x,y;
    const int n = h1->GetNbinsX()+1;
    for (int i=0; i< n; i++){
        double z = 0.;
        double w = 0.;
        double answer = 0.;
        //int m = h1->GetBin(i);
        a  = h1->GetBinContent(i);
        b  = h2->GetBinContent(i);
        c  = h3->GetBinContent(i);
        d  = h4->GetBinContent(i);
        if( a !=0 ) z = b/a;
        if( c !=0 ) w = d/c;
        h_ratioAC->SetBinContent(i,z);
        h_ratioCA->SetBinContent(i,w);
        if( w != 0) answer = z/w;
        if(b != 0){
        std::cout << "a= " << a << std::endl;
        std::cout << "b= " << b << std::endl;
        std::cout << "c= " << c << std::endl;
        std::cout << "d= " << d << std::endl;
        std::cout << "z= " << z << std::endl;
        std::cout << "w= " << w << std::endl;
        std::cout << "answer = " << answer << std::endl;
        h_ratioratio->SetBinContent(i,answer);
        x.push_back(i);
        y.push_back(answer);
        }
    }

    Double_t* xpointer=&(x.at(0));
    Double_t* ypointer=&(y.at(0));
    TGraph* tg=new TGraph(x.size(),xpointer,ypointer);
    tg->SetMarkerStyle(20);
    tg->SetMarkerColor(kRed);
    tg->SetMarkerSize(0.5);
    TCanvas *c0 = new TCanvas("c0","c0",700,500);
    tg->Draw("AP");

    TCanvas *c1 = new TCanvas("c1", "c1");
    h_ratioratio->GetYaxis()->SetRangeUser(0.7,1.3);
    h_ratioratio->Draw("P");
    h_ratioratio->SetLineColor(3); //5
    h_ratioratio->SetMarkerColor(2);
    h_ratioratio->SetMarkerStyle(21);
    h_ratioratio->SetMarkerSize(0.3);


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

