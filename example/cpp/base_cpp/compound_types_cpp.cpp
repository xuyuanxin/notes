/*-----------------------------------------------------------------------------------
A compound type is a type that is defined in terms of another type. C++ has several -
compound types, two of which (references and pointers) we'll cover in this chapter.

Simple declarations consist of a type followed by a list of variable names. More gen-
erally, a declaration is a base type followed by a list of declarators. Each declara-
tor names a variable and gives the variable a type that is related to the base  type.
The declarations we have seen so far have declarators that are nothing more than var-
iable names. The type of such variables is the base type of the declaration. More co-
mplicated declarators specify variables with compound types that are built from the -
base type of the declaration.

----> References
A reference defines an alternative name for an object. A reference type "refers to" -
another type. Technically speaking, when we use the term reference, we mean "lvalue -
reference".

We define a reference type by writing a declarator of the form &d, where d is the na-
me being declared:
    int ival = 1024;
    int &refVal = ival; // refVal refers to (is another name for) ival
    int &refVal2;       // error: a reference must be initialized
Ordinarily, when we initialize a variable, the value of the initializer is copied in-
to the object we are creating. When we define a reference, instead of copying the in-
itializer's value, we bind the reference to its initializer. Once initialized, a ref-
erence remains bound to its initial object. There is no way to rebind a reference  to 
refer to a different object. Because there is no way to rebind a reference,references 
must be initialized.
---> A Reference Is an Alias
A reference is not an object. Instead, a reference is just another name for an alrea-
dy existing object. After a reference has been defined, all operations on that refer-
ence are actually operations on the object to which the reference is bound. Because -
references are not objects, we may not define a reference to a reference.
    refVal = 2; // assigns 2 to the object to which refVal refers, i.e., to ival
    int ii = refVal; // same as ii = ival
    // ok: refVal3 is bound to the object to which refVal is bound, i.e., to ival
    int &refVal3 = refVal;
    // initializes i from the value in the object to which refVal is bound
    int i = refVal; // ok: initializes i to the same value as ival
----> Reference Definitions
We can define multiple references in a single definition. Each identifier that is a -
reference must be preceded by the & symbol:
    int i = 1024, i2 = 2048; // i and i2 are both ints
    int &r = i, r2 = i2;     // r is a reference bound to i; r2 is an int
    int i3 = 1024, &ri = i3; // i3 is an int; ri is a reference bound to i3
    int &r3 = i3, &r4 = i2;  // both r3 and r4 are references
With two exceptions that we'll cover in 2.4.1 (p. 61) and 15.2.3 (p. 601), the type -
of a reference and the object to which the reference refers must match exactly. More-
over, for reasons we'll explore in 2.4.1, a reference may be bound only to an object, 
not to a literal or to the result of a more general expression:
    int &refVal4 = 10;   // error: initializer must be an object
    double dval = 3.14;
    int &refVal5 = dval; // error: initializer must be an int object