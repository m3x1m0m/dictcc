#!/bin/sh
COMPILE_CMD="g++ dict/*.cc dictcc.cc -o dictcc -lcurl -lcurlpp -g"
INST_FILE="/usr/local/bin/dictcc"
INST_CMD="sudo ln -s $PWD/dictcc $INST_FILE"
echo "Compiling ... "
$COMPILE_CMD
echo "Installing ..."
if [ ! -f "$INST_FILE" ]
then
  $INST_CMD
fi
