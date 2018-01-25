#include <CAENDigitizer.h>
#include <CAENDigitizerType.h>

#include "CAENdaq.h"
#include "xmlParser.h"
#include "fileManager.h"

using namespace std;

#ifndef DIGITIZER_h
#define DIGITIZER_h



class Digitizer{

 public:

  Digitizer(){
    DefaultSettings();
  };
  
  Digitizer(XmlParser settings);

  ~Digitizer(){}

  void DefaultSettings();
  bool OpenDigitizer();
  void Readout();
  void CloseDigitizer();
  void CheckKeyboardCommands();

  void startAcq();
  
  CAEN_DGTZ_ErrorCode ProgramDigitizer();  
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
  int nevent;
  uint32_t RecordLength;
  int PostTrigger;
  int InterruptNumEvents;
  int TestPattern;
  CAEN_DGTZ_IOLevel_t FPIOtype;
  CAEN_DGTZ_TriggerMode_t ExtTriggerMode;
  uint16_t EnableMask;
  
  CAEN_DGTZ_TriggerMode_t ChannelTriggerMode[MAX_SET];
  CAEN_DGTZ_PulsePolarity_t PulsePolarity[MAX_SET];
  CAEN_DGTZ_TriggerPolarity_t TrigPolarity[MAX_SET];
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

  fileManager fman;
  string fname;

  double RunStartTime;
  double nowTime;

  bool eventLimit;
  bool timeLimit;
  int numOfEvents;
  int DurationOfRun;
  bool startImmed;


  
  
};

static const string errors[34] = {"Operation completed successfully", //0
				  "Communication error",  //1
				  "Unspecified error", //2
				  "Invalid parameter", //3
				  "Invalid Link Type", //4
				  "Invalid device handler", //5
				  "Maximum number of devices exceeded", //6
				  "Operation not allowed on this type of board", //7
				  "The interrupt level is not allowed", //8
				  "The event number is bad", //9
				  "Unable to read the registry", //10
				  "Unable to write into the registry", //11
				  "", //12
				  "The Channel is busy", //13
				  "The channel number is invalid", //14
				  "Invalid FPIO Mode", //15
				  "Wrong acquisition mode",//16
				  "This function is not allowed for this module",//17
				  "Communication Timeout",//18
				  "The buffer is invalid", //19
				  "The event is not found", //20
				  "The event is invalid", //21
				  "Out of memory", //22
				  "Unable to calibrate the board", //23
				  "Unable to open the digitizer", //24
				  "The Digitizer is already open", //25
				  "The Digitizer is not ready to operate", //26 
				  "The Digitizer has not the IRQ configured",//27
				  "The digitizer flash memory is corrupted",//28
				  "The digitizer DPP firmware is not supported in this lib version", //29
				  "Invalid Firmware License",//30
				  "The digitizer is found in a corrupted status",//31
				  "The given trace is not supported by the digitizer", //32
				  "The given probe is not supported for the given digitizer's trace"}; //33

#endif

