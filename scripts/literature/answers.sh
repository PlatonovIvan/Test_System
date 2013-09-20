#!/bin/bash
let i=1
let j=1;
file="a_14"
let title=14
let question=1
number=`cat $file | wc -l`
plus="+"
echo $number

while [ $i -le $number ]; do 
	
	#+++++++++++++++++++++++++++++++++++++++++
	a_1=`cat $file | head -n$i | tail -n1`
	if { echo $a_1 | grep ^+ > /dev/null; }; then
		a_1=`echo $a_1 | sed 's/^+//'`
		correct=1
		echo $a_1
	fi
	let i=($i+1)
	
	#+++++++++++++++++++++++++++++++++++++++++
	a_2=`cat $file | head -n$i | tail -n1`
	if { echo $a_2 | grep ^+ >/dev/null; }; then
		a_2=`echo $a_2 | sed 's/^+//'`
		correct=2
		echo $a_2
	fi
	let i=($i+1)	
  	
	#+++++++++++++++++++++++++++++++++++++++++
	a_3=`cat $file | head -n$i | tail -n1`
	if { echo $a_3 | grep ^+ >/dev/null; }; then
		a_3=`echo $a_3 | sed 's/^+//'`
		correct=3
		echo $a_3
	fi
	let i=($i+1)

	#+++++++++++++++++++++++++++++++++++++++++
	a_4=`cat $file | head -n$i | tail -n1`
	if { echo $a_4 | grep ^+ >/dev/null; }; then
		a_4=`echo $a_4 | sed 's/^+//'`
		correct=4
		echo $a_4
	fi
	let i=($i+1)
	echo "correct $correct"
	sqlite3 test.db "insert into Answers values ($title, $question, \"$a_1\", \"$a_2\", \"$a_3\", \"$a_4\", $correct);" 
	
	let question=($question+1)
	let correct=0	
done
