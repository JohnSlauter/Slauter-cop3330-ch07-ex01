/*
 *  UCF COP3330 Fall 2021 Assignment 6 Solution
 *  Copyright 2021 first_name last_name
 */

#include "Token_stream.h"

Token Token_stream::get()
{

    /*
        if there is something in the buffer,
        then return it and set full to false
    */

	if (full){ 
    
        full = false; 
    
        return buffer; 
    
    }

	char ch;

	cin >> ch;

	switch (ch) {
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case ';':
	case '=':
		return Token(ch);	
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':{

        /* 
            if the character is a number, 
            then it should be read as a double
        */

		cin.unget();

		double val;

		cin >> val;

		return Token(NUMBER, val);
        
	}

	    default:{

		    if (isalpha(ch) || ch == '_') {
			
			    string s;

			    s += ch;

			    while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')){ 
            
                    //CHANGE: s = ch; -> s += ch;

                    s += ch;
            
                }
			
			    cin.unget();
			
			    if (s == "LET"){ 
            
                    return Token(LET);
            
                }

                if (s == "CONST"){

                    return Token(CONST);

                }
			
			    if (s == "QUIT"){ 

                    //CHANGE: return Token(NAME); -> return TOKEN(QUIT); 
                
                    return Token(QUIT);
            
                }
			
			    return Token(NAME, s);
		
		    }

		    error("Bad token");

	    }

    }

    return 0;

}

void Token_stream::ignore(char c)
{
	
	if (full && c == buffer.kind) {
	
		full = false;
	
		return;
	
	}
	
	full = false;
	
	char ch;
	
	while (cin >> ch){
	
		if (ch == c){

			return;
	
		}
	
	}

}