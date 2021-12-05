#include "std_lib_facilities.h"

#ifndef token_H
#define token_H

struct Token {

	char kind;

	double value;

	string name;

	Token(char ch) :kind(ch), value(0), name("") { }

	Token(char ch, double val) :kind(ch), value(val), name("") { }

    Token(char ch, string str) :kind(ch), value(0), name(str) { }

};

#endif