#include "fileManager.h"
#include <sstream>
#include <stdint.h>

fileManager::fileManager(){
  fname="CAEN.root";
  mask = bitset<8>(0);
  RunStartTime=0;
  isOpen=false;
  lastTrigTime=0;
  nRollover=0;
}

fileManager::fileManager(string filename, uint16_t EnableMask){
  fname = filename;
  mask = bitset<8>(EnableMask);
  RunStartTime=0;
  isOpen=false;
  lastTrigTime=0;
  nRollover=0;
}



void fileManager::OpenFile(){

  f = new TFile(fname.c_str(), "RECREATE");  //open TFile
  t = new TTree("data", "Waveform data");  //initalize the TTree

  //resize the vector of vectors to have 4 entries
  data.resize(8);  

  stringstream ss;
  
  //add vectors to TTree
  for(int i=0; i<8; i++){
    ss<<i;
    string branch="ch"+ss.str();
    ss.str("");
    if(mask[i]==1){
      t->Branch(branch.c_str(), &data[i]);
    }
  }

  //time is the unix time that the event occured
  t->Branch("time", &eventTime, "time/D");
  t->Branch("xinc", &xinc, "xinc/D");

  xinc=2e-9;

  isOpen=true;
  
}

void fileManager::CloseFile(){
  if(isOpen){
    t->Write();
    f->Close();
  }
}


void fileManager::addEvent(CAEN_DGTZ_EventInfo_t *EventInfo, CAEN_DGTZ_UINT16_EVENT_t *Event16){

  if(!isOpen)
    return;
  
  for(int ch=0; ch<8; ch++){
    if(mask[ch]==0)
      continue;
    int Size=Event16->ChSize[ch];
    if(Size<=0)
      continue;

    for(int i=0; i<Size; i++){
      data[ch].push_back(Event16->DataChannel[ch][i]);
    }
    

    eventTime = (double)EventInfo->TriggerTimeTag*1.0e-8+RunStartTime+nRollover*rolloverAdd; 

    
    if(EventInfo->TriggerTimeTag<lastTrigTime){
      nRollover++;
      lastTrigTime=0;
      
    }else
      lastTrigTime=EventInfo->TriggerTimeTag;
  
    

  }

  t->Fill();
  
  for(int ch=0; ch<8; ch++)
    data[ch].clear();


}
