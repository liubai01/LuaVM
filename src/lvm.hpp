#ifndef LVM_H // include guard
#define LVM_H

#include <vector>
#include "utils.hpp"
#include "lobject.hpp"

using namespace std;

class VM {
public:
	vector<TValue> upvals;
	vector<TValue> regs;

    VM();
    ~VM();
};

#endif