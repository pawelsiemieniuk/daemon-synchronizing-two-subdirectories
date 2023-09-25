#!/bin/bash

PID=`pidof sync2d`

if [[ -z $PID ]]
then
	echo "sync2d isn't running."
else
	kill $PID
fi

