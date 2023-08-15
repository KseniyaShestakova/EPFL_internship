#! /bin/python

report_file = open('../report/report.txt', 'r')
result_file = open('../report/result.csv', 'a')
lines = report_file.readlines()

for line in lines:
    res = line.split(' ')
    if 'sec\n' in res:
        if 'Passed' in res:
            result_file.write(res[-2] + ',')
        elif 'Total' in res:
            result_file.write(res[-2] + '\n')
        else:
            result_file.write('-1,')

report_file.close()
result_file.close()
