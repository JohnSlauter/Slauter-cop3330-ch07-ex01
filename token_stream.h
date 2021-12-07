/*
 *  UCF COP3330 Fall 2021 Assignment 6 Solution
 *  Copyright 2021 first_name last_name
 */

#include "token.h"

#ifndef Token_stream_H
#define Token_stream_H

const char LET = 'L';

const char QUIT = 'Q';

const char PRINT = ';';

const char NUMBER = '8';

const char NAME = 'a';

const char CONST = 'c';

class Token_stream {
	
	bool full;
	
	Token buffer;

    public:
	
	    Token_stream() :full(0), buffer(0) { }

	    Token get();
	
	    void unget(Token t) { buffer = t; full = true; }

	    void ignore(char);

};

#endif