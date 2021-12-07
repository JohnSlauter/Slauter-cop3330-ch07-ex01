/*
 *  UCF COP3330 Fall 2021 Assignment 6 Solution
 *  Copyright 2021 John Slauter
 */

#include "calculator.h"

using namespace calculator;

Variable* calculator::get(string s){

	for (int i = 0; i < names.size(); ++i){
	
		if (names[i].name == s){ 
            
            return &names[i];
        
        }
    
    }

	error("Undefined name ", s);

}

double calculator::get_value(string s){

	try{

		return get(s)->value;

	}

	catch(exception& e){		

		error("get: ", e.what());

	}

}

void calculator::set_value(string s, double d){

	try{

		Variable* target = get(s);

		if(target->constant){

			error("Cannot change the value of constant ", s);

		}

		target->value = d;	

	}

	catch(exception& e){

		error("set: ", e.what());

	}

}

bool calculator::is_declared(string s){

	for (int i = 0; i < names.size(); i++)

		if (names[i].name == s){ 
            
            return true;

        }

	return false;

}

double calculator::primary()
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

			return negative_zero_check(-1*primary());
		
		}

	    case NUMBER:{

		    return t.value;

        }

	    case NAME:{

			Token t2 = ts.get();

			ts.unget(t2);

			if(t2.kind == '='){

				return assign(t.name);

			}

		    return get_value(t.name);

        }

	    default:{

		    error("primary expected");

        }

	}

	return -1;

}

double calculator::term(){

	double left = primary();
	
	while (true) {
	
		Token t = ts.get();
	
		switch (t.kind) {
	
			case '*':{

				left *= primary();
	
				negative_zero_check(left);

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

double calculator::expression(){
	
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


double calculator::declaration(bool constant){

	Token t = ts.get();

	if (t.kind != NAME){ 
		
		error("Name expected in declaration");
	}

	string name = t.name;

	if(is_declared(name)){

        return assign(name);

    }

	Token t2 = ts.get();

	if (t2.kind != '='){ 
		
		error("= missing in declaration of ", name);

	}

	double d = expression();

    names.push_back(Variable(name, d, constant));

	return d;

}

double calculator::statement(){

	Token t = ts.get();
	
	if (t.kind == LET) {
		
		return declaration(false);
	
	}

    else if (t.kind == CONST){

        return declaration(true);

    }

	else if(t.kind == SQRT){

		return square_root();

	}

	else if(t.kind == POW){

		return power();

	}

	else{
	
		ts.unget(t);
	
    	return expression();

	}

	error("Invalid statement");

}

void calculator::clean_up_mess(){

	ts.ignore(PRINT);

}

void calculator::calculate()
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

double calculator::negative_zero_check(double number){

	if(number == 0 && signbit(number) == 1){

		return 0;

	}

	return number;

}

double calculator::assign(string s){

	Token t = ts.get();

	if(t.kind != '='){

		error("= missing in assignment of ", t.name);

	}

	double d = expression();

	set_value(s, d);

	return d;

}

double calculator::square_root(){

	Token t = ts.get();

	if(t.kind != '('){

		error("( expected");

	}

	double d = expression();

	if(d < 0){

		error("Cannot take the square root of a negative number");

	}

	t = ts.get();

	if(t.kind != ')'){

		error(") expected");

	}

	return sqrt(d);

}

double calculator::power(){

	Token t = ts.get();

	if(t.kind != '('){

		error("( expected");

	}

	double base = expression();

	t = ts.get();

	if(t.kind != ','){

		error(", expected");

	}

	double exponent = expression();

	t = ts.get();

	if(t.kind != ')'){

		error(") expected");

	}

	return(pow(base, exponent));

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