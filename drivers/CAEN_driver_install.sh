
#untar the archives
for tar in *.tgz
do
    tar zxvf $tar
done


errorVME="$(ls CAENVME* 2>&1)"
if [[ $errorVME = *"No such file"* ]]; then
    echo "CAEN VME library not found!"
else
   cd CAENVME*/lib
   echo "installing CAEN VME library"
   sh install_x64
   cd $OLDPWD

   errorUSB="$(ls CAENUSB* 2>&1)"
   if [[ $errorUSB = *"No such file"* ]]; then
       echo "CAEN USB library not found!"
   else
       cd CAENUSB*
       echo "installing CAEN USB library"
       make
       make install
       cd $OLDPWD

       errorComm="$(ls CAENComm* 2>&1)"
       if [[ $errorComm = *"No such file"* ]]; then
	   echo "CAEN Comm library not found!"
       else
	   cd CAENComm*/lib
	   echo "installing CAEN Comm library"
	   sh install_x64
	   cd $OLDPWD
	   
	   errorDigi="$(ls CAENDigitizer* 2>&1)"
	   if [[ $errorComm = *"No such file"* ]]; then
	       echo "CAEN Digitizer library not found!"
	   else
	       cd CAENDigitizer*
	       echo "installing CAEN Digitizer library"
	       sh install_64
	       cd $OLDPWD
	   fi
       fi	   
   fi
fi









