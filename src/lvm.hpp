#ifndef LVM_H // include guard
#define LVM_H

#include <vector>
#include <stack>
#include "utils.hpp"
#include "lobject.hpp"

using namespace std;

class CallInfo {
public:
	int stktop;   // first free slot in the stack
	int stkbase;  // stack base (point to current function)
};

class VM {
public:
	vector<TValue>   upvals;
	vector<TValue>   regs;
	vector<TValue*>  stk;

	stack<CallInfo> cis;

	int stktop;   // first free slot in the stack
	int stkbase;  // stack base (point to current function)	

    VM();
    ~VM();

    void setTableUp(int upidx, string key, TValue val);
    void getTableUp(int upidx, string key, int toidx);

    void pushNow2CallInfo();
    void popCallInfo2Now();
    void callcfunc(int funcidx, int argnum);
};

#endif