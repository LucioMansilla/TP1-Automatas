

LOGFILE="exec/logs"

cd ..

# Compile project
cmake -E make_directory build && cmake -E chdir build cmake .. && cmake --build build

# Change back to TP-AUTOMATAS/C/tests directory
cd tests

./exec/test_concat >> $LOGFILE
if [ $? -eq 1 ]
then
 echo "test_concat passed"
else
 echo "test_concat failed"
fi


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



./exec/test_union >> $LOGFILE
if [ $? -eq 1 ]
then
 echo "test_union passed"
else
 echo "test_union failed"
fi

./exec/test_kleene >> $LOGFILE
if [ $? -eq 1 ]
then
 echo "test_kleene passed"
else
 echo "test_kleene failed"
fi

./exec/test_tp1 >> $LOGFILE
if [ $? -eq 1 ]
then
 echo "test_tp1 passed"
else
 echo "test_tp1 failed"
fi

./exec/test_tp2 >> $LOGFILE
if [ $? -eq 1 ]
then
 echo "test_tp2 passed"
else
 echo "test_tp2 failed"
fi

./exec/test_minimize >> $LOGFILE
if [ $? -eq 1 ]
then
 echo "test_minimize passed"
else
 echo "test_minimize failed"
fi




echo "Tests finished. Check $LOGFILE for more information"