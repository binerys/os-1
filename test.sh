#!/bin/sh

touch a
touch b
touch c

# TEST 1
./simpsh --rdonly a
if [ $? -eq 0 ] 
	then
		exit 0
	else
		echo "make check failed - rdonly"
		exit 1
fi

# TEST 2
./simpsh --rdonly a --wronly b --wronly c --command 0 1 2 echo a 
if [ $? -eq 0 ] 
	then
		exit 0
	else
		echo "make check failed - command"
		exit 1
fi

# TEST 3
./simpsh --rdonly --rdonly
if [ $? -eq 1 ] 
	then
		exit 0
	else
		echo "make check did not catch error"
		exit 1
fi