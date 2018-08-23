#!/bim/bash

ProcLog="../log/proclog.log"
NowTime=`date +"%Y-%m-%d__%H:%M:%S"`
PID=`ps -aux -h | awk  '($3 > 20 || $4 > 50) {print $0}' | awk '{if(NR>1){printf(",")};{printf("%d",$2)}};'`
if [[ $PID ]]; then
    sleep 5
    else exit 0
fi
ps -aux -h -q $PID | \
    awk -v time=$NowTime '($3 > 20 || $4 >50)\
    {if(NR==1){printf("time\t\t\tPID\tUSER\tCPU\tMEM\tcommand\n")};\
    {printf("%s\t%s\t%s\t%s%%\t%s%%\t%s\n", time, $2, $1, $3, $4, $11)}}' >> $ProcLog

