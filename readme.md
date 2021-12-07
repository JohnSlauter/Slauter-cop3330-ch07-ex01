1). Using the Calculator
    The calculator prompts for input with ">" and precedes the result of the input with "=".
    Supported Operations: Addition (+), Subtraction (-), Multiplication (*), Division (/).
    To submit input, type ";".
    
    Example
    > 1 + 2;
    = 3
    > 87 - 5;
    = 82
    > 4 * 7;
    = 28
    > 7 / 5;
    = 1.4;

2). Variables
    Variables are named entities that store values.
    They are declared with the "LET" keyword.
    Variable names are case-sensitive and must start with a alphabetical character or an underscore.
    Variable names must be following by "=" and the value that it will store.
    Variables can used in expressions.
  
    Example
    > LET x = 4;
    = 4
    > x + 4;
    = 8
    
2a). Variables and Expressions
     The value stored by a variable can be an expression.
     The calculator will evaluate the expression and the variable will store the result.
     
     Example
     > LET _x = 12*16;
     = 192
     
2b). Reassigning Variables
     The value stored by a variable can be changed by redeclaring the variable the "LET" keyword  
     or by stating the variable name "=" the new value.
     
     Example
     Suppose that y is a variable storing the value 23
     > y;
     = 23
     > LET y = 104;
     = 104
     > y;
     = 104
     > y = 61;
     = 61
     > y;
     = 61
     
3). Constants
    Constants are variables that cannot have their value changed.
    They are declared with the "CONST" keyword.
    
    Example: 
    > CONST C = 12; 
    = 12
    
4). Exiting the Application
    To exit the application, type QUIT; in response to the prompt symbol (>).
    
    Example: 
    > QUIT;
