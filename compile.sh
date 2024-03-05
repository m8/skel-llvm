#!/bin/bash

# Simple script to compile a program with using Mage pass

CLANG_VERSION=14
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
PASS_DIR=$SCRIPT_DIR/build

if [ -z "$1" ]
then
    echo "Usage: ./compile.sh <input_file>"
    exit 1
fi

INPUT_FILE=$1
OUTPUT_NAME=$2
MAGE_C=$SCRIPT_DIR/mage.c

CMD="clang-${CLANG_VERSION} -flegacy-pass-manager -Xclang -load -Xclang ${PASS_DIR}/Mage.so ${INPUT_FILE} ${MAGE_C} -o
    ${OUTPUT_NAME}" 

echo "Compiling..."
$CMD