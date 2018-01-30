
bool verbose;

XmlParser getOpt(int argc, char *argv[]){


  verbose=false;
  
  string settingsFile="";
  XmlParser settings;

  string savedSettingsFile="";
  bool quitAfterSettingSave=false;
  
  int c; 
  
  while(true){
  
  static struct option long_options[] =
    {
      {"help",		no_argument,       0, 'h'},	// help
      {"verbose",	no_argument,       0, 'v'},	// verbose mode
      {"xml",   	required_argument, 0, 'x'},	// xml file
      {"outfile",       required_argument, 0, 'o'},     // output file name
      {"reclen",        required_argument, 0, 'r'},     // RecordLength
      {"baseaddress",   required_argument, 0, 'a'},     // digitizer base address
      {"ch",		required_argument, 0, 'w'},	// record waveform
      {"polarity0",     required_argument, 0, '0'},	// polarity of channel0
      {"polarity1",     required_argument, 0, '1'},	
      {"polarity2",     required_argument, 0, '2'},	
      {"polarity3",     required_argument, 0, '3'},	
      {"polarity4",     required_argument, 0, '4'},	
      {"polarity5",     required_argument, 0, '5'},	
      {"polarity6",     required_argument, 0, '6'},	
      {"polarity7",     required_argument, 0, '7'},	
      {"DCoffset0",     required_argument, 0, 'A'},	// DC offset
      {"DCoffset1",     required_argument, 0, 'B'},     
      {"DCoffset2",     required_argument, 0, 'C'},     
      {"DCoffset3",     required_argument, 0, 'D'},     
      {"DCoffset4",     required_argument, 0, 'E'},     
      {"DCoffset5",     required_argument, 0, 'F'},     
      {"DCoffset6",     required_argument, 0, 'G'},     
      {"DCoffset7",     required_argument, 0, 'H'},
      {"threshold0",    required_argument, 0, 'I'},     // Trigger threshold
      {"threshold1",    required_argument, 0, 'J'},      
      {"threshold2",    required_argument, 0, 'K'},      
      {"threshold3",    required_argument, 0, 'L'},      
      {"threshold4",    required_argument, 0, 'M'},      
      {"threshold5",    required_argument, 0, 'N'},      
      {"threshold6",    required_argument, 0, 'O'},      
      {"threshold7",    required_argument, 0, 'P'},
      {"posttrigger",   required_argument, 0, 'Q'},     // post trigger
      {"duration",      required_argument, 0, 'd'},     // duration
      {"xmlout",        required_argument, 0, 's'},     // xml output file
      {"quit",          no_argument,       0, 'q'},     // quit after saving xml
      {"trslope0",      required_argument, 0, 'R'},     // trigger slope
      {"trslope1",      required_argument, 0, 'S'},
      {"trslope2",      required_argument, 0, 'T'},
      {"trslope3",      required_argument, 0, 'U'},
      {"trslope4",      required_argument, 0, 'V'},
      {"trslope5",      required_argument, 0, 'W'},
      {"trslope6",      required_argument, 0, 'X'},
      {"trslope7",      required_argument, 0, 'Y'},
      
      {0, 0, 0, 0}
    };

    int option_index = 0;
    // leave case out of the list if no short option is to be allowed
    c = getopt_long (argc, argv, "hvqx:w:a:r:o:d:", long_options, &option_index);

    if (c == -1)
    {
      break;					// end of the options
    }
    
    switch (c){
    case 0:
      if (long_options[option_index].flag != 0){
	break;
      }
    case 's':
      savedSettingsFile=optarg;
      break;
    case 'q':
      quitAfterSettingSave=true;
      break;
    case 'h':
      printHelp(argv[0]);
      break;
    case 'v': 
      verbose=true;
      break;
    case 'x':
      settingsFile = optarg;
      break;
    case 'o':
      settings.addValue("outfile", optarg);
      break;
    case 'r':
      if(string(optarg).find_first_not_of("0123456789") == std::string::npos){
	settings.addValue("reclen", optarg);
      } else{
	cout<<"Invalid record length. Must be numerical\n";
	exit(0);
      }        
      break;
    case 'a':
      settings.addValue("baseaddress", optarg);
      break;      
    case 'w':
      if(string(optarg).find_first_not_of("01234567") == std::string::npos){
	settings.addValue("ch"+string(optarg), "1");
      } else {
	cout<<"Invalid channel setting. Must be between 0 and 7\n";
	exit(0);
      }
      break;
    case 'd':
      if(string(optarg).find_first_not_of("0123456789:") == std::string::npos){
	settings.addValue("duration", optarg);
      } else {
	cout<<"Invalid duration. Must be integer or hh:mm:ss\n";
	exit(0);
      }
      break;
    case '0':
      if(strcmp (optarg,"POSITIVE")== 0){
	settings.addValue("polarity0", "POSITIVE");
      }else if(strcmp (optarg,"NEGATIVE")== 0){
	settings.addValue("polarity0", "NEGATIVE");
      } else{
	cout<<"Incorrect polarity for channel 0. Valid options are POSITIVE or NEGATIVE\n";
	exit(0);
      }      
      break;
    case '1':
      if(strcmp (optarg,"POSITIVE")== 0){
	settings.addValue("polarity1", "POSITIVE");
      }else if(strcmp (optarg,"NEGATIVE")== 0){
	settings.addValue("polarity1", "NEGATIVE");
      } else{
	cout<<"Incorrect polarity for channel 1. Valid options are POSITIVE or NEGATIVE\n";
	exit(0);
      }      
      break;
    case '2':
      if(strcmp (optarg,"POSITIVE")== 0){
	settings.addValue("polarity2", "POSITIVE");
      }else if(strcmp (optarg,"NEGATIVE")== 0){
	settings.addValue("polarity2", "NEGATIVE");
      } else{
	cout<<"Incorrect polarity for channel 2. Valid options are POSITIVE or NEGATIVE\n";
	exit(0);
      }      
      break;
    case '3':
      if(strcmp (optarg,"POSITIVE")== 0){
	settings.addValue("polarity3", "POSITIVE");
      }else if(strcmp (optarg,"NEGATIVE")== 0){
	settings.addValue("polarity3", "NEGATIVE");
      } else{
	cout<<"Incorrect polarity for channel 3. Valid options are POSITIVE or NEGATIVE\n";
	exit(0);
      }      
      break;
    case '4':
      if(strcmp (optarg,"POSITIVE")== 0){
	settings.addValue("polarity4", "POSITIVE");
      }else if(strcmp (optarg,"NEGATIVE")== 0){
	settings.addValue("polarity4", "NEGATIVE");
      } else{
	cout<<"Incorrect polarity for channel 4. Valid options are POSITIVE or NEGATIVE\n";
	exit(0);
      }      
      break;
    case '5':
      if(strcmp (optarg,"POSITIVE")== 0){
	settings.addValue("polarity5", "POSITIVE");
      }else if(strcmp (optarg,"NEGATIVE")== 0){
	settings.addValue("polarity5", "NEGATIVE");
      } else{
	cout<<"Incorrect polarity for channel 5. Valid options are POSITIVE or NEGATIVE\n";
	exit(0);
      }      
      break;
    case '6':
      if(strcmp (optarg,"POSITIVE")== 0){
	settings.addValue("polarity6", "POSITIVE");
      }else if(strcmp (optarg,"NEGATIVE")== 0){
	settings.addValue("polarity6", "NEGATIVE");
      } else{
	cout<<"Incorrect polarity for channel 6. Valid options are POSITIVE or NEGATIVE\n";
	exit(0);
      }      
      break;
    case '7':
      if(strcmp (optarg,"POSITIVE")== 0){
	settings.addValue("polarity7", "POSITIVE");
      }else if(strcmp (optarg,"NEGATIVE")== 0){
	settings.addValue("polarity7", "NEGATIVE");
      } else{
	cout<<"Incorrect polarity for channel 7. Valid options are POSITIVE or NEGATIVE\n";
	exit(0);
      }      
      break;
    case 'A':
      if(string(optarg).find_first_not_of("0123456789") == std::string::npos){
	settings.addValue("DCoffset0", optarg);
      } else{
	cout<<"Invalid DC offset option for channel 0. Must be numerical\n";
	exit(0);
      }
      break;
    case 'B':
      if(string(optarg).find_first_not_of("0123456789") == std::string::npos){
	settings.addValue("DCoffset1", optarg);
      } else{
	cout<<"Invalid DC offset option for channel 1. Must be numerical\n";
	exit(0);
      }      
      break;
    case 'C':
      if(string(optarg).find_first_not_of("0123456789") == std::string::npos){
	settings.addValue("DCoffset2", optarg);
      } else{
	cout<<"Invalid DC offset option for channel 2. Must be numerical\n";
	exit(0);
      }      
      break;
    case 'D':
      if(string(optarg).find_first_not_of("0123456789") == std::string::npos){
	settings.addValue("DCoffset3", optarg);
      } else{
	cout<<"Invalid DC offset option for channel 3. Must be numerical\n";
	exit(0);
      }      
      break;
    case 'E':
      if(string(optarg).find_first_not_of("0123456789") == std::string::npos){
	settings.addValue("DCoffset4", optarg);
      } else{
	cout<<"Invalid DC offset option for channel 4. Must be numerical\n";
	exit(0);
      }      
      break;
    case 'F':
      if(string(optarg).find_first_not_of("0123456789") == std::string::npos){
	settings.addValue("DCoffset5", optarg);
      } else{
	cout<<"Invalid DC offset option for channel 5. Must be numerical\n";
	exit(0);
      }      
      break;
    case 'G':
      if(string(optarg).find_first_not_of("0123456789") == std::string::npos){
	settings.addValue("DCoffset6", optarg);
      } else{
	cout<<"Invalid DC offset option for channel 6. Must be numerical\n";
	exit(0);
      }      
      break;
    case 'H':
      if(string(optarg).find_first_not_of("0123456789") == std::string::npos){
	settings.addValue("DCoffset7", optarg);
      } else{
	cout<<"Invalid DC offset option for channel 7. Must be numerical\n";
	exit(0);
      }      
      break;
    case 'I':
      if(string(optarg).find_first_not_of("-0123456789") == std::string::npos){
	settings.addValue("threshold0", optarg);
      } else{
	cout<<"Invalid trigger threshold for channel 0. Must be numerical\n";
	exit(0);
      }      
      break;
    case 'J':
      if(string(optarg).find_first_not_of("-0123456789") == std::string::npos){
	settings.addValue("threshold1", optarg);
      } else{
	cout<<"Invalid trigger threshold for channel 1. Must be numerical\n";
	exit(0);
      }      
      break;
    case 'K':
      if(string(optarg).find_first_not_of("-0123456789") == std::string::npos){
	settings.addValue("threshold2", optarg);
      } else{
	cout<<"Invalid trigger threshold for channel 2. Must be numerical\n";
	exit(0);
      }      
      break;
    case 'L':
      if(string(optarg).find_first_not_of("-0123456789") == std::string::npos){
	settings.addValue("threshold3", optarg);
      } else{
	cout<<"Invalid trigger threshold for channel 3. Must be numerical\n";
	exit(0);
      }      
      break;
    case 'M':
      if(string(optarg).find_first_not_of("-0123456789") == std::string::npos){
	settings.addValue("threshold4", optarg);
      } else{
	cout<<"Invalid trigger threshold for channel 4. Must be numerical\n";
	exit(0);
      }      
      break;
    case 'N':
      if(string(optarg).find_first_not_of("-0123456789") == std::string::npos){
	settings.addValue("threshold5", optarg);
      } else{
	cout<<"Invalid trigger threshold for channel 5. Must be numerical\n";
	exit(0);
      }      
      break;
    case 'O':
      if(string(optarg).find_first_not_of("-0123456789") == std::string::npos){
	settings.addValue("threshold6", optarg);
      } else{
	cout<<"Invalid trigger threshold for channel 6. Must be numerical\n";
	exit(0);
      }      
      break;
    case 'P':
      if(string(optarg).find_first_not_of("-0123456789") == std::string::npos){
	settings.addValue("threshold7", optarg);
      } else{
	cout<<"Invalid trigger threshold for channel 7. Must be numerical\n";
	exit(0);
      }      
      break;
    case 'Q':
      if(string(optarg).find_first_not_of("0123456789") == std::string::npos){
	settings.addValue("posttrigger", optarg);
      } else{
	cout<<"Invalid post trigger setting. Must be numerical\n";
	exit(0);
      }      
      break;
    case 'R':
      if(strcmp (optarg,"POSITIVE")== 0){
	settings.addValue("trslope0", "POSITIVE");
      }else if(strcmp (optarg,"NEGATIVE")== 0){
	settings.addValue("trslope0", "NEGATIVE");
      } else{
	cout<<"Incorrect trigger polarity for channel 0. Valid options are POSITIVE or NEGATIVE\n";
	exit(0);
      }      
      break;   
    case 'S':
      if(strcmp (optarg,"POSITIVE")== 0){
	settings.addValue("trslope1", "POSITIVE");
      }else if(strcmp (optarg,"NEGATIVE")== 0){
	settings.addValue("trslope1", "NEGATIVE");
      } else{
	cout<<"Incorrect trigger polarity for channel 1. Valid options are POSITIVE or NEGATIVE\n";
	exit(0);
      }      
      break;  
    case 'T':
      if(strcmp (optarg,"POSITIVE")== 0){
	settings.addValue("trslope2", "POSITIVE");
      }else if(strcmp (optarg,"NEGATIVE")== 0){
	settings.addValue("trslope2", "NEGATIVE");
      } else{
	cout<<"Incorrect trigger polarity for channel 2. Valid options are POSITIVE or NEGATIVE\n";
	exit(0);
      }      
      break;  
    case 'U':
      if(strcmp (optarg,"POSITIVE")== 0){
	settings.addValue("trslope3", "POSITIVE");
      }else if(strcmp (optarg,"NEGATIVE")== 0){
	settings.addValue("trslope3", "NEGATIVE");
      } else{
	cout<<"Incorrect trigger polarity for channel 3. Valid options are POSITIVE or NEGATIVE\n";
	exit(0);
      }      
      break;  
    case 'V':
      if(strcmp (optarg,"POSITIVE")== 0){
	settings.addValue("trslope4", "POSITIVE");
      }else if(strcmp (optarg,"NEGATIVE")== 0){
	settings.addValue("trslope4", "NEGATIVE");
      } else{
	cout<<"Incorrect trigger polarity for channel 4. Valid options are POSITIVE or NEGATIVE\n";
	exit(0);
      }      
      break;  
    case 'W':
      if(strcmp (optarg,"POSITIVE")== 0){
	settings.addValue("trslope5", "POSITIVE");
      }else if(strcmp (optarg,"NEGATIVE")== 0){
	settings.addValue("trslope5", "NEGATIVE");
      } else{
	cout<<"Incorrect trigger polarity for channel 5. Valid options are POSITIVE or NEGATIVE\n";
	exit(0);
      }      
      break;  
    case 'X':
      if(strcmp (optarg,"POSITIVE")== 0){
	settings.addValue("trslope6", "POSITIVE");
      }else if(strcmp (optarg,"NEGATIVE")== 0){
	settings.addValue("trslope6", "NEGATIVE");
      } else{
	cout<<"Incorrect trigger polarity for channel 6. Valid options are POSITIVE or NEGATIVE\n";
	exit(0);
      }      
      break;  
    case 'Y':
      if(strcmp (optarg,"POSITIVE")== 0){
	settings.addValue("trslope7", "POSITIVE");
      }else if(strcmp (optarg,"NEGATIVE")== 0){
	settings.addValue("trslope7", "NEGATIVE");
      } else{
	cout<<"Incorrect trigger polarity for channel 7. Valid options are POSITIVE or NEGATIVE\n";
	exit(0);
      }      
      break;   

      
    }
     
  }

  if(savedSettingsFile!=""){
    settings.writeXml(savedSettingsFile);
    cout<<"Saving specified settings.";
    if(quitAfterSettingSave){
      cout<< " Quitting\n";
      exit(0);
    }
    cout<<endl;
      
  }
  
  

  if(settingsFile!="")
    settings = XmlParser(settingsFile, verbose);


  return settings;




}
