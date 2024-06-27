#!/bin/bash

echo "Thold  ReadsOver" >> PEBS.txt
for ((i = 1; i <= 250; i++))
do
    for ((n = 1; n <= 1; n++))
    do
    export PEBS_LD_LAT_THRESHOLD=0x3F6
    export CPU=18
    export CPU_MASK=0x40000
    wrmsr -p ${CPU} ${PEBS_LD_LAT_THRESHOLD} 0
    wrmsr -p ${CPU} ${PEBS_LD_LAT_THRESHOLD} $i
    ./laten2_proj.sh
    done
done
