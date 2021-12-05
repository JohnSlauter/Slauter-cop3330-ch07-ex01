#include "std_lib_facilities.h"
#include "token_stream.h"
#include "token_stream.cpp"
#include "Variable.h"

#ifndef calculator_H
#define calculator_H

namespace calculator{

    const string prompt = "> ";

    const string result = "= ";

    vector<Variable> names;

    Token_stream ts;

    double get_value(string s);
    
    void set_value(string s, double d); 

    bool is_declared(string s);

    double expression();

    double primary();

    double term();

    double declaration(bool constant);

    double statement();

    void clean_up_mess();

    void calculate();

    double negative_zero_check(double number);

    double assign(string s);

    Variable* get(string s);

}

#endif