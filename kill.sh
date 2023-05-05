#!/bin/bash

if [ "$1" ]
then
	PID=`pidof $1`
	kill $PID
else
	PID=`pidof daemon`
	kill $PID
fi

