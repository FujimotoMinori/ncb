void getmean() {
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
    TH2F *hpxpy = (TH2F*)fin->Get("nHitsA_beam2"); 

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
    // Fit slices projected along Y fron bins in X [7,32] with more than 20 bins  in Y filled
    //hpxpy->FitSlicesY(0,7,32,20);
    //hpxpy->FitSlicesY();
    // Show fitted "mean" for each slice
    leftPad->cd(2);
    gPad->SetFillColor(0);
    int j = 0;

    TH1F *h_mean = new TH1F("h_mean", "; Run Number; mean", 16340, 348150.5, 364490.5);
    TH1F *h_meanmean = new TH1F("h_meanmean", "; Run Number; mean", 100, 0, 1000);
    const int n = hpxpy->GetNbinsX()+1;
    for (int i=0; i< n; i++){
        TH1D *pj = hpxpy->ProjectionY("projectiony",i,i);
        int num = 0;
        num = pj->GetBinContent(i);
        //if(num!=0){
            if(pj->GetMean() != 0.0) {
                //h_mean->SetBinContent(i,pj->GetMean());
                if(pj->GetMean() > 1.0) {
                h_mean->SetBinContent(i,pj->GetMean());
                    j = i; 
                    //if(pj->GetMean() > 500){
                        //std::cout << "mean= " << pj->GetMean() << std::endl;
                        //std::cout << "j= " << j << std::endl;
                    //}
                    h_meanmean->Fill(pj->GetMean());
                //}

            }
        }
    }

    h_mean->GetYaxis()->SetRangeUser(0,1000);
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
    int first = 1117;
    int last = 1118;
    TH1D *proj = hpxpy->ProjectionY("projectiony",first,last);
    //TH1D *proj = hpxpy->ProjectionY("projectiony",0,15797);
    proj->Draw();
    //TH2F *hpxpy_2 = (TH2F*)fin->Get("zasym_AC_2");
    //hpxpy_2->SetMinimum(0.8);
    //hpxpy_2->Draw();

    //attributes
    h_mean->SetLineColor(3); //5
    h_mean->SetMarkerColor(2);
    h_mean->SetMarkerStyle(21);
    h_mean->SetMarkerSize(0.3);
    //hpxpy_0->SetLineColor(1); //5
    //hpxpy_1->SetLineColor(1);
    //hpxpy_2->SetLineColor(1);
    //hpxpy_0->SetMarkerColor(2);
    //hpxpy_1->SetMarkerColor(2);
    //hpxpy_2->SetMarkerColor(2);
    //hpxpy_0->SetMarkerStyle(21);
    //hpxpy_1->SetMarkerStyle(21);
    //hpxpy_2->SetMarkerStyle(21);
    //hpxpy_0->SetMarkerSize(0.3);
    //hpxpy_1->SetMarkerSize(0.3);
    //hpxpy_2->SetMarkerSize(0.3);
}
