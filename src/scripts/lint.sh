set -ex
FOLDERS_TO_LINT="../BusinessLayer ../API ../HAL"
CPPLINT_FLAGS="--counting=detailed --filter=-whitespace/tab,-legal/copyright,-whitespace/line_length,-runtime/references,-build/c++11,-build/header_guard,-build/include,-readability/casting,-readability/todo,-runtime/explicit,-runtime/threadsafe_fn,-whitespace/blank_line,-whitespace/braces,-whitespace/comma,-whitespace/comments,-whitespace/end_of_line,-whitespace/ending_newline,-whitespace/indent,-whitespace/newline,-whitespace/operators,-whitespace/parens,-whitespace/semicolon,-readability/braces,-readability/multiline_string"

for FOLDER in ${FOLDERS_TO_LINT}; do
	cpplint ${CPPLINT_FLAGS} $(
            find "${FOLDER}"
        ) 
done
