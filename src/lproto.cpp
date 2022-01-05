#include "lproto.hpp"
#include "linstr.hpp"

#include <iostream>
#include <string>
#include <math.h>

using namespace std;


void Proto::exec()
{
    ParserInstr pInstr;

    for(size_t i = 0; i < ptdb.instrs.size(); ++i)
    {
        Instr* instrParserObj = pInstr.parseInstr(ptdb.instrs[i]);

    }
}