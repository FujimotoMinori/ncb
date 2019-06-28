#include "TMath.h"
using namespace std;

void calcasym() {

    float a,c = 0.;
    float zasym = -5.0;

    float orga = 648;
    float orgc = 480;
    float goala = 650;
    float goalc = 500;
    int n = 50;
    float da = (goala-orga)/n;
    float dc = (goalc-orgc)/n;

    vector<Double_t> x,y;

    for(int i =0;i<n;i++){
        a = orga+da*i;
        c = orgc+dc*i;
        cout << "a= " << a << endl;
        cout << "c= " << c << endl;

        if((a+c) != 0) zasym = (a-c)/(a+c);
        cout << "asym= " << zasym << endl;
        x.push_back(i);
        y.push_back(abs(zasym));
    }

    Double_t* xpointer=&(x.at(0));
    Double_t* ypointer=&(y.at(0));
    TGraph* tg=new TGraph(x.size(),xpointer,ypointer);
    tg->SetMarkerStyle(20);
    tg->SetMarkerColor(kRed);
    tg->SetMarkerSize(0.5);
    tg->GetYaxis()->SetRangeUser(0.,0.3);
    TCanvas *c0 = new TCanvas("c0","c0",700,500);
    tg->Draw("AP");

    //draw histogram
    //TCanvas *c1 = new TCanvas("c1", "c1");
    //h1->GetYaxis()->SetRangeUser(0,2800);
    //h1->SetTitle("NPixels");
    //h1->GetXaxis()->SetTitle("NPixels");
    //draw histogram
    //h1->Draw();
    
    //c1->SaveAs("mHist_BCMUItrigwoPV.pdf");

    return;

}

