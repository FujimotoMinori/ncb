void getasymfrommean() {
    // Change some default parameters in the current style
    gStyle->SetLabelSize(0.06,"x");
    gStyle->SetLabelSize(0.06,"y");
    gStyle->SetFrameFillColor(0);//38
    gStyle->SetTitleW(0.6);
    gStyle->SetTitleH(0.1);

    string finname = "../data/merged_18_0626.hist.root";
    //string finname = "../data/merged_17_0618.hist.root";
    //file open
    TFile* fin = TFile::Open(finname.c_str(), "READ");
    if (!fin) {
        cout << " input file:" << finname.c_str() << " does not exist"<< endl;
        return;
    }
    cout << " input data file:" << finname.c_str() << " open..." << endl;
    //get histograms
    TH2F *hpxpy = (TH2F*)fin->Get("nHitsA_beam2_woSmallHits"); 
    TH2F *hpxpyC = (TH2F*)fin->Get("nHitsC_beam2_woSmallHits"); 

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
    leftPad->cd(2);
    gPad->SetFillColor(0);
    int j = 0;

    TH1F *h_mean = new TH1F("h_mean", "; Run Number; mean", 16340, 348150.5, 364490.5);
    TH1F *h_meanmean = new TH1F("h_meanmean", "; Run Number; mean", 100, 0, 1000);
    TH1F *h_meannew = new TH1F("h_asym", "; Run Number; asym", 16340, 348150.5, 364490.5);

    vector<Double_t> x,y,xe,ye;
    const int n = hpxpy->GetNbinsX()+1;
    for (int i=0; i< n; i++){
        TH1D *pj = hpxpy->ProjectionY("projectiony",i,i);
        TH1D *pjC = hpxpyC->ProjectionY("projectionyC",i,i);
        int num = 0;
        float meanA = 0;
        float meanC = 0;
        float RMSA = 0;
        float RMSC = 0;
        float eA = 0;
        float eC = 0;

        float zasym = -5.;
        float ezasym = -5.;
        float denom = -5.; 
        num = pj->GetBinContent(i);
        //if(num!=0){
            if(pj->GetMean() != 0.0) {
                h_mean->SetBinContent(i,pj->GetMean());
                meanA = pj->GetMean();
                meanC = pjC->GetMean();
                RMSA = pj->GetRMS();
                RMSC = pjC->GetRMS();
                //eA = sqrt(meanA);
                //eC = sqrt(meanC);
                eA = pj->GetMeanError();
                eC = pjC->GetMeanError();
                cout << "meanA= "<< meanA << endl;
                cout << "meanC= "<< meanC << endl;
                cout << "RMSA= "<< RMSA << endl;
                cout << "RMSC= "<< RMSC << endl;
                cout << "eA= "<< eA << endl;
                cout << "eC= "<< eC << endl;

                if((meanA + meanC) != 0) {
                    zasym = (meanA-meanC)/(meanA+meanC); 
                    denom = 2/((meanA+meanC)*(meanA+meanC));   
                    ezasym = sqrt(meanC*meanC*eA*eA+meanA*meanA*eC*eC)*denom;  
                    h_meannew->SetBinContent(i,zasym);
                    x.push_back(i);
                    y.push_back(zasym);
                    cout << "asym= "<< zasym << endl;
                    cout << "easym= "<< ezasym << endl;
                    xe.push_back(0.);
                    //ye.push_back(ezasym);
                    ye.push_back(ezasym);
                }

                h_meanmean->Fill(pj->GetMean());

        }
    }

    Double_t* xpointer=&(x.at(0));
    Double_t* ypointer=&(y.at(0));
    Double_t* xepointer=&(xe.at(0));
    Double_t* yepointer=&(ye.at(0));
    TGraphErrors* tg=new TGraphErrors(x.size(),xpointer,ypointer,xepointer,yepointer);
    tg->SetMarkerStyle(20);
    tg->SetMarkerColor(kRed);
    tg->SetMarkerSize(0.5);
    tg->GetYaxis()->SetRangeUser(0.0,0.2);
    gStyle->SetPadGridY(1);
    tg->SetTitle("asym;RunNumber;zasym");
    tg->GetXaxis()->SetLabelSize(0.03);
    tg->GetYaxis()->SetLabelSize(0.03);

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
    //TH1D *proj = hpxpy->ProjectionY("projectiony",0,15797);
    proj->Draw();
    //TH2F *hpxpy_2 = (TH2F*)fin->Get("zasym_AC_2");
    //hpxpy_2->SetMinimum(0.8);
    //hpxpy_2->Draw();

    TCanvas *c2 = new TCanvas("c2","c2",700,500);
    h_meannew->GetYaxis()->SetRangeUser(-0.3,0.0);
    h_meannew->Draw("P");

    //attributes
    h_mean->SetLineColor(3); //5
    h_mean->SetMarkerColor(2);
    h_mean->SetMarkerStyle(21);
    h_mean->SetMarkerSize(0.3);
    h_meannew->SetLineColor(3); //5
    h_meannew->SetMarkerColor(2);
    h_meannew->SetMarkerStyle(20);
    h_meannew->SetMarkerSize(0.5);
    TCanvas *c0 = new TCanvas("c0","c0",700,500);
    tg->Draw("AP");
}

