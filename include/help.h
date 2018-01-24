

void printHelp(string progName){
  
  cout<<"usage: "<<progName<<"  [-h] [-v] [-x XMLFILE]"<<endl;
  cout<<endl;
  cout<<"Reads waveforms from a CAEN V1730 digitizer.\n\n";

  cout<<"optional arguments:\n";
  cout<<"  -h, --help                 show this help message and exit\n";
  cout<<"  -v, --verbose              prints verbose setup information\n";
  cout<<"  -x XMLFILE, --xml XMLFILE  Use settings in XMLFILE\n";
  
  
  exit(0);
  
}
