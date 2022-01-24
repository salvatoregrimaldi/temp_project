#!/bin/bash


YELLOW='\033[0;92m'
NORMAL='\033[0;39m'
BLUE='\033[0;34m'

TIMEFORMAT='%4U;%4E;%4S;%P'
TIMESTAMP=$(date +%F.%T)

NMEASURES=20
ARRAY_SIZE=(10000 10000000 100000000) #carico
ARRAY_MAX_NUM=(1000 100000 1000000) #cnum max
ARRAY_THS=(0 1 2 4 8)
ARRAY_OPT=(0)


SCRIPTPATH=$2

for size in "${ARRAY_SIZE[@]}"; do
	for nTh in "${ARRAY_THS[@]}"; do
		for opt in "${ARRAY_OPT[@]}"; do
            for num in "${ARRAY_MAX_NUM[@]}"; do
                nThStr=$(printf "%02d" $nTh)
                    
                OUT_FILE=$SCRIPTPATH/measure/$TIMESTAMP/SIZE-$size-MAX-$num-O$opt/SIZE-$size-NPR-$nThStr-O$opt.csv

                mkdir -p $(dirname $OUT_FILE)
                
                printf "${NORMAL}"
                echo "MAX= $num FILE= $(basename $OUT_FILE)"
                echo 'nThread;timeInit;timeCount'>$OUT_FILE 

                for (( nExec = 0 ; nExec < $NMEASURES ; nExec += 1 )) ; do
                    if [[ $nTh -eq 0 ]]; then
					    $1/eseguibileSeqO$opt $size $num  >> $OUT_FILE
                    else
                        mpirun.mpich -np $nTh $1/eseguibileO$opt $size $num >> $OUT_FILE 
                    fi

                    printf "\r${YELLOW}> ${BLUE}%5d/%d ${YELLOW}%3.1d%% [ " $(expr $nExec + 1) $NMEASURES $(expr \( \( $nExec + 1  \) \* 100 \) / $NMEASURES)
                    printf "#%.0s" $(seq -s " " 1 $(expr \( $nExec \* 40 \) / $NMEASURES))
                    printf " %.0s" $(seq -s " " 1 $(expr 40 - \( $nExec \* 40 \) / $NMEASURES))
                    printf "] "

                done
                
                printf "\n"
            done
        done
    done
done



