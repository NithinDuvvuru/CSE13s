./xd /home/nithin/nduvvuru/asgn3/tests/letters.txt > output.txt
if [ $? -ne 0]; then
        echo "invalid exit code" $?
        rm output.txt
        exit 1
fi
xxd /home/nithin/nduvvuru/asgn3/tests/letters.txt > expected.txt
if [ $? -ne 0]; then
        echo "invalid exit code" $?
        rm output.txt
       	rm expected.txt
        exit 1
fi
diff output.txt expected.txt
if [ $? -ne 0 ]; then
    echo "standard output doesn't match!"
    rm output.txt
    rm expected.txt
    exit 1
fi

echo "Passed all tests!"
rm output.txt
rm expected.txt
exit 0