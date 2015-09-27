'''                                                                                  |
Python是一门非常简洁的语言，对于数据类型的表示，不像其他语言预定义了许多类型（如：在 |
C#中，光整型就定义了8种），它只定义了六种基本类型：字符串，整数，浮点数，元组，列表，|
字典。通过这六种数据类型，我们可以完成大部分工作。但当Python需要通过网络与其他的平台 |
进行交互的时候，必须考虑到将这些数据类型与其他平台或语言之间的类型进行互相转换问题。 |
打个比方：C++写的客户端发送一个int型(4字节)变量的数据到Python写的服务器，Python接收到|
表示这个整数的4个字节数据，怎么解析成Python认识的整数呢？ Python的标准模块struct就用 |
来解决这个问题。                                                                     |

----> 字节顺序                                                                       |
打包的后的字节顺序默认上是由操作系统的决定的，当然struct模块也提供了自定义字节顺序的 |
功能，可以指定大端存储、小端存储等特定的字节顺序，对于底层通信的字节顺序是十分重要的 |
，不同的字节顺序和存储方式也会导致字节大小的不同。在format字符串前面加上特定的符号即 |
可以表示不同的字节顺序存储方式，例如采用小端存储 s = struct.Struct(‘<I3sf’)就可以了。|
官方api library 也提供了相应的对照列表：                                             |
Character    Byte order                Size        Alignment
@            native                    native      native
=            native                    standard    none
<            little-endian             standard    none
>            big-endian                standard    none
!            network (= big-endian)    standard    none

----> Format Characters
Format    C Type                Python type          Standard size    Notes
x         pad byte              no value          
c         char                  string of length 1   1     
b         signed char           integer              1                (3)
B         unsigned char         integer              1                (3)
?         _Bool                 bool                 1                (1)
h         short                 integer              2                (3)
H         unsigned short        integer              2                (3)
i         int                   integer              4                (3)
I         unsigned int          integer              4                (3)
l         long                  integer              4                (3)
L         unsigned long         integer              4                (3)
q         long long             integer              8                (2), (3)
Q         unsigned long long    integer              8                (2), (3)
f         float                 float                4                (4)
d         double                float                8                (4)
s         char[]                string          
p         char[]                string          
P         void *                integer                               (5), (3)


'''




