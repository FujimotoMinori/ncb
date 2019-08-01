void getmeandiff() {
    // Change some default parameters in the current style
    gStyle->SetLabelSize(0.06,"x");
    gStyle->SetLabelSize(0.06,"y");
    gStyle->SetFrameFillColor(0);//38
    gStyle->SetTitleW(0.6);
    gStyle->SetTitleH(0.1);

    string finname = "../data/merged_18_0626.hist.root";
    //file open
    TFile* fin = TFile::Open(finname.c_str(), "READ");
    if (!fin) {
        cout << " input file:" << finname.c_str() << " does not exist"<< endl;
        return;
    }
    cout << " input data file:" << finname.c_str() << " open..." << endl;
    //get histograms
    TH2F *hpxpy = (TH2F*)fin->Get("nHitsA_beam1_woSmallHits"); 
    TH2F *hpxpyC = (TH2F*)fin->Get("nHitsC_beam1_woSmallHits"); 

    TH2F *hpxpy2 = (TH2F*)fin->Get("nHitsA_beam2_woSmallHits"); 
    TH2F *hpxpyC2 = (TH2F*)fin->Get("nHitsC_beam2_woSmallHits"); 

    // Create a canvas and divide it
    TCanvas *c1 = new TCanvas("c1","c1",700,500);
    c1->SetFillColor(0);//42
    c1->Divide(2,1);
    TPad *leftPad = (TPad*)c1->cd(1);;
    leftPad->Divide(1,2);
    // Draw 2-d original histogram
    leftPad->cd(1);
    gPad->SetTopMargin(0.12);
    gPad->SetFillColor(0);//33
    gPad->SetLogz();
    hpxpy->SetStats(0);
    hpxpy->Draw("colz");
    hpxpy->GetXaxis()->SetLabelSize(0.06);
    hpxpy->GetYaxis()->SetLabelSize(0.06);
    hpxpy->SetMarkerColor(kYellow);
    // Show fitted "mean" for each slice
    leftPad->cd(2);
    gPad->SetFillColor(0);
    int j = 0;

    TH1F *h_mean = new TH1F("h_mean", "; Run Number; mean", 16340, 348150.5, 364490.5);
    TH1F *h_meanmean = new TH1F("h_meanmean", "; Run Number; mean", 100, 0, 1000);
    vector<Double_t> x,y,xe,ye;
    vector<Double_t> xc,yc,xec,yec;
    vector<Double_t> xd,yd,xed,yed;
    const int n = hpxpy->GetNbinsX()+1;
    float bi = 0;
    for (int i=0; i< n; i++){
        bi = i + 348150.0;   
        TH1D *pj = hpxpy->ProjectionY("projectiony",i,i);
        TH1D *pjc = hpxpyC->ProjectionY("projectionyC",i,i);
        TH1D *pj2 = hpxpy2->ProjectionY("projectiony2",i,i);
        TH1D *pjc2 = hpxpyC2->ProjectionY("projectionyC2",i,i);
        int num = 0;
        double meanAC = 0.;
        double meanCA = 0.;
        double errorAC = 0.;
        double errorCA = 0.;
        num = pj->GetBinContent(i);
        if(pj->GetMean() != 0.0) {
            h_mean->SetBinContent(i,pj->GetMean());
            x.push_back(bi);
            xc.push_back(bi);
            xd.push_back(bi);
            y.push_back(pj->GetMean());
            yc.push_back(pjc->GetMean());
            meanAC = pj->GetMean() + pjc->GetMean();
            meanCA = pj2->GetMean() + pjc2->GetMean();
            errorAC = pow(pj->GetMeanError(),2) + pow(pjc->GetMeanError(),2);
            errorCA = pow(pj2->GetMeanError(),2) + pow(pjc2->GetMeanError(),2);
            yd.push_back((meanAC-meanCA)/(meanAC+meanCA));
            xe.push_back(0.);
            xec.push_back(0.);
            xed.push_back(0.);
            ye.push_back(pj->GetMeanError());
            yec.push_back(pjc->GetMeanError());
            //std::cout << "errorAC= " << errorAC << std::endl;
            //std::cout << "errorCA= " << errorCA << std::endl;
            //std::cout << "error= " << sqrt(errorAC+errorCA) << std::endl;
            yed.push_back(sqrt(errorAC+errorCA));
            h_meanmean->Fill(pj->GetMean());
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
    Double_t* xpointerd=&(xd.at(0));
    Double_t* ypointerd=&(yd.at(0));
    Double_t* xepointerd=&(xed.at(0));
    Double_t* yepointerd=&(yed.at(0));
    TGraphErrors* tg=new TGraphErrors(x.size(),xpointer,ypointer,xepointer,yepointer);
    TGraphErrors* tgc=new TGraphErrors(xc.size(),xpointerc,ypointerc,xepointerc,yepointerc);
    TGraphErrors* tgd=new TGraphErrors(xd.size(),xpointerd,ypointerd,xepointerd,yepointerd);
    tg->SetMarkerStyle(20);
    tg->SetMarkerColor(kRed);
    tg->SetMarkerSize(0.5);
    tg->GetYaxis()->SetRangeUser(420,720);
    tgc->SetMarkerStyle(20);
    tgc->SetMarkerColor(kRed);
    tgc->SetMarkerSize(0.5);
    tgc->GetYaxis()->SetRangeUser(420,720);
    tgd->SetMarkerStyle(20);
    tgd->SetMarkerColor(kRed);
    tgd->SetMarkerSize(0.5);
    tgd->GetYaxis()->SetRangeUser(-50,50);
    gStyle->SetPadGridY(1);
    tg->SetTitle(";RunNumber;mean of NHits");
    tg->GetXaxis()->SetLabelSize(0.03);
    tg->GetYaxis()->SetLabelSize(0.03);
    tgc->SetTitle(";RunNumber;mean of NHits");
    tgc->GetXaxis()->SetLabelSize(0.03);
    tgc->GetYaxis()->SetLabelSize(0.03);
    tgd->SetTitle(";RunNumber;diff of mean of NHits");
    tgd->GetXaxis()->SetLabelSize(0.03);
    tgd->GetYaxis()->SetLabelSize(0.03);

    h_mean->GetYaxis()->SetRangeUser(420,720); //420,720
    h_mean->Draw("P");
    TPad *rightPad = (TPad*)c1->cd(2);
    rightPad->Divide(1,2);
    rightPad->cd(1);
    gPad->SetTopMargin(0.12);
    gPad->SetLeftMargin(0.15);
    gPad->SetFillColor(0);
    //TH2F *hpxpy_1 = (TH2F*)fin->Get("zasym_AC_1");
    //hpxpy_1->GetYaxis()->SetRangeUser(-1.0,1.0);
    //hpxpy_1->Draw();
    h_meanmean->Draw();
    // Show fitted "sigma" for each slice
    rightPad->cd(2);
    gPad->SetTopMargin(0.12);
    gPad->SetLeftMargin(0.15);
    gPad->SetFillColor(0);//33
    gPad->SetLogy();
    int first = 7501; //7501,13546
    int last = 7501;
    TH1D *proj = hpxpy->ProjectionY("projectiony",first,last);
    proj->Draw("e");
    float error = 0;
    proj->GetMeanError(first);
    //std::cout << "error= " << error << std::endl;

    //attributes
    h_mean->SetLineColor(3); //5
    h_mean->SetMarkerColor(2);
    h_mean->SetMarkerStyle(21);
    h_mean->SetMarkerSize(0.3);

    TCanvas *c0 = new TCanvas("c0","c0",700,500);
    tg->Draw("AP");
    //c0->Print("testA.pdf");
    TCanvas *c4 = new TCanvas("c4","c4",700,500);
    tgc->Draw("AP");
    //c4->Print("testC.pdf");
    TCanvas *c5 = new TCanvas("c5","c5",700,500);
    tgd->Draw("AP");
    //c5->Print("testdiff.pdf");
}
