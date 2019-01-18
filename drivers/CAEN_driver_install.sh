
#untar the archives
for tar in *.tgz
do
    tar zxvf $tar
done


errorVME="$(ls CAENVME* 2>&1)"
if [[ $errorVME = *"No such file"* ]]; then
    echo "CAEN VME library not found!"
else
    array=()
    while IFS=  read -r -d $'\0'; do
	array+=("$REPLY")
    done < <(find . -type d -name "CAENVME*" -print0)

    cd ${array[0]}/lib
    echo
    echo "installing CAEN VME library"
    pwd
    sudo sh install_x64
    cd $OLDPWD
    unset array

    errorUSB="$(ls CAENUSB* 2>&1)"
    if [[ $errorUSB = *"No such file"* ]]; then
	echo "CAEN USB library not found!"
    else
	array=()
	while IFS=  read -r -d $'\0'; do
	    array+=("$REPLY")
	done < <(find . -type d -name "CAENUSB*" -print0)

	cd ${array[0]}
	echo
	echo "installing CAEN USB library"
	pwd
	make
	sudo make install
	cd $OLDPWD
	unset array
	
	errorComm="$(ls CAENComm* 2>&1)"
	if [[ $errorComm = *"No such file"* ]]; then
	    echo "CAEN Comm library not found!"
	else
	    array=()
	    while IFS=  read -r -d $'\0'; do
		array+=("$REPLY")
	    done < <(find . -type d -name "CAENComm*" -print0)
	    	    
	    cd ${array[0]}/lib
	    echo
	    echo "installing CAEN Comm library"
	    pwd
	    sudo sh install_x64
	    cd $OLDPWD

	    unset array
	    
	    errorDigi="$(ls CAENDigitizer* 2>&1)"
	    if [[ $errorComm = *"No such file"* ]]; then
		echo "CAEN Digitizer library not found!"
	    else
		array=()
		while IFS=  read -r -d $'\0'; do
		    array+=("$REPLY")
		done < <(find . -type d -name "CAENDigitizer*" -print0)
		
		cd ${array[0]}
		echo
		echo "installing CAEN Digitizer library"		
		pwd
		sudo sh install_64
		cd $OLDPWD
		unset array
	   fi
       fi	   
   fi
fi








