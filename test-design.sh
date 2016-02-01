#!/bin/sh

# TEST 1
echo "Running Test 1"
./simpsh --verbose --creat --rdonly a --pipe --pipe --creat --wronly b --creat --wronly  c --command 1 4 6 sort --command 0 2 6 ls --command 3 5 6 tr a-z A-Z --close 4 --close 2 --wait 0
if [ $? -eq 0 ] 
	then
		echo "Test 1 Success!"
	else
		echo "Make check failed for test 1"
		echo " Test: ./simpsh --verbose --creat --rdonly a --pipe --pipe --creat --wronly b --creat --wronly  c --command 1 4 6 sort --command 0 2 6 ls --command 3 5 6 tr a-z A-Z --close 4 --close 2 --wait 0"
		exit 1
fi

rm a b c

echo "Running Test 2"
./simpsh --verbose --creat --rdonly a --pipe --pipe --creat --wronly b --creat --wronly  c --command 1 4 6 sort --command 0 2 6 ls --command 3 5 6 tr a-z A-Z --close 4 --close 2 --wait 0 --close 3 --wait 2
if [ $? -eq 0 ] 
	then
		echo "Test 2 Success!"
	else
		echo "Make check failed for test 2"
		echo " Test: ./simpsh --verbose --creat --rdonly a --pipe --pipe --creat --wronly b --creat --wronly  c --command 1 4 6 sort --command 0 2 6 ls --command 3 5 6 tr a-z A-Z --close 4 --close 2 --wait 0 --close 3 --wait 2"
		exit 1
fi

rm a b c

echo "Running Test 3"
# TEST 3
./simpsh --verbose --creat --rdonly a --pipe --pipe --creat --wronly b --creat --wronly  c --command 1 4 6 sort --command 0 2 6 ls --command 3 5 6 tr a-z A-Z --close 2 --wait 1 --close 4 --wait 0 --close 3 --close 1 --wait 2
if [ $? -eq 0 ] 
	then
		echo "Test 3 success!"
	else
		echo "Make check failed for test 3"
		echo "Test: ./simpsh --verbose --creat --rdonly a --pipe --pipe --creat --wronly b --creat --wronly  c --command 1 4 6 sort --command 0 2 6 ls --command 3 5 6 tr a-z A-Z --close 2 --wait 1 --close 4 --wait 0 --close 3 --close 1 --wait 2"
		exit 1
fi
rm a b c
echo "Make check successfully completed"
