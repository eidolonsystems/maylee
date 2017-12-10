#!/bin/bash
set -o errexit
set -o pipefail
directory=$(pwd)
$directory/../../../../build/make/local_build.sh $directory $1
