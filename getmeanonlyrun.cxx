int getmeanonlyrun() {
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
        return 0;
    }
    cout << " input data file:" << finname.c_str() << " open..." << endl;
    //get histograms
    TH2F *hpxpy = (TH2F*)fin->Get("nHitsA_beam1_woSmallHits"); 
    TH2F *hpxpyC = (TH2F*)fin->Get("nHitsC_beam1_woSmallHits"); 

    //get runsummary
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
    std::map<int,int> pattern;

    while(getline(findata,strdata))
    {
        if(strdata[0] == '#') continue;
        a = 0;
        b = 0;
        sscanf(strdata.data(), "%d,%d", &a, &b);
        pattern.insert(make_pair(a,b));
    }

    // Create a canvas and divide it
    TCanvas *c1 = new TCanvas("c1","c1",700,500);
    c1->SetFillColor(0);//42
    c1->Divide(2,1);
    TPad *leftPad = (TPad*)c1->cd(1);;
    leftPad->Divide(1,2);
    leftPad->cd(1);
    gPad->SetTopMargin(0.12);
    gPad->SetFillColor(0);//33
    gPad->SetLogz();
    hpxpy->SetStats(0);
    hpxpy->Draw("colz");
    hpxpy->GetXaxis()->SetLabelSize(0.06);
    hpxpy->GetYaxis()->SetLabelSize(0.06);
    hpxpy->SetMarkerColor(kYellow);
    leftPad->cd(2);
    gPad->SetFillColor(0);
    int j = 0;

    TH1F *h_mean = new TH1F("h_mean", "; Run Number; mean", 16340, 348150.5, 364490.5);
    TH1F *h_meanmean = new TH1F("h_meanmean", "; Run Number; mean", 100, 0, 1000);
    vector<Double_t> x,y,xe,ye;
    vector<Double_t> xc,yc,xec,yec;
    const int n = hpxpy->GetNbinsX()+1;
    float bi = 0;

    for (int i=0; i< n; i++){//bin loop
        bool bingo = false;
        bi = i + 348150.0;   
        TH1D *pj = hpxpy->ProjectionY("projectiony",i,i);
        TH1D *pjc = hpxpyC->ProjectionY("projectionyC",i,i);
        int num = 0;
        int flag = 0;
        num = pj->GetBinContent(i);
        if(pj->GetMean() != 0.0) {

            auto itr = pattern.find(bi);
            if( itr != pattern.end() ) {
                flag = itr->second;
                if(flag == 2544){
                    bingo = true;
                }
            }

            h_mean->SetBinContent(i,pj->GetMean());
            x.push_back(bi);
            xc.push_back(bi);
            xe.push_back(0.);
            xec.push_back(0.);
            h_meanmean->Fill(pj->GetMean());
            if(bingo){
                y.push_back(pj->GetMean());
                yc.push_back(pjc->GetMean());
                ye.push_back(pj->GetMeanError());
                yec.push_back(pjc->GetMeanError());
            }else{
                y.push_back(0.);
                yc.push_back(0.);
                ye.push_back(0.);
                yec.push_back(0.);
            }

        }
    }//end of bin loop

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
    tg->GetYaxis()->SetRangeUser(420,720);
    tgc->SetMarkerStyle(20);
    tgc->SetMarkerColor(kRed);
    tgc->SetMarkerSize(0.5);
    tgc->GetYaxis()->SetRangeUser(420,720);
    gStyle->SetPadGridY(1);
    tg->SetTitle(";RunNumber;mean of NHits");
    tg->GetXaxis()->SetLabelSize(0.03);
    tg->GetYaxis()->SetLabelSize(0.03);
    tgc->SetTitle(";RunNumber;mean of NHits");
    tgc->GetXaxis()->SetLabelSize(0.03);
    tgc->GetYaxis()->SetLabelSize(0.03);

    h_mean->GetYaxis()->SetRangeUser(420,720); //420,720
    h_mean->Draw("P");
    TPad *rightPad = (TPad*)c1->cd(2);
    rightPad->Divide(1,2);
    rightPad->cd(1);
    gPad->SetTopMargin(0.12);
    gPad->SetLeftMargin(0.15);
    gPad->SetFillColor(0);
    h_meanmean->Draw();
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

    //map clear
    pattern.clear();

    //attributes
    h_mean->SetLineColor(3); //5
    h_mean->SetMarkerColor(2);
    h_mean->SetMarkerStyle(21);
    h_mean->SetMarkerSize(0.3);

    TCanvas *c0 = new TCanvas("c0","c0",700,500);
    tg->Draw("AP");
    c0->Print("testA.pdf");
    TCanvas *c4 = new TCanvas("c4","c4",700,500);
    tgc->Draw("AP");
    c4->Print("testC.pdf");

    return 0;
}
