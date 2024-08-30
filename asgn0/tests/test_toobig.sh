#creating example output
echo "TOO BIG" > expected.txt

#running program and saving output
./calc -1000 10 > output.txt

#making sure exit code is zero
if [ $? -ne 0]; then
        echo "invalid exit code" $?
        rm output.txt
       	rm expected.txt
        exit 1
fi

./calc 10 1000 > output2.txt

if [ $? -ne 0]; then
        echo "invalid exit code" $?
        rm output.txt
	rm output2.txt
        rm expected.txt
        exit 1
fi

./calc -1000 1000 > output3.txt

if [ $? -ne 0]; then
        echo "invalid exit code" $?
       	rm output.txt
	rm output2.txt
       	rm output3.txt
        rm expected.txt
        exit 1
fi

./calc 600 300 > output4.txt

if [ $? -ne 0]; then
        echo "invalid exit code" $?
        rm output.txt
        rm output2.txt
        rm output3.txt
        rm expected.txt
        exit 1
fi

#checking for differences
diff output.txt expected.txt
if [ $? -ne 0 ]; then
        echo "Answer is incorrect"
        rm expected.txt
	rm output2.txt
        rm output3.txt
	rm output.txt
	rm output4.txt
        exit 1
fi

diff output2.txt expected.txt
if [ $? -ne 0 ]; then
        echo "Answer is incorrect"
        rm expected.txt
        rm output2.txt
        rm output3.txt
        rm output4.txt
	rm output.txt
        exit 1
fi

diff output3.txt expected.txt
if [ $? -ne 0 ]; then
        echo "Answer is incorrect"
        rm expected.txt
        rm output2.txt
        rm output3.txt
        rm output.txt
        rm output4.txt
	exit 1
fi

diff output4.txt expected.txt
if [ $? -ne 0 ]; then
        echo "Answer is incorrect"
        rm expected.txt
        rm output2.txt
        rm output3.txt
        rm output.txt
        rm output4.txt
        exit 1
fi

#success message
echo "TOO BIG Test Passed"

#cleaning up files
rm expected.txt
rm output.txt
rm output2.txt
rm output3.txt
rm output4.txt
exit 0
