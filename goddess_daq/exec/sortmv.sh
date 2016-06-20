#!/bin/bash

if [ $# -ne 1 ] 
  then
   echo "USAGE: sortmv.sh <merged folder>"
  exit 1
fi

DIR1="$1"

for i in {401..404}
do
	echo "Now sorting run $i"
	./gebsort.sh $DIR1 $i
done

for i in {406..408}
do
	echo "Now sorting run $i"
	./gebsort.sh $DIR1 $i
done

for i in {419..423}
do
	echo "Now sorting run $i"
	./gebsort.sh $DIR1 $i
done

for i in {432..446}
do
	echo "Now sorting run $i"
	./gebsort.sh $DIR1 $i
done

for i in {449..454}
do
	echo "Now sorting run $i"
	./gebsort.sh $DIR1 $i
done

for i in {456..457}
do
	echo "Now sorting run $i"
	./gebsort.sh $DIR1 $i
done

for i in {460..464}
do
	echo "Now sorting run $i"
	./gebsort.sh $DIR1 $i
done

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

