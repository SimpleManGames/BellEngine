#!/bin/bash

if["$1" = "release"]
then
	../bin/Release-windows-x86_64/Sandbox $2 $3 $4 $5 $6 $7 $8 $9
else
	../bin/Debug-windows-x86_64/Sandbox $2 $3 $4 $5 $6 $7 $8 $9

fi
