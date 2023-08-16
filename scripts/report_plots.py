import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np


def process_results():
    result_file = open('result.csv', 'r')
    report_file = open('report.csv', 'a')

    report_file.truncate()

    lines = result_file.readlines()
    cnt = 1

    for line in lines:
        new_line = str(cnt) + ',' + line
        report_file.write(new_line)
        cnt += 1

    result_file.close()
    report_file.close()


process_results()

names = ['JustBoot', 'CreateNS',
         'CreateSmall', 'CreateLarge',
         'OpenSmall', 'OpenLarge',
         'DeleteSmall', 'DeleteLarge',
         'Write512Small', 'Write512Large',
         'Write2048Small', 'Write2048Large',
         'Read512Small', 'Read512Large',
         'Read2048Small', 'Read2048Large',
         'ListNoPrefix', 'ListWithPrefix',
         'IterateNoPrefix', 'IterateWithPrefix',
         'CloseSmall', 'CloseLarge', 'Total']

subjects = len(names)


frame = pd.read_csv('report.csv',
                    names=names)
print(frame)
x = []
y = []

num_rows = len(frame)
print(num_rows)
cnt = 1

for name in names:
    if name == 'Total':
        continue
    y += frame.loc[:, name].tolist()
    x += [cnt] * num_rows
    cnt += 1


plt.figure(figsize=(10, 10))
plt.scatter(x=x, y=y, alpha=0.1)

avg = frame.mean(axis=0).tolist()[:-1]
plt.scatter(x=np.arange(1, subjects, 1), y=avg,
            color='red', alpha=1, marker='_', linewidths=3)
median = frame.median(axis=0).tolist()[:-1]
plt.scatter(x=np.arange(1, subjects, 1), y=median,
            color='yellow', alpha=1, marker='_', linewidths=3)


ticks = np.arange(1, 24, 1)
plt.xticks(ticks=ticks, labels=names, rotation=90)
plt.grid(axis='both')

plt.show()
