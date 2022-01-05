#include "lobject.hpp"
#include "ltable.hpp"

TValue::TValue(char tag)
{
	if (tag == LUA_TABLE)
	{
		this->tag = LUA_TABLE;
    	this->val.lptr.ptr = new Table();	
	}
}

TValue::~TValue()
{
	if (tag == LUA_TABLE)
	{
		delete (Table*) val.lptr.ptr;
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