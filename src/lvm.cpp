#include "lvm.hpp"
#include "ltable.hpp"

#include <iostream>
#include <cassert>

using namespace std;

VM::VM()
{
    // create the _ENV table
    TValue envtabTval(LUA_TABLE);
    Table* envtab = tval2tab(envtabTval);

    upvals.push_back(envtabTval);

    // initialize the registers
    regs.resize(256, tvalnil);

    // initialize the stack
    stk.resize(256, nullptr);
    stktop = 0;
    stkbase = -1;

    // standard library: print
    envtab->insert("print", tvalcfunc(
        [](VM* vm) -> int {
            for (int idx = vm->stkbase + 1; idx < vm->stktop; ++idx)
            {
                TValue outtval = vm->regs[idx];
                if (outtval.tag == LUA_INTEGER)
                {
                    cout << tval2int(outtval) << endl;    
                } else {
                    cout << "TValue Print TBD" << endl;
                } 
            }

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

void VM::pushNow2CallInfo()
{
    CallInfo ci;
    ci.stktop  = stktop;
    ci.stkbase = stkbase;

    cis.push(ci);
}

void VM::popCallInfo2Now()
{
    CallInfo ci = cis.top();
    cis.pop();

    stktop  = ci.stktop;
    stkbase = ci.stkbase;
}

void VM::callcfunc(int funcidx, int argnum)
{
    // currently, support print only
    pushNow2CallInfo();

    // assign function handler to new stkbase
    stkbase = stktop;
    stk[stkbase] = &regs[funcidx];
    for (int i = 0; i < argnum; ++i)
    {
        stk[stkbase + i + 1] = &regs[funcidx + i + 1];
    }
    stktop = stkbase + argnum + 1;

    assert(regs[funcidx].isFunc());
    regs[funcidx].callCFunc(this);
    
    popCallInfo2Now();
}