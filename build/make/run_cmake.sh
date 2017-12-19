#!/bin/bash
set -o errexit
set -o pipefail
directory=$(dirname $(readlink -f $0))
if [ "$1" = "" ]
then
  build_type="Release"
else
  build_type=$1
fi
pushd $directory/../../maylee/build/make/
./run_cmake.sh $build_type
popd

applications=""
applications+="ming"

for i in $applications; do
  pushd $directory/../../applications/$i/build/make
  ./run_cmake.sh $build_type
  popd
done
