#!/bin/sh

CURDir=$PWD;
EXEFILE="$CURDir"/CVS2PList
CSV_PATH="$CURDir"/../../GameX/Assets/GameX/CSV/*
CLIENT_OUTPUT_PATH="$CURDir"/../../GameX/
SERVER_OUTPUT_PATH="$CURDir"/../../../GameXServer/game-server/config/data/
TEMP_PATH="$CURDir"/CVS2PListTemplates
 

for file in $CSV_PATH
do
if [ -f "$file" ]; then
    $EXEFILE $TEMP_PATH $file $CLIENT_OUTPUT_PATH $SERVER_OUTPUT_PATH
fi
done
