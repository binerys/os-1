#!/bin/sh

# TEST 1
echo "Running Test 1"
./simpsh --verbose --creat --rdonly a --pipe --pipe --creat --wronly b --creat --wronly  c --command 1 4 6 sort --command 0 2 6 ls --command 3 5 6 tr a-z A-Z 
if [ $? -eq 0 ] 
	then
		echo "Test 1 Success!"
	else
		echo "Make check failed for test 1"
		echo " Test: ./simpsh --verbose --creat --rdonly a --pipe --pipe --wronly --creat b --wronly --creat c --command 1 4 6 sort --command 0 2 6 ls --command 3 5 6 tr a-z A-Z "
		exit 1
fi

echo "Running Test 2"
# TEST 2 a 0 b 1 c 2 p1r 3 p1w 4 p2r 5 p2w 6: tr | sed | cat
./simpsh --verbose --ignore 11 --rdwr a --append --rdwr b --append --wronly c --abort --pipe --pipe --command 1 4 2 tr A-Z a-z  --command 5 0 2 cat -  --command 3 6 2 sed '1d' --close 4 --close 5 --close 3 --close 6 --wait
if [ $? -eq 0 ] 
	then
		echo "Test 2 Success!"
	else
		echo "Make check failed for test 2"
		echo " Test: ./simpsh --verbose --ignore 11 --rdwr a --append --rdwr b --append --wronly c --abort --pipe --pipe --command 1 4 2 tr A-Z a-z --command 5 0 2 cat - --command 3 6 2 sed '10d' --wait"
		exit 1
fi

echo "Running Test 3"
# TEST 3
./simpsh --rdonly a --wronly b --wronly c --command 1 0 2 echo a --wait
if [ $? -ne 0 ] 
	then
		echo "Test 3 success!"
	else
		echo "Make check did not catch error"
		echo "Test: ./simpsh --rdonly a --wronly b --wronly c --command 1 0 2 echo a --wait"
		exit 1
fi

rm a b c

echo "Make check successfully completed"
