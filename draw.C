

void draw(TString file, int ch, int event){

  TFile *f = new TFile(file);
  TTree *t = (TTree*)f->Get("data");

  stringstream ss;
  ss<<ch;
  TString c = ss.str();

  vector<double> *data;
  double xinc;
  
  t->SetBranchAddress("ch"+c, &data);

  t->GetEntry(event);

  TGraph *gr = new TGraph();
  
  for(int i=0; i<data->size(); i++){
    gr->SetPoint(i, i, data->at(i));
  }

  gr->GetXaxis()->SetTitle("time (#mus)");
  gr->GetYaxis()->SetTitle("Voltage (mV)");

  gr->Draw("AL");



}
