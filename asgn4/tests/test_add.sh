calc_ref=/tests/calc_arm
if [ $(uname -m) = "x86_64" ]; then
    calc_ref=/tests/calc_x86
fi

./calc < ~/nduvvuru/asgn4/tests/add.txt > output.txt
if [ $? -ne 0]; then
        echo "invalid exit code" $?
        rm output.txt
        exit 1
fi
./$calc_ref < ~/nduvvuru/asgn4/tests/add.txt > expected.txt
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