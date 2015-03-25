#------------------------------------------------------------------------------------  
#http://www.ibm.com/developerworks/library/l-sed1/index.html
#
#http://www.ibm.com/developerworks/cn/linux/shell/sed/sed-1/index.html
#http://www.ibm.com/developerworks/cn/linux/shell/sed/sed-2/index.html
#http://www.ibm.com/developerworks/cn/linux/shell/sed/sed-3/index.html
#
#Sed works by performing any number of user-specified editing operations ("commands") 
#on the input data. Sed is line-based , so the commands are performed on each line in 
#order. And, sed writes its results to standard output (stdout);it doesn't modify any 
#input files. 
#--------------------------------
#$ sed -e 'd' /etc/services
#If you type this command, you'll get absolutely no output. Now, what happened? In t-
#his example, we called sed with one editing command 'd'. Sed opened the /etc/services 
#file, read a line into its pattern buffer, performed our editing command ("delete li-
#ne"), and then printed the pattern buffer (which was empty). It then repeated these -
#steps for each successive line. This produced no output, because the "d" command zap-
#ped every single line in the pattern buffer! 
#There are a couple of things to notice in this example. 
#First, /etc/services was not modified at all. This is because, again, sed only reads 
#from the file you specify on the command line, using it as input -- it doesn't try -
#to modify the file. 
#The second thing to notice is that sed is line-oriented. The 'd' command didn't sim-
#ply tell sed to delete all incoming data in one fell swoop. Instead, sed read each -
#line of /etc/services one by one into its internal buffer, called the pattern buffer. 
#Once a line was read into the pattern buffer, it performed the 'd' command and prin-
#ted the contents of the pattern buffer (nothing in this example). Later, I'll show -
#you how to use address ranges to control which lines a command is applied to --  but 
#in the absence of addresses, a command is applied to all lines.
#The third thing to notice is the use of single quotes to surround the 'd' command. -
#It's a good idea to get into the habit of using single quotes to surround your sed -
#commands, so that shell expansion is disabled. 
#------------------------------------
#$ sed -e '1d' /etc/services | more
#this time we use the 'd' command preceded by an optional numerical address. By using 
#addresses, you can tell sed to perform edits only on a particular line or lines.
#$ sed -e '1,10d' /etc/services | more
#When we separate two addresses by a comma, sed will apply the following command to -
#the range that starts with the first address, and ends with the second address. In -
#this example, the 'd' command was applied to lines 1-10, inclusive . All other lines 
#were ignored.
#------------------------------------
#$ sed -e '/^#/d' /etc/services | more 
# '/^#/' is a regular expression, Will match any line that begins with a '#'
#You can use a regexp this way: 
#$ sed -e '/regexp/d' /path/to/my/test/file | more
#This will cause sed to delete any matching lines. However, it may be easier to get -
#familiar with regular expressions by telling sed to print regexp matches, and delete 
#non-matches, rather than the other way around. This can be done with the following -
#command: 
#$ sed -n -e '/regexp/p' /path/to/my/test/file | more
#Note the new '-n' option, which tells sed to not print the pattern space unless exp-
#licitly commanded to do so. You'll also notice that we've replaced the 'd' command -
#with the 'p' command, which as you might guess, explicitly commands sed to print the 
#pattern space. Voila, now only matches will be printed. 
#------------------------------------
#We can specify two regular expressions separated by a comma, and sed will match  all 
#lines starting from the first line that matches the first regular expression , up to 
#and including the line that matches the second regular expression. 
#For example, the following command will print out a block of text that begins with a 
#line containing "BEGIN", and ending with a line that contains "END".If "BEGIN" isn't 
#found, no data will be printed. And, if "BEGIN" is found, but no "END" is found on -
#any line below it, all subsequent lines will be printed. This happens because of sed
#is stream-oriented nature -- it doesn't know whether or not an "END" will appear. 
#$ sed -n -e '/BEGIN/,/END/p' /my/test/file | more
#------------------------------------
#If you want to print out only the main function in a C source file, you could type : 
#$ sed -n -e '/main[[:space:]]*(/,/^}/p' sourcefile.c | more
#This command has two regular expressions, '/main[[:space:]]*(/' and '/^}/' , and one 
#command, 'p' . The first regular expression will match the string "main" followed by 
#any number of spaces or tabs, followed by an open parenthesis. This should match the 
#start of your average ANSI C main() declaration. 
#In this particular regular expression, we encounter the '[[:space:]]' character cla-
#ss.This is simply a special keyword that tells sed to match either a TAB or a space. 
#If you wanted, instead of typing '[[:space:]]', you could have typed '[', then a li-
#teral space, then Control-V, then a literal tab and a ']' -- The Control-V tells ba-
#sh that you want to insert a "real" tab rather than perform command expansion . It's 
#clearer, especially in scripts, to use the '[[:space:]]' command class. 
#OK, now on to the second regexp. '/^}' will match a '}' character that appears at t-
#he beginning of a new line. If your code is formatted nicely, this will match the c-
#losing brace of your main() function. If it's not, it won't -- one of the tricky th-
#ings about performing pattern matching. 
#The 'p' command does what it always does, explicitly telling sed to print out the l-
#ine, since we are in '-n' quiet mode . Try running the command on a C source file -- 
#it should output the entire main() { } block, including the initial "main()" and the 
#closing '}'.
#
#
#
#
#
#替换！
#$ sed -e 's/foo/bar/' myfile.txt
#上面的命令将 myfile.txt 中每行第一次出现的 'foo'（如果有的话）用字符串 'bar' 替换，然
#后将该文件内容输出到标准输出。在进行字符串替换时，通常想执行全局替换。也就是说，要替
#换每行中的 所有出现，如下所示： 
#$ sed -e 's/foo/bar/g' myfile.txt
#在最后一个斜杠之后附加的 'g' 选项告诉 sed 执行全局替换。

#关于 's///' 替换命令，还有其它几件要了解的事。首先，它是一个命令，并且只是一个命令，
#在所有上例中都没有指定地址。这意味着，'s///' 还可以与地址一起使用来控制要将命令应用到
#哪些行，如下所示：
#$ sed -e '1,10s/enchantment/entrapment/g' myfile2.txt
#上例将导致用短语 'entrapment' 替换所有出现的短语 'enchantment'，但是只在第一到第十行
#（包括这两行）上这样做。

#$ sed -e '/^$/,/^END/s/hills/mountains/g' myfile3.txt
#该例将用 'mountains' 替换 'hills'，但是，只从空行开始，到以三个字符 'END' 开始的行结
#束（包括这两行）的文本块上这样做。

#关于 's///' 命令的另一个妙处是 '/' 分隔符有许多替换选项。如果正在执行字符串替换，并且
#规则表达式或替换字符串中有许多斜杠，则可以通过在 's' 之后指定一个不同的字符来更改分隔
#符。例如，下例将把所有出现的 /usr/local 替换成 /usr：
#$ sed -e 's:/usr/local:/usr:g' mylist.txt
#在该例中，使用冒号作为分隔符。如果需要在规则表达式中指定分隔符字符，可以在它前面加入
#反斜杠。

#以下 sed 命令将匹配从 '<' 开始、到 '>' 结束、并且在其中包含任意数量字符的短语。下例将
#删除该短语（用空字符串替换）：
#$ sed -e 's/<.*>//g' myfile.html
#这意味着，上例将把下行：
#<b>This</b> is what <b>I</b> meant.
#变成：
#meant.

#'<' 字符后面跟有任意数量非 '>' 字符并以 '>' 字符结束，的规则表达式。这将与最短、而不是
#最长的可能性匹配
#$ sed -e 's/<[^>]*>//g' myfile.html
#这意味着，上例将把下行：
#<b>This</b> is what <b>I</b> meant.
#变成：
#This is what I meant.
#在上例中，'[^>]' 指定“非 '>'”字符，其后的 '*' 完成该表达式以表示“零或多个非 '>' 字符”。

#以下是可用字符类的相当完整的列表：
#字符类	    描述
#[:alnum:]	字母数字 [a-z A-Z 0-9]
#[:alpha:]	字母 [a-z A-Z]
#[:blank:]	空格或制表键
#[:cntrl:]	任何控制字符
#[:digit:]	数字 [0-9]
#[:graph:]	任何可视字符（无空格）
#[:lower:]	小写 [a-z]
#[:print:]	非控制字符
#[:punct:]	标点字符
#[:space:]	空格
#[:upper:]	大写 [A-Z]
#[:xdigit:]	十六进制数字 [0-9 a-f A-F]
#尽可能使用字符类是很有利的，因为它们可以更好地适应非英语 locale（包括某些必需的重音字
#符等等）.

#cat a.txt
#ab cd
#aa
# bb
#$ sed -e 's/.*/ralph said: &/' a.txt
#ralph said: ab cd
#ralph said: aa
#ralph said:  bb
#该例的替换字符串中使用了 '&' 字符，该字符告诉 sed 插入整个匹配的规则表达式。

#'s///' 允许我们在规则表达式中定义区域，然后可以在替换字符串中引用这些特定区域。作为示
#例，假设有一个包含以下文本的文件：
# foo bar oni eeny meeny miny larry curly moe 
#现在假设要编写一个 sed 脚本，该脚本将把 "eeny meeny miny" 替换成 "Victor eeny-meeny Von
# miny" 等等。要这样做，首先要编写一个由空格分隔并与三个字符串匹配的规则表达式。
# '.* .* .*'
#现在，将在其中每个感兴趣的区域两边插入带反斜杠的圆括号来定义区域：
# '\(.*\) \(.*\) \(.*\)'
#除了要定义三个可在替换字符串中引用的逻辑区域以外，该规则表达式的工作原理将与第一个规则
#表达式相同。下面是最终脚本：
# $ sed -e 's/\(.*\) \(.*\) \(.*\)/Victor \1-\2 Von \3/' myfile.txt
#如您所见，通过输入 '\x'（其中，x 是从 1 开始的区域号）来引用每个由圆括号定界的区域。输
#入如下：
#Victor foo-bar Von oni Victor eeny-meeny Von miny Victor larry-curly Von moe


