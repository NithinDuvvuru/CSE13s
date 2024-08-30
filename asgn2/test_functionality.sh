./hangman "zyxwvutsrqponmlkjihgfedcba" < tester.txt > output.txt
diff output.txt win.txt

if [ $? -ne 0 ]; then
    echo "standard out doesn't match!"
    exit 1
fi

./hangman "don't go in empty-handed" < tester.txt > lose.txt
if [ $? -ne 0 ]; then
    echo "standard out doesn't match!"
    exit 1
fi

echo "Passed all tests!"
rm output.txt