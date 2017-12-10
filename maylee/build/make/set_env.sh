#!/bin/bash
maylee_local_path=$(pwd)
if [ "$(uname -s)" = "Darwin" ]
then
  so_ext="dylib"
else
  so_ext="so"
fi
export MAYLEE_INCLUDE_PATH=$maylee_local_path/../../include
