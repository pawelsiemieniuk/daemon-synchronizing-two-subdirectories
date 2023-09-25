#!/bin/bash

PID=`pidof sync2d`

if [[ -z $PID ]]
then
	echo "sync2d isn't running."
else
	kill -s SIGUSR1 $PID
fi
