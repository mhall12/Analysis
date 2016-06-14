#!/bin/bash

if [ $# -ne 1 ] 
  then
   echo "USAGE: sortmv.sh <merged folder>"
  exit 1
fi

DIR1="$1"

for i in {469..483}
do
	echo "Now sorting run $i"
	./gebsort.sh $DIR1 $i
done

for i in {485..494}
do
	echo "Now sorting run $i"
	./gebsort.sh $DIR1 $i
done


