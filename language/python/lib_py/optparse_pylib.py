# http://shelly-kuang.iteye.com/blog/797713  Python模块学习——使用 optparse 处理命令行参数



class OptionParser(...): # optparse.OptionParser

  def OptionParser.add_option(option):
    pass

  def add_option(*opt_str, attr=value, ...):
    pass

--> 处理异常
                                                                                     |
 包括程序异常和用户异常。这里主要讨论的是用户异常，是指因用户输入无效的、不完整的命令|
 行参数而引发的异常。optparse 可以自动探测并处理一些用户异常：                       |

 $ /usr/bin/foo -n 4x  
 usage: foo [options]  
  
 foo: error: option -n: invalid integer value: '4x'  
  
 $ /usr/bin/foo -n  
 usage: foo [options]  
  
 foo: error: -n option requires an argument  
 
 用户也可以使用 parser.error() 方法来自定义部分异常的处理：

 
 (options, args) = parser.parse_args()    
 if options.a and options.b:  
     parser.error("options -a and -b are mutually exclusive")  
                                                                                     |
 上面的例子，当 -b 和 -b 命令行参数同时存在时,会打印出“options -a and -b are mutually|
 exclusive“，以警告用户。如果以上的异常处理方法还不能满足要求，你可能需要继承        |
 OptionParser 类，并重载 exit() 和 erro() 方法。
	
--> Option attributes   
 https://docs.python.org/2/library/optparse.html#optparse.OptionParser
 
 The following option attributes may be passed as keyword arguments to              -
 OptionParser.add_option(). If you pass an option attribute that is not relevant to a 
 particular option, or fail to pass a required option attribute, optparse raises    -
 OptionError.

 Option.action  (default: "store")
   Determines optparse‘s behaviour when this option is seen on the command line;  the 
   available options are documented "here".
                                                                                     |
   action 是 parse_args() 方法的参数之一，它指示 optparse 当解析到一个命令行参数时该 |
   如何处理。actions 有一组固定的值可供选择，默认是'store'，表示将命令行参数值保存在 |
   options 对象里。
   ---------------------------
   parser.add_option("-f", "--file", action="store", type="string", dest="filename")  
   args = ["-f", "foo.txt"]  
   (options, args) = parser.parse_args(args)  
   print options.filename 
   --------------------------   
   最后将会打印出 "foo.txt"。
   当 optparse 解析到'-f'，会继续解析后面的'foo.txt'，然后将'foo.txt'保存到          |
   options.filename 里。当调用 parser.args() 后，options.filename 的值就为'foo.txt'。|
   你也可以指定 add_option() 方法中 type 参数为其它值，如 int 或者 float 等等：
   
   parser.add_option("-n", type="int", dest="num")  
 
   默认地，type 为'string'。也正如上面所示，长参数名也是可选的。其实，dest 参数也是可|
   选的。如果没有指定 dest 参数，将用命令行的参数名来对 options 对象的值进行存取。   |
   store 也有其它的两种形式： store_true 和 store_false ，用于处理带命令行参数后面不 |
   带值的情况。如 -v,-q 等命令行参数：

   parser.add_option("-v", action="store_true", dest="verbose")  
   parser.add_option("-q", action="store_false", dest="verbose")  
 
   这样的话，当解析到 ‘-v’，options.verbose 将被赋予 True 值，反之，解析到 ‘-q’，会被|
   赋予 False 值。其它的 actions 值还有：
   store_const 、append 、count 、callback 。
   

 Option.type
   (default: "string")

   The argument type expected by this option (e.g., "string" or "int"); the available option types are documented here.

 Option.dest
   (default: derived from option strings)

   If the option’s action implies writing or modifying a value somewhere, this tells optparse where to write it: dest names an attribute of the options object that optparse builds as it parses the command line.

 Option.default
   The value to use for this option’s destination if the option is not seen on the c-
   ommand line. See also OptionParser.set_defaults().
   
   parse_args() 方法提供了一个 default 参数用于设置默认值。如：
   
   parser.add_option("-f","--file", action="store", dest="filename", default="foo.txt")  
   parser.add_option("-v", action="store_true", dest="verbose", default=True)
 
   又或者使用 set_defaults()：

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
   optparse 另一个方便的功能是自动生成程序的帮助信息。你只需要为 add_option() 方法的 |
   help 参数指定帮助信息文本：

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
   当 optparse 解析到 -h 或者 –help 命令行参数时，会调用 parser.print_help() 打印程序|
   的帮助信息：
   usage: <yourscript> [options] arg1 arg2  
  
   options:  
     -h, --help            show this help message and exit  
     -v, --verbose         make lots of noise [default]  
     -q, --quiet           be vewwy quiet (I'm hunting wabbits)  
     -f FILE, --filename=FILE  
                           write output to FILE  
     -m MODE, --mode=MODE  interaction mode: novice, intermediate, or  
                           expert [default: intermediate]  
 
   注意： 打印出帮助信息后，optparse 将会退出，不再解析其它的命令行参数。

   以上面的例子来一步步解释如何生成帮助信息：
   自定义的程序使用方法信息（usage message）：
   
   usage = "usage: %prog [options] arg1 arg2"  
                                                                                     |
   这行信息会优先打印在程序的选项信息前。当中的 %prog，optparse 会以当前程序名的字符 |
   串来替代：如 os.path.basename.(sys.argv[0])。如果用户没有提供自定义的使用方法信息 |
   ，optparse 会默认使用： “usage: %prog [options]”。用户在定义命令行参数的帮助信息时|
   ，不用担心换行带来的问题，optparse 会处理好这一切。
   
   设置 add_option 方法中的 metavar 参数，有助于提醒用户，该命令行参数所期待的参数， |
   如 metavar=“mode”：
   
   -m MODE, --mode=MODE  
 
   注意： metavar 参数中的字符串会自动变为大写。
   在 help 参数的帮助信息里使用 %default 可以插入该命令行参数的默认值。
   
   如果程序有很多的命令行参数，你可能想为他们进行分组，这时可以使用 OptonGroup：

   group = OptionGroup(parser, ``Dangerous Options'',  
                       ``Caution: use these options at your own risk.  ``  
                       ``It is believed that some of them bite.'')  
   group.add_option(``-g'', action=''store_true'', help=''Group option.'')  
   parser.add_option_group(group)  
 
   下面是将会打印出来的帮助信息：

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
   
 显示程序版本
                                                                                     |
   象 usage message 一样，你可以在创建 OptionParser 对象时，指定其 version 参数，用于|
   显示当前程序的版本信息：

   parser = OptionParser(usage="%prog [-f] [-q]", version="%prog 1.0")  
 
   这样，optparse 就会自动解释 –version 命令行参数：

   $ /usr/bin/foo --version  
   foo 1.0     
   
   
