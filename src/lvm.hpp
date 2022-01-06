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

    void setTableUp(int upidx, string key, TValue val);
    void getTableUp(int upidx, string key, int toidx);

    void call(int funcidx, int argnum);
};

#endif