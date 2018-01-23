#include <iostream>

#include "CAENdaq.h"

//#include "DigitizerSettings.h"
#include "Digitizer.h"
#include "xmlParser.h"



int main(int argc, char *argv[]){

  Digitizer digi;

  digi.OpenDigitizer();

  digi.Readout();
   
  digi.CloseDigitizer();
  

  
  cout<<"Hello World"<<endl;









}
