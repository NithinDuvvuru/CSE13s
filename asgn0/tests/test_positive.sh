#creating example output
echo 10 > expected.txt

#running program and saving output
./calc 4 6 > output.txt

#making sure exit code is zero
if [ $? -ne 0]; then
        echo "invalid exit code" $?
        rm expected.txt
        rm output.txt
        exit 1
fi

#checking for differences
diff output.txt expected.txt
if [ $? -ne 0 ]; then
        echo "Answer is incorrect"
        rm expected.txt
        rm output.txt
        exit 1
fi

diff output.txt expected.txt
if [ $? -eq 0 ]; then
	#success message
	echo "Test passed 4 + 6"
	rm expected.txt
	rm output.txt
	exit 0
fi

rm expected.txt
rm output.txt
exit 1
