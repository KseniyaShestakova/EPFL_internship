#! /bin/bash

./setup
echo "Setup done"

x=1

while [ $x -le 50 ];
do
    echo "Started $x testing session"
    ctest > ../report/report_nod.txt
    ./parse_report.py
    echo "Refreshing..."
    x=$(( $x + 1 ))
done

./finish
echo "Finished."




