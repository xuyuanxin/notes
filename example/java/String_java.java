/*-----------------------------------------------------------------------------------
Conceptually, Java strings are sequences of Unicode characters. For example, the str-
ing "Java\u2122" consists of the five Unicode characters J, a, v, a, and ^TM. Java d-
oes not have a built-in string type. Instead, the standard Java library contains a p-
redefined class called, naturally enough, String. Each quoted string is an instance -
of the String class:
    String e = ""; // an empty string
    String greeting = "Hello";
