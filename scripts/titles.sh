#!/bin/bash
let i=1
let theme=14
let number=`wc -l $theme`
echo $number
while [ $i -le $number ]; do 
	sqlite3 test.db "insert into Questions values ($theme, $i, \"`cat $theme | head -n$i | tail -n1`\");" 
	let i=($i+1)
done
