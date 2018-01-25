

void draw(TString file, int ch, int event){

  TFile *f = TFile::Open("CAEN.root");//new TFile(file);
  TTree *t = (TTree*)f->Get("data");

  cout<<t->GetEntries()<<endl;
  
  stringstream ss;
  ss<<ch;
  TString c = ss.str();

  vector<double> *data;
  double xinc;
  double tm;
  
  t->SetBranchAddress("ch"+c, &data);
  t->SetBranchAddress("time", &tm);

  t->GetEntry(event);

  cout<<data->size()<<endl;
  
  cout.precision(15);
  cout<<tm<<endl;

  
  TGraph *gr = new TGraph();
  
  for(int i=0; i<data->size(); i++){
    gr->SetPoint(i, i, data->at(i));
  }

  gr->GetXaxis()->SetTitle("time (#mus)");
  gr->GetYaxis()->SetTitle("Voltage (mV)");

  gr->Draw("AL");

  //f->Close();


}
