#!/bin/sh

touch b
touch c

#echo " a b c d e" > $a

./simpsh --rdonly --rdonly a 2>&1 | grep "option '--rdonly' requires an argument" > /dev/null ||{ echo "option '--rdonly' requires an argument"; exit 1; }

touch a

./simpsh --rdonly a --wronly b --wronly c --command 0 1 2 echo a | grep "a" b > /dev/null || { echo "--command: execute 'echo' "; exit 1;}

./simpsh --verbose --wronly c 2>&1 | grep "--wronly c" > /dev/null || { echo "--verbose print out --wronly c"; exit 1;}


