#!/bin/bash
i=1
let theme=2
let number=`wc -l a2`
echo $number
j=1
while [ $i -le $number ]; do
	let correct=0
	a_1=`cat a2 | head -n$i | tail -n1`
	let i=$i+1
	a_2=`cat a2 | head -n$i | tail -n1`
	let i=$i+1
	a_3=`cat a2 | head -n$i | tail -n1`
	let i=$i+1
	a_4=`cat a2 | head -n$i | tail -n1`
	let i=$i+1
	#echo $a_1
	if echo $a_1 | grep -iq ^+ ; then
		a_1=`echo $a_1 | sed 's/^+//'`
		echo $a_1
		correct=1
	fi;
	if echo $a_2 | grep -iq ^+ ; then
		a_2=`echo $a_2 | sed 's/^+//'`
		echo $a_2
		correct=2
	fi;
	if echo $a_3 | grep -iq ^+ ; then
		a_3=`echo $a_3 | sed 's/^+//'`
		echo $a_3
		correct=3
	fi;
	if echo $a_4 | grep -iq ^+ ; then
		a_4=`echo $a_4 | sed 's/^+//'`	
		echo $a_4
		correct=4
	fi;
	echo $correct
	sqlite3 ../test.db "insert into Control_Answers values ($theme, $j, \"$a_1\", \"$a_2\", \"$a_3\", \"$a_4\", $correct);" 
	j=$j+1
done
