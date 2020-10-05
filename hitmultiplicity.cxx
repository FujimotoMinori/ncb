int hitmultiplicity(){
    //string finname = "../data/output17.root";
    string finname = "../data/merged_17_4.root";
    //string finname = "../data/merged_18_1003_2.root";

    //file open
    TFile* fin = TFile::Open(finname.c_str(), "READ");
    if (!fin) {
        cout << " input file:" << finname.c_str() << " does not exist"<< endl;
        return 0 ;
    }

    //get histograms
    TH2F *hitACA = (TH2F*)fin->Get("nHitsA_beam1_woSmallHits"); 
    TH2F *hitACC = (TH2F*)fin->Get("nHitsC_beam1_woSmallHits"); 
    TH2F *hitCAA = (TH2F*)fin->Get("nHitsA_beam2_woSmallHits"); 
    TH2F *hitCAC = (TH2F*)fin->Get("nHitsC_beam2_woSmallHits"); 
    TH1F *triggerAC = (TH1F*)fin->Get("eventsACwoPV"); 
    TH1F *triggerCA = (TH1F*)fin->Get("eventsCAwoPV"); 

    double firstrun = 324310;  //17
    //double firstrun = 348150; 
    //calc multiplicity
    vector<Double_t> x,y,xe,ye;
    vector<Double_t> x2,y2,xe2,ye2;
    const int n = triggerAC->GetNbinsX()+1;
    cout << "number of entries= " << n << endl; 
    for (int i=0;i<n;i++){
        int nTrig = 0;
        int nhitAC = 0;
        int nhitCA = 0;
        int nhitACe = 0;
        int nhitCAe = 0;
        nTrig = triggerAC->GetBinContent(i);
        nhitAC = hitACA->ProjectionY("projXACA",i,i)->GetMean()
                +hitACC->ProjectionY("projXACC",i,i)->GetMean();
        nhitACe = TMath::Sqrt(TMath::Power(hitACA->ProjectionY("projXACA",i,i)->GetMeanError(),2)
                      +TMath::Power(hitACC->ProjectionY("projXACC",i,i)->GetMeanError(),2));
        nhitCA = hitCAA->ProjectionY("projXCAA",i,i)->GetMean()
                +hitCAC->ProjectionY("projXCAC",i,i)->GetMean();
        nhitCAe = TMath::Sqrt(TMath::Power(hitCAA->ProjectionY("projXACA",i,i)->GetMeanError(),2)
                      +TMath::Power(hitCAC->ProjectionY("projXACC",i,i)->GetMeanError(),2));
        if ( nhitAC>1){
            x.push_back(firstrun+i);
            y.push_back(nhitAC);
            xe.push_back(0.);
            ye.push_back(nhitACe);
            x2.push_back(firstrun+i);
            y2.push_back(nhitCA);
            xe2.push_back(0.);
            ye2.push_back(nhitCAe);
        }

    }

    Double_t* xpointer=&(x.at(0));
    Double_t* ypointer=&(y.at(0));
    Double_t* xepointer=&(xe.at(0));
    Double_t* yepointer=&(ye.at(0));
    Double_t* xpointer2=&(x2.at(0));
    Double_t* ypointer2=&(y2.at(0));
    Double_t* xepointer2=&(xe2.at(0));
    Double_t* yepointer2=&(ye2.at(0));

    Double_t xlo = 0.+firstrun;    // x の下限
    Double_t xhi = n+firstrun;   // x の上限
    Double_t ylo = 0.;    // y の下限
    Double_t yhi = 2500.;   // y の上限
    TCanvas *c1 = new TCanvas("c1","c1",700,500);
    TH1F *frame = gPad->DrawFrame(xlo,ylo,xhi,yhi);

    TGraphErrors* tg=new TGraphErrors(x.size(),xpointer,ypointer,xepointer,yepointer);
    //tg->GetYaxis()->SetRangeUser(0,3000);
    tg->SetMarkerStyle(8);
    tg->SetMarkerColor(kBlue);
    tg->SetLineColor(kBlue);
    tg->SetMarkerSize(0.35);
    tg->SetTitle("average pixel cluster hits;LB;average pixel cluster hits");
    tg->GetXaxis()->SetLabelSize(0.03);
    tg->GetYaxis()->SetLabelSize(0.03);

    TGraphErrors* tg2=new TGraphErrors(x2.size(),xpointer2,ypointer2,xepointer2,yepointer2);
    //tg2->GetYaxis()->SetRangeUser(0,3000);
    tg2->SetMarkerStyle(8);
    tg2->SetMarkerColor(kRed);
    tg2->SetLineColor(kRed);
    tg2->SetMarkerSize(0.35);
    tg2->SetTitle("average pixel cluster hits;LB;average pixel cluster hits");
    tg2->GetXaxis()->SetLabelSize(0.03);
    tg2->GetYaxis()->SetLabelSize(0.03);

    tg->Draw("P");
    tg2->Draw("P");
    frame->SetTitle(";Run Number;average hit multiplicity in pixel EndCaps");
    frame->GetYaxis()->SetTitleOffset(1.2);

    TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
    leg->AddEntry(tg,"Beam AC ","lep");
    leg->AddEntry(tg2,"Beam CA","lep");
    leg->SetBorderSize(0); 
    leg->SetFillStyle(0); 
    leg->Draw();

    return 0;
}
