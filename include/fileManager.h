#include <vector>
#include <bitset>
#include <CAENDigitizer.h>
#include <CAENDigitizerType.h>

#include "TFile.h"
#include "TTree.h"

#include "CAENdaq.h"


using namespace std;

#ifndef FILEMAN_h
#define FILEMAN_h

class fileManager{

 public:
  fileManager(){
    fname="CAEN.root";
    mask = bitset<8>(0);
  }
  fileManager(string filename, uint16_t EnableMask){
    fname = filename;
    mask = bitset<8>(EnableMask);
  }

  void OpenFile();
  void addEvent(CAEN_DGTZ_EventInfo_t *EventInfo, CAEN_DGTZ_UINT16_EVENT_t *Event16);
  void CloseFile();
  
 private:
  
  string fname;
  TFile *f;
  TTree *t;

  vector<vector<double> > data;
  uint32_t TriggerTimeTag;

  bitset<8> mask;

};

#endif
