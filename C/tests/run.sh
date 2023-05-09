

LOGFILE="exec/logs"

cd ..

# Compile project
cmake -E make_directory build && cmake -E chdir build cmake .. && cmake --build build

# Change back to TP-AUTOMATAS/C/tests directory
cd tests


./exec/test_afnd_to_afd > $LOGFILE
if [ $? -eq 1 ]
then
 echo "test_afnd_to_afd passed"
else
 echo "test_afnd_to_afd failed"
fi

./exec/test_build >> $LOGFILE
if [ $? -eq 1 ]
then
 echo "test_build passed"
else
 echo "test_build failed"
fi

./exec/test_build_from_dot >> $LOGFILE
if [ $? -eq 1 ]
then
 echo "test_build_from_dot passed"
else
 echo "test_build_from_dot failed"
fi

./exec/test_pertains >> $LOGFILE
if [ $? -eq 1 ]
then
 echo "test_pertains passed"
else
 echo "test_pertains failed"
fi

./exec/test_strings_pertains >> $LOGFILE
if [ $? -eq 1 ]
then
 echo "test_strings_pertains passed"
else
 echo "test_strings_pertains failed"
fi



./exec/test_read_and_write >> $LOGFILE
if [ $? -eq 1 ]
then
 echo "test_read_and_write passed"
else
 echo "test_read_and_write failed"
fi


echo "Tests finished. Check $LOGFILE for more information"