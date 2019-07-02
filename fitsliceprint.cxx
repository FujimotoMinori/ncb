void fitsliceprint() {
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
    TH2F *hpxpy = (TH2F*)fin->Get("zasym_AC_woSmallHits"); 
    int first = 13588; //7501,13588
    int last = 13588;
    TH1D *proj = hpxpy->ProjectionY("projectiony",first,last);

    TCanvas *c1 = new TCanvas("c1","c1",700,500);
    c1->SetFillColor(0);//42
    gPad->SetTopMargin(0.12);
    gPad->SetFillColor(0);//33
    gPad->SetLogz();
    hpxpy->Draw("colz");
    hpxpy->GetXaxis()->SetLabelSize(0.06);
    hpxpy->GetYaxis()->SetLabelSize(0.06);
    
    // Fit slices 
    hpxpy->FitSlicesY();
    TCanvas *c2 = new TCanvas("c2","c2",700,500);
    gPad->SetTopMargin(0.12);
    gPad->SetLeftMargin(0.15);
    gPad->SetFillColor(0);
    TH2F *hpxpy_1 = (TH2F*)fin->Get("zasym_AC_woSmallHits_1");
    hpxpy_1->GetYaxis()->SetRangeUser(-0.3,0.0);
    std::cout << "getbincontent= " << hpxpy_1->GetBinContent(13588) <<std::endl;
    hpxpy_1->Draw();

    aouble start,end;
    //第一引数はポインタ、第二引数は項目名、第三引数で表示したいattributeを指定
    double mean,rms;
    mean = proj->GetMean();
    rms = proj->GetRMS();
    start = mean-rms;
    end = mean+rms;
    std::cout << "mean = " << mean << std::endl;
    std::cout << "rms = " << rms << std::endl;
    TF1 * f1 = new TF1("func","gaus");
    proj->SetStats(0);
    std::cout << "meanfitted = " << f1->GetParameter(1) << std::endl;
    TCanvas *c3 = new TCanvas("c3","c3",700,500);
    proj->Draw();

    //attributes
    hpxpy_1->SetLineColor(1);
    hpxpy_1->SetMarkerColor(2);
    hpxpy_1->SetMarkerStyle(21);
    hpxpy_1->SetMarkerSize(0.5);
    c2->Print("mean.pdf");
    c3->Print("gaus.pdf");
}
