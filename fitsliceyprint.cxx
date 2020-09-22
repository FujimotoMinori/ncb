void fitsliceyprint() {
    // Change some default parameters in the current style
    gStyle->SetLabelSize(0.04,"x");
    gStyle->SetLabelSize(0.04,"y");
    gStyle->SetFrameFillColor(0);//38
    gStyle->SetTitleW(0.4);
    gStyle->SetTitleH(0.1);

    string finname = "../data/merged_18_0626.hist.root";
    //string finname = "../data/PixelNCB_18.00348495.f920_m1950.hist.root";
    //string finname = "../data/output349011.root";
    //file open
    TFile* fin = TFile::Open(finname.c_str(), "READ");
    if (!fin) {
        cout << " input file:" << finname.c_str() << " does not exist"<< endl;
        return;
    }
    cout << " input data file:" << finname.c_str() << " open..." << endl;
    //get histograms
    //TH2F *hpxpy = (TH2F*)fin->Get("zasym_CA_bcid"); 
    TH2F *hpxpy = (TH2F*)fin->Get("zasym_CA"); 
    int first = 7501; //7501,13588
    int last = 7501;
    TH1D *proj = hpxpy->ProjectionY("projectiony",first,last);

    TCanvas *c1 = new TCanvas("c1","c1",700,500);
    c1->SetFillColor(0);//42
    gPad->SetFillColor(0);//33
    gPad->SetLogz();
    hpxpy->Draw("colz");
    hpxpy->GetXaxis()->SetLabelSize(0.04);
    hpxpy->GetYaxis()->SetLabelSize(0.04);
    hpxpy->GetYaxis()->SetTitle("");
    hpxpy->SetMarkerColor(kYellow);
    hpxpy->SetStats(0);

    TCanvas *c2 = new TCanvas("c2","c2",700,500);
    hpxpy->FitSlicesY();
    gPad->SetFillColor(0);
    gStyle->SetPadGridY(1);
    TH2F *hpxpy_0 = (TH2F*)fin->Get("zasym_CA_bcid_0");
    //TH2F *hpxpy_0 = (TH2F*)fin->Get("zasym_CA_LB_0");
    hpxpy_0->Draw("P");
    gPad->SetFillColor(0);
    TCanvas *c3 = new TCanvas("c3","c3",700,500);
    TH2F *hpxpy_1 = (TH2F*)fin->Get("zasym_CA_bcid_1");
    //TH2F *hpxpy_1 = (TH2F*)fin->Get("zasym_CA_LB_1");
    hpxpy_1->GetYaxis()->SetRangeUser(0.0,0.3);
    hpxpy_1->Draw();
    gPad->SetFillColor(0);//33

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
    TCanvas *c4 = new TCanvas("c4","c4",700,500);
    hpxpy_0->Draw("P");
    proj->GetXaxis()->SetTitle("");
    proj->Draw();

    //attributes
    hpxpy_0->SetLineColor(1); //5
    hpxpy_1->SetLineColor(1);
    hpxpy_0->SetMarkerColor(2);
    hpxpy_1->SetMarkerColor(2);
    hpxpy_0->SetMarkerStyle(20);
    hpxpy_1->SetMarkerStyle(20);
    hpxpy_0->SetMarkerSize(0.5);
    hpxpy_1->SetMarkerSize(0.5);
    hpxpy_1->SetTitle("fitted mean of z-asymmetry");
    hpxpy_1->SetTitleSize(0.04);
    hpxpy_1->SetStats(0);
    c1->Print("originalzasym.pdf");
    c3->Print("fitmean.pdf");
    c4->Print("gaussian.pdf");
}

