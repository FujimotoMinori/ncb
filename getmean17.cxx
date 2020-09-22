void getmean17() {
    // Change some default parameters in the current style
    gStyle->SetLabelSize(0.045,"x");
    gStyle->SetLabelSize(0.045,"y");
    gStyle->SetFrameFillColor(0);//38
    gStyle->SetTitleW(0.5);
    gStyle->SetTitleH(0.08);
    gStyle->SetTitleOffset(1.3,"x");
    gStyle->SetTitleOffset(1.3,"y");

    string finname = "../data/merged_17_3.hist.root";
    //file open
    TFile* fin = TFile::Open(finname.c_str(), "READ");
    if (!fin) {
        cout << " input file:" << finname.c_str() << " does not exist"<< endl;
        return;
    }
    cout << " input data file:" << finname.c_str() << " open..." << endl;

    //get histograms
    TH2F *hpxpy = (TH2F*)fin->Get("nHitsA_beam1"); 
    TH2F *hpxpyC = (TH2F*)fin->Get("nHitsC_beam1"); 

    // Create a canvas and divide it
    TCanvas *c1 = new TCanvas("c1","c1",700,500);
    c1->SetFillColor(0);//42
    //c1->Divide(2,1);
    //TPad *leftPad = (TPad*)c1->cd(1);;
    //leftPad->Divide(1,2);
    // Draw 2-d original histogram
    //leftPad->cd(1);
    gPad->SetTopMargin(0.12);
    gPad->SetFillColor(0);//33
    gPad->SetLogz();
    gPad->SetRightMargin(0.15);
    hpxpy->SetStats(0);
    hpxpy->Draw("colz");
    hpxpy->GetXaxis()->SetLabelSize(0.045);
    hpxpy->GetYaxis()->SetLabelSize(0.045);
    hpxpy->GetYaxis()->SetTitle("Nhits");
    hpxpy->GetZaxis()->SetTitleOffset(-1.1);
    hpxpy->GetYaxis()->SetTitleOffset(1.3);
    hpxpy->GetZaxis()->SetTitle("Events");
    hpxpy->GetZaxis()->SetTitleSize(0.04);
    hpxpy->GetYaxis()->SetTitleSize(0.04);
    hpxpy->GetYaxis()->SetRangeUser(0.,5000);//5000
    hpxpy->GetZaxis()->SetRangeUser(0.,1000);
    hpxpy->SetMarkerColor(kYellow);
    // Show fitted "mean" for each slice
    //leftPad->cd(2);
    //gPad->SetFillColor(0);
    //TCanvas *c9 = new TCanvas("c9","c9",700,500);
    //hpxpy->Draw("colz");
    

    TH1F *h_mean = new TH1F("h_mean", "; Run Number; mean", 17345, 324310.5, 341655.5);
    TH1F *h_meanmean = new TH1F("h_meanmean", "; Run Number; mean", 100, 0, 1000);
    vector<Double_t> x,y,xe,ye;
    vector<Double_t> xc,yc,xec,yec;
    const int n = hpxpy->GetNbinsX()+1;
    float bi = 0;

    TH1D *pjone = hpxpy->ProjectionY("projectiony",13540,13540);

    float sigma2 = 0.;
    float sigma2x = 0.;
    float mean = 0.;
    float sigma = 0.;
    for (int i=0; i< n; i++){
        float meanx = 0.;
        float sigmax = 0.;
        bi = i + 324310.0;   
        TH1D *pj = hpxpy->ProjectionY("projectiony",i,i);
        TH1D *pjc = hpxpyC->ProjectionY("projectionyC",i,i);
        int num = 0;
        num = pj->GetBinContent(i);
        if(pj->GetMean() != 0.0) {
            if(pj->GetMean() <= 0.5) continue;
            if(pjc->GetMean() <= 0.5) continue;
            h_mean->SetBinContent(i,pj->GetMean());
            //if(pj->GetEntries() == 21328) {
            //    cout << "bingo " << i << endl;
            //}
            x.push_back(bi);
            xc.push_back(bi);
            y.push_back(pj->GetMean());
            yc.push_back(pjc->GetMean());
            xe.push_back(0.);
            xec.push_back(0.);
            ye.push_back(pj->GetMeanError());
            yec.push_back(pjc->GetMeanError());
            h_meanmean->Fill(pj->GetMean());
            meanx = pj->GetMean();
            sigmax = pj->GetMeanError();
            sigma2 += 1/(sigmax*sigmax);
            sigma2x += meanx/(sigmax*sigmax);
        }
    }
    mean = sigma2x/sigma2;
    sigma = sqrt(1/sigma2); 
    cout << "mean = " << mean <<endl;
    cout << "sigma = " << sigma <<endl;

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
    tg->GetYaxis()->SetRangeUser(0,720);//420,720
    tgc->SetMarkerStyle(20);
    tgc->SetMarkerColor(kRed);
    tgc->SetMarkerSize(0.5);
    tgc->GetYaxis()->SetRangeUser(0,720);//420,720
    gStyle->SetPadGridY(1);
    tg->SetTitle(";RunNumber;mean of NHits");
    tg->GetXaxis()->SetLabelSize(0.045);
    tg->GetYaxis()->SetLabelSize(0.045);
    tgc->SetTitle(";RunNumber;mean of NHits");
    tgc->GetXaxis()->SetLabelSize(0.045);
    tgc->GetYaxis()->SetLabelSize(0.045);
    //tg->Fit("pol1","","",348494,364293);
    //tgc->Fit("pol1","","",348494,364293);

    /*
    h_mean->GetYaxis()->SetRangeUser(420,720); //420,720
    h_mean->SetStats(0);
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
    int first = 3973; //3973,7501,13546
    int last = 3973;
    TH1D *proj = hpxpy->ProjectionY("projectiony",first,last);
    TH1D *projc = hpxpyC->ProjectionY("projectiony",first,last);
    proj->GetXaxis()->SetRangeUser(0,500);
    proj->GetXaxis()->SetTitle("Nhits");
    proj->GetYaxis()->SetTitle("Events");
    proj->GetXaxis()->SetLabelSize(0.045);
    proj->GetYaxis()->SetLabelSize(0.045);
    proj->GetXaxis()->SetTitleSize(0.043);
    proj->GetYaxis()->SetTitleSize(0.043);
    proj->GetYaxis()->SetTitleOffset(1.1);
    gPad->SetLogy();
    gPad->SetLeftMargin(0.12);
    gStyle->SetPadGridY(1);
    float error = 0;
    proj->GetMeanError(first);
    //std::cout << "error= " << error << std::endl;

    //attributes
    h_mean->SetLineColor(3); //5
    h_mean->SetMarkerColor(2);
    h_mean->SetMarkerStyle(21);
    h_mean->SetMarkerSize(0.3);
    */

    TCanvas *c0 = new TCanvas("c0","c0",700,500);
    tg->Draw("AP");
    //c0->Print("testA.pdf");
    TCanvas *c4 = new TCanvas("c4","c4",700,500);
    tgc->Draw("AP");
    //c4->Print("testC.pdf");
    //TCanvas *c6 = new TCanvas("c6","c6",700,500);
    //proj->SetLineColor(3);
    //projc->SetLineColor(2);
    //projc->Draw();
    //proj->Draw("sames");
    //TCanvas *c7 = new TCanvas("c7","c7",700,500);
    //hpxpy->Draw("colz");
}
