#ifndef LTABLE_H // include guard
#define LTABLE_H

#include <unordered_map>
#include "utils.hpp"
#include "lobject.hpp"

using namespace std;

class Table {
public:
	unordered_map<string, TValue> key2val;

	void insert(string key, TValue val);
};

#endif