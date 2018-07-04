#include <iostream>
#include <getopt.h>

#include "CAENdaq.h"

//#include "DigitizerSettings.h"
#include "Digitizer.h"
#include "xmlParser.h"
#include "help.h"
#include "parseOpt.h"

volatile sig_atomic_t flag=0;

void my_function(int sig){ // can be called asynchronously
  flag = 1; // set flag
}


int main(int argc, char *argv[]){

  signal(SIGINT, my_function); 

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
