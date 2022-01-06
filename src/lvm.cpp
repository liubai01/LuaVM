#include "lvm.hpp"
#include "ltable.hpp"

#include <iostream>

using namespace std;

VM::VM()
{
    // create the _ENV table
    TValue envtabTval(LUA_TABLE);
    Table* envtab = tval2tab(envtabTval);

    upvals.push_back(envtabTval);

    // initialize the registers
    regs.resize(256, tvalnil);

    // standard library: print (TBD)
    envtab->insert("print", tvalcfunc(
        [](VM* vm) -> int {
            cout << "printTBD" << endl; 
            return 0;
        })
    );

    // playground
    
}

VM::~VM()
{
    for (TValue& tval: upvals)
    {
        tval.clear();
    }
}

void VM::setTableUp(int upidx, string key, TValue val)
{
    Table* tab = tval2tab(upvals[upidx]);
    tab->insert(key, val);
    // envtab->insert("a", tvalint(6));
}

void VM::getTableUp(int upidx, string key, int toidx)
{
    Table* tab = tval2tab(upvals[upidx]);
    auto f = tab->key2val.find(key);
    if (f != tab->key2val.end())
    {
        regs[toidx] = f->second;
    } else {
        regs[toidx] = tvalnil;
    }
    
}

void VM::call(int funcidx, int argnum)
{
    // currently, support print only
    TValue outtval = regs[funcidx + 1];
    if (outtval.tag == LUA_INTEGER)
    {
        cout << tval2int(outtval) << endl;    
    } else {
        cout << "TValue Print TBD" << endl;
    }
    
}