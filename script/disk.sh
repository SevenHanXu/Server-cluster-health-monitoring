#!/bin/bash 

DiskLog="../log/disk.log"
NowTime=`date +"%Y-%m-%d__%H:%M:%S"`
list=(`df -T -m | grep -v tmpfs | grep dev`)
MaxIndex=`df -T -m | grep -v tmpfs | grep dev| wc -l | awk '{print $1}'`
parname=(`df -T -m | grep -v tmpfs | grep dev | awk '{print $1}'`)
paramount=(`df -T -m | grep -v tmpfs | grep dev | awk '{print $3}'`)
parleft=(`df -T -m | grep -v tmpfs | grep dev | awk '{print $4}'`)
usedperc=(`df -T -m | grep -v tmpfs | grep dev | awk '{print $6}'`)

for (( i = 0; i < MaxIndex; i++)); do
    echo -e "$NowTime 1 ${parname[$i]}\t${paramount[$i]}\t${parleft[$i]}\t${usedperc[$i]}" >> $DiskLog
    disksum=$[ $disksum + ${paramount[$i]} ] 
    diskleft=$[ $diskleft + ${parleft[$i]}]
done
echo -e "$NowTime 0 disk\t\t$disksum\t$diskleft\t${usedperc[$i]}$[($diskleft * 100 /$disksum)]%" >> $DiskLog


