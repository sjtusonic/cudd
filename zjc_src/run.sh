#!/bin/bash
echo "---------------------------"
echo "DELETE output files"
echo "---------------------------"
rm output.*
rm tutorial 
echo "---------------------------"
echo "COMPILING"
echo "---------------------------"
make > make.log 
ls -l tutorial 
echo "---------------------------"
echo "RUNNING"
echo "---------------------------"
./tutorial > run.log
echo "---------------------------"
echo "DOT2SVG"
echo "---------------------------"
#dot -Tsvg output.dot  -o output.svg
#ls -larth output.*
#set ll=`find | grep \.dot$`
ll=`find | grep \.dot$`
for i in $ll
do
	#set dot=$i
	dot=$i
	echo "GOT dot=$i"
	echo "dot -Tsvg $dot -o ${dot}.svg"
	dot -Tsvg $dot -o ${dot}.svg
done
