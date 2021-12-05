#include "std_lib_facilities.h"

#ifndef Variable_H
#define Variable_H

struct Variable {
	
	string name;
	
	double value;

    bool constant;

    Variable(string n, double v, bool c) :name(n), value(v), constant(c) { }

};

#endif