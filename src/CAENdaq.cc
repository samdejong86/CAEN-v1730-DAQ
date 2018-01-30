#include <iostream>
#include <getopt.h>

#include "CAENdaq.h"

//#include "DigitizerSettings.h"
#include "Digitizer.h"
#include "xmlParser.h"
#include "help.h"
#include "parseOpt.h"


int main(int argc, char *argv[]){


  XmlParser settings = getOpt(argc, argv);
    
  
  Digitizer digi(settings);

  
  if(verbose){
    cout<<digi;
    digi.setVerbose(verbose);
  }
  bool digiOpen = digi.OpenDigitizer();

  if(digiOpen){
    digi.Readout();   
    digi.CloseDigitizer();
  }



}
