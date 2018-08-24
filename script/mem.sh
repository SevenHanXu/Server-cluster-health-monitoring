#!/bin/bash

function Usage() {
	echo "Usage: $0 DyAver"
}

if [[ $# -lt 1 ]]; then
	Usage
	exit 1
fi

DyAver=$1;

NowTime=`date +"%Y-%m-%d__%H:%M:%S"`
MemValue=`free -m | tail -2 | head -1 | awk  '{printf("%dM %dM", $2, $3)}'`
AveValue=`free -m | tail -2 | head -1 | awk '{printf("%.1f", $3*100/$2)}'`
MemAvePrec=`echo 1 | awk -v a=$AveValue b=$DyAver'{printf("%.1f", a * 0.8 + b * 0.2)}'`


echo "$NowTime $MemValue  $AveValue% $MemAvePrec%"
