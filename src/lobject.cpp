#include "lobject.hpp"
#include "ltable.hpp"

#include <cassert>

TValue::TValue(char tag)
{
    if (tag == LUA_TABLE)
    {
        this->tag = LUA_TABLE;
        this->val.lptr.ptr = new Table();   
    } else if (tag == LUA_NIL) {
        this->tag = LUA_NIL;
    }
}

TValue::TValue(lua_CFunction cfunc)
{
    this->tag = LUA_TFUNCTION;
    this->val.cfunc = cfunc;
}

TValue::TValue(char tag, lua_Integer val)
{
    assert(tag == LUA_INTEGER);

    this->tag = LUA_INTEGER;
    this->val.intgr = val;
}

TValue::TValue(char tag, lua_Number val)
{
    assert(tag == LUA_NUMBER);

    this->tag = LUA_NUMBER;
    this->val.numbr = val;
}

TValue::~TValue()
{

}

void TValue::clear()
{
    if (tag == LUA_TABLE)
    {
        Table* ptr = (Table*) val.lptr.ptr;
        if (ptr)
        {
            delete ptr;
            val.lptr.ptr = nullptr;
        }
        
    }
}

bool TValue::isFunc()
{
    return tag == LUA_TFUNCTION;
}

int TValue::callCFunc(VM *L)
{
    return (*val.cfunc)(L); 
}