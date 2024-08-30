#creating example output
echo -5 > neg5.txt

#running program and saving output
./calc -4 -1 > output.txt

#making sure exit code is zero
if [ $? -ne 0]; then
        echo "invalid exit code" $?
        rm output.txt
        rm neg5.txt
        exit 1
fi

#checking for differences
diff output.txt neg5.txt
if [ $? -ne 0 ]; then
        echo "Answer is incorrect"
        rm neg5.txt
        rm output.txt
        exit 1
fi

#success message
echo "Test did passed -4 + -1"

#cleaning up files
rm neg5.txt
rm output.txt
exit 0
