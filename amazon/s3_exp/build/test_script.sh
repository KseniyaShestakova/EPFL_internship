#! /bin/bash

./setup
echo "Setup done"

x=1

while [ $x -le 15 ];
do
    echo "Started $x testing session"
    ctest > ../report/report_rw.txt
    ./parse_report.py
    echo "Refreshing..."
    x=$(( $x + 1 ))
done

./finish
echo "Finished."




