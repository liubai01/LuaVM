#ifndef LOBJECT_H // include guard
#define LOBJECT_H

#include <vector>
#include <string>

using namespace std;

#define lua_Integer  long
#define lua_Number   double
#define Instruction  unsigned int

class VM;

typedef union LargeValuePtr {
	void* ptr;
} LargeValuePtr;

/**
 * @brief A type alias of c functions invoked in lua
 * @details 
 */
typedef int (*lua_CFunction) (VM *L);

/**
 * @brief A union of all possible values in runtime lua.
 * @details A union of all possible values in runtime lua.
 */
typedef union Value {
	LargeValuePtr  lptr;
	lua_Integer    intgr;
	lua_Number     numbr;
	lua_CFunction  cfunc;
} Value;

/**
 * @brief Tagged value (a tag for run-time type id)
 * @details 
 * 
 */
class TValue {
public:
	char tag;
	Value val;

	TValue(char tag);
	~TValue();

	bool isFunc();
	int callCFunc(VM *L);
};

// tags
#define LUA_TFUNCTION		0
#define LUA_TABLE           1

// TValue Transformation
#define tval2tab(X) ((Table*) X.val.lptr.ptr)

// Proto data
// Remark: why we split data and proto itself is to allow
// other objects (e.g: instruction) to modify it, while themselves
// could be referred in interface class (Proto itself)
class ProtoData
{
public:
    // instruction VM assembly codes
    vector<Instruction> instrs;
    // constant display names
    vector<string> kdisplay;
    // local variable display names
    vector<string> locDisplay{};
    // up display names
    vector<string> upDisplay{};
};

#endif