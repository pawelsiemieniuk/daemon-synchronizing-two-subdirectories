#!/bin/bash

if [ "$1" ]
then
	PID=`pidof $1`
	kill -s SIGUSR1 $PID
else
	echo No process name given.
fi