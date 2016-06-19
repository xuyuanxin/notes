

public class ArrayList<E> extends AbstractList<E> implements List<E>, RandomAccess, Cloneable, Serializable
{

}


/*
Here we declare and construct an array list that holds Employee objects:
ArrayList<Employee> staff = new ArrayList<Employee>();
It is a bit tedious that the type parameter Employee is used on both sides. As of Java
SE 7, you can omit the type parameter on the right-hand side:
ArrayList<Employee> staff = new ArrayList<>();




*/
