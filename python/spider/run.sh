#!/bin/sh
#multi process

keyword_file=$1
NUM=12

if [ $# -eq 0 ] ; then
    echo "error: run.sh keyword_file"
    exit
fi

LINES=`wc -l $1 | awk '{print $1}'`

echo $LINES
SPLIT_LINE=$((LINES / NUM))
MOD=$((LINES % NUM))
#echo $MOD 
#echo $SPLIT_LINE
if [ $MOD != 0 ];then
    echo $SPLIT_LINE
    SPLIT_LINE=$(($SPLIT_LINE+1))
    echo $SPLIT_LINE
fi

split -l $SPLIT_LINE -d $1 ${1}.
echo "split ${1} into ${NUM} files"

#for i in `seq $NUM`
for file in `ls |grep ${1}.`
do
    echo $file
    python3 scratch_google.py $file &

done




