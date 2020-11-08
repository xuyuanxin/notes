# http://shelly-kuang.iteye.com/blog/797713  Pythonģ��ѧϰ����ʹ�� optparse ���������в���



class OptionParser(...): # optparse.OptionParser

  def OptionParser.add_option(option):
    pass

  def add_option(*opt_str, attr=value, ...):
    pass

--> �����쳣
                                                                                     |
 ���������쳣���û��쳣��������Ҫ���۵����û��쳣����ָ���û�������Ч�ġ�������������|
 �в������������쳣��optparse �����Զ�̽�Ⲣ����һЩ�û��쳣��                       |

 $ /usr/bin/foo -n 4x  
 usage: foo [options]  
  
 foo: error: option -n: invalid integer value: '4x'  
  
 $ /usr/bin/foo -n  
 usage: foo [options]  
  
 foo: error: -n option requires an argument  
 
 �û�Ҳ����ʹ�� parser.error() �������Զ��岿���쳣�Ĵ���

 
 (options, args) = parser.parse_args()    
 if options.a and options.b:  
     parser.error("options -a and -b are mutually exclusive")  
                                                                                     |
 ��������ӣ��� -b �� -b �����в���ͬʱ����ʱ,���ӡ����options -a and -b are mutually|
 exclusive�����Ծ����û���������ϵ��쳣����������������Ҫ���������Ҫ�̳�        |
 OptionParser �࣬������ exit() �� erro() ������
	
--> Option attributes   
 https://docs.python.org/2/library/optparse.html#optparse.OptionParser
 
 The following option attributes may be passed as keyword arguments to              -
 OptionParser.add_option(). If you pass an option attribute that is not relevant to a 
 particular option, or fail to pass a required option attribute, optparse raises    -
 OptionError.

 Option.action  (default: "store")
   Determines optparse��s behaviour when this option is seen on the command line;  the 
   available options are documented "here".
                                                                                     |
   action �� parse_args() �����Ĳ���֮һ����ָʾ optparse ��������һ�������в���ʱ�� |
   ��δ���actions ��һ��̶���ֵ�ɹ�ѡ��Ĭ����'store'����ʾ�������в���ֵ������ |
   options �����
   ---------------------------
   parser.add_option("-f", "--file", action="store", type="string", dest="filename")  
   args = ["-f", "foo.txt"]  
   (options, args) = parser.parse_args(args)  
   print options.filename 
   --------------------------   
   ��󽫻��ӡ�� "foo.txt"��
   �� optparse ������'-f'����������������'foo.txt'��Ȼ��'foo.txt'���浽          |
   options.filename ������� parser.args() ��options.filename ��ֵ��Ϊ'foo.txt'��|
   ��Ҳ����ָ�� add_option() ������ type ����Ϊ����ֵ���� int ���� float �ȵȣ�
   
   parser.add_option("-n", type="int", dest="num")  
 
   Ĭ�ϵأ�type Ϊ'string'��Ҳ����������ʾ����������Ҳ�ǿ�ѡ�ġ���ʵ��dest ����Ҳ�ǿ�|
   ѡ�ġ����û��ָ�� dest ���������������еĲ��������� options �����ֵ���д�ȡ��   |
   store Ҳ��������������ʽ�� store_true �� store_false �����ڴ���������в������治 |
   ��ֵ��������� -v,-q �������в�����

   parser.add_option("-v", action="store_true", dest="verbose")  
   parser.add_option("-q", action="store_false", dest="verbose")  
 
   �����Ļ����������� ��-v����options.verbose �������� True ֵ����֮�������� ��-q�����ᱻ|
   ���� False ֵ�������� actions ֵ���У�
   store_const ��append ��count ��callback ��
   

 Option.type
   (default: "string")

   The argument type expected by this option (e.g., "string" or "int"); the available option types are documented here.

 Option.dest
   (default: derived from option strings)

   If the option��s action implies writing or modifying a value somewhere, this tells optparse where to write it: dest names an attribute of the options object that optparse builds as it parses the command line.

 Option.default
   The value to use for this option��s destination if the option is not seen on the c-
   ommand line. See also OptionParser.set_defaults().
   
   parse_args() �����ṩ��һ�� default ������������Ĭ��ֵ���磺
   
   parser.add_option("-f","--file", action="store", dest="filename", default="foo.txt")  
   parser.add_option("-v", action="store_true", dest="verbose", default=True)
 
   �ֻ���ʹ�� set_defaults()��

   parser.set_defaults(filename="foo.txt",verbose=True)  
   parser.add_option(...)  
   (options, args) = parser.parse_args()  

 Option.nargs
   (default: 1)

   How many arguments of type type should be consumed when this option is seen. If > 1, optparse will store a tuple of values to dest.

 Option.const
   For actions that store a constant value, the constant value to store.

 Option.choices
   For options of type "choice", the list of strings the user may choose from.

 Option.callback
   For options with action "callback", the callable to call when this option is seen. See section Option Callbacks for detail on the arguments passed to the callable.

 Option.callback_args
 Option.callback_kwargs
   Additional positional and keyword arguments to pass to callback after the four standard callback arguments.

 Option.help
   Help text to print for this option when listing all available options after the u-
   ser supplies a help option (such as --help). If no help text is supplied, the opt-
   ion will be listed without help text. To hide this option, use the special value -
   optparse.SUPPRESS_HELP.
                                                                                     |
   optparse ��һ������Ĺ������Զ����ɳ���İ�����Ϣ����ֻ��ҪΪ add_option() ������ |
   help ����ָ��������Ϣ�ı���

   usage = "usage: %prog [options] arg1 arg2"  
   parser = OptionParser(usage=usage)  
   parser.add_option("-v", "--verbose",  
                     action="store_true", dest="verbose", default=True,  
                     help="make lots of noise [default]")  
   parser.add_option("-q", "--quiet",  
                     action="store_false", dest="verbose",  
                     help="be vewwy quiet (I'm hunting wabbits)")  
   parser.add_option("-f", "--filename",  
                     metavar="FILE", help="write output to FILE"),  
   parser.add_option("-m", "--mode",  
                     default="intermediate",  
                     help="interaction mode: novice, intermediate, "  
                     "or expert [default: %default]")  
                                                                                     |
   �� optparse ������ -h ���� �Chelp �����в���ʱ������� parser.print_help() ��ӡ����|
   �İ�����Ϣ��
   usage: <yourscript> [options] arg1 arg2  
  
   options:  
     -h, --help            show this help message and exit  
     -v, --verbose         make lots of noise [default]  
     -q, --quiet           be vewwy quiet (I'm hunting wabbits)  
     -f FILE, --filename=FILE  
                           write output to FILE  
     -m MODE, --mode=MODE  interaction mode: novice, intermediate, or  
                           expert [default: intermediate]  
 
   ע�⣺ ��ӡ��������Ϣ��optparse �����˳������ٽ��������������в�����

   �������������һ��������������ɰ�����Ϣ��
   �Զ���ĳ���ʹ�÷�����Ϣ��usage message����
   
   usage = "usage: %prog [options] arg1 arg2"  
                                                                                     |
   ������Ϣ�����ȴ�ӡ�ڳ����ѡ����Ϣǰ�����е� %prog��optparse ���Ե�ǰ���������ַ� |
   ����������� os.path.basename.(sys.argv[0])������û�û���ṩ�Զ����ʹ�÷�����Ϣ |
   ��optparse ��Ĭ��ʹ�ã� ��usage: %prog [options]�����û��ڶ��������в����İ�����Ϣʱ|
   �����õ��Ļ��д��������⣬optparse �ᴦ�����һ�С�
   
   ���� add_option �����е� metavar �����������������û����������в������ڴ��Ĳ����� |
   �� metavar=��mode����
   
   -m MODE, --mode=MODE  
 
   ע�⣺ metavar �����е��ַ������Զ���Ϊ��д��
   �� help �����İ�����Ϣ��ʹ�� %default ���Բ���������в�����Ĭ��ֵ��
   
   ��������кܶ�������в������������Ϊ���ǽ��з��飬��ʱ����ʹ�� OptonGroup��

   group = OptionGroup(parser, ``Dangerous Options'',  
                       ``Caution: use these options at your own risk.  ``  
                       ``It is believed that some of them bite.'')  
   group.add_option(``-g'', action=''store_true'', help=''Group option.'')  
   parser.add_option_group(group)  
 
   �����ǽ����ӡ�����İ�����Ϣ��

   usage:  [options] arg1 arg2  
  
   options:  
     -h, --help           show this help message and exit  
     -v, --verbose        make lots of noise [default]  
     -q, --quiet          be vewwy quiet (I'm hunting wabbits)  
     -fFILE, --file=FILE  write output to FILE  
     -mMODE, --mode=MODE  interaction mode: one of 'novice', 'intermediate'  
                       [default], 'expert'  
  
     Dangerous Options:  
       Caution: use of these options is at your own risk.  It is believed that  
       some of them bite.  
       -g                 Group option.  

 Option.metavar
   (default: derived from option strings)

   Stand-in for the option argument(s) to use when printing help text. See section Tutorial for an example.
   
 ��ʾ����汾
                                                                                     |
   �� usage message һ����������ڴ��� OptionParser ����ʱ��ָ���� version ����������|
   ��ʾ��ǰ����İ汾��Ϣ��

   parser = OptionParser(usage="%prog [-f] [-q]", version="%prog 1.0")  
 
   ������optparse �ͻ��Զ����� �Cversion �����в�����

   $ /usr/bin/foo --version  
   foo 1.0     
   
   
