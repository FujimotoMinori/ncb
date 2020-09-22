int triggerrate(){
    string finname = "../data/output17.root";
    //file open
    TFile* fin = TFile::Open(finname.c_str(), "READ");
    if (!fin) {
        cout << " input file:" << finname.c_str() << " does not exist"<< endl;
        return 0 ;
    }

    //get histograms
    TH1F *triggerAC = (TH1F*)fin->Get("eventsACwoPV"); 
    TH1F *triggerCA = (TH1F*)fin->Get("eventsCAwoPV"); 
    TH1F *h_rateAC = new TH1F("h_rateAC", "; LumiBlock; Trigrate[Hz]", 550, 0.5, 550.5);
    TH1F *h_rateCA = new TH1F("h_rateCA", "; LumiBlock; Trigrate[Hz]", 550, 0.5, 550.5);

    const int n = triggerAC->GetNbinsX()+1;
    cout << "number of entries= " << n << endl; 
    for (int i=0;i<n;i++){
        float TrigrateAC = 0;
        float TrigrateCA = 0;
        float nTrigAC = 0;
        float nTrigCA = 0;
        nTrigAC = triggerAC->GetBinContent(i);
        nTrigCA = triggerCA->GetBinContent(i);
        TrigrateAC = nTrigAC/3600;
        TrigrateCA = nTrigCA/3600;
        h_rateAC->Fill(i,TrigrateAC);
        h_rateCA->Fill(i,TrigrateCA);

    }

    TCanvas *c1 = new TCanvas("c1","c1",700,500);
    h_rateAC->SetMaximum(10);
    h_rateCA->SetMaximum(10);
    h_rateAC->SetStats(0);
    h_rateAC->SetLineColor(kBlue);
    h_rateCA->SetStats(0);
    h_rateCA->SetLineColor(kRed);
    h_rateAC->Draw("HIST");
    h_rateCA->Draw("HIST same");
    gPad->SetLogy();

    TLegend *leg = new TLegend(0.7,0.78,0.9,0.90);
    leg->AddEntry(h_rateAC,"Beam AC ","lp");
    leg->AddEntry(h_rateCA,"Beam CA ","lp");
    leg->SetBorderSize(0); 
    leg->SetFillStyle(0); 
    leg->Draw();

    return 0;
}
