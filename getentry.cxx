void getentry(){
    string finname = "../data/merged_18_0712.hist.root";
    //file open
    TFile* fin = TFile::Open(finname.c_str(), "READ");
    if (!fin) {
        cout << " input file:" << finname.c_str() << " does not exist"<< endl;
        return;
    }
    cout << " input data file:" << finname.c_str() << " open..." << endl;
    //get histograms
    TH2F *hAbeam1 = (TH2F*)fin->Get("nHitsA_beam1"); 
    TH2F *hCbeam1 = (TH2F*)fin->Get("nHitsC_beam1"); 
    TH2F *hAbeam2 = (TH2F*)fin->Get("nHitsA_beam2"); 
    TH2F *hCbeam2 = (TH2F*)fin->Get("nHitsC_beam2"); 
    TH2F *hAbeam1wo = (TH2F*)fin->Get("nHitsA_beam1_woSmallHits"); 
    TH2F *hCbeam1wo = (TH2F*)fin->Get("nHitsC_beam1_woSmallHits"); 
    TH2F *hAbeam2wo = (TH2F*)fin->Get("nHitsA_beam2_woSmallHits"); 
    TH2F *hCbeam2wo = (TH2F*)fin->Get("nHitsC_beam2_woSmallHits"); 
    TH2F *hAbeam1w = (TH2F*)fin->Get("nHitsA_beam1_wSmallHits"); 
    TH2F *hCbeam1w = (TH2F*)fin->Get("nHitsC_beam1_wSmallHits"); 
    TH2F *hAbeam2w = (TH2F*)fin->Get("nHitsA_beam2_wSmallHits"); 
    TH2F *hCbeam2w = (TH2F*)fin->Get("nHitsC_beam2_wSmallHits"); 
    TH2F *hAbeam13 = (TH2F*)fin->Get("nHitsA_beam1_3"); 
    TH2F *hCbeam13 = (TH2F*)fin->Get("nHitsC_beam1_3"); 
    TH2F *hAbeam23 = (TH2F*)fin->Get("nHitsA_beam2_3"); 
    TH2F *hCbeam23 = (TH2F*)fin->Get("nHitsC_beam2_3"); 
    TH2F *hAbeam16 = (TH2F*)fin->Get("nHitsA_beam1_6"); 
    TH2F *hCbeam16 = (TH2F*)fin->Get("nHitsC_beam1_6"); 
    TH2F *hAbeam26 = (TH2F*)fin->Get("nHitsA_beam2_6"); 
    TH2F *hCbeam26 = (TH2F*)fin->Get("nHitsC_beam2_6"); 

    double a1,c1,a2,c2 = 0;
    double a1wo,c1wo,a2wo,c2wo = 0;
    double a1w,c1w,a2w,c2w = 0;
    double a13,c13,a23,c23 = 0;
    double a16,c16,a26,c26 = 0;

    a1 = hAbeam1->GetEntries();
    c1 = hCbeam1->GetEntries();
    a2 = hAbeam2->GetEntries();
    c2 = hCbeam2->GetEntries();
    a1wo = hAbeam1wo->GetEntries();
    c1wo = hCbeam1wo->GetEntries();
    a2wo = hAbeam2wo->GetEntries();
    c2wo = hCbeam2wo->GetEntries();
    a1w = hAbeam1w->GetEntries();
    c1w = hCbeam1w->GetEntries();
    a2w = hAbeam2w->GetEntries();
    c2w = hCbeam2w->GetEntries();
    a13 = hAbeam13->GetEntries();
    c13 = hCbeam13->GetEntries();
    a23 = hAbeam23->GetEntries();
    c23 = hCbeam23->GetEntries();
    a16 = hAbeam16->GetEntries();
    c16 = hCbeam16->GetEntries();
    a26 = hAbeam26->GetEntries();
    c26 = hCbeam26->GetEntries();

    cout << "***********************number of entries***********************" << endl;
    cout << "---all " << endl;
    cout << "beam1A : beam1C : beam2A : beam2C " << endl;
    cout << a1 << " " << c1 << " " << a2 << " " << c2 << " " <<endl;
    cout << "---woSmallHits " << endl;
    cout << "beam1A : beam1C : beam2A : beam2C " << endl;
    cout << a1wo << " " << c1wo << " " << a2wo << " " << c2wo << " " <<endl;
    cout << "---wSmallHits " << endl;
    cout << "beam1A : beam1C : beam2A : beam2C " << endl;
    cout << a1w << " " << c1w << " " << a2w << " " << c2w << " " <<endl;
    cout << "---3 " << endl;
    cout << "beam1A : beam1C : beam2A : beam2C " << endl;
    cout << a13 << " " << c13 << " " << a23 << " " << c23 << " " <<endl;
    cout << "---6 " << endl;
    cout << "beam1A : beam1C : beam2A : beam2C " << endl;
    cout << a16 << " " << c16 << " " << a26 << " " << c26 << " " <<endl;
    cout << " " << endl;
    cout << "***********************ratio***********************" << endl;
    cout << "---woSmallHits " << endl;
    cout << "beam1A : beam1C : beam2A : beam2C " << endl;
    cout << a1wo/a1 << " " << c1wo/c1 << " " << a2wo/c2 << " " << c2wo/c2 << " " <<endl;
    cout << "---3 " << endl;
    cout << "beam1A : beam1C : beam2A : beam2C " << endl;
    cout << a13/a1 << " " << c13/c1 << " " << a23/c2 << " " << c23/c2 << " " <<endl;
    cout << "---6 " << endl;
    cout << "beam1A : beam1C : beam2A : beam2C " << endl;
    cout << a16/a1 << " " << c16/c1 << " " << a26/c2 << " " << c26/c2 << " " <<endl;

    return;
}
