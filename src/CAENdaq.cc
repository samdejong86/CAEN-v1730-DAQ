#include <iostream>

#include "CAENdaq.h"

//#include "DigitizerSettings.h"
#include "Digitizer.h"
#include "xmlParser.h"



int main(int argc, char *argv[]){

  XmlParser settings("xml/Settings.xml", false);
  
  Digitizer digi(settings);
  //Digitizer digi;

  cout<<digi;
  
  digi.OpenDigitizer();

  digi.Readout();
   
  digi.CloseDigitizer();

  




}
