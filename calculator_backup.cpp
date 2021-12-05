/*
	calculator08buggy.cpp | From: Programming -- Principles and Practice Using C++, by Bjarne Stroustrup
	We have inserted 3 bugs that the compiler will catch and 3 that it won't.
*/

#include "std_lib_facilities.h"

struct Token {

	char kind;

	double value;

	string name;

	Token(char ch) :kind(ch), value(0), name("") { }

	Token(char ch, double val) :kind(ch), value(val), name("") { }

    Token(char ch, string str) :kind(ch), value(0), name(str) { }

};

class Token_stream {
	
	bool full;
	
	Token buffer;

    public:
	
	    Token_stream() :full(0), buffer(0) { }

	    Token get();
	
	    void unget(Token t) { buffer = t; full = true; }

	    void ignore(char);

};

const char LET = 'L';

const char QUIT = 'Q';

const char PRINT = ';';

const char NUMBER = '8';

const char NAME = 'a';

const char CONST = 'c';

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

struct Variable {
	
	string name;
	
	double value;

    bool constant;

    Variable(string n, double v, bool c) :name(n), value(v), constant(c) { }

};

vector<Variable> names;

double get_value(string s){
	
	for (int i = 0; i < names.size(); ++i){
	
		if (names[i].name == s){ 
            
            return names[i].value;
        
        }
    
    }
	
	error("get: undefined NAME ", s);

	return 0;

}

void set_value(string s, double d){

	for (int i = 0; i <= names.size(); ++i)

		if (names[i].name == s) {

            if(names[i].constant){

                error("Cannot change the value of a constant");

            }

			names[i].value = d;

			return;

		}

	error("set: undefined NAME ", s);

}

bool is_declared(string s){

	for (int i = 0; i < names.size(); i++)

		if (names[i].name == s){ 

            //cout << names[i].name;
            
            return true;

        }

	return false;

}

Token_stream ts;

double expression();

double primary()
{

	Token t = ts.get();

	switch (t.kind) {

	    case '(':{	

		    double d = expression();

		    t = ts.get();

		    if (t.kind != ')'){
		
			    error("'(' expected");
		
		    }

            return d;

	    }

	    case '-':{

			double temp = -1*primary();

			if(temp == 0 && signbit(temp)){

				return -1*temp;

			}

			return temp;
		
		}

	    case NUMBER:{

		    return t.value;

        }

	    case NAME:{

		    return get_value(t.name);

        }

	    default:{

		    error("primary expected");

        }

	}

	return -1;

}

double term(){

	double left = primary();
	
	while (true) {
	
		Token t = ts.get();
	
		switch (t.kind) {
	
			case '*':{

				left *= primary();
	
				if(left == 0 && signbit(left) == 1){

					left *= -1;

				}

				break;
		
			}
	
			case '/':{	
			
				double d = primary();
	
				if (d == 0){ 
					
					error("divide by zero");
				
				}

				left /= d;
	
				break;
	
			}

			default:{
		
				ts.unget(t);
		
				return left;
		
			}

		}
	}
}

double expression(){
	
	double left = term();
	
	while (true) {
		
		Token t = ts.get();
		
		switch (t.kind) {
			
			case '+':{
			
				left += term();
			
				break;
			}
			
			case '-':{
			
				left -= term();
			
				break;

			}
			
			default:{
			
				ts.unget(t);
			
				return left;
			}

		}

	}

}


double declaration(bool constant){

	Token t = ts.get();

	if (t.kind != NAME){ 
		
		error("Name expected in declaration");
	}

	string name = t.name;

	Token t2 = ts.get();

	if (t2.kind != '='){ 
		
		error("= missing in declaration of ", name);

	}

	double d = expression();

    if(is_declared(name)){

        set_value(name, d);

    }

    else{

        if(constant){

            names.push_back(Variable(name, d, true));

        }

        else{
    
            names.push_back(Variable(name, d, false));

        }

    }

	return d;

}

double statement(){

	Token t = ts.get();
	
	if (t.kind == LET) {
		
		return declaration(false);
	
	}

    else if (t.kind == CONST){

        return declaration(true);

    }

	else{
	
		ts.unget(t);
	
    	return expression();
	
	}

}

void clean_up_mess(){

	ts.ignore(PRINT);

}

const string prompt = "> ";

const string result = "= ";

void calculate()
{

	while (true) try {

		cout << prompt;

		Token t = ts.get();

		while (t.kind == PRINT){ 
			
			t = ts.get();
		
		}
		
		if (t.kind == QUIT){ 
			
			return;

		}

		ts.unget(t);

		cout << result << statement() << endl;
	
	}

	catch (runtime_error& e) {
	
		cerr << e.what() << endl;
	
		clean_up_mess();
	
	}

}

int main(){

    try {

	    calculate();

	    return 0;

    }

    catch (exception& e) {

	    cerr << "exception: " << e.what() << endl;

	    char c;

	    while (cin >> c && c != ';');

	    return 1;

    }

    catch (...) {

	    cerr << "exception\n";

	    char c;

	    while (cin >> c && c != ';');

	    return 2;

    }

}