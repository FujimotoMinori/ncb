void fitprojectiony() {
    // Change some default parameters in the current style
    gStyle->SetLabelSize(0.06,"x");
    gStyle->SetLabelSize(0.06,"y");
    gStyle->SetFrameFillColor(0);//38
    gStyle->SetTitleW(0.6);
    gStyle->SetTitleH(0.1);

    string finname = "../data/merged18_re.hist.root";
    //file open
    TFile* fin = TFile::Open(finname.c_str(), "READ");
    if (!fin) {
        cout << " input file:" << finname.c_str() << " does not exist"<< endl;
        return;
    }
    cout << " input data file:" << finname.c_str() << " open..." << endl;
    //get histograms
    TH2F *hpxpy = (TH2F*)fin->Get("zasym_AC"); 
    TH1F *h_mean = new TH1F("h_mean", "; Run Number; mean", 16340, 348150.5, 364490.5);
    const int n = hpxpy->GetNbinsX()+1;
        std::cout << "n=" << n << std::endl;
    for (int i=0; i< n; i++){
        TH1D *pj = hpxpy->ProjectionY("projectiony",i,i);
        int num = 0;
        double mean = 0.;
        double sigma = 0.;
        double getmean = 0.;
        int first,last;
        mean = pj->GetMean();
        //std::cout << "mean1=" << mean << std::endl;
        //std::cout << "sigma=" << sigma << std::endl;
        sigma = pj->GetRMS();
        if(mean != 0.0) {
                std::cout << "mean1=" << mean << std::endl;
                first = mean-sigma; 
                last = mean+sigma; 
                TF1 * f1 = new TF1("func","gaus");
                pj->Fit("func","","",first,last);
                getmean = f1->GetParameter(1);
                std::cout << "mean=" << getmean << std::endl;
                if (getmean != 0.0)  h_mean->SetBinContent(i,getmean);
        }
    }

    // Create a canvas and divide it
    TCanvas *c1 = new TCanvas("c1","c1",700,500);
    c1->SetFillColor(0);//42
    c1->Divide(2,1);
    TPad *leftPad = (TPad*)c1->cd(1);;
    leftPad->Divide(1,2);
    // Draw 2-d original histogram
    leftPad->cd(1); //first canvas
    gPad->SetTopMargin(0.12);
    gPad->SetFillColor(0);//33
    gPad->SetLogz();
    hpxpy->Draw("colz");
    hpxpy->GetXaxis()->SetLabelSize(0.06);
    hpxpy->GetYaxis()->SetLabelSize(0.06);
    hpxpy->SetMarkerColor(kYellow);
    // Fit slices projected along Y fron bins in X [7,32] with more than 20 bins  in Y filled
    //hpxpy->FitSlicesY(0,7,32,20);
    hpxpy->FitSlicesY();

    // Show fitted "mean" for each slice
    leftPad->cd(2); //secondcanvas
    gPad->SetFillColor(0);
    TH2F *hpxpy_0 = (TH2F*)fin->Get("zasym_AC_0");
    hpxpy_0->Draw();

    TPad *rightPad = (TPad*)c1->cd(2);
    rightPad->Divide(1,2);
    rightPad->cd(1); //third canvas
    gPad->SetTopMargin(0.12);
    gPad->SetLeftMargin(0.15);
    gPad->SetFillColor(0);
    TH2F *hpxpy_1 = (TH2F*)fin->Get("zasym_AC_1");
    hpxpy_1->GetYaxis()->SetRangeUser(-0.3,0.0);
    hpxpy_1->Draw();

    // Show fitted "sigma" for each slice
    rightPad->cd(2); //forth canvas
    gPad->SetTopMargin(0.12);
    gPad->SetLeftMargin(0.15);
    gPad->SetFillColor(0);//33
    //TH2F *hpxpy_2 = (TH2F*)fin->Get("zasym_AC_2");
    //hpxpy_2->SetMinimum(0.8);
    //hpxpy_2->Draw();

    //project in y axis and get each means
    //int first = 3972;
    //int last = 3973;
    //TH1D *proj = hpxpy_1->ProjectionY("projectiony",first,last);
    //TF1 * f1 = new TF1("func","gaus",-1.,1.);
    //proj->SetStats(0);
    //proj->Fit("func");
    //proj->Draw();
    h_mean->GetYaxis()->SetRangeUser(-0.3,0.0);
    h_mean->Draw("P");

    //attributes
    hpxpy_0->SetLineColor(1); //5
    hpxpy_1->SetLineColor(1);
    //hpxpy_2->SetLineColor(1);
    hpxpy_0->SetMarkerColor(2);
    hpxpy_1->SetMarkerColor(2);
    //hpxpy_2->SetMarkerColor(2);
    hpxpy_0->SetMarkerStyle(21);
    hpxpy_1->SetMarkerStyle(21);
    //hpxpy_2->SetMarkerStyle(21);
    hpxpy_0->SetMarkerSize(0.3);
    hpxpy_1->SetMarkerSize(0.3);
    //hpxpy_2->SetMarkerSize(0.3);
    h_mean->SetLineColor(1);
    h_mean->SetMarkerColor(2);
    h_mean->SetMarkerStyle(21);
    h_mean->SetMarkerSize(0.3);
}
