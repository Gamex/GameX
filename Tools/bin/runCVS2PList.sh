#!/bin/sh

CURDir=$PWD;
EXEFILE="$CURDir"/CVS2PList
DICT_PATH="$CURDir"/../../GameX/Assets/GameX/CSV/Dictionary/*
ARRAY_PATH="$CURDir"/../../GameX/Assets/GameX/CSV/Array/*
OUTPUT_PATH="$CURDir"/../../GameX/Classes/
TEMP_PATH="$CURDir"/CVS2PListTemplates

for file in $DICT_PATH
do
if [ -f "$file" ]; then
    $EXEFILE -cpp -d $TEMP_PATH $file $OUTPUT_PATH
fi
done

for file in $ARRAY_PATH
do
if [ -f "$file" ]; then
    $EXEFILE -cpp -a $TEMP_PATH $file $OUTPUT_PATH
fi
done
