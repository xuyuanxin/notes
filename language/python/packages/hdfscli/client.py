

def get_file_size(hdfscli, file):
  '''
  @file: file name(with path)
  @return: file size (bytes,int)    
  '''
  size = -1
  c = hdfscli.content(file,strict=False)
  #print(c)
  if(None != c):
    size = c['length']
  return size



class Client(url, root=None, proxy=None, timeout=None, session=None): #  hdfs.client.
  '''Bases: object
  Base HDFS web client.
  '''

  def content(hdfs_path, strict=True):
    '''
    @hdfs_path: Remote path.
    @strict: If False, return None rather than raise an exception if the path doesn’t 
	  exist.
	
    Get ContentSummary for a file or folder on HDFS.
    '''
 
  def list(hdfs_path, status=False):
    '''
    @hdfs_path: Remote path to a directory. If hdfs_path doesn’t exist or points to -
      a normal file, an HdfsError will be raised.
    @status: Also return each file’s corresponding FileStatus.
    
    Return names of files contained in a remote folder.
    '''
    pass

  def makedirs(hdfs_path, permission=None):
    '''
    @hdfs_path: Remote path. Intermediate directories will be created appropriately.
    @permission: Octal permission to set on the newly created directory. These permi-
	  ssions will only be set on directories that do not already exist. This function 
	  currently has no return value as WebHDFS doesn’t return a meaningful flag.

    Create a remote directory, recursively if necessary.
	
	if(None == client.status(log_path,False)):
        client.makedirs(log_path) #无此目录就创建一个
		
    if(None == client.status(record_file,False)):
        client.write(record_file,data='\n',append=False) # 写会触发创建文件	
    '''
    pass	

  def read(*args, **kwds):
    '''
    @hdfs_path: HDFS path.
    @offset: Starting byte position.
    @length: Number of bytes to be processed. None will read the entire file.
    @buffer_size: Size of the buffer in bytes used for transferring the data. Defaul-
      ts the the value set in the HDFS configuration.
    @encoding: Encoding used to decode the request. By default the raw data is retur-
      ned. This is mostly helpful in python 3, for example to deserialize JSON data -
      (as the decoder expects unicode).
    @chunk_size: If set to a positive number, the context manager will return a gene-
      rator yielding every chunk_size bytes instead of a file-like object (unless de-
      limiter is also set, see below).
    @delimiter: If set, the context manager will return a generator yielding each ti-
      me the delimiter is encountered. This parameter requires the encoding to be sp-
      ecified.
    @progress: Callback function to track progress, called every chunk_size bytes (n-
      ot available if the chunk size isn’t specified). It will be passed two argumen-
      ts, the path to the file being uploaded and the number of bytes transferred  so 
      far. On completion, it will be called once with -1 as second argument.
    
    Read a file from HDFS.
	
	----/aaa.txt
	aaa
	bbb

    with client.read('/aaa.txt') as reader:
        content = reader.read()  # content <type 'str'>
        processed_flist = content.split('\n') # ['aaa', 'bbb']
    '''
    pass

  def status(hdfs_path, strict=True):
    '''
    @hdfs_path: Remote path.
    @strict – If False, return None rather than raise an exception if the path doesn’t exist.	
	
	Get FileStatus for a file or folder on HDFS.
	'''

  def walk(hdfs_path, depth=0, status=False):
    '''
    @hdfs_path: Starting path.If the path doesn’t exist, an HdfsError will be raised. 
	  If it points to a file, the returned generator will be empty.
    @depth: Maximum depth to explore. 0 for no limit.
    @status: Also return each file or folder’s corresponding FileStatus.
    
    This method returns a generator yielding tuples (path, dirs,files) where @path is 
	the absolute path to the current directory, @dirs is the list of directory  names 
	it contains, and files is the list of file names it contains.
	
    Depth-first walk of remote filesystem.
	'''
	pass
	
  def write(hdfs_path, data=None, overwrite=False, permission=None, blocksize=None, \
            replication=None, buffersize=None, append=False, encoding=None):
    '''
    @hdfs_path: Path where to create file. The necessary directories will be  created 
      appropriately.
    @data: Contents of file to write. Can be a string, a generator or a file  object. 
      The last two options will allow streaming upload (i.e. without having to load -
      the entire contents into memory). If None, this method will return a  file-like 
      object and should be called using a with block (see below for examples).
    @overwrite: Overwrite any existing file or directory.
    @permission: Octal permission to set on the newly created file. Leading zeros may 
      be omitted.
    @blocksize: Block size of the file.
    @replication: Number of replications of the file.
    @buffersize: Size of upload buffer.
    @append: Append to a file rather than create a new one.
    @encoding: Encoding used to serialize data written.    

    Create a file on HDFS.
	
	for line in datas:
        client.write(filename,data=line+'\n',append=True)
    '''
    pass

class InsecureClient(url, user=None, **kwargs): # hdfs.client. 
  ''' Bases: hdfs.client.Client
  @url 
    Hostname or IP address of HDFS namenode, prefixed with protocol, followed by    -
    WebHDFS port on namenode
  @user
    User default. Defaults to the current user’s (as determined by whoami).
  @**kwargs
    Keyword arguments passed to the base class’ constructor.

  HDFS web client to use when security is off.
  
  from hdfs import InsecureClient
  client = InsecureClient('http://host:port', user='ann')
  '''
  

ContentSummary JSON Schema
{
  "name"      : "ContentSummary",
  "properties":
  {
    "ContentSummary":
    {
      "type"      : "object",
      "properties":
      {
        "directoryCount":
        {
          "description": "The number of directories.",
          "type"       : "integer",
          "required"   : true
        },
        "fileCount":
        {
          "description": "The number of files.",
          "type"       : "integer",
          "required"   : true
        },
        "length":
        {
          "description": "The number of bytes used by the content.",
          "type"       : "integer",
          "required"   : true
        },
        "quota":
        {
          "description": "The namespace quota of this directory.",
          "type"       : "integer",
          "required"   : true
        },
        "spaceConsumed":
        {
          "description": "The disk space consumed by the content.",
          "type"       : "integer",
          "required"   : true
        },
        "spaceQuota":
        {
          "description": "The disk space quota.",
          "type"       : "integer",
          "required"   : true
        }
      }
    }
  }
}




