#!/bin/bash

cleanup() {
	rm -f cmp out
}

assert() {
	printf '%-30s:' "\"$1\""
	# exit status
	echo -n -e "$1" | bash >cmp 2>&-
	expected=$?
	echo -n -e "$1" | ./minishell >out 2>&-
	actual=$?

	diff cmp out >/dev/null && echo -n '  diff OK' || echo -n '  diff NG'

	if [ "$actual" = "$expected" ]; then
		echo -n '  status OK'
	else
		echo -n "  status NG, expected $expected but got $actual"
	fi
	echo
}

# Empty line (EOF)
assert ''

# buitins
assert "env"
assert "export"
assert "export NEW_VAR"
assert "export NEW_VAR=42"
assert "unset"
assert "unset NEW_VAR"
assert "unset NON_EXISTING_VAR"
assert "echo"
assert "echo hello"
assert "echo -n hello"
assert "echo -n -n hello"
assert "echo -nnn hello"
assert "echo -nabc hello"
assert "echo -nnnn -nn -nnnn abc"
assert "echo -n -n -nab hello"
assert "echo -nnn -n -nab hello"
assert "echo -nan -n -nab hello"
assert "echo -nn -na -nab hello"


assert "cd"
assert "unset HOME"
assert "cd"
assert "pwd"
assert "cd /"
assert "pwd"
assert "cd ."
assert "pwd"
assert "cd .."
assert "pwd"
assert "cd -"
assert "pwd"
assert "cd /home/user/bin"
assert "pwd"
assert "cd /home/user/bin/.."
assert "pwd"
assert "cd ./bin"
assert "pwd"
assert "cd ./bin/../usr"
assert "pwd"
assert "cd /non-existing-dir"
assert "pwd"
assert "cd invalid!path"
assert "pwd"

assert 'exit' 0
assert 'exit 42' 42
assert 'exit ""' 0
assert 'exit hello' 0  # This might differ depending on how invalid arguments are handled
assert 'exit 42Tokyo' 0  # This might differ depending on handling of non-integer args
assert 'exit 1 2' 1

assert 'exit'
assert 'exit 42'
assert 'exit ""'
assert 'exit hello'
assert 'exit 42Tokyo'
assert 'exit 1 2'
assert 'exit  +1'
assert 'exit  ++1'
assert 'exit -1'
assert 'exit --1'
assert 'exit 99999999999999999999'
assert 'exit 2147483648'
assert 'exit 256'
assert 'exit -1'
assert 'exit 9223372036854775806'
assert 'exit 9223372036854775807'
assert 'exit 9223372036854775808'
assert 'exit -9223372036854775807'
assert 'exit -9223372036854775808'
assert 'exit -9223372036854775809'


cleanup