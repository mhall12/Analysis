#!/bin/bash

if [ $# -ne 1 ] 
  then
   echo "USAGE: sortmv.sh <merged folder>"
  exit 1
fi

DIR1="$1"
#401 402 403 404 
FileNums=(404 405 406 407 408 410 411 413 414 415 416 417 418 419 420 421 422 423 432 433 434 437 438 439 440 441 442 443 444 445 446 449 450 451 452 453 454 456 457 460 461 462 463 464 469 470 471 472 473 474 475 476 477 478 479 480 481 482 483 485 486 487 488 489 490 491 492 493 494)

for i in "${FileNums[@]}"
do
	echo "Now sorting run $i"
	./gebsort.sh $DIR1 $i rootfiles/TotalFiles sidetails=1 nohists config=goddess_SX3GainMatch_new_new.config nevents=all userfilter
	

	for file in /media/mhall12/Zeus/NewDAQ/goddess_daq/exec/rootfiles/TotalFiles/run$i*.root
	do
		if [ -e $file ] ; then
			rsync -ahP $file /media/ds1/TotalRootFiles/
		
			rm $file

		else echo "No files found for run $i"
		fi
	done

done

: <<'END'

END


