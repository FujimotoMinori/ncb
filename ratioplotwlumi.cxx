int ratioplotwlumi(){
    // Change some default parameters in the current style
    gStyle->SetLabelSize(0.06,"x");
    gStyle->SetLabelSize(0.04,"y");
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
    TH1F *h1 = (TH1F*)fin->Get("eventsAC"); 
    TH1F *h2 = (TH1F*)fin->Get("eventsCA"); 

    //get data of luminosity
    TString ifndata = "c.txt";
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
    std::map<int,double> pattern;

    int a;
    double b;
    while(getline(findata,strdata))
    {
        if(strdata[0] == '#') continue;
        a = 0;
        b = 0;
        sscanf(strdata.data(), "%d,%lf", &a, &b);
        pattern.insert(make_pair(a,b));
    }


    double c,d,m;
    vector<Double_t> x,y,xe,ye;
    vector<Double_t> xc,yc,xec,yec;
    float bi = 0;

    const int n = h1->GetNbinsX()+1;
    std::cout << "n= " << n << std::endl;
    int k = 0;
    int l = 0;
    for (int i=0; i< n; i++){ //bin loop
        bi = i + 348150.0;   
        double lumi = 0;

        c  = h1->GetBinContent(i);
        d  = h2->GetBinContent(i);

        auto itr = pattern.find(bi);
        if( itr != pattern.end() ) {
            lumi = itr->second;
            m = c-d;
            if(lumi != 0){
                c = c/lumi;
                d = d/lumi;
                m = m/lumi;
                k++;
                //std::cout << "mmodified = " << m << std::endl;
            }
        }

        if(m != 0.){
            l++;
            x.push_back(bi);
            xc.push_back(bi);
            xe.push_back(0.);
            xec.push_back(0.);
            y.push_back(c);
            yc.push_back(m);
            ye.push_back(0.);
            yec.push_back(0.);
        }

    }//end of bin loop
    std::cout << "k= " << k << std::endl;
    std::cout << "l= " << l << std::endl;

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
    tg->GetYaxis()->SetRangeUser(-10000,10000);
    tgc->SetMarkerStyle(20);
    tgc->SetMarkerColor(kRed);
    tgc->SetMarkerSize(0.5);
    tgc->GetYaxis()->SetRangeUser(-10000,10000);
    gStyle->SetPadGridY(1);
    tg->SetTitle(";RunNumber;# of trigger / lumi");
    tg->GetXaxis()->SetLabelSize(0.03);
    tg->GetYaxis()->SetLabelSize(0.03);
    tgc->SetTitle(";RunNumber; #(BCMAC)-#(BCMCA) / lumi");
    tgc->GetXaxis()->SetLabelSize(0.03);
    tgc->GetYaxis()->SetLabelSize(0.03);


    //map clear
    pattern.clear();

    //attributes
    TCanvas *c0 = new TCanvas("c0","c0",700,500);
    tg->Draw("AP");
    //c0->Print("testA.pdf");
    TCanvas *c1 = new TCanvas("c1","c1",700,500);
    tgc->Draw("AP");
    //c1->Print("testC.pdf");

    return 0;
}
