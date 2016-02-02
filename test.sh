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
# TEST 2
./simpsh --verbose --ignore 11 --rdwr a --append --rdwr b --append --wronly c --abort --pipe --pipe --command 1 4 2 tr A-Z a-z --command 5 0 2 cat - --command 3 6 2 sed '1d' --wait
if [ $? -eq 0 ] 
	then
		echo "Test 2 Success!"
	else
		echo "Make check failed for test 2"
		echo " Test: ./simpsh --verbose --ignore 11 --rdwr a --append --rdwr b --append --wronly c --abort --pipe --pipe --command 1 4 2 tr A-Z a-z --command 5 0 2 cat - --command 3 6 2 sed '10d' --wait if [ $? -eq 0 ] "
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

# TEST 4
echo "Running Test 4"
base64 /dev/urandom | head -c 10000000 > b1in.txt
./simpsh --profile --rdonly b1in.txt --trunc --wronly b1out.txt --wronly b1err.txt --pipe --pipe --command 0 4 2 sort --command 5 1 2 cat - --command 3 6 2 tr a-z A-z --close 3 --close 4 --close 5 --close 6 --wait
if [ $? -eq 0 ]
    then
        echo "Test 4 Success!"
    else
        echo "Make check failed for test 4"
        echo " Test: ./simpsh --profile --rdonly b1in.txt --trunc --wronly b1out.txt --wronly b1err.txt --pipe --pipe --command 0 4 2 sort --command 5 1 2 cat - --command 3 6 2 tr a-z A-z --close 3 --close 4 --close 5 --close 6 --wait "
        exit 1
fi

rm b1in.txt

# TEST 5
echo "Running Test 5"
touch b2in.txt b2out.txt b2err.txt
./simpsh --profile --rdonly b2in.txt --pipe --pipe --trunc --wronly b2out.txt --wronly b2err.txt --command 1 4 6 sort  --command 0 2 6 ls --command 3 5 6 tr a-z A-Z --close 1 --close 2 --close 3 --close 4 --wait
if [ $? -eq 0 ]
    then
        echo "Test 5 Success!"
    else
        echo "Make check failed for test 5"
        echo " Test: ./simpsh --profile --rdonly b2in.txt --pipe --pipe --trunc --wronly b2out.txt --wronly b2err.txt --command 1 4 6 sort  --command 0 2 6 ls --command 3 5 6 tr a-z A-Z --close 1 --close 2 --close 3 --close 4 --wait "
        exit 1
fi

rm b2in.txt b2out.txt b2err.txt


echo "Make check successfully completed"
