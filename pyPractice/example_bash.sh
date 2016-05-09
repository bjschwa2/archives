#!/bin/bash
NAME=$1
GREETING="Greetings!"
NOD_HEAD="*Nod the head*"
SHAKE_HEAD="*Shake head*"

if [ "$NAME" = "Bradley" ]; then
	echo $GREETING
elif [ "$Name" = "John" ]; then
	echo $NOD_HEAD
else 
	echo $SHAKE_HEAD
fi