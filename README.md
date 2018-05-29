# CAEN V1370 DAQ

## Description:

DAQ software for a CAEN V1730 digitizer with waveform recording firmware. Software assumes connection through a V1718 VME-USB Bridge

This software is based on the CAEN wavedump example program

## Installation:
Requires the CAEN Digitizer libraries. Install in this order:
1. [CAEN VME library](http://www.caen.it/csite/CaenProd.jsp?idmod=689&parent=38) 
2. [CAEN USB library](http://www.caen.it/csite/CaenProd.jsp?idmod=417&parent=11)
3. [CAEN Comm library](http://www.caen.it/csite/CaenProd.jsp?parent=38&idmod=684)
4. [CAEN digitizer](http://www.caen.it/csite/CaenProd.jsp?parent=43&idmod=717)

**Note:** Updates to your system may break the CAEN libraries. If the DAQ software stops working, try reinstalling the VME and USB libraries.

Requires ROOT (available [here](https://root.cern.ch/downloading-root)). You may need these libraries:
1. libX11-devel.x86_64
2. libXpm-devel.x86_64
3. libXft-devel.x86_64
4. libXext-devel.x86_64

* If you are getting an error about 'shape.h', try:

        ln -s /usr/include/X11/extensions/shapeproto.h /usr/include/X11/extensions/shape.h


Once these are installed, use make to build the software.

## Usage:

    usage: CAENdaq  [-h] [-v] [-x XMLFILE] [--xmlout XMLFILE] [-q] [w0] [w1]
                    [w2] [w3] ... [-o FILE] [-r RECLEN] [-a BASEADDRESS] 
                    [-n NUM] [-d DURATION] [--posttrigger VAL]
                    [--polarity0 POLARITY] ... [--DCoffset0 OFFSET] ...
                    [--threshold0 THRESHOLD] ... [--trslope0 POLARITY] ... 

    Reads waveforms from a CAEN V1730 digitizer.

    Mandatory arguments to long options are mandatory for short options too.
      -h, --help                 Show this help message and exit
      -v, --verbose              Prints verbose setup information
      -x XMLFILE, --xml XMLFILE  Use settings in XMLFILE. This
                                 overrides other command line settings
      --xmlout XMLFILE           Save settings to xml file
      -q, --quit                 Used with --xmlout. Quits program after
                                 saving settings

     The following options can also be set using an XML file, with the
     long options as the XML tags:
      -w<CH>, --ch<CH>           Record the waveform on CH
                                 Valid options are 0-7
      -o FILE, --outfile FILE    Save waveform to FILE
      -n NUM, --saveInterval     After NUM events, save a temporary file.
                                 At the end of the run, these will be merged
      -r RECLEN, --reclen RECLEN Set number of samples recorded to RECLEN
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


### Note
   When the program starts, it will create a temporary directory called temp_`<timestamp>`, where `<timestamp>` is the unix time when the program started. Temporary root files containing `<saveInterval>` events will be saved here.

When the program exits safely these files will be merged together, with the resulting file moved to the working directory. The temporary directory will then be removed. 

If the program crashes, the temporary files will not be removed, so most of the data from the run can be salvaged by looking in this directory.

## Files:

	src/
		source files
	include/
		header files
	xml/Settings.xml
		an example settings file
	icon/CAEN.png
		Icon for the notification
	Makefile
		for building the software
	draw.C
		A root script for drawing waveforms
	
## Acknowledgements 

This software used code in CAEN's wavedump example, modified to be in an object oriented framework.


