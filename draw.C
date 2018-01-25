

void draw(string filename, int ch, int event){

  //TFile *f = TFile::Open(filename.c_str());//new TFile(file);
  TFile *f = new TFile(filename.c_str(), "READ");
  TTree *t = (TTree*)f->Get("data");

  cout<<t->GetEntries()<<endl;
  
  stringstream ss;
  ss<<ch;
  TString c = ss.str();

  vector<double> *data = new vector<double>;
  double xinc;
  double tm;
  
  t->SetBranchAddress("ch"+c, &data);
  t->SetBranchAddress("time", &tm);
  t->SetBranchAddress("xinc", &xinc);

  t->GetEntry(event);

  cout<<data->size()<<endl;
  
  cout.precision(15);
  cout<<tm<<endl;

  
  
  TGraph *gr = new TGraph();
  
  for(int i=0; i<data->size(); i++){
    gr->SetPoint(i, i*xinc/1e-6, data->at(i));
  }

  gr->GetXaxis()->SetTitle("time (#mus)");
  gr->GetYaxis()->SetTitle("Voltage (mV)");

  gr->Draw("AL");
  

  
  f->Close();


}
