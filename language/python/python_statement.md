# Part--Statements and Syntax  

# Introducing Python Statements  

In simple terms, statements are the things you write to tell Python what your programs should do.  Less informally, Python is a procedural, statement-based language; by combining statements, you specify a procedure that Python performs to satisfy a program’s goals.  

## Python’s Statements

Table 10-1 summarizes Python’s statement set. Each statement in Python has its own specific purpose and its own specific syntax—the rules that define its structure— though, as we’ll see, many share common syntax patterns, and some statements’ roles overlap. Table 10-1 also gives examples of each statement, when coded according to its syntax rules. In your programs, these units of code can perform actions, repeat tasks, make choices, build larger program structures, and so on.  





# Assignments, Expressions, and Prints

## Assignment Statements  

In its basic form, you write the target of an assignment on the left of an equals sign, and the object to be assigned on the right. The target on the left may be a name or object component, and the object on the right can be an arbitrary expression that computes an object.  

- **Assignments create object references.** Python assignments store references to objects in names or data structure components. They always create references to objects instead of copying the objects. Because of that, Python variables are more like pointers than data storage areas.  
- **Names are created when first assigned.**  Python creates a variable name the first time you assign it a value, so there’s no need to predeclare names ahead of time.  Once assigned, a name is replaced with the value it references whenever it appears in an expression.  
- **Names must be assigned before being referenced.** It’s an error to use a name to which you haven’t yet assigned a value. Python raises an exception if you try, rather than returning some sort of ambiguous default value.   
- **Some operations perform assignments implicitly.** In this section we’re concerned with the = statement, but assignment occurs in many contexts in Python. For instance, we’ll see later that module imports, function and class definitions, for loop variables, and function arguments are all implicit assignments. Because assignment works the same everywhere it pops up, all these contexts simply bind names to object references at runtime.  

Table 11-1. Assignment statement forms Operation Interpretation

| spam = 'Spam'                | Basic form                                                   |
| ---------------------------- | ------------------------------------------------------------ |
| spam, ham = 'yum', 'YUM'     | Tuple assignment (positional)                                |
| [spam, ham] = ['yum', 'YUM'] | List assignment (positional)                                 |
| a, b, c, d = 'spam'          | Sequence assignment, generalized.a is assigned 's', b is assigned 'p', and so on. |
| a, *b = 'spam'               | Extended sequence unpacking (Python 3.X). a is assigned 's', and b is assigned 'pam'. |
| spam = ham = 'lunch'         | Multiple-target assignment. The effect is the same as if we had<br/>coded ham = 'lunch' followed by spam = ham, as ham evaluates to the original string object |
| spams += 42                  | Augmented assignment (equivalent to spams = spams + 42)      |

### Sequence Assignments  

```python
% python
>>> nudge = 1 # Basic assignment
>>> wink = 2
>>> A, B = nudge, wink # Tuple assignment, omitted their enclosing parentheses
>>> A, B # Like A = nudge; B = wink
(1, 2)
>>> [C, D] = [nudge, wink] # List assignment
>>> C, D
(1, 2)
```

Because Python creates a temporary tuple that saves the original values of the variables on the right while the statement runs, unpacking assignments are also a way to swap two variables’ values without creating a temporary variable of your own—the tuple on the right remembers the prior values of the variables automatically:  

```python
>>> nudge = 1
>>> wink = 2
>>> nudge, wink = wink, nudge # Tuples: swaps values
>>> nudge, wink # Like T = nudge; nudge = wink; wink = T
(2, 1)
```

In fact, the original tuple and list assignment forms in Python have been generalized to accept any type of sequence (really, iterable) on the right as long as it is of the same length as the sequence on the left. You can assign a tuple of values to a list of variables, a string of characters to a tuple of variables, and so on. In all cases, Python assigns items in the sequence on the right to variables in the sequence on the left by position, from left to right:  

```python
>>> [a, b, c] = (1, 2, 3) # Assign tuple of values to list of names
>>> a, c
(1, 3)
>>> (a, b, c) = "ABC" # Assign string of characters to tuple
>>> a, c
('A', 'C')
```

Technically speaking, sequence assignment actually supports any iterable object on the right, not just any sequence. 

Although we can mix and match sequence types around the = symbol, we must generally have the same number of items on the right as we have variables on the left, or we’ll get an error. 

```python
>>> string = 'SPAM'
>>> a, b, c, d = string # Same number on both sides
>>> a, d
('S', 'M')
>>> a, b, c = string # Error if not
...error text omitted...
ValueError: too many values to unpack (expected 3)
```

To be more flexible, we can slice in both 2.X and 3.X. There are a variety of ways to employ slicing to make this last case work:  

```python
>>> a, b, c = string[0], string[1], string[2:] # Index and slice
>>> a, b, c
('S', 'P', 'AM')
>>> a, b, c = list(string[:2]) + [string[2:]] # Slice and concatenate
>>> a, b, c
('S', 'P', 'AM')
>>> a, b = string[:2] # Same, but simpler
>>> c = string[2:]
>>> a, b, c
('S', 'P', 'AM')
>>> (a, b), c = string[:2], string[2:] # Nested sequences
>>> a, b, c
('S', 'P', 'AM')
```

As the last example in this interaction demonstrates, we can even assign nested sequences, and Python unpacks their parts according to their shape, as expected.

```python
>>> ((a, b), c) = ('SP', 'AM') # Paired by shape and position
>>> a, b, c
('S', 'P', 'AM')

for (a, b, c) in [(1, 2, 3), (4, 5, 6)]: ... # Simple tuple assignment
for ((a, b), c) in [((1, 2), 3), ((4, 5), 6)]: ... # Nested tuple assignment
```

In this event, the sequence-nesting shape of the object on the left must match that of the object on the right. Nested sequence assignment like this is somewhat rare to see, but it can be convenient for picking out the parts of data structures with known shapes.

## Expression Statements  

In Python, you can use an expression as a statement, too—that is, on a line by itself. But because the result of the expression won’t be saved, it usually makes sense to do so only if the expression does something useful as a side effect. Expressions are commonly used as statements in two situations:  

- For calls to functions and methods. Some functions and methods do their work without returning a value. Such functions are sometimes called procedures in other languages. Because they don’t return values that you might be interested in retaining, you can call these functions with expression statements.
- For printing values at the interactive prompt. Python echoes back the results of expressions typed at the interactive command line. Technically, these are expression statements, too; they serve as a shorthand for typing print statements.  

Table 11-4. Common Python expression statements Operation Interpretation

| spam(eggs, ham)        | Function calls                                    |
| ---------------------- | ------------------------------------------------- |
| spam.ham(eggs)         | Method calls                                      |
| spam                   | Printing variables in the interactive interpreter |
| print(a, b, c, sep='') | Printing operations in Python 3.X                 |
| yield x ** 2           | Yielding expression statements                    |

printing in Python 3.X is a function call usually coded on a line by itself, and the yield operation in generator functions (discussed in Chapter 20) is often coded as a statement as well. Both are really just instances of expression statements.  

This brings up another mistake that is common in Python work. Expression statements are often used to run list methods that change a list in place:

```python
>>> L = [1, 2]
>>> L.append(3) # Append is an in-place change
>>> L
[1, 2, 3]
```

However, it’s not unusual for Python newcomers to code such an operation as an assignment statement instead, intending to assign L to the larger list:

```python
>>> L = L.append(4) # But append returns None, not L
>>> print(L) # So we lose our list!
None
```

This doesn’t quite work, though. Calling an in-place change operation such as append, sort, or reverse on a list always changes the list in place, but these methods do not return the list they have changed; instead, they return the None object.  









## 参考：

learning python （python学习手册）





expression : 是什么

比如: 1+2是3, 1+2就是expression, 3 就是expression的 value



statement: 做什么

比如: a = 1, 把 a 绑定到整数1上, 并没有什么value 返回, 只是一个动作而已.



Expression是有值的。一个函数调用（Function Call）是一个表达式，一个普通的运算例如![[公式]](https://www.zhihu.com/equation?tex=x%5E2%2B2x%2B1)是一个表达式

Statement是没有值的。一个函数定义（Function Definition）是一个声明，一个赋值语句是一个声明