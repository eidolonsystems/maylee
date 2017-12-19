#!/bin/bash
set -o errexit
set -o pipefail
directory=$(pwd)
if [ "$1" = "" ]
then
  config="install"
else
  config=$1
fi

build_function() {
  pushd $directory/../../applications/$1/build/make
  ./build.sh $config
  popd
}

let cores="`grep -c "processor" < /proc/cpuinfo` / 2 + 1"
let mem="`grep -oP "MemTotal: +\K([[:digit:]]+)(?=.*)" < /proc/meminfo` / 4194304"
let jobs="$(($cores<$mem?$cores:$mem))"

pushd $directory/../../maylee/build/make
./build.sh $config
popd
export -f build_function
export directory
export config
applications=""
applications+="ming "
parallel -j$cores --no-notice build_function ::: $applications
