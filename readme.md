1). Using the Calculator:
    The calculator prompts for input with ">" and precedes the result of the input with "=".
    Supported Operations: Addition (+), Subtraction (-), Multiplication (*), Division (/), Power (See Section 2), Square Root(See Section 3).
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

2). Power:
    To perform a power operation, use the keyword "POW" followed by parathesis enclosing the operands. 
    Within the parenthesis, type the base followed by ",", and then the exponent.
    
    Example
    > POW(2, 4);
    = 16

3). Square Root:
    To perform a square root operation, use the keyword "SQRT" followed by parenthesis enclosing the operand.
    
    Example
    > SQRT(64);
    = 8

4). Variables:
    Variables are named entities that store values.
    They are declared with the "LET" keyword.
    Variable names are case-sensitive and must start with a alphabetical character or an underscore.
    Variable names must be following by "=" and the value that it will store.
    Variables cannot have the name as a keyword. Keywords include "LET", "CONST", "POW", "SQRT", and "QUIT".
    Variables can used in expressions.
  
    Example
    > LET x = 4;
    = 4
    > x + 4;
    = 8
    
4a). Variables and Expressions:
     The value stored by a variable can be an expression.
     The calculator will evaluate the expression and the variable will store the result.
     
     Example
     > LET _x = 12*16;
     = 192
     
4b). Reassigning Variables:
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
     
5). Constants:
    Constants are variables that cannot have their value changed.
    They are declared with the "CONST" keyword.
    
    Example: 
    > CONST C = 12; 
    = 12
    
6). Exiting the Application:
    To exit the application, type QUIT; in response to the prompt symbol (>).
    
    Example: 
    > QUIT;
