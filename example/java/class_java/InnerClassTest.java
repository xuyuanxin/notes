//package innerClass;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import javax.swing.Timer;

public class InnerClassTest
{
   public static void main(String[] args)
   {
      TalkingClock clock = new TalkingClock(2000, true);
      clock.start();

      // keep program running until user selects "Ok"
      JOptionPane.showMessageDialog(null, "Quit program?");
      System.exit(0);
   }
}

/**
 * A clock that prints the time in regular intervals.
 */
class TalkingClock
{
   private int interval;
   private boolean beep;

   /**
    * Constructs a talking clock
    * @param interval the interval between messages (in milliseconds)
    * @param beep true if the clock should beep
    */
   public TalkingClock(int interval, boolean beep)
   {
      this.interval = interval;
      this.beep = beep;
   }

   /**
    * Starts the clock.
    */
   public void start()
   {
      ActionListener listener = new TimePrinter();
      Timer t = new Timer(interval, listener);
      t.start();
   }

/*-----------------------------------------------------------------------------------
 The @TimePrinter class has no instance field or variable named @beep. An inner class 
 method gets to access both its own data fields and those of the outer object creati-
 ng it. For this to work, an object of an inner class always gets an implicit refere-
 nce to the object that created it. This reference  is invisible in the definition of 
 the inner class. However, to illuminate the concept, let us call the reference to t-
 he outer object outer. Then, the actionPerformed method is equivalent to the follow-
 ing:
     public void actionPerformed(ActionEvent event)
     {
         Date now = new Date();
         System.out.println("At the tone, the time is " + now);
         if (outer.beep) Toolkit.getDefaultToolkit().beep();
     }
 The outer class reference is set in the constructor. The compiler modifies all inner
 class constructors, adding a parameter for the outer class reference.The TimePrinter
 class defines no constructors; therefore, the compiler synthesizes a no-argument co-
 nstructor, generating code like this:
     public TimePrinter( TalkingClock clock) // automatically generated code
     {
         outer = clock;
     }
 Again, please note, @outer is not a Java keyword. We just use it to illustrate the -
 mechanism involved in an inner class.

 When a TimePrinter object is constructed in the start method, the compiler passes t-
 he @this reference to the current talking clock into the constructor:
     ActionListener listener = new TimePrinter(this);// parameter automatically added
-----------------------------------------------------------------------------------*/
   public class TimePrinter implements ActionListener // an inner class
   {
      public void actionPerformed(ActionEvent event)
      {
         Date now = new Date();
         System.out.println("At the tone, the time is " + now);
         if (beep) Toolkit.getDefaultToolkit().beep();
      }
   }
}



/*-----------------------------------------------------------------------------------
 ----> Special Syntax Rules for Inner Classes
 In the preceding section, we explained the outer class reference of an inner class -
 by calling it @outer. Actually, the proper syntax for the outer reference is a bit -
 more complex. The expression
      OuterClass.this
 denotes the outer class reference. For example, you can write the actionPerformed m-
 ethod of the TimePrinter inner class as
     public void actionPerformed(ActionEvent event)
     {
         . . .
         if (TalkingClock.this.beep) Toolkit.getDefaultToolkit().beep();
     }
     
 Conversely, you can write the inner object constructor more explicitly, using the s-
 yntax
     outerObject.new InnerClass(construction parameters)
 For example:
     ActionListener listener = this.new TimePrinter();
 Here, the outer class reference of the newly constructed TimePrinter object is set -
 to the @this reference of the method that creates the inner class object. This is t-
 he most common case. As always, the this. qualifier is redundant. However, it is al-
 so possible to set the outer class reference to another object by explicitly  naming 
 it. For example, since TimePrinter is a public inner class, you can construct a Tim-
 ePrinter for any talking clock:
     TalkingClock jabberer = new TalkingClock(1000, true);
     TalkingClock.TimePrinter listener = jabberer.new TimePrinter();
  Note that you refer to an inner class as
      OuterClass.InnerClass
 when it occurs outside the scope of the outer class.

 ----> Local Inner Classes
 If you look carefully at the code of the TalkingClock example, you will find that y-
 ou need the name of the type TimePrinter only once: when you create an object of th-
 at type in the start method.
 In a situation like this, you can define the class locally in a single method.
     public void start()
     {
         class TimePrinter implements ActionListener
         {
             public void actionPerformed(ActionEvent event)
             {
                 Date now = new Date();
                 System.out.println("At the tone, the time is " + now);
                 if (beep) Toolkit.getDefaultToolkit().beep();
             }
         }
         ActionListener listener = new TimePrinter();
         Timer t = new Timer(interval, listener);
         t.start();
     }
 Local classes are never declared with an access specifier (that is, public or priva-
 te). Their scope is always restricted to the block in which they are declared. Local 
 classes have one great advantage: They are completely hidden from the outside  world
 not even other code in the TalkingClock class can access them.No method except start 
 has any knowledge of the TimePrinter class.

 ----> Timer
 The javax.swing package contains a @Timer class that is useful if you want to be no-
 tified whenever a time interval has elapsed . The timer requires that you specify an 
 object of a class that implements the ActionListener interface of the java.awt.event 
 package. Here is that interface:
     public interface ActionListener
     {
         void actionPerformed(ActionEvent event);
     }
 The timer calls the actionPerformed method when the time interval has expired.

 Suppose you want to print a message "At the tone, the time is . . ." , followed by -
 a beep, once every 10 seconds. 
 1 You would define a class that implements the ActionListener interface.
     class TimePrinter implements ActionListener
     {
         public void actionPerformed(ActionEvent event)
         {
             Date now = new Date();
             System.out.println("At the tone, the time is " + now);
             Toolkit.getDefaultToolkit().beep();
         }
     }
 Note the ActionEvent parameter of the actionPerformed method. This parameter gives i-
 nformation about the event, such as the source object that generated. However, detai-
 led information about the event is not important in this program , and you can safely 
 ignore the parameter.

 2 Next, you construct an object of this class and pass it to the @Timer constructor.
     ActionListener listener = new TimePrinter();
     Timer t = new Timer(10000, listener);
 The first parameter of the Timer constructor is the time interval that must elapse -
 between notifications, measured in milliseconds. We want to be notified every 10 se-
 conds. The second parameter is the listener object.

 3 Finally, you start the timer.
     t.start();
 Every 10 seconds, a message like
     At the tone, the time is Thu Apr 13 23:29:08 PDT 2000
 is displayed, followed by a beep.


 After the timer is started, the program puts up a message dialog and waits for the -
 user to click the Ok button to stop. While the program waits for the user, the curr-
 ent time is displayed at 10-second intervals.
 Be patient when running the program. The "Quit program?" dialog box appears right a-
 way, but the first timer message is displayed after 10 seconds.

 Note that the program imports the javax.swing.Timer class by name, in addition to i-
 mporting javax.swing.* and java.util.*. This breaks the ambiguity between javax.swing.Timer 
 and java.util.Timer, an unrelated class for scheduling background tasks.
-----------------------------------------------------------------------------------*/
