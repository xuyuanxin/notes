



def pandas.read_csv(filepath_or_buffer, sep=', ', dialect=None, compression='infer', \
                    doublequote=True, escapechar=None, quotechar='"', quoting=0, \
					skipinitialspace=False, lineterminator=None, header='infer', \
					index_col=None, names=None, prefix=None, skiprows=None, \
					skipfooter=None, skip_footer=0, na_values=None, true_values=None, \
					false_values=None, delimiter=None, converters=None, dtype=None, \
					usecols=None, engine=None, delim_whitespace=False, as_recarray=False, \
					na_filter=True, compact_ints=False, use_unsigned=False, low_memory=True, \
					buffer_lines=None, warn_bad_lines=True, error_bad_lines=True, \
					keep_default_na=True, thousands=None, comment=None, decimal='.', \
					parse_dates=False, keep_date_col=False, dayfirst=False, date_parser=None,\
					memory_map=False, float_precision=None, nrows=None, iterator=False, \
					chunksize=None, verbose=False, encoding=None, squeeze=False, \
					mangle_dupe_cols=True, tupleize_cols=False, infer_datetime_format=False,\
					skip_blank_lines=True):
  '''
  http://pandas.pydata.org/pandas-docs/stable/io.html#io-read-csv-table
  http://pandas.pydata.org/pandas-docs/stable/generated/pandas.read_csv.html?highlight=read_csv#pandas.read_csv
  
  Read CSV (comma-separated) file into DataFrame. Also supports optionally  iterating 
  or breaking of the file into chunks. Additional help can be found in the "online d-
  ocs for IO Tools".

  @dtype : Type name or dict of column -> type, default None
   Data type for data or columns. E.g. {¡®a¡¯: np.float64, ¡®b¡¯: np.int32} ( Unsupported 
   with engine=¡¯python¡¯)
  
  @header : int, list of ints, default ¡®infer¡¯
   Row number(s) to use as the column names, and the start of the data. Defaults to -
   0 if no names passed, otherwise None. Explicitly pass header=0 to be able to repl-
   ace existing names. The header can be a list of integers that specify row locatio-
   ns for a multi-index on the columns E.g. [0,1,3]. Intervening rows that are not s-
   pecified will be skipped (e.g. 2 in this example are skipped). Note that this par-
   ameter ignores commented lines and empty lines if skip_blank_lines=True, so      -
   header=0 denotes the first line of data rather than the first line of the file.
  
  @names : array-like, default None
   List of column names to use. If file contains no header row, then you should expl-
   icitly pass header=None.
  
  Consider a typical CSV file containing, in this case, some time series data:

  --> example
   In [1]: print(open('foo.csv').read())
   date,A,B,C
   20090101,a,1,2
   20090102,b,3,4
   20090103,c,4,5
   The default for read_csv is to create a DataFrame with simple numbered rows:
   In [2]: pd.read_csv('foo.csv')
   Out[2]: 
          date  A  B  C
   0  20090101  a  1  2
   1  20090102  b  3  4
   2  20090103  c  4  5
   In the case of indexed data, you can pass the column number or column name you wi-
   sh to use as the index:

   In [3]: pd.read_csv('foo.csv', index_col=0)
   Out[3]: 
             A  B  C
   date             
   20090101  a  1  2
   20090102  b  3  4
   20090103  c  4  5
   In [4]: pd.read_csv('foo.csv', index_col='date')
   Out[4]: 
             A  B  C
   date             
   20090101  a  1  2
   20090102  b  3  4
   20090103  c  4  5
   You can also use a list of columns to create a hierarchical index:

   In [5]: pd.read_csv('foo.csv', index_col=[0, 'A'])
   Out[5]: 
               B  C
   date     A      
   20090101 a  1  2
   20090102 b  3  4
   20090103 c  4  5
  '''