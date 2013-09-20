#!/bin/bash
let i=1
file="l_15"
theme=15
type=1
let number=`wc -l $file`
echo $number
while [ $i -le $number ]; do 
	sqlite3 test.db "insert into Literature values ($theme, ($i), $type, \"\", \"`cat $file | head -n$i | tail -n1`\");" 
	let i=($i+1)
done
