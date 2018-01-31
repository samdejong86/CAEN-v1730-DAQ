# CAEN V1370 DAQ

## Description:

DAQ software for a CAEN V1730 digitizer with waveform recording firmware. Software assumes connection through a V1718 VME-USB Bridge

This software is based on the CAEN wavedump example program

## Installation:
Requires the CAEN Digitizer libraries. Install in this order:
1. CAEN VME library 
2. CAEN USB library 
3. CAEN Comm library
4. CAEN digitizer

Requires ROOT (available [here](https://root.cern.ch/downloading-root))

Once these are installed, use make to build the software.

## Usage:
	CAENdaq  [-h] [-v] [-x XMLFILE]
	optional arguments:
	  -h, --help                 Show this help message and exit
	  -v, --verbose              Prints verbose setup information
	  ---------------------------------------------------------------
  	  -w CH, --ch CH             Record the wavefrom on CH
             	                     Valid options are 0-7
	  -o FILE, --outfile FILE    Save waveform to FILE
  	  -r RECLEN, --reclen RECLEN Set recordlength to RECLEN
  	  -a BASEADDRESS, --baseaddress BASEADDRESS
             		             Set digitizer base address to BASEADDRESS
	  -d DURATION, --duration DURATION
				     Duration of the run. If an integer is
                             	     specified, that many events are recorded.
                             	     If a time is specified in HH:MM:SS format
                             	     the daq will run for that long. Acquisition
                             	     starts automatically.
                             	     If not used, daq must be started manually
          --polarity<CH> POLARITY    Set pulse polarity of channel CH
                                     Valid options are POSITIVE or NEGATIVE
          --DCoffset<CH> OFFSET      Set DC offset of channel CH in ADC counts
          --threshold<CH> THRESHOLD  Set the trigger threshold of channel CH
                             	     in ADC counts
          --trslope<CH> POLARITY     Trigger slope. Can be POSITIVE or NEGATIVE
          --posttrigger VAL          Set the post trigger
	  ---------------------------------------------------------------
  	  -x XMLFILE, --xml XMLFILE  Use settings in XMLFILE. This
                                     overrides other command line settings
          --xmlout XMLFILE           Save settings to xml file
          -q, --quit                 Used with --xmlout. Quits program after
                             	     saving settings

	 Long options between ------ can be used as xml tags in an xml settings file




## Files:

	src/
		source files
	include/
		header files
	xml/Settings.xml
		an example settings file
	Makefile
		for building the software
	draw.C
		A root script for drawing waveforms
	
