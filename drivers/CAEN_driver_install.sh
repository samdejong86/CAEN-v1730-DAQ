
#untar the archives
for tar in *.tgz
do
    tar zxvf $tar
done


errorVME="$(ls CAENVME* 2>&1)"
if [[ $errorVME = *"No such file"* ]]; then
    echo "CAEN VME library not found!"
else
    a=$(find ./ -type d -name "CAENVME*")
    cd $a/lib
    echo
    echo "installing CAEN VME library"
    pwd
    sudo sh install_x64
    cd $OLDPWD

    errorUSB="$(ls CAENUSB* 2>&1)"
    if [[ $errorUSB = *"No such file"* ]]; then
	echo "CAEN USB library not found!"
    else
       a=$(find ./ -type d -name "CAENUSB*")
       cd $a
       echo
       echo "installing CAEN USB library"
       pwd
       make
       sudo make install
       cd $OLDPWD

       errorComm="$(ls CAENComm* 2>&1)"
       if [[ $errorComm = *"No such file"* ]]; then
	   echo "CAEN Comm library not found!"
       else
	   a=$(find ./ -type d -name "CAENComm*")
	   cd $a/lib
	   echo
	   echo "installing CAEN Comm library"
	   pwd
	   sudo sh install_x64
	   cd $OLDPWD
	   
	   errorDigi="$(ls CAENDigitizer* 2>&1)"
	   if [[ $errorComm = *"No such file"* ]]; then
	       echo "CAEN Digitizer library not found!"
	   else
	       a=$(find ./ -type d -name "CAENDigitizer*")
	       cd $a
	       pwd
	       echo
	       echo "installing CAEN Digitizer library"
	       sudo sh install_64
	       cd $OLDPWD
	   fi
       fi	   
   fi
fi

#remove temporary directories
rm -r ./CAEN*/







