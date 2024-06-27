#!/bin/bash

# (Architectural Version 1)
export PMC0=0x0C1
export PMC1=0x0C2
export PMC2=0x0C3
export PMC3=0x0C4
export PERFEVTSEL0=0x186
export PERFEVTSEL1=0x187
export PERFEVTSEL2=0x188
export PERFEVTSEL3=0x189

# (Architectural Version 2)
export PERF_GLOBAL_CTRL=0x38F
export PERF_GLOBAL_STATUS=0x38E
export PERF_GLOBAL_OVF_CTRL=0x390
export DEBUGCTL=0x1D9
export FIXED_CTR_CTRL=0x38D

# (Sandy Bridge Specific)
export PEBS_ENABLE=0x3F1
#export PEBS_LD_LAT_THRESHOLD=0x3F6
export MISC_ENABLE=0x1A0
export PERF_CAPABILITIES=0x345

#Extra counters
#Instructions Retired/Any
export FIXED_CTR0=0x309
#CPU Clock / unhalted core
export FIXED_CTR1=0x30A
#CPU Clock / unhalted ref
export FIXED_CTR2=0x30B
export D5_AREA=0x600

#Using isolated cpu18
#export CPU=18
#export CPU_MASK=0x40000

#echo "Turning everyting off..."

wrmsr -p ${CPU} ${PERF_GLOBAL_CTRL} 0
wrmsr -p ${CPU} ${PERF_GLOBAL_OVF_CTRL} 0

wrmsr -p ${CPU} ${PERFEVTSEL0} 0
wrmsr -p ${CPU} ${PERFEVTSEL1} 0
wrmsr -p ${CPU} ${PERFEVTSEL2} 0
wrmsr -p ${CPU} ${PERFEVTSEL3} 0

wrmsr -p ${CPU} ${FIXED_CTR_CTRL} 0
wrmsr -p ${CPU} ${FIXED_CTR0} 0
wrmsr -p ${CPU} ${FIXED_CTR1} 0
wrmsr -p ${CPU} ${FIXED_CTR2} 0

wrmsr -p ${CPU} ${PEBS_ENABLE} 0
#wrmsr -p ${CPU} ${PEBS_LD_LAT_THRESHOLD} 0

#echo "Sleeping for 5 seconds..."
#sleep 5


#echo "Enabling fixed function counters and running stomp (~20 seconds)."
wrmsr -p ${CPU} ${FIXED_CTR_CTRL} 0x222
wrmsr -p ${CPU} ${PERF_GLOBAL_CTRL} 0x700000000
wrmsr -p ${CPU} ${PERF_GLOBAL_CTRL} 0
wrmsr -p ${CPU} ${FIXED_CTR_CTRL} 0
#echo "Instructions Retired (any):  " `rdmsr -p ${CPU} ${FIXED_CTR0}`
#echo "Unhalted core clocks:        " `rdmsr -p ${CPU} ${FIXED_CTR1}`
#echo "Unhalted reference clocks:   " `rdmsr -p ${CPU} ${FIXED_CTR2}`

wrmsr -p ${CPU} ${FIXED_CTR0} 0
wrmsr -p ${CPU} ${FIXED_CTR1} 0
wrmsr -p ${CPU} ${FIXED_CTR2} 0

#echo "Enabling PEBS Load Latency and Fixed Function Counters on PMC0."
#wrmsr -p ${CPU} ${PEBS_LD_LAT_THRESHOLD} 385
wrmsr -p ${CPU} ${PERFEVTSEL0} 0x4101CD
wrmsr -p ${CPU} ${PEBS_ENABLE} 0x100000001
wrmsr -p ${CPU} ${PERF_GLOBAL_CTRL} 0x1i
#echo "Running Toy Program (~20 seconds)."
taskset ${CPU_MASK} ./a.out
wrmsr -p ${CPU} ${PERF_GLOBAL_CTRL} 0
#echo "Threshold                   " `rdmsr -p ${CPU} ${PEBS_LD_LAT_THRESHOLD}`

#echo "Tagged reads over threshold " `rdmsr -p ${CPU} ${PMC0}`
echo `rdmsr -p ${CPU} ${PEBS_LD_LAT_THRESHOLD}` `rdmsr -d -p ${CPU} ${PMC0}` >> PEBS.txt 
wrmsr -p ${CPU} ${PEBS_ENABLE} 0
wrmsr -p ${CPU} ${PEBS_LD_LAT_THRESHOLD} 0
wrmsr -p ${CPU} ${PERFEVTSEL0} 0
wrmsr -p ${CPU} ${PMC0} 0




