/************************************************************************************
namespace
    When a program uses different classes and functions written by different programmers 
    there is a possibility that two programmers will use the same name for two different 
    things. Namespaces are a way to deal with this problem. A namespace is a collection 
    of name definitions, such as class definitions and variable declarations.

std namespace
    The std namespace contains all the names defined in the standard library files (such
    as iostream and cstdlib) that you use.Your program does not know about names in 
    the std namespace unless you specify that it is using the std namespace. So far, 
    the only way we know how to specify the std namespace (or any namespace) is with 
    the following sort of using directive:
                using namespace std;

global namespace
    Every bit of code you write is in some namespace. If you do not place the code in 
    some specific namespace,then the code is in a namespace known as the global namespace. 
    The global namespace does not have a using directive because you are always using 
    the global namespace. You could say that there is always an implicit automatic using 
    directive that says you are using the global namespace.

scope
    suppose ns1 and ns2 are two namespaces, and suppose my_function is a void function 
    with no arguments that is defined in both namespaces but defined in different ways 
    in the two namespaces. The following is then legal:
				{
				 using namespace ns1;
				 my_function( );
				}
				{
				 using namespace ns2;
				 my_function( );
				}
    The first invocation would use the definition of my_function given in the namespace 
    ns1, and the second invocation would use the definition of my_function given in the 
    namespace ns2.
    
    Recall that a block is a list of statements, declarations, and possibly other code, 
    enclosed in braces {}. A using directive at the start of a block applies only to 
    that block. So the first using directive applies only in the first block, and the 
    second using directive applies only in the second block. 

    When you use a using directive in a block, it is typically the block consisting 
    of the body of a function definition.If you place a using directive at the start 
    of a file , then the using directive applies to the entire file. 

Creating a Namespace
    namespace Name_Space_Name
    {
        Some_Code
    }

using declaration
    Suppose you are faced with the following situation: You have two namespaces, ns1 and 
    ns2. You want to use the function fun1 defined in ns1 and the function fun2 defined 
    in namespace ns2. 
                using ns1::fun1;
                using ns2::fun2;
    A using declaration of the form
                using Name_Space::One_Name
    makes (the definition of) the name One_Name from the namespace Name_Space available, 
    but does not make any other names in Name_Space available.

A Subtle Point About Namespaces (Optional )
    There are two differences between a using declaration, such as
                using std::cout;
    and a usingdirective, such as
                using namespace std;
    The differences are as follows:
    1 A using declaration (like using std::cout; ) makes only one name in the namespace 
      available to your code, while a using directive (like using namespace std; ) makes 
      all the names in a namespace available.
    2 A using declaration introduces a name (like cout) into your code so that no other 
      use of the name can be made.However,a using directive only potentially introduces 
      the names in the namespace.
    Point 1 is pretty obvious. Point 2 has some subtleties. For example, suppose the 
    namespaces ns1 and ns2 both provide definitions for my_function, but have no other 
    name conflicts. Then the following will produce no problems:
                using namespace ns1;
                using namespace ns2;
    provided that (within the scope of these directives) the conflicting name my_function 
    is never used in your code.On the other hand, the following is illegal, even if the 
    function my_function is never used:
                using ns1::my_function;
                using ns2::my_function;
    Sometimes this subtle point can be important, but it does not impinge on most routine 
    code.

unnamed namespace
    A compilation unit is a file, such as a class implementation file, along with all 
    the files that are #included in the file, such as the interface header file for 
    the class. Every compilation unit has an unnamed namespace.  A namespace grouping 
    for the unnamed namespace is written in the same way as any other namespace, but 
    no name is given, as in the following example:
                namespace
                {
                    void sample_function( )
                    .
                    .
                    .
                } //unnamed namespace

    All the names defined in the unnamed namespace are local to the compilation unit, 
    and thus the names can be reused for something else outside the compilation unit. 

*/
