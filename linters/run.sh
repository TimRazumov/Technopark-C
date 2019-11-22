#!/usr/bin/env bash

set -e
set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

print_header "RUN cppcheck"
if [ "${1}" == "--local" ]; then
	CPPCHECK="cppcheck"
else
	CPPCHECK="./linters/cppcheck/cppcheck"
fi
${CPPCHECK} lib_substr --enable=all --error-exitcode=1 -I lib_substr/parall_substr -I lib_substr/substr -I lib_substr/test --suppress=missingIncludeSystem # --check-config

print_header "RUN cpplint.py"
python2.7 ./linters/cpplint/cpplint.py --extensions=c,cpp lib_substr/parall_substr/* lib_substr/substr/* lib_substr/test/test.cpp

print_header "SUCCESS"
