//package arrayList;
import java.util.*;

public class ArrayListTest
{
   public static void main(String[] args)
   {
      ArrayList<EmployeeAl> staff = new ArrayList<>();

      staff.add(new EmployeeAl("Carl Cracker", 75000, 1987, 12, 15));
      staff.add(new EmployeeAl("Harry Hacker", 50000, 1989, 10, 1));
      staff.add(new EmployeeAl("Tony Tester", 40000, 1990, 3, 15));

      // raise everyone's salary by 5%
      for (EmployeeAl e : staff)
         e.raiseSalary(5);

      // print out information about all Employee objects
      for (EmployeeAl e : staff)
         System.out.println("name=" + e.getName() + ",salary=" + e.getSalary() + ",hireDay="
               + e.getHireDay());
   }
}

/*-----------------------------------------------------------------------------------
 ArrayList is a generic class with a type parameter.
 
 Here we declare and construct an array list that holds Employee objects:
     ArrayList<Employee> staff = new ArrayList<Employee>();
 It is a bit tedious that the type parameter Employee is used on both sides. As of J-
 ava 7, you can omit the type parameter on the right-hand side:
     ArrayList<Employee> staff = new ArrayList<>();

 ---> set get
 to set the ith element, you use
     staff.set(i, harry);
 This is equivalent to
     a[i] = harry;
 for an array a. (As with arrays, the index values are zero-based.)

 Caution
 Do not call list.set(i, x) until the size of the array list is larger than i. For e-
 xample, the following code is wrong:
     ArrayList<Employee> list = new ArrayList<>(100); // capacity 100, size 0
     list.set(0, x); // no element 0 yet
 Use the add method instead of set to fill up an array, and use set only to replace -
 a previously added element.

 To get an array list element, use
     Employee e = staff.get(i);
 This is equivalent to
     Employee e = a[i];



 java.util.ArrayList<T> 1.2
 
 ArrayList<T>()
 constructs an empty array list.

 ArrayList<T>(int initialCapacity)
 constructs an empty array list with the specified capacity.

 boolean add(T obj)
 appends an element at the end of the array list. Always returns true.

 void add(int index, T obj)
 shifts up elements to insert an element.

 int size()
 returns the number of elements currently stored in the array list. (Of course , this 
 is never larger than the array list's capacity.)

 void ensureCapacity(int capacity)
 ensures that the array list has the capacity to store the given number of elements -
 without reallocating its internal storage array.
 
 void trimToSize()
 reduces the storage capacity of the array list to its current size

 void set(int index, T obj)
 puts a value in the array list at the specified index, overwriting the previous con-
 tents.
 
 T get(int index)
 gets the value stored at a specified index.

 T remove(int index)
 removes an element and shifts down all elements above it. The removed element is re-
 turned. 
 ----------------------------------------------------------------------------------*/

