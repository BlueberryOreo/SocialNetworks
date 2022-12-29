#pragma once

#include <iostream>
#include <vector>
#include <set>
using namespace std;

#ifndef __POSITIVE__
#define __POSITIVE__
const set<string> positive = {
	"good", "fine", "nice", "virtuous", "great", "excellent", 
	"sweet", "cute", "wonderful", "dear"
};

#endif // !__POSITIVE__

#ifndef __NEGTIVE__
#define __NEGTIVE__
const set<string> negative = {
	"bad", "awful", "evil", "wicked", "terrible", "poor", "horrible"
};

#endif // !__NEGTIVE__



#ifndef __INSTRUCTOR__
#define __INSTRUCTOR__
void instructor();

int solve(string req, string& name1, string& name2, string& relation, int& intimacy);

#endif // !__INSTRUCTOR__
