

void printHelp(string progName){
  
  cout<<"usage: CAENdaq  [-h] [-v] [-x XMLFILE] [--xmlout XMLFILE] [-q] [w0] [w1]\n";//<<endl;
  cout<<"                [w2] [w3] ... [-o FILE] [-r RECLEN] [-a BASEADDRESS] \n";
  cout<<"                [-d DURATION] [--posttrigger VAL]\n";
  cout<<"                [--polarity0 POLARITY] ... [--DCoffset0 OFFSET] ...\n";
  cout<<"                [--threshold0 THRESHOLD] ... [--trslope0 POLARITY] ... \n";

  cout<<endl;
  cout<<"Reads waveforms from a CAEN V1730 digitizer.\n\n";

  cout<<"Mandatory arguments to long options are mandatory for short options too.\n";
  cout<<"  -h, --help                 Show this help message and exit\n";
  cout<<"  -v, --verbose              Prints verbose setup information\n";
  cout<<"  -x XMLFILE, --xml XMLFILE  Use settings in XMLFILE. This\n";
  cout<<"                             overrides other command line settings\n";
  cout<<"  --xmlout XMLFILE           Save settings to xml file\n";
  cout<<"  -q, --quit                 Used with --xmlout. Quits program after\n";
  cout<<"                             saving settings\n";
  cout<<endl;
  cout<<" The following options can also be set using an XML file, with the\n";
  cout<<" long options as the XML tags:\n";
  cout<<"  -w<CH>, --ch<CH>           Record the waveform on CH\n";
  cout<<"                             Valid options are 0-7\n";
  cout<<"  -o FILE, --outfile FILE    Save waveform to FILE\n";
  cout<<"  -n NUM, --saveInterval     After NUM events, save a temporary file.\n";
  cout<<"                             At the end of the run, these will be merged\n";
  cout<<"  -r RECLEN, --reclen RECLEN Set number of samples recorded to RECLEN\n";
  cout<<"  -a BASEADDRESS, --baseaddress BASEADDRESS\n";
  cout<<"                             Set digitizer base address to BASEADDRESS\n";
  cout<<"  -d DURATION, --duration DURATION\n";
  cout<<"                             Duration of the run. If an integer is\n";
  cout<<"                             specified, that many events are recorded.\n";
  cout<<"                             If a time is specified in HH:MM:SS format\n";
  cout<<"                             the daq will run for that long. Acquisition\n";
  cout<<"                             starts automatically.\n";
  cout<<"                             If not used, daq must be started manually\n";
  cout<<"  --polarity<CH> POLARITY    Set pulse polarity of channel CH\n";
  cout<<"                             Valid options are POSITIVE or NEGATIVE\n";
  cout<<"  --DCoffset<CH> OFFSET      Set DC offset of channel CH in ADC counts\n";
  cout<<"  --threshold<CH> THRESHOLD  Set the trigger threshold of channel CH\n";
  cout<<"                             in ADC counts\n";
  cout<<"  --trslope<CH> POLARITY     Trigger slope. Can be POSITIVE or NEGATIVE\n";
  cout<<"  --posttrigger VAL          Set the post trigger\n";
  cout<<endl;
    
  
  
  exit(0);
  
}
