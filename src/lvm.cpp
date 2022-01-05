#include "lvm.hpp"
#include "ltable.hpp"

VM::VM()
{
    TValue envtab(LUA_TABLE);
    Table* envtabobj = tval2tab(envtab);

    upvals.push_back(envtab);
}

VM::~VM()
{
}
