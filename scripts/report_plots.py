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
        print(new_line)
        report_file.write(new_line)
        cnt += 1

    result_file.close()
    report_file.close()


def plot_scatter(frame, names):
    x = []
    y = []

    num_rows = len(frame)
    cnt = 1

    for name in names:
        y += frame.loc[:, name].tolist()
        x += [cnt] * num_rows
        cnt += 1

    plt.scatter(x=x, y=y, alpha=0.2, color='navy')

    avg = frame.mean(axis=0).tolist()
    plt.plot(np.arange(1, cnt, 1), avg, color='red', label='average')
    median = frame.median(axis=0).tolist()
    plt.plot(np.arange(1, cnt, 1), median, color='yellow', label='median')

    ticks = np.arange(1, len(frame.columns) + 1, 1)
    plt.xticks(ticks=ticks, labels=names, rotation=90)
    plt.grid(axis='both')
    plt.xlabel('Test', fontsize=13)
    plt.ylabel('Time elapsed, sec.', fontsize=13)
    plt.legend(fontsize=13)


def boxplot(frame, names):
    data = []
    for name in names:
        data.append(frame.loc[:, name])
    sns.boxplot(data=data, palette='PuRd')
    ticks = np.arange(0, len(frame.columns), 1)
    plt.xticks(ticks=ticks, labels=names, rotation=90)


def overall_plot(names):
    process_results()

    subjects = len(names)

    frame = pd.read_csv('report.csv',
                        names=names)
    x = []
    y = []

    num_rows = len(frame)
    cnt = 1

    for name in names:
        if name == 'Total':
            continue
        y += frame.loc[:, name].tolist()
        x += [cnt] * num_rows
        cnt += 1

    # plt.figure(figsize=(10, 10))
    '''
    plt.scatter(x=x, y=y, alpha=0.2)
    
    avg = frame.mean(axis=0).tolist()[:-1]
    plt.scatter(x=np.arange(1, subjects, 1), y=avg,
                color='red', alpha=1, marker='_', linewidths=3)
    median = frame.median(axis=0).tolist()[:-1]
    plt.scatter(x=np.arange(1, subjects, 1), y=median,
                color='yellow', alpha=1, marker='_', linewidths=3)
    '''
    boxplot(frame, names)
    plt.ylim([0, 75])
    ticks = np.arange(0, len(frame.columns), 1)
    plt.xticks(ticks=ticks, labels=names, rotation=90)
    plt.grid(axis='both')

    plt.xlabel('Test', fontsize=13)
    plt.ylabel('Time elapsed, sec.', fontsize=13)
    plt.title('Time elapsed for different operations', fontsize=15)


overall_names = ['JustBoot', 'CreateNS',
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

rw_names = ['JustBoot', 'CreateNS',
            'Read512', 'Read1024', 'Read2048',
            'Read4096', 'Read8192', 'Read12288', 'Read16384',
            'Read32768',
            'Write512', 'Write1024', 'Write2048',
            'Write4096', 'Write8192', 'Write12288', 'Write16384',
            'Write32768',
            'Total']


def rw_plot():
    process_results()

    frame = pd.read_csv('report.csv',
                        names=rw_names)

    r_names = ['Read512', 'Read1024', 'Read2048', 'Read4096',
               'Read8192', 'Read12288', 'Read16384', 'Read32768']
    r_frame = frame[r_names]
    w_names = ['Write512', 'Write1024', 'Write2048',
               'Write4096', 'Write8192', 'Write12288', 'Write16384',
               'Write32768']
    w_frame = frame[w_names]

    # plot_scatter(w_frame, w_names)
    plot_scatter(r_frame, r_names)
    plt.xlabel('Operation and size of block (bytes)', fontsize=13)
    plt.ylabel('Time elapsed, sec.', fontsize=13)
    plt.title('Dependency between time elapsed and block size', fontsize=15)


report_file = open('report.csv', 'w')
report_file.truncate()
report_file.close()

plt.figure(figsize=(10, 10))
overall_plot(overall_names)
plt.show()

report_file = open('report.csv', 'w')
report_file.truncate()
report_file.close()
