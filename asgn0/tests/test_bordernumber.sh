#creating example output
echo 1024 > expected.txt
echo -1024 > expected2.txt
#running program and saving output
./calc 512 512 > output.txt

#making sure exit code is zero
if [ $? -ne 0]; then
        echo "invalid exit code" $?
        rm expected.txt
        rm output.txt
        exit 1
fi

#running program and saving output
./calc -512 -512 > output2.txt

#making sure exit code is zero
if [ $? -ne 0]; then
        echo "invalid exit code" $?
        rm expected.txt
        rm expected2.txt
	rm output.txt
	rm output2.txt
        exit 1
fi

#checking for differences
diff output.txt expected.txt
if [ $? -ne 0 ]; then
        echo "Answer is incorrect"
        rm expected.txt
	rm expected2.txt
        rm output.txt
	rm output2.txt
        exit 1
fi

#checking for differences
diff output2.txt expected2.txt
if [ $? -ne 0 ]; then
        echo "Answer is incorrect"
        rm expected.txt
	rm expected2.txt
        rm output.txt
        rm output2.txt
        exit 1
fi

#success message
echo "Test passed 512 + 512 and -512 + -512"

#cleaning up files
rm expected.txt
rm output.txt
rm output2.txt
rm expected2.txt
exit 0
