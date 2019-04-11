using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SkalProj_Datastrukturer_Minne
{
    class Program
    {
        /// <summary>
        /// The main method, vill handle the menues for the program
        /// </summary>
        /// <param name="args"></param>
        static void Main()
        {

            while (true)
            {

                Console.WriteLine("Please navigate through the menu by inputting the number \n(1, 2, 3 ,4, 0) of your choice"
                    + "\n1. Examine a List"
                    + "\n2. Examine a Queue"
                    + "\n3. Examine a Stack"
                    + "\n4. CheckParanthesis"
                    + "\n0. Exit the application");
                char input = ' '; //Creates the character input to be used with the switch-case below.
                try
                {
                    input = Console.ReadLine()[0];   // Tries to set input to the first char in an input line
                }
                catch (IndexOutOfRangeException)     // If the input line is empty, we ask the users for some input.
                {
                    Console.Clear();
                    Console.WriteLine("Please enter some input!");
                }
                switch (input)
                {
                    case '1':
                        ExamineList();
                        break;
                    case '2':
                        ExamineQueue();
                        break;
                    case '3':
                        ExamineStack();
                        break;
                    case '4':
                        CheckParanthesis();
                        break;
                    /*
                     * Extend the menu to include the recursive 
                     * and iterative exercises.
                     */
                    case '0':
                        return;
                    default:
                        Console.WriteLine("Please enter some valid input (0, 1, 2, 3, 4)");
                        break;
                }
            }
        }

        /// <summary>
        /// Examines the datastructure List
        /// </summary>
        static void ExamineList()
        {
            /*
             * Loop this method untill the user inputs something to exit to main menue.
             * Create a switch statement with cases '+' and '-'
             * '+': Add the rest of the input to the list (The user could write +Adam and "Adam" would be added to the list)
             * '-': Remove the rest of the input from the list (The user could write -Adam and "Adam" would be removed from the list)
             * In both cases, look at the count and capacity of the list
             * As a default case, tell them to use only + or -
             * Below you can see some inspirational code to begin working.
            */

            // Create a string list
            List<string> theList = new List<string>();

            //1.2  If count exeeds capacity while adding elements, the capacity will be automatically increased.
            //1.3  Capacity will be added so that the count is always greater than or equal to count.
            //1.4  leave some extra for effiency? so, more space will be added 
            //1.5  do not decrease capacity when remove list
            //1.6  use the array index to access array element should be little faster than use list. When do element sorting, 
            //     array is perfered over list.

            bool loopOn = true;

            // Give user some instuctions
            Console.WriteLine("And and remove string to the list:"
                + "\n+String, Add the String to the list"
                + "\n-String, Remove the String from the list"
                + "\n0, Back to the main menu");
            do
            {
                // Read from the console
                string userInput;

                userInput = Console.ReadLine();          // Tries to set input to the first char in an input line

                if (string.IsNullOrEmpty(userInput) && userInput.Length > 1)
                {
                    Console.WriteLine("Please int type a string begin with + or -");
                    continue;
                }
                char nav = userInput[0];
                Console.WriteLine("-------->" + nav);
                //char nav = userInput[0];
                ////string input = Console.ReadLine();
                //StringComparison comparison = StringComparison.InvariantCulture;
                //if (userInput.StartsWith(startString1, comparison)) 

                //{
                //    nav = '+';
                //    userString = userInput.Substring(1);
                //}
                //else if (userInput.StartsWith(startString2, comparison))
                //{
                //    nav = '-';
                //    userString = userInput.Substring(1);
                //}
                //else
                //{
                //    continue;
                //}
                string userString;
                switch (nav)
                {
                    case '+':
                        userString = userInput.TrimStart('+');
                        theList.Add(userString);
                        Console.WriteLine("The list count is: " + theList.Count);
                        Console.WriteLine("The list compacity is: " + theList.Capacity);
                        Console.WriteLine(userString + "has been added to the list");
                        break;
                    case '-':
                        userString = userInput.TrimStart('-');
                        if (theList.Remove(userString))
                        {
                            Console.WriteLine(userString + "is successfully removed from the list.");
                        }
                        else
                        {
                            Console.WriteLine(userString + "does not exist on the list.");
                        }
                        Console.WriteLine("The list count is: " + theList.Count);
                        Console.WriteLine("The list capacity is: " + theList.Capacity);
                        break;
                    case '0':
                        loopOn = false;
                        break;
                    default:
                        Console.WriteLine("Try to type in a + or - only without other text");
                        break;
                }
            }
            while (loopOn);
        }


        /// <summary>
        /// Examines the datastructure Queue
        /// </summary>
        static void ExamineQueue()
        {
            /*
             * Loop this method untill the user inputs something to exit to main menue.
             * Create a switch with cases to enqueue items or dequeue items
             * Make sure to look at the queue after Enqueueing and Dequeueing to see how it behaves
            */
            Queue<String> theQueue = new Queue<string>();


            // loop until user input something

            bool loopOn = true;
            char userChoice = ' ';          //Creates the character input to be used with the switch-case below.
            string userString;
            while (loopOn)
            {

                Console.WriteLine("Type 1 to enqueue something to the queue"
                                + "\nType 2 to dequeue one element from the tail of the queue"
                                + "\nType 0 to go back to the main menu");
                //try
                //{
                //    userChoice = Console.ReadLine()[0];      // Tries to set input to the first char in an input line ###### Check more, if type 1xxx, 2xxx, 3xxxx, should not pass here
                //}
                //catch (IndexOutOfRangeException)             // If the input line is empty, we ask the users for some input.
                //{
                //    Console.WriteLine("The input is not right, you need to make a choice from the following! try again!");
                //    continue;
                //}
                try
                {
                    userString = Console.ReadLine();           // Tries to set input to the first char in an input line ###### Check more, if type 1xxx, 2xxx, 3xxxx, should not pass here
                }
                catch (IndexOutOfRangeException)               // If the input line is empty, we ask the users for some input.
                {
                    Console.WriteLine("The input is not right, you need to make a choice from the following! try again!");
                    continue;
                }
                if (userString.Length > 1)
                {
                    Console.WriteLine("The input is not right, Try again!");
                    continue;
                }
                else
                {
                    userChoice = userString[0];
                }

                if (userChoice == '1' || userChoice == '2' || userChoice == '0')
                {
                    switch (userChoice)
                    {
                        case '1':

                            Console.WriteLine("Type something to put into the queue.");
                            string uString = Console.ReadLine();
                            theQueue.Enqueue(uString);
                            Console.WriteLine("Following items is now in the queue:");
                            foreach (string item in theQueue)
                            {
                                Console.WriteLine(item);
                            }

                            break;

                        case '2':
                            //Console.WriteLine("Dequeue an item from the queue.");
                            if (theQueue.Count > 0)
                            {
                                string dequeuedItem = theQueue.Dequeue();
                                Console.WriteLine(dequeuedItem + "has beed dequeued from the queue");
                                if (theQueue.Count > 0)
                                {
                                    Console.WriteLine("The queue has the following items:");
                                    foreach (string item in theQueue)
                                    {
                                        Console.WriteLine(item);
                                    }
                                }
                                else
                                {
                                    Console.WriteLine("The queue is now empty");
                                }
                            }
                            else
                            {
                                Console.WriteLine("The queue is empty");
                            }

                            break;
                        case '0':
                            loopOn = false;
                            break;
                        default:
                            break;

                    }
                }
                else
                {
                    Console.WriteLine("====> Your choice is not right, try again!");
                }

            }
        }

        /// <summary>
        /// Examines the datastructure Stack
        /// </summary>
        static void ExamineStack()
        {
            /*
             * Loop this method until the user inputs something to exit to main menue.
             * Create a switch with cases to push or pop items
             * Make sure to look at the stack after pushing and and poping to see how it behaves
            */
            //Declare a string type stack
            Stack<string> theStack = new Stack<string>();

            Console.WriteLine("Please make one of the following choice");
            bool loopOn = true;
            int userChoice = 0;
            Console.WriteLine("\nType 1 and then type a string to push it on to the stack"
                            + "\nType 2 to pop out a string from the stack"
                            + "\nType 3 to input a string, program will reverse it."
                            + "\nType 0 to return back to the main menu.");
            while (loopOn)
            {
                try
                {
                    userChoice = int.Parse(Console.ReadLine());
                }
                catch (FormatException)
                {
                    Console.WriteLine("Input is Null, try again!");
                    continue;
                }
                catch (ArgumentNullException)
                {
                    Console.WriteLine("Input format is wrong, try again");
                    continue;
                }

                if (userChoice == 1 || userChoice == 2 || userChoice == 0 || userChoice == 3)
                {
                    switch (userChoice)
                    {
                        case 1:
                            Console.WriteLine("Type a string to push onto  the stack");
                            string uString = Console.ReadLine();
                            theStack.Push(uString);
                            Console.WriteLine(uString + "has been pushed onto the stack, now the stack contains:");
                            if (theStack.Peek() != null)
                            {
                                foreach (string str in theStack)
                                {
                                    Console.WriteLine(str + "On the stack");
                                }
                            }
                            else
                            {
                                Console.WriteLine("The stack is empty now.");
                            }
                            break;
                        case 2:
                            if (theStack.Peek() != null)
                            {
                                string poped = theStack.Pop();
                                Console.WriteLine(poped + "has been popped off the stack ");
                            }
                            else
                            {
                                Console.WriteLine("The stack is empty now.");
                            }
                            break;
                        case 3:
                            ReversString();
                            break;

                        case 0:
                            loopOn = false;
                            break;
                    }
                }
                else
                {
                    Console.WriteLine("Wrong Choice, try again!");
                }
            }
        }

        // Ask user to input a string, and then with the help of a stack, reverse the string and display 
        // to user.
        static void ReversString()
        {
            Console.WriteLine("Type in a string and the program will display a reversed string\n");

            string userInput = Console.ReadLine();

            Stack<char> charStack = new Stack<char>(userInput.Length);     // declare a stack with the size fit the user input string

            if (!string.IsNullOrEmpty(userInput))
            {
                foreach (char c in userInput)                             // push the string onto a stack
                {
                    charStack.Push(c);
                }
            }
            else
            {
                Console.WriteLine("Input is wrong! Try again!");
            }

            //// Pop the chars back
            //char[] charArray = new char[charStack.Count];                 // declare a char array which size fit the user string

            //int numberLoops = charStack.Count;
            //for (int i = 0; i < numberLoops; /* charStack.Count;*/ i++)   // note here, the stack.Count changes every time we pop out an element ! 
            //{
            //    charArray[i] = charStack.Pop();
            //}

            //string reversedString = new string(charArray);                // create a string from the char array.

            //Console.WriteLine("The reversed string is: " + reversedString);
            foreach (var item in charStack)
            {
                Console.Write(item);
            }
       
        }

        ////public static string reverse(string str)
        ////{
        ////    char[] charArr = str.ToCharArray();
        ////    int size = charArr.Length;
        ////    Stack<char> stack = new Stack<char>(size);
        ////    int i;
        ////    for (i = 0; i < size; ++i)
        ////    {
        ////        stack.Push(charArr[i]);
        ////    }
        ////    for (i = 0; i < size; ++i)
        ////    {
        ////        charArr[i] = stack.Pop();
        ////    }
        ////    string reverseString = new string(charArr);
        ////    return reverseString;
        ////    return string.Va .ValueOf(charArr);
        ////}


        static void CheckParanthesis()
        {
            /*
             * Use this method to check if the paranthesis in a string is Correct or incorrect.
             * Example of correct: (()), {}, [({})]
             * Example of incorrect: (()]), [), {[()}]
             */
            
            Dictionary<char, char> ParanthesisPairs = new Dictionary<char, char>()
                    {
                        {'(', ')'},
                        {'[', ']'},
                        {'{', '}'}
                    };

            // declare a stack
            Stack<char> charStack = new Stack<char>();
            Console.WriteLine("Please type in the brackets pattern:");
            string userInput = Console.ReadLine();
            bool isGood = true;
            if (!string.IsNullOrEmpty(userInput))
            {
                foreach (char c in userInput)                                // walk through the chars on the string
                {
                    if (ParanthesisPairs.Keys.Contains(c))                  // if it is a key(a open paranthesis) in the dictionary
                    {
                        charStack.Push(c);                                  // push it onto the stack
                    }
                    else if (ParanthesisPairs.Values.Contains(c))           // If it is a value(a closing bracket) in the dictionary
                    {
                        if (charStack.Count > 0)                            // Make sure that there is a key on the stack, so we do not operate with empty stack
                        {
                            if (c == ParanthesisPairs[charStack.First()])   // ...further check to see if the first(last pushed opening bracket) on the stack match the key
                            {
                                charStack.Pop();                            // if so, we get a march, and pop the open bracket(key) off the stack (this pair is done)
                            }
                            else
                            {
                                break;                                      // a mismatch, there still a key(open braket) on stack, that means pattern is bad
                            }
                        }
                        else
                        {
                            isGood = false;                                 // mis match, there is more value than key.
                            break;
                        }
                    }
                    else
                    {
                        continue;
                    }
                }

                if (charStack.Count == 0 && isGood)
                {
                    Console.WriteLine("\nThe brackets pattern " + userInput + " is good!\n");
                }
                else
                {
                    Console.WriteLine("\nThe brackets pattern " + userInput + " is NOT good!\n");
                }
            }
            else
            {
                Console.WriteLine("Wrong input! try again!");
            }
        }

        // Take an user string as argument and check to see if the paranthesis is in good shape (balanced)
        static bool CheckParantheses(string userInput)
        {
            Dictionary<char, char> ParanthesisPairs = new Dictionary<char, char>()
                    {
                        {'(', ')'},
                        {'[', ']'},
                        {'{', '}'}
                    };

            // declare a stack
            Stack<char> charStack = new Stack<char>();
            
            bool isGood = true;
            if (!string.IsNullOrEmpty(userInput))                            // check to make sure it is not null
            {
                foreach (char c in userInput)                                // walk through the chars on the string
                {
                    if (ParanthesisPairs.Keys.Contains(c))                  // if it is a key(a open paranthesis) in the dictionary
                    {
                        charStack.Push(c);                                  // push it onto the stack
                    }
                    else if (ParanthesisPairs.Values.Contains(c))           // If it is a value(a closing bracket) in the dictionary
                    {
                        if (charStack.Count > 0)                            // Make sure that there are key on the stack, so we do not operate on empty stack
                        {
                            if (c == ParanthesisPairs[charStack.First()])   // further check to see if the first(last pushed opening bracket) on the stack match the key
                            {
                                charStack.Pop();                            // if so, we get a march, and pop the open bracket(key) off the stack
                            }
                            else
                            {
                                break;
                            }
                        }
                        else
                        {
                            isGood = false;
                            break;
                        }
                    }
                    else
                    {
                        continue;
                    }
                }

            }
            if (charStack.Count == 0 && isGood)
            {
                Console.WriteLine("\nThe brackets pattern " + userInput + " is good!\n");
                return true;
            }
            else
            {
                Console.WriteLine("\nThe brackets pattern " + userInput + " is NOT good!\n");
                return false;
            }
        }
    }
}
    



