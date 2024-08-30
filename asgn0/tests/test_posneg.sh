#creating example output
echo 24 > expected.txt

#running program and saving output
./calc 36 -12 > output.txt

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
echo "Test passed 36 + -12"

#cleaning up files
rm expected.txt
rm output.txt
exit 0

