#!/bin/bash
set -o errexit
set -o pipefail
mkdir -p ./../../include/ming
printf "#define MING_VERSION \""> ./../../include/ming/version.hpp
git rev-list --count --first-parent HEAD | tr -d "\n" >> ./../../include/ming/version.hpp
printf \""\n" >> ./../../include/ming/version.hpp
