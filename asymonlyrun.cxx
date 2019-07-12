int asymonlyrun() {
    // Change some default parameters in the current style
    gStyle->SetLabelSize(0.04,"x");
    gStyle->SetLabelSize(0.04,"y");
    gStyle->SetFrameFillColor(0);//38
    gStyle->SetTitleW(0.4);
    gStyle->SetTitleH(0.1);

    string finname = "../data/merged_18_0626.hist.root";
    //file open
    TFile* fin = TFile::Open(finname.c_str(), "READ");
    if (!fin) {
        cout << " input file:" << finname.c_str() << " does not exist"<< endl;
        return 0 ;
    }
    cout << " input data file:" << finname.c_str() << " open..." << endl;
    //get histograms
    TH2F *hpxpy = (TH2F*)fin->Get("zasym_CA_woSmallHits"); 
    int first = 7501; //7501,13588
    int last = 7501;
    TH1D *proj = hpxpy->ProjectionY("projectiony",first,last);

    //get runsummary
    //map of run and # of bunches
    std::map<int,int> pattern;
    TString ifndata = "a.txt";
    //first read datasummary file
    fstream findata;
    std::string strdata;
    findata.open(ifndata);
    if(findata.fail()){
        cerr << "cannot open datasummary file : " << ifndata << std::endl;
        return 1;
    }
    //read file
    const int n_Run = 1000;
    const int n_Colliding = 1000;
    int a,b;
    //int runF[n_Run] = {};
    //int collidingF[n_Colliding] = {};
    int n = 0;

    while(getline(findata,strdata))
    {
        if(strdata[0] == '#') continue;
        n++;
        a = 0;
        b = 0;
        sscanf(strdata.data(), "%d,%d", &a, &b);
        //runF[n] = a;
        //collidingF[n] = b;
        pattern.insert(make_pair(a,b));
    }

    auto begin = pattern.begin(), end = pattern.end();
    for (auto iter = begin; iter != end; iter++) {
        //if(iter->second == 7){
            std::cout << "run= " << iter->first << " colliding= " << iter->second << std::endl;
            //if(iter->first>=100) ++ntrackA;
            //else ++ntrackC;
        //}
    }
    pattern.clear();

    return 0;

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
    //slice and fit
    hpxpy->FitSlicesY();
    gPad->SetFillColor(0);
    gStyle->SetPadGridY(1);
    TH2F *hpxpy_0 = (TH2F*)fin->Get("zasym_CA_woSmallHits_0");
    hpxpy_0->Draw("P");
    gPad->SetFillColor(0);
    TCanvas *c3 = new TCanvas("c3","c3",700,500);
    TH2F *hpxpy_1 = (TH2F*)fin->Get("zasym_CA_woSmallHits_1");
    hpxpy_1->GetYaxis()->SetRangeUser(0.0,0.3);
    hpxpy_1->Draw();
    gPad->SetFillColor(0);//33

    //double start,end;
    double mean,rms;
    mean = proj->GetMean();
    rms = proj->GetRMS();
    start = mean-rms;
    //end = mean+rms;
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

