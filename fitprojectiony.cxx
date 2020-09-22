void fitprojectiony() {
    // Change some default parameters in the current style
    gStyle->SetLabelSize(0.03,"x");
    gStyle->SetLabelSize(0.03,"y");
    gStyle->SetFrameFillColor(0);//38
    gStyle->SetTitleW(0.4);
    gStyle->SetTitleH(0.08);

    //string finname = "../data/merged18_0905.hist.root";
    string finname = "../data/merged_18_1023.hist.root";
    //file open
    TFile* fin = TFile::Open(finname.c_str(), "READ");
    if (!fin) {
        cout << " input file:" << finname.c_str() << " does not exist"<< endl;
        return;
    }
    cout << " input data file:" << finname.c_str() << " open..." << endl;

    //get runsummary
    TString ifndata = "a.txt";
    //first read datasummary file
    fstream findata;
    std::string strdata;
    findata.open(ifndata);
    if(findata.fail()){
        cerr << "cannot open datasummary file : " << ifndata << std::endl;
        return;
    }
    //read file
    const int n_Run = 1000;
    const int n_Colliding = 1000;
    int a,b;
    std::map<int,int> pattern;

    while(getline(findata,strdata))
    {
        if(strdata[0] == '#') continue;
        a = 0;
        b = 0;
        sscanf(strdata.data(), "%d,%d", &a, &b);
        pattern.insert(make_pair(a,b));
    }

    //get histograms
    TH2F *hpxpy = (TH2F*)fin->Get("zasym_AC_woSmallHits"); 
    TH2F *hpxpy2 = (TH2F*)fin->Get("zasym_CA_woSmallHits"); 
    TH1F *h_mean = new TH1F("h_mean", "; Run Number; mean", 16340, 348150.5, 364490.5);
    TH1F *h_mean2 = new TH1F("h_mean2", "; Run Number; mean", 16340, 348150.5, 364490.5);
    TH1F *h_diff = new TH1F("h_diff", "; Run Number; mean", 16340, 348150.5, 364490.5);
    const int n = hpxpy->GetNbinsX()+1;
    vector<Double_t> x,y;
    vector<Double_t> xf,yf,xfe,yfe;
    int bi = 0;
    for (int i=0; i< n; i++){
        bool bingo = false;
        bi = i+348150;
        TH1D *pj = hpxpy->ProjectionY("projectiony",i,i);
        TH1D *pj2 = hpxpy2->ProjectionY("projectiony2",i,i);
        int num = 0;
        int flag = 0;
        double mean = 0.;
        double mean2 = 0.;
        double sigma = 0.;
        double sigma2 = 0.;
        double getmean = 0.;
        double getmean2 = 0.;
        double getmeanerr = 0.;
        double getmean2err = 0.;
        double chi2 = 0.;
        double ndof = 0.;
        int first,last;
        int first2,last2;
        mean = pj->GetMean();
        mean2 = pj2->GetMean();
        sigma = pj->GetRMS();
        sigma2 = pj2->GetRMS();
        if(mean != 0.0) {
            if(mean2 != 0.0) {
                first = mean-sigma; 
                last = mean+sigma; 
                first2 = mean2-sigma2; 
                last2 = mean2+sigma2; 
                TF1 * f1 = new TF1("func","gaus");
                TF1 * f2 = new TF1("func2","gaus");
                pj->Fit("func","","",first,last);
                pj2->Fit("func2","","",first2,last2);
                getmean = f1->GetParameter(1);
                getmean2 = f2->GetParameter(1);
                getmeanerr = f1->GetParError(1);
                getmean2err = f2->GetParError(1);
                chi2 = f1->GetChisquare();
                ndof = f1->GetNDF();


                if (getmean != 0.0)  h_mean->SetBinContent(i,getmean);
                if (getmean2 != 0.0)  h_mean2->SetBinContent(i,getmean2);
                h_diff->SetBinContent(i,abs(getmean)-abs(getmean2));

                auto itr = pattern.find(bi);
                if( itr != pattern.end() ) {
                    flag = itr->second;
                    if(flag != 2544){
                        bingo = true;
                    }
                }

                x.push_back(bi);
                y.push_back(abs(getmean)-abs(getmean2));
                xf.push_back(bi);
                xfe.push_back(0.);
                if(bingo){
                    yf.push_back(getmean2);
                    yfe.push_back(getmean2err);
                }else{
                    yf.push_back(-1.);
                    yfe.push_back(0.);
                }
            }
        }
    }
    Double_t* xpointer=&(x.at(0));
    Double_t* ypointer=&(y.at(0));
    TGraph* tg=new TGraph(x.size(),xpointer,ypointer);
    tg->SetMarkerStyle(20);
    tg->SetMarkerColor(kRed);
    tg->SetMarkerSize(0.5);
    gStyle->SetPadGridY(1);
    //tg->GetYaxis()->SetRangeUser();
    tg->SetTitle("abs(asymAC)-abs(asymCA);RunNumber;difference of zasym");
    tg->GetXaxis()->SetLabelSize(0.03);
    tg->GetYaxis()->SetLabelSize(0.03);
    tg->GetYaxis()->SetRangeUser(-0.2,0.2);
    TCanvas *c0 = new TCanvas("c0","c0",700,500);
    tg->Draw("AP");


    Double_t* xpointerf=&(xf.at(0));
    Double_t* ypointerf=&(yf.at(0));
    Double_t* xpointerfe=&(xfe.at(0));
    Double_t* ypointerfe=&(yfe.at(0));
    TGraphErrors* tgf=new TGraphErrors(xf.size(),xpointerf,ypointerf,xpointerfe,ypointerfe);
    tgf->SetMarkerStyle(20);
    tgf->SetMarkerColor(kRed);
    tgf->SetMarkerSize(0.5);
    gStyle->SetPadGridY(1);
    tgf->SetTitle("fitted mean of z-asymmetry;RunNumber;");
    tgf->GetXaxis()->SetLabelSize(0.04);
    tgf->GetYaxis()->SetLabelSize(0.04);
    tgf->GetYaxis()->SetRangeUser(0.0,0.3);

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
    hpxpy->GetXaxis()->SetLabelSize(0.03);
    hpxpy->GetYaxis()->SetLabelSize(0.03);
    hpxpy->SetMarkerColor(kYellow);
    // Fit slices projected along Y fron bins in X [7,32] with more than 20 bins  in Y filled
    //hpxpy->FitSlicesY(0,7,32,20);
    hpxpy->FitSlicesY();

    cout << "xsize=" << xf.size() << endl;

    // Show fitted "mean" for each slice
    leftPad->cd(2); //secondcanvas
    gPad->SetFillColor(0);
    TH2F *hpxpy_0 = (TH2F*)fin->Get("zasym_AC_woSmallHits_0");
    hpxpy_0->Draw();

    TPad *rightPad = (TPad*)c1->cd(2);
    rightPad->Divide(1,2);
    rightPad->cd(1); //third canvas
    gPad->SetTopMargin(0.12);
    gPad->SetLeftMargin(0.15);
    gPad->SetFillColor(0);
    TH2F *hpxpy_1 = (TH2F*)fin->Get("zasym_AC_woSmallHits_1");
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
    h_mean2->SetLineColor(1);
    h_mean2->SetMarkerColor(2);
    h_mean2->SetMarkerStyle(21);
    h_mean2->SetMarkerSize(0.3);
    h_diff->SetLineColor(1);
    h_diff->SetMarkerColor(2);
    h_diff->SetMarkerStyle(21);
    h_diff->SetMarkerSize(0.3);

    TCanvas *c2 = new TCanvas("c2","c2",700,500);
    h_mean2->Draw("P");
    TCanvas *c3 = new TCanvas("c3","c3",700,500);
    h_mean->Draw("P");
    TCanvas *c4 = new TCanvas("c4","c4",700,500);
    h_diff->Draw("P");
    TCanvas *c5 = new TCanvas("c5","c5",700,500);
    tgf->Draw("AP");
}
