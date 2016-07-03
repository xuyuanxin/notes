

public class ArrayList<E> extends AbstractList<E> implements List<E>, RandomAccess, Cloneable, Serializable
{

}


/*
--> 
 ArrayList is a generic class with a type parameter. To specify the type of the elem-
 ent objects that the array list holds, you append a class name enclosed in angle br-
 ackets, such as ArrayList<Employee>. 

 Here we declare and construct an array list that holds Employee objects:
 
 ArrayList<Employee> staff = new ArrayList<Employee>();
 
 It is a bit tedious that the type parameter Employee is used on both sides. As of  -
 Java SE 7, you can omit the type parameter on the right-hand side:
 
 ArrayList<Employee> staff = new ArrayList<>();




*/
