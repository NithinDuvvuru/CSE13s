#creating example output
echo 50 > expected.txt

#running program and saving output
./calc -100 150 > output.txt

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
echo "Test passed -100 + 150"

#cleaning up files
rm expected.txt
rm output.txt
exit 0
