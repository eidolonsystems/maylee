#!/bin/bash
set -o errexit
set -o pipefail
directory=$1
if [ "$2" = "" ]
then
  config="install"
else
  config=$2
fi
let cores="`grep -c "processor" < /proc/cpuinfo` / 2 + 1"
let mem="`grep -oP "MemTotal: +\K([[:digit:]]+)(?=.*)" < /proc/meminfo` / 4194304"
let jobs="$(($cores<$mem?$cores:$mem))"
cmake --build $directory --target $config -- -j$jobs
