#ifndef LOBJECT_H // include guard
#define LOBJECT_H

#include <vector>
#include <string>

using namespace std;

#define lua_Integer  long
#define lua_Number   double
#define Instruction  unsigned int


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