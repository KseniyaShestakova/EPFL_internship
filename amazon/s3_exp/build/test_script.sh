#! /bin/bash

./setup
echo "Setup done"

x=1

while [ $x -le 10 ];
do
    echo "Started $x testing session"
    ctest > ../report/report.txt
    ./parse_report.py
    echo "Refreshing..."
    ./refresh
    x=$(( $x + 1 ))
done

./finish
echo "Finished."




