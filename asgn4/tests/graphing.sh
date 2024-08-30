echo "" > tanOut.txt
echo "" > tan.txt

for i in $(seq 0.00 0.01 6.28)
do
   echo "$i t" | ./tests/calc_arm >> tanOut.txt
   echo "$i t" | ./calc >> tan.txt
done

exit 0
