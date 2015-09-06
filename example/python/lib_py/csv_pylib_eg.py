#_*_coding:UTF-8_*_
#python csv

import os
import csv

'''
    在python中，CSV(Comma Separated Values)，从字面上面理解为：逗号分隔值
    举个例子，如：test_csv = 'one, two, three, 4, 5'
    对于test_csv这个变量来说，他里面就存放着这样的值：逗号分隔的值。这样的形式
    在导入和导出中非常常见，如python(version:3.3.2)的API中所描述的一样：

        The so-called CSV(Comma Separated Values) format is the most
        common import and export for spreadsheets and databases.

    csv模块定义了以下函数：

        csv.reader(csvfile, dialect = 'excel', **fmtparams)
            Retuen a reader object which will iterate over lines
            in the given csvfile.
    A short usage example:
        import csv
        with open('eggs.csv', newline = '') as cf:
            spamreader = csv.reader(cf, delimiter = ' ',  quotechar = '|')
            for row in spamreader:
                print(','.join(row))

        csv.write(csvfile, dialect = 'excel', **fmtparams)
            Return a writer object reaponsible for converting the
            user's data into delimited strings on the given file-like
            object.

    A short usage example:
        import csv
        with open('eggs.csv', 'w', newline = '') as cf:
            spamwrite = csv.writer(cf, delimiter = ' ', quotechar = '|', quoting = csv.QUOTE_MINIMAL)
            spamwriter.writerow(['Spam'] * 5 + ['Baked Beans'])
            spamwriter.writerow(['Spam', 'Lovely Spam', 'Wonderful Spam'])
'''

#global var
SHOW_LOG = True
#csv file apth
CSV_FILE_PATH = ''

def write_data_2_csv_file(path, data):
    '''把数据写入到csv文件
    这里对要写入的数据进行限制，
    数据格式为一个列表：['one', 'two', 'three', 'four']
    '''
    if SHOW_LOG:
        print('打开文件:[{}]'.format(path))
    with open(path, 'w', newline = '') as cf:
        writer = csv.writer(cf, delimiter = ',', quotechar = '|', quoting = csv.QUOTE_MINIMAL)
        if SHOW_LOG:
            print('写入数据:{}'.format(data))
        writer.writerow(data)
    
def write_datas_2_csv_file(path, datas):
    '''把数据写入到csv文件
    这里对要写入的数据进行限制，
    数据格式为一个列表,列表里面的每一个元素都是一个列表：
    [
    ['one', 'two', 'three', 'four'],
    ['1', '2', '3'],
    ['a', 'b', 'c', 'd']
    ]
    '''
    if SHOW_LOG:
        print('打开文件:[{}]'.format(path))
    with open(path, 'w', newline = '') as cf:
        writer = csv.writer(cf, delimiter = ',', quotechar = '|', quoting = csv.QUOTE_MINIMAL)
        for row in datas:
            if SHOW_LOG:
                print('写入数据:{}'.format(row))
            writer.writerow(row)

def read_csv_file(path):
    '''读取指定的csv文件，并且把csv文件的内容以字符串的形式返回'''
    if os.path.exists(path):
        if SHOW_LOG:
            print('打开文件:[{}]'.format(path))
        content = ''
        with open(path, newline = '') as cf:
            reader = csv.reader(cf, delimiter = ' ', quotechar = '|')
            try:
                for row in reader:
                    if SHOW_LOG:
                        print('读取行:{}'.format(row))
                    c = ','.join(row) +'\n'
                    content += c
                return content[0:-1]
            except csv.Errow as e:
                sys.exit('file {}, line {} : {}'.format(path, reader.line_num, e))
    else:
        print('不存在文件:[{}]'.format(path))
                
def mkdirs(path):
    '''创建多级目录'''
    if os.path.exists(path):
        if SHOW_LOG:
            print('The path [{}] existing!'.format(path))
    else:
        if SHOW_LOG:
            print('The path [{}] dosen\'t exist!'.format(path))
        os.makedirs(path)
        if SHOW_LOG:
            print('Created the path [{}]'.format(path))

def get_path(absPath):
    '''获取到一个绝对路径的目录，
    如绝对路径：'C:\\test\\test.csv'
    则返回的是'C:\\test'
    '''
    if os.path.exists(absPath):
        if SHOW_LOG:
            print('the path [{}] existing!'.format(absPath))
        return os.path.split(absPath)[0]
    else:
        return os.path.split(absPath)[0]

def init():
    global SHOW_LOG
    SHOW_LOG = True
    global CSV_FILE_PATH
    CSV_FILE_PATH = 'C:\\test\\test.csv'
    csv_dir = get_path(CSV_FILE_PATH)
    mkdirs(csv_dir)
        
def main():
    init()
    data = ['one', 'two', 'three', 'four']
    datas = [
    ['one', 'two', 'three', 'four'],
    ['1', '2', '3'],
    ['a', 'b', 'c', 'd'],
    ['中国', '美国', '日本', '韩国', '新加坡']
    ]
    write_data_2_csv_file(CSV_FILE_PATH, data)
    content = read_csv_file(CSV_FILE_PATH)
    print(content)
    print('#' * 50)
    write_datas_2_csv_file(CSV_FILE_PATH,  datas)
    content = read_csv_file(CSV_FILE_PATH)
    print(content)

    
if __name__ == '__main__':
    main()