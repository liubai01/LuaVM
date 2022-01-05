#include "ldump.hpp"

#include "utils.hpp"
#include <cassert>
#include <iostream>



using namespace std;

Dumped::Dumped(unsigned char* bytecodeAddr)
{
    this->bytecodeAddr = bytecodeAddr;
    HeaderBlock hb;

    // parse the header by HeaderBlock structure
    std::memcpy(&hb, bytecodeAddr, sizeof(HeaderBlock));

    // big endian or litte endian, signature differs
    assert(hb.Lua_Signature ==  0x1b4c7561 || hb.Lua_Signature == 0x61754c1b);

    // check whether lua version is 5.3
    assert(hghByte(hb.Lua_VerNumber) == 5);
    assert(lowByte(hb.Lua_VerNumber) == 3);

    // check whether data conversion is correction
    assert(strcmp(reinterpret_cast<const char*>(hb.Lua_Data), "\x19\x93\r\n\x1a\n"));
}

int getFunctionBlockSize(unsigned char* baseAddr)
{
    unsigned char* initBase = baseAddr;

    // source name
    loadAndProceed<string>(&baseAddr);

    // base
    baseAddr = baseAddr + sizeof(FuncBlock);

    // instruction list
    int numInstr = loadAndProceed<int>(&baseAddr);
    baseAddr += sizeof(int) * numInstr;
   

    // constant list
    int numConsant = loadAndProceed<int>(&baseAddr);

    for (int i = 0; i < numConsant; ++i)
    {
        // Constant Layout: 
        //  (1) 1 byte of type constant
        //  (2) variant bytes of constant content

        // The low byte(0-3) bits of tt_ w.r.t. constant decides the type
        int constType = loadAndProceed<unsigned char>(&baseAddr);
        int nonvarTag = lowByte(constType);
        int varTag    = hghByte(constType);

        switch(nonvarTag)
        {
            case 0:
                // NIL
                break;
            case 1:
                // Boolean: TBD
                break;
            case 3:
                if (varTag == 0)
                {
                    // double
                    baseAddr += sizeof(lua_Number);
                } else {
                    // long
                    baseAddr += sizeof(lua_Integer);
                }
                break;
            case 4:
                loadAndProceed<string>(&baseAddr);
                break;
            default:
                // should not reach here
                assert(0 == 1);
                break;
        }
    }

    // up value lists
    int numUpVal = loadAndProceed<int>(&baseAddr);
    baseAddr += 2 * numUpVal;

    // nested function list
    int numNestedFuncs = loadAndProceed<int>(&baseAddr);

    for (int i = 0; i < numNestedFuncs; ++i)
    {
        baseAddr += getFunctionBlockSize(baseAddr);
    }

    // line info list (debug)
    int numLineInfo = loadAndProceed<int>(&baseAddr);
    baseAddr += sizeof(int) * numLineInfo;

    // local vars (debug)
    int numLocVars = loadAndProceed<int>(&baseAddr);
    for (int i = 0; i < numLocVars; ++i)
    {
        // original dump code in ldump.c DumpDebug function for reference: 
        // DumpString(f->locvars[i].varname, D);
        // DumpInt(f->locvars[i].startpc, D);
        // DumpInt(f->locvars[i].endpc, D);

        loadAndProceed<string>(&baseAddr);
        baseAddr += sizeof(int) * 2;
    }

    // Up Values Names
    int numUpVals = loadAndProceed<int>(&baseAddr);

    // by default, there is a _ENV, you could refer to lua-users.org/wiki/EnvironmentsTutorial
    for (int i = 0; i < numUpVals; ++i)
    {
        loadAndProceed<string>(&baseAddr);
    }

    return baseAddr - initBase;
}

vector<unsigned char*> Dumped::subFuncsAddrs(unsigned char* startAddr)
{
    vector<unsigned char*> ret;

    unsigned char* baseAddr;

    if (startAddr)
    {
        baseAddr = startAddr;
    } else {
        baseAddr = bytecodeAddr + sizeof(HeaderBlock);
    }

    // source name
    loadAndProceed<string>(&baseAddr);

    // base
    baseAddr = baseAddr + sizeof(FuncBlock);

    // instruction list
    int numInstr = loadAndProceed<int>(&baseAddr);
    baseAddr += sizeof(int) * numInstr;
   

    // constant list
    int numConsant = loadAndProceed<int>(&baseAddr);

    for (int i = 0; i < numConsant; ++i)
    {
        // Constant Layout: 
        //  (1) 1 byte of type constant
        //  (2) variant bytes of constant content

        // The low byte(0-3) bits of tt_ w.r.t. constant decides the type
        int constType = loadAndProceed<unsigned char>(&baseAddr);
        int nonvarTag = lowByte(constType);
        int varTag    = hghByte(constType);

        switch(nonvarTag)
        {
            case 0:
                // NIL
                break;
            case 1:
                // Boolean: TBD
                break;
            case 3:
                if (varTag == 0)
                {
                    // double
                    baseAddr += sizeof(lua_Number);
                } else {
                    // long
                    baseAddr += sizeof(lua_Integer);
                }
                break;
            case 4:
                loadAndProceed<string>(&baseAddr);
                break;
            default:
                // should not reach here
                assert(0 == 1);
                break;
        }
    }

    // up value lists
    int numUpVal = loadAndProceed<int>(&baseAddr);
    baseAddr += 2 * numUpVal;

    // nested function list
    int numNestedFuncs = loadAndProceed<int>(&baseAddr);

    for (int i = 0; i < numNestedFuncs; ++i)
    {
        ret.push_back(baseAddr);
        baseAddr += getFunctionBlockSize(baseAddr);
    }

    return ret;
}


void __dumpProtos(unsigned char* startAddr, string name, Proto * proot)
{
    unsigned char* baseAddr = startAddr;

    // source name
    loadAndProceed<string>(&baseAddr);

    // base
    baseAddr = baseAddr + sizeof(FuncBlock);

    // instruction list
    int numInstr = loadAndProceed<int>(&baseAddr);
    // lt.push_back(o, to_string(numInstr), "Number of instructions");

    for(int i = 0; i < numInstr; ++i)
    {
        Instruction asbly_code = loadAndProceed<Instruction>(&baseAddr);
        proot->ptdb.instrs.push_back(asbly_code);
    }

    // constant list
    int numConsant = loadAndProceed<int>(&baseAddr);

    for (int i = 0; i < numConsant; ++i)
    {
        int constType = loadAndProceed<unsigned char>(&baseAddr);
        int nonvarTag = lowByte(constType);
        int varTag    = hghByte(constType);

        switch(nonvarTag)
        {
            case 0:
                proot->ptdb.kdisplay.push_back("NIL");
                break;
            case 3:
                if (varTag == 0)
                {
                    proot->ptdb.kdisplay.push_back(to_string(loadAndProceed<lua_Number>(&baseAddr)));
                } else {
                    proot->ptdb.kdisplay.push_back(to_string(loadAndProceed<lua_Integer>(&baseAddr)));
                }
                break;
            case 4:
                proot->ptdb.kdisplay.push_back("\"" + loadAndProceed<string>(&baseAddr) + "\"");
                break;
            default:
                proot->ptdb.kdisplay.push_back("unknown");
                break;
        }
    }

    // up value lists
    int numUpVal = loadAndProceed<int>(&baseAddr);
    baseAddr += 2 * numUpVal;

    // nested function list
    int numNestedFuncs = loadAndProceed<int>(&baseAddr);

    for (int i = 0; i < numNestedFuncs; ++i)
    {
        proot->subprotos.emplace_back();
        __dumpProtos(
            baseAddr, 
            string_format("%s.%d", name.c_str(), i), 
            &proot->subprotos[proot->subprotos.size() - 1]
        );
        baseAddr += getFunctionBlockSize(baseAddr);
    }


    int numLineInfo = loadAndProceed<int>(&baseAddr);
    baseAddr += sizeof(int) * numLineInfo;


    int numLocVars = loadAndProceed<int>(&baseAddr);

    for (int i = 0; i < numLocVars; ++i)
    {
        proot->ptdb.locDisplay.push_back("\"" + loadAndProceed<string>(&baseAddr) + "\"");
        baseAddr += sizeof(int) * 2;
    }

    int numUpVals = loadAndProceed<int>(&baseAddr);

    // by default, there is a _ENV, you could refer to lua-users.org/wiki/EnvironmentsTutorial
    for (int i = 0; i < numUpVals; ++i)
    {
        proot->ptdb.upDisplay.push_back(loadAndProceed<string>(&baseAddr));
    }
}

void Dumped::dump2proto(unsigned char* startAddr)
{
    Proto proot;

    if (!startAddr)
    {
        startAddr = bytecodeAddr + sizeof(HeaderBlock);
    }
    __dumpProtos(startAddr, "main", &proot);
}