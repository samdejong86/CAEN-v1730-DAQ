#include "fileManager.h"
#include <sstream>
#include <stdint.h>
#include <sys/stat.h>


void fileManager::init(string filename="CAEN.root", uint16_t EnableMask=0, int saveInt=100){
  string temp = filename;

  saveInterval=saveInt;

  
  string suffix=".root";
  size_t pos = temp.find(suffix);
  
  if (pos != std::string::npos) {
    // If found then erase it from string
    temp.erase(pos, suffix.length());
  }
  
  stringstream ss;
  ss<<int(util::markTime());
  dirname ="./temp_"+ss.str();
  ss.str();



  string makeCommand = "mkdir -p "+dirname;  
 
  int ret = system(makeCommand.c_str());
  if(ret!=0){
    cout<<"fileManager: Error creating temporary file directory"<<endl;
    exit(0);
  }
 


  
  fname=dirname+"/"+temp;  
  
  mask = bitset<8>(EnableMask);
  RunStartTime=0;
  isOpen=false;
  for(int i=0; i<8; i++){
    lastTrigTime[i]=0;
    nRollover[i]=0;
  }
  verbose=false;
}



void fileManager::OpenFile(){

  if(verbose){
    cout<<"fileManager: Opening "<<fname<<endl;
    cout<<"fileManager: Save interval: "<<saveInterval<<endl;
  }

  string firstFile = fname+"_0.root";

  f = new TFile(firstFile.c_str(), "RECREATE");  //open TFile
  t = new TTree("data", "Waveform data");  //initalize the TTree

  //resize the vector of vectors to have 4 entries
  data.resize(8);  

  counter=0;
  
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

  string files="";

  stringstream ss;
  for(int i=0; i<counter/saveInterval; i++){
    ss<<i;
    files += fname+"_"+ss.str()+".root ";
    ss.str("");
  }
  string targetFile = fname+".root";
  
  remove(targetFile.c_str());

  string command = "hadd -f "+targetFile+" "+files;
  
  if(verbose){
    cout<<"fileManager: Merging temporary files"<<endl;
  }
  int ret = system(command.c_str());
    
  if(ret!=0)
    cout<<"fileManager: Error with merger command"<<endl;
  
  
  for(int i=0; i<counter/saveInterval; i++){
    ss<<i;
    remove((fname+"_"+ss.str()+".root").c_str());
    ss.str("");
  }

  
  string moveCmd = "mv "+targetFile+" ./";
  ret = system(moveCmd.c_str());
  
  if(ret!=0)
    cout<<"fileManager: Unable to move output file"<<endl;

  
  DeleteDir();
  
  
  if(verbose)
    cout<<"fileManager: Closed "<<fname<<endl;
}


void fileManager::addEvent(CAEN_DGTZ_EventInfo_t *EventInfo, CAEN_DGTZ_UINT16_EVENT_t *Event16){

  
  if(!isOpen)
    return;

  if(counter!=0&&counter%saveInterval==0) OpenNewFile();
  
  for(int ch=0; ch<8; ch++){
    if(mask[ch]==0)
      continue;
    int Size=Event16->ChSize[ch];
    if(Size<=0)
      continue;

    for(int i=0; i<Size; i++){
      data[ch].push_back(Event16->DataChannel[ch][i]);
    }
    


    
    if(EventInfo->TriggerTimeTag<lastTrigTime[ch]){
      nRollover[ch]++;
      lastTrigTime[ch]=0;
           
    }else
      lastTrigTime[ch]=EventInfo->TriggerTimeTag;
  
    
    eventTime = (double)EventInfo->TriggerTimeTag*8e-9+RunStartTime+nRollover[ch]*rolloverAdd; 

  }

  t->Fill();
  
  for(int ch=0; ch<8; ch++)
    data[ch].clear();

  counter++;
  
}


void fileManager::OpenNewFile(){

  if(verbose){
    cout<<"fileManager: number of events so far = "<<counter<<endl;
  }

  t->Write(); //write the data ntuple
  f->Close();
  
  

  stringstream ss;
  ss<<counter/saveInterval;

  string thisFile=fname+"_"+ss.str()+".root";
  
  ss.str("");


  f = new TFile(thisFile.c_str(), "RECREATE");  //open TFile
  t = new TTree("data", "Waveform data");  //initalize the TTree

  //resize the vector of vectors to have 4 entries
  data.resize(8);  
    
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
  

}


void fileManager::DeleteDir(){
  string command = "rmdir "+dirname+"/";  

  int ret = system(command.c_str());
  if(ret!=0)
    cout<<"fileManager: Could not delete temporary directory"<<endl;
  
  
}
