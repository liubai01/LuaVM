#include <iostream>
#include <string>

#include "src/utils.hpp"
#include "src/ldump.hpp"
#include "src/lobject.hpp"
#include "src/lvm.hpp"

using namespace std;

void printUsage()
{
    cout << "Usage: luavm <file> <options>"                             << endl;
}

int main(int argc, char* argv[])
{
    string filename;
    if (argc > 1)
    {
        filename = string(argv[1]);

    } else {
        printUsage();
        return -1;
    }

    unsigned char* fileBase = openMmapRO(filename);
    if (!fileBase)
    {
        return -1;
    }

    Dumped d(fileBase);
    d.dump2proto();

    VM vm;

    // TValue dummyf;
    // dummyf.tag = LUA_TFUNCTION;
    // dummyf.val.cfunc = [](VM* v) -> int {return 233;};

    // cout << dummyf.callCFunc(nullptr) << endl;

    return 0;
}