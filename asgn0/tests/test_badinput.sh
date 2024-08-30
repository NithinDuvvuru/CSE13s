#creating example output
echo "BAD INPUT" > expected.txt

#running program and saving output
./calc a b > output.txt

#making sure exit code is zero
if [ $? -ne 0]; then
        echo "invalid exit code" $?
        rm output.txt
       	rm expected.txt
        exit 1
fi

./calc 6 a > output2.txt

if [ $? -ne 0]; then
        echo "invalid exit code" $?
        rm output.txt
	rm output2.txt
        rm expected.txt
        exit 1
fi

./calc a 6 > output3.txt

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
        exit 1
fi

diff output2.txt expected.txt
if [ $? -ne 0 ]; then
        echo "Answer is incorrect"
        rm expected.txt
        rm output2.txt
        rm output3.txt
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
        exit 1
fi

#success message
echo "BAD INPUT Test Passed"

#cleaning up files
rm expected.txt
rm output.txt
rm output2.txt
rm output3.txt
exit 0          
