#include "ltable.hpp"

void Table::insert(string key, TValue val)
{
	key2val.insert({key, val});
}