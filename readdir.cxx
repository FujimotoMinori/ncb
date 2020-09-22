#include <stdio.h>

void readdir() {
    // Change some default parameters in the current style
    gStyle->SetLabelSize(0.045,"x");
    gStyle->SetLabelSize(0.045,"y");
    gStyle->SetFrameFillColor(0);//38
    gStyle->SetTitleW(0.5);
    gStyle->SetTitleH(0.08);

    string finname = "../data/NoiseMap_00352123_calibration_PixelNoise_daq_190808_1226.root";
    //file open
    TFile* fin = TFile::Open(finname.c_str(), "READ");
    if (!fin) {
        cout << " input file:" << finname.c_str() << " does not exist"<< endl;
        return;
    }
    cout << " input data file:" << finname.c_str() << " open..." << endl;

    //move to the directory?
    TDirectory *all = (TDirectory*)fin->Get("All");
    TDirectory *occupancyLB = (TDirectory*)all->Get("OccupancyLb");
    float totalhit = 0.; 
    TCanvas c1;
    c1.Print("hsimple.ps[");
    float npixels = 2211840.; //number of pixels in sigle Disk
    float meantotal = 0;
    int alln = 0;
    for(int i = 1;i<4;i++){
        cout << "i= " << i << endl;
        TDirectory *Disk = (TDirectory*)occupancyLB->Get(Form("Disk%dC",i));
        TIter next(Disk->GetListOfKeys());
        TKey *key;

        float integral = 0.;
        float totalintegral = 0.; 
        int n = 0;
        int nbins = 0;

        while ((key = (TKey*)next())) {
            TClass *cl = gROOT->GetClass(key->GetClassName());
            if (!cl->InheritsFrom("TH1")) continue;
            TH1 *h = (TH1*)key->ReadObj();

            nbins = h->GetNbinsX();
            int realbins = 0;
            float sum = 0;
            float mean = 0;
            for (int i = 0;i < nbins;i++){
                if (h->GetBinContent(i) != 0 ){
                    realbins++;
                    sum += h->GetBinContent(i);
                }
            }
            if (realbins != 0 ) mean = sum/realbins;
            cout << "mean=" << mean << endl;
            meantotal += mean;
            cout << "meantotal=" << meantotal << endl;
            integral = h->Integral();
            totalintegral += integral;
            std::cout << "integral = " << integral << std::endl;
            if (integral != 0.) n++;
            alln++;
            std::cout << "totalintegral = " << totalintegral << std::endl;
            h->Draw();
            c1.Print("hsimple.ps");
        }
        cout << "n= " << n << endl;
        cout << "alln= " << alln << endl;
        totalintegral = totalintegral/n;
        totalhit += totalintegral*npixels;
        std::cout << "totalhits = " << totalhit << std::endl;
    }
    std::cout << "totalhitsall = " << totalhit << std::endl;
    std::cout << "totalmean = " << meantotal/alln << std::endl;
    std::cout << "totalmeanperevent = " << (meantotal/alln)*npixels << std::endl;
    c1.Print("hsimple.ps]");

    //get histograms
    /*
    TH2F *hpxpy = (TH2F*)fin->Get("nHitsA_beam1"); 
    TH2F *hpxpyC = (TH2F*)fin->Get("nHitsC_beam1"); 
    hpxpy->SetStats(0);
    hpxpy->GetYaxis()->SetRangeUser(0.,300);//5000
    hpxpyC->GetYaxis()->SetRangeUser(0.,300);//5000
    */

    /*
    vector<Double_t> x,y,xe,ye;
    vector<Double_t> xc,yc,xec,yec;
    vector<Double_t> ratiox,ratioy,ratioxe,ratioye;
    const int n = hpxpy->GetNbinsX()+1;
    int bi = 0;

    float sigma2 = 0.;
    float sigma2x = 0.;
    float mean = 0.;
    float sigma = 0.;
    float integralbig = 0.;
    float integralsmall = 0.;
    float integralbin = 0.;
    float ratiointeg = 500.;
    TCanvas *c1 = new TCanvas("c1","c1",700,500);
    TKey *key = 0;
    const char* str = "beam1.pdf";
    c1->Print(Form("%s(",str));
    c1->SetLogy();
    for (int i=0; i< n; i++){
        float meanx = 0.;
        float sigmax = 0.;
        bi = i + 348150.0;   
        TH1D *pj = hpxpy->ProjectionY(Form("ECA[%d]",bi),i,i);
        pj->GetXaxis()->SetTitle("Nhits(Number of clusters)");
        TH1D *pjc = hpxpyC->ProjectionY(Form("ECC[%d]",bi),i,i);
        pjc->GetXaxis()->SetTitle("Nhits(Number of clusters)");
        pjc->GetYaxis()->SetTitle("Events");
        int num = 0;
        num = pj->GetBinContent(i);

        if(pj->GetMean() != 0.0) {
            pjc->Draw();
            c1->Print(str);
            c1->Clear();

            integralbig = pj->Integral(51,5000);
            integralsmall = pj->Integral(2,50);
            integralbin = pj->Integral(1,1);
            //if(bi == 360348) cout << integralbin << endl;

            if(integralbig != 0) ratiointeg = integralsmall/integralbig;
            if(ratiointeg <  0.1 ) cout << bi << endl;
            //cout << ratiointeg << endl;
            x.push_back(bi);
            xc.push_back(bi);
            y.push_back(pj->GetMean());
            yc.push_back(pjc->GetMean());
            xe.push_back(0.);
            xec.push_back(0.);
            ye.push_back(pj->GetMeanError());
            yec.push_back(pjc->GetMeanError());

            ratiox.push_back(bi);
            ratioy.push_back(ratiointeg);
            ratioxe.push_back(0.);
            ratioye.push_back(0.);

            meanx = pj->GetMean();
            sigmax = pj->GetMeanError();
            sigma2 += 1/(sigmax*sigmax);
            sigma2x += meanx/(sigmax*sigmax);
        }
    }

    c1->Print(Form("%s)",str)); //ページの最後に白紙を追加
    c1->Close();

    mean = sigma2x/sigma2;
    sigma = sqrt(1/sigma2); 
    //cout << "mean = " << mean <<endl;
    //cout << "sigma = " << sigma <<endl;

    Double_t* xpointer=&(x.at(0));
    Double_t* ypointer=&(y.at(0));
    Double_t* xepointer=&(xe.at(0));
    Double_t* yepointer=&(ye.at(0));
    Double_t* xpointerc=&(xc.at(0));
    Double_t* ypointerc=&(yc.at(0));
    Double_t* xepointerc=&(xec.at(0));
    Double_t* yepointerc=&(yec.at(0));
    Double_t* ratioxpointer=&(ratiox.at(0));
    Double_t* ratioypointer=&(ratioy.at(0));
    Double_t* ratioxepointer=&(ratioxe.at(0));
    Double_t* ratioyepointer=&(ratioye.at(0));
    TGraphErrors* tg=new TGraphErrors(x.size(),xpointer,ypointer,xepointer,yepointer);
    TGraphErrors* tgc=new TGraphErrors(xc.size(),xpointerc,ypointerc,xepointerc,yepointerc);
    TGraphErrors* tratio=new TGraphErrors(ratiox.size(),ratioxpointer,ratioypointer,ratioxepointer,ratioyepointer);

    tg->SetMarkerStyle(20);
    tg->SetMarkerColor(kRed);
    tg->SetMarkerSize(0.5);
    tg->GetYaxis()->SetRangeUser(0,720);
    tg->SetTitle(";RunNumber;mean of NHits");
    tg->GetXaxis()->SetLabelSize(0.045);
    tg->GetYaxis()->SetLabelSize(0.045);
    gStyle->SetPadGridY(1);

    tgc->SetMarkerStyle(20);
    tgc->SetMarkerColor(kRed);
    tgc->SetMarkerSize(0.5);
    tgc->GetYaxis()->SetRangeUser(0,720); //420,720
    tgc->SetTitle(";RunNumber;mean of NHits");
    tgc->GetXaxis()->SetLabelSize(0.045);
    tgc->GetYaxis()->SetLabelSize(0.045);
    gStyle->SetPadGridY(1);

    tratio->SetMarkerStyle(20);
    tratio->SetMarkerColor(kRed);
    tratio->SetMarkerSize(0.5);
    tratio->GetYaxis()->SetRangeUser(0,50); 
    tratio->SetTitle(";RunNumber;#events (<=50) / #events (>50)");
    tratio->GetXaxis()->SetLabelSize(0.045);
    tratio->GetYaxis()->SetLabelSize(0.045);
    gStyle->SetPadGridY(1);
    
    int first = 352123-348150; //3973,7501,13546
    int last = 352123-348150;
    TH1D *proj = hpxpy->ProjectionY("projectiony",first,last);
    TH1D *projc = hpxpyC->ProjectionY("projectiony",first,last);
    projc->GetXaxis()->SetRangeUser(0,300);
    projc->GetXaxis()->SetTitle("Nhits");
    projc->GetYaxis()->SetTitle("Events");
    projc->GetXaxis()->SetLabelSize(0.045);
    projc->GetYaxis()->SetLabelSize(0.045);
    projc->GetXaxis()->SetTitleSize(0.043);
    projc->GetYaxis()->SetTitleSize(0.043);
    projc->GetYaxis()->SetTitleOffset(1.1);
    projc->SetStats(0);
    TCanvas *c6 = new TCanvas("c6","c6",700,500);
    //c6->SetLogy();
    projc->Draw("");

    TCanvas *c3 = new TCanvas("c3","c3",700,500);
    tg->Draw("AP");
    TCanvas *c4 = new TCanvas("c4","c4",700,500);
    tgc->Draw("AP");
    TCanvas *c5 = new TCanvas("c5","c5",700,500);
    tratio->Draw("AP");
    */

    return;
}
    
