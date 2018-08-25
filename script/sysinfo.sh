#!/bin/bash

NowTime=`date +"%Y-%m-%d__%H:%M:%S"`

HostName=`hostname`

OsType=`cat /etc/issue.net | tr -s ' ' '_'`

Kernel=`uname -r`

UpTime=`uptime -p | tr -s ' ' '_'`

LoadAvg=`cat /proc/loadavg | cut -d ' ' -f 1-3`

DiskSum=(`df -T -m | grep -v tmpfs | tail -n +2 | awk '{sum1+=$3;sum2+=$4;}END{print sum1,sum2}'`)

DiskUser=$[ ${DiskSum[1]} * 100 / ${DiskSum[0]} ]

eval $(free -m | tail -n +2 | head -1 | awk '{printf("MemSum=%d; MemUser=%d", $2, $3*100/$2)}')

Cuptemp=`cat /sys/class/thermal/thermal_zone0/temp | awk '{printf("%d", $1 / 1000)}'`

Warning=(normal noet Warning)

WarNum=(`echo 1 | awk -v disk=$DiskUser -v mem=$MemUser -v cpu=$Cuptemp \
    '{diskwar+=(disk>50)+(disk>70);memwar+=(mem>50)+(mem>70);cpuwar+=(cpu>50)+(cpu>70);}\
    END{print diskwar,memwar,cpuwar}'`)

echo $NowTime $HostName $OsType $Kernel $UpTime $LoadAvg $DiskSum $DiskUser% $MemSum $MemUser% \
    ${Warning[${WarNum[1]}]} ${Warning[${WarNum[2]}]} ${Warning[${WarNum[3]}]}
