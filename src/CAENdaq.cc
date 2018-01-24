#include <iostream>
#include <getopt.h>

#include "CAENdaq.h"

//#include "DigitizerSettings.h"
#include "Digitizer.h"
#include "xmlParser.h"
#include "help.h"


int main(int argc, char *argv[]){

  string settingsFile="";
  bool verbose=false;

  int c; 
  
  while(true){
  
  static struct option long_options[] =
    {
      {"help",		no_argument,       0, 'h'},	// help
      {"verbose",	no_argument,       0, 'v'},	// verbose mode
      {"xml",   	required_argument, 0, 'x'},	// output file name
      {0, 0, 0, 0}
    };

    int option_index = 0;
    // leave case out of the list if no short option is to be allowed
    c = getopt_long (argc, argv, "hvx:", long_options, &option_index);

    if (c == -1)
    {
      break;					// end of the options
    }

    switch (c){
    case 0:
      if (long_options[option_index].flag != 0){
	break;
      }
    case 'h':
      printHelp(argv[0]);
      break;
    case 'v': 
      verbose=true;
      break;
    case 'x':
      settingsFile = optarg;
      break;
    }
     
  }
  

  
  
  Digitizer digi;

  if(settingsFile!=""){
    XmlParser settings(settingsFile, verbose);

    digi=Digitizer(settings);
    
  }
  

  

  //XmlParser settings("xml/Settings.xml", false);
  
  //Digitizer digi(settings);
  //Digitizer digi;
  if(verbose)
    cout<<digi;

  bool digiOpen = digi.OpenDigitizer();

  if(digiOpen){
    digi.Readout();   
    digi.CloseDigitizer();
  }



}
