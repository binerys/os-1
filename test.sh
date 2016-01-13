#!/bin/sh

a = /tmp/a 

echo " a b c d e" > $a

./simpsh --rdonly --rdonly a | grep "option '--rdonly' requires an argument" > /dev/null


