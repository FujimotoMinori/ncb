int checktag(){

    string finname = "../data/merged_18_0626.hist.root";
    //file open
    TFile* fin = TFile::Open(finname.c_str(), "READ");
    if (!fin) {
        cout << " input file:" << finname.c_str() << " does not exist"<< endl;
        return 0;
    }
    cout << " input data file:" << finname.c_str() << " open..." << endl;
    //get histograms
    TH1F *h1 = (TH1F*)fin->Get("eventsAC"); 
    TH2F *hpxpy = (TH2F*)fin->Get("nHitsA_beam1"); 
    //TH1F *h2 = (TH1F*)fin->Get("eventsCA"); 

    //get data of luminosity
    TString ifndata = "../runinfo_org/inputfiles_grid2018.txt";
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
    char * tag;
    std::map<int,string> pattern;

    int a;
    char b[30];
    
    cout << " now here:" <<  endl;
    while(getline(findata,strdata))
    {
        if(strdata[0] == '#') continue;
        a = 0;
        sscanf(strdata.data(), "%d %s", &a, b);
        std::string str(b, 10);
        pattern.insert(make_pair(a,str));
    }

    const int n = h1->GetNbinsX()+1;
    int bi = 0;
    double m = 0.;
    int f = 0;
        for (int i=0; i< n; i++){
            bi = i+348150.0;
            m  = h1->GetBinContent(i);
            TH1D *pj = hpxpy->ProjectionY("projectiony",i,i);
            int num = 0;
            num = pj->GetBinContent(i);
            if(pj->GetMean() != 0.0){

                auto itr = pattern.find(bi);
                if( itr != pattern.end() ) {
                    cout << itr->second << endl;
                    f++;
                }

            }
        }
    cout << "n= " << n << endl;
    cout << "pattern size= " << pattern.size() << endl;
    cout << "f= " << f << endl;

    //map clear
    pattern.clear();

    return 0;
}

