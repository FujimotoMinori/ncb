void getmeanandcompare() {
    // Change some default parameters in the current style
    gStyle->SetLabelSize(0.045,"x");
    gStyle->SetLabelSize(0.045,"y");
    gStyle->SetFrameFillColor(0);//38
    gStyle->SetTitleW(0.5);
    gStyle->SetTitleH(0.08);

    string finname = "../data/merged_18_0728.hist.root";
    //file open
    TFile* fin = TFile::Open(finname.c_str(), "READ");
    if (!fin) {
        cout << " input file:" << finname.c_str() << " does not exist"<< endl;
        return;
    }
    cout << " input data file:" << finname.c_str() << " open..." << endl;
    //get histograms
    TH2F *hall = (TH2F*)fin->Get("nHitsC_beam1"); 
    TH2F *hpxpy = (TH2F*)fin->Get("nHitsC_beam1_woSmallHits"); 
    TH2F *hpxpyC = (TH2F*)fin->Get("nHitsC_beam1_3"); 
    TH2F *hpxpyD = (TH2F*)fin->Get("nHitsC_beam1_6"); 

    // Create a canvas and divide it

    TH1F *h_mean = new TH1F("h_mean", "; Run Number; mean", 16340, 348150.5, 364490.5);
    vector<Double_t> x,y,xe,ye;
    vector<Double_t> xc,yc,xec,yec;
    const int n = hpxpy->GetNbinsX()+1;
    float bi = 0;

    for (int i=0; i< n; i++){
        bi = i + 348150.0;   
        TH1D *pj = hpxpy->ProjectionY("projectiony",i,i);
        TH1D *pjc = hpxpyC->ProjectionY("projectiony3",i,i);
        TH1D *pjd = hpxpyC->ProjectionY("projectiony6",i,i);
        int num = 0;
        num = pj->GetBinContent(i);
        if(pj->GetMean() != 0.0) {
            cout << "i = " << i << " bi = " << bi << endl;
            h_mean->SetBinContent(i,pj->GetMean());
            x.push_back(bi);
            xc.push_back(bi);
            y.push_back(pj->GetMean());
            yc.push_back(pjc->GetMean());
            xe.push_back(0.);
            xec.push_back(0.);
            ye.push_back(pj->GetMeanError());
            yec.push_back(pjc->GetMeanError());
        }
    }

    Double_t* xpointer=&(x.at(0));
    Double_t* ypointer=&(y.at(0));
    Double_t* xepointer=&(xe.at(0));
    Double_t* yepointer=&(ye.at(0));
    Double_t* xpointerc=&(xc.at(0));
    Double_t* ypointerc=&(yc.at(0));
    Double_t* xepointerc=&(xec.at(0));
    Double_t* yepointerc=&(yec.at(0));
    TGraphErrors* tg=new TGraphErrors(x.size(),xpointer,ypointer,xepointer,yepointer);
    TGraphErrors* tgc=new TGraphErrors(xc.size(),xpointerc,ypointerc,xepointerc,yepointerc);
    tg->SetMarkerStyle(20);
    tg->SetMarkerColor(kRed);
    tg->SetMarkerSize(0.5);
    tg->GetYaxis()->SetRangeUser(0,720);
    tgc->SetMarkerStyle(20);
    tgc->SetMarkerColor(kRed);
    tgc->SetMarkerSize(0.5);
    tgc->GetYaxis()->SetRangeUser(0,720);
    gStyle->SetPadGridY(1);
    tg->SetTitle(";RunNumber;mean of NHits");
    tg->GetXaxis()->SetLabelSize(0.045);
    tg->GetYaxis()->SetLabelSize(0.045);
    tgc->SetTitle(";RunNumber;mean of NHits");
    tgc->GetXaxis()->SetLabelSize(0.045);
    tgc->GetYaxis()->SetLabelSize(0.045);

    h_mean->GetYaxis()->SetRangeUser(0,720); //420,720
    h_mean->SetStats(0);

    int first = 14235; //3973,7501,13546
    int last = 14235;
    TH1D *pall = hall->ProjectionY("all",first,last);
    TH1D *proj = hpxpy->ProjectionY("woSmallhits",first,last);
    TH1D *projc = hpxpyC->ProjectionY("3hits",first,last);
    TH1D *projd = hpxpyD->ProjectionY("6hits",first,last);
    //proj->GetXaxis()->SetRangeUser(0,500);
    proj->GetXaxis()->SetTitle("Nhits");
    proj->GetYaxis()->SetTitle("Events");
    projc->GetXaxis()->SetTitle("Nhits");
    projc->GetYaxis()->SetTitle("Events");
    projd->GetXaxis()->SetTitle("Nhits");
    projd->GetYaxis()->SetTitle("Events");
    pall->GetXaxis()->SetTitle("Nhits");
    pall->GetYaxis()->SetTitle("Events");
    proj->GetXaxis()->SetLabelSize(0.045);
    projc->GetXaxis()->SetLabelSize(0.045);
    projd->GetYaxis()->SetLabelSize(0.045);
    pall->GetYaxis()->SetLabelSize(0.045);
    proj->GetXaxis()->SetTitleSize(0.043);
    projc->GetYaxis()->SetTitleSize(0.043);
    projd->GetYaxis()->SetTitleOffset(1.1);
    pall->GetYaxis()->SetTitleOffset(1.1);
    proj->GetXaxis()->SetTitleOffset(1.25);
    projc->GetXaxis()->SetTitleOffset(1.25);
    projd->GetXaxis()->SetTitleOffset(1.25);
    pall->GetXaxis()->SetTitleOffset(1.25);
    //proj->Rebin(5);
    //projc->Rebin(5);
    //projd->Rebin(5);
    //gPad->SetLogy();
    //gPad->SetLeftMargin(0.12);
    gStyle->SetPadGridY(1);
    float error = 0;

    //attributes
    h_mean->SetLineColor(3); //5
    h_mean->SetMarkerColor(2);
    h_mean->SetMarkerStyle(21);
    h_mean->SetMarkerSize(0.3);

    TCanvas *c0 = new TCanvas("c0","c0",700,500);
    tg->Draw("AP");
    TCanvas *c1 = new TCanvas("c1","c1",700,500);
    tgc->Draw("AP");
    //TCanvas *c2 = new TCanvas("c2","c2",700,500);
    //pojone->Draw();
    TCanvas *c3 = new TCanvas("c3","c3",700,500);
    pall->SetLineColor(kGreen);
    pall->Draw();
    projc->SetLineColor(kRed);
    projc->Draw("sames");
    proj->SetLineColor(kBlack);
    projd->SetLineColor(kBlue);
    proj->Draw("sames");
    projd->Draw("sames");
    c3->Update();
    TPaveStats *st0 = (TPaveStats*)pall->FindObject("stats");
    st0->SetTextColor(kGreen);
    TPaveStats *st1 = (TPaveStats*)projc->FindObject("stats");
    st1->SetTextColor(kRed);
    TPaveStats *st2 = (TPaveStats*)proj->FindObject("stats");
    st2->SetTextColor(kBlack);
    TPaveStats *st3 = (TPaveStats*)projd->FindObject("stats");
    st3->SetTextColor(kBlue);
    c3->Modified();
    //TCanvas *c4 = new TCanvas("c4","c4",700,500);
    //hpxpy->Draw("colz");
}

