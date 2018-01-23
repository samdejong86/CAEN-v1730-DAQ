#include <CAENDigitizer.h>
#include <CAENDigitizerType.h>

#include "CAENdaq.h"
#include "xmlParser.h"

using namespace std;

#ifndef DIGITIZER_h
#define DIGITIZER_h



class Digitizer{

 public:

  Digitizer(){
    DefaultSettings();
  };
  
  Digitizer(XmlParser settings);


  void DefaultSettings();
  void OpenDigitizer();
  void Readout();
  void CloseDigitizer();

  void CheckKeyboardCommands();
  
  
  CAEN_DGTZ_ErrorCode ProgramDigitizer();
  CAEN_DGTZ_ErrorCode WriteOutputFiles(CAEN_DGTZ_EventInfo_t *EventInfo, CAEN_DGTZ_UINT16_EVENT_t *event);
  
  CAEN_DGTZ_ErrorCode Calibrate_DC_Offset();
  CAEN_DGTZ_ErrorCode WriteRegisterBitmask(uint32_t address, uint32_t data, uint32_t mask);
  CAEN_DGTZ_ErrorCode SetCorrectThreshold();

  void printOn(ostream & out) const;

  friend ostream& operator<<(ostream& os, const Digitizer& r);
    
 private:
    
  int  handle = -1;
  CAEN_DGTZ_BoardInfo_t       BoardInfo;
  CAEN_DGTZ_ErrorCode ret;

  //from waveformconfig
  CAEN_DGTZ_ConnectionType LinkType;
  int LinkNum;
  int ConetNode;
  int BaseAddress;
  int Nch;
  int Nbit;
  float Ts;
  int NumEvents;
  uint32_t RecordLength;
  int PostTrigger;
  int InterruptNumEvents;
  int TestPattern;
  CAEN_DGTZ_IOLevel_t FPIOtype;
  CAEN_DGTZ_TriggerMode_t ExtTriggerMode;
  uint16_t EnableMask;
  
  CAEN_DGTZ_TriggerMode_t ChannelTriggerMode[MAX_SET];
  CAEN_DGTZ_PulsePolarity_t PulsePolarity[MAX_SET];
  uint32_t DCoffset[MAX_SET];
  uint32_t Threshold[MAX_SET];
  int Version_used[MAX_SET];
  
  int GWn;
  uint32_t GWaddr[MAX_GW];
  uint32_t GWdata[MAX_GW];
  uint32_t GWmask[MAX_GW];
  

  


  //from WDrun:
  int Quit;
  int AcqRun;
  int PlotType;
  int ContinuousTrigger;
  int ContinuousWrite;
  int SingleWrite;
  int Restart;
  int RunHisto;
  FILE *fout[MAX_CH];


  
  int cal_ok[MAX_CH];
  int dc_file[MAX_CH];
  int thr_file[MAX_CH];


  
  uint64_t CurrentTime, PrevRateTime, ElapsedTime;
  uint32_t AllocatedSize, BufferSize, NEvents;
  int isVMEDevice, MajorNumber;
  int nCycles= 0;
    
  CAEN_DGTZ_EventInfo_t       EventInfo;

  CAEN_DGTZ_UINT16_EVENT_t    *Event16; 

  //int ch;
  int Nb=0;
  int Ne=0;
  char *buffer;
  char *EventPtr;
  
  
};


#endif

