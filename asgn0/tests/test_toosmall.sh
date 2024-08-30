#creating example output
echo TOO BIG > expected.txt

#running program and saving output
./calc -1000 -1000 > output.txt

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

#success message
echo "Test passed -1000 + -1000"

#cleaning up files
rm expected.txt
rm output.txt
exit 0
