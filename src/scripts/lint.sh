#!/bin/sh
set -ex

FOLDERS_TO_LINT=""
CPPLINT_FLAGS='--filter=-whitespace/tab,-legal/copyright,-whitespace/line_length,-runtime/references'

for FOLDER in ${FOLDERS_TO_LINT}; do
	cpplint ${CPPLINT_FLAGS} $(
            find "${FOLDER}"
                -type f
                -regextype posix-extended
                -regex '^.*\.(c|h|cpp|hpp)$'
        ) nofile
done
