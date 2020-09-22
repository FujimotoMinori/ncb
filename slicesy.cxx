void slicesy() {
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
    //TH1F *h_meanmean = new TH1F("h_meanmean", "; ; mean", 100, -0.5, 0.5);
    //get histograms
    TH2F *hpxpy = (TH2F*)fin->Get("zasym_AC"); 
    int first = 13588;
    int last = 13588;
    TH1D *proj = hpxpy->ProjectionY("projectiony",first,last);

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
    hpxpy->Draw("colz");
    hpxpy->GetXaxis()->SetLabelSize(0.06);
    hpxpy->GetYaxis()->SetLabelSize(0.06);
    hpxpy->SetMarkerColor(kYellow);

     




    
    hpxpy->FitSlicesY();
    // Show fitted "mean" for each slice
    leftPad->cd(2);
    gPad->SetFillColor(0);
    TH2F *hpxpy_0 = (TH2F*)fin->Get("zasym_AC_2");
    hpxpy_0->GetYaxis()->SetRangeUser(0.,0.3);
    hpxpy_0->Draw();
    TPad *rightPad = (TPad*)c1->cd(2);
    rightPad->Divide(1,2);
    rightPad->cd(1);
    gPad->SetTopMargin(0.12);
    gPad->SetLeftMargin(0.15);
    gPad->SetFillColor(0);
    TH2F *hpxpy_1 = (TH2F*)fin->Get("zasym_AC_1");
    hpxpy_1->GetYaxis()->SetRangeUser(0.,0.3);
    hpxpy_1->Draw();
    // Show fitted "sigma" for each slice
    rightPad->cd(2);
    gPad->SetTopMargin(0.12);
    gPad->SetLeftMargin(0.15);
    gPad->SetFillColor(0);//33
    //TH2F *hpxpy_2 = (TH2F*)fin->Get("zasym_CA_2");
    //hpxpy_2->SetMinimum(0.8);
    //hpxpy_2->Draw();
    double start,end;
    double mean,rms;
    mean = proj->GetMean();
    rms = proj->GetRMS();
    start = mean-rms;
    end = mean+rms;
    std::cout << "mean = " << mean << std::endl;
    std::cout << "rms = " << rms << std::endl;
    TF1 * f1 = new TF1("func","gaus");
    proj->SetStats(0);
    //proj->Fit("func","","",start,end);
    std::cout << "meanfitted = " << f1->GetParameter(1) << std::endl;
    proj->Draw();
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
}
