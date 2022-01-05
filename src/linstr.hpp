#ifndef LINSTR_H // include guard
#define LINSTR_H

#include "utils.hpp"
#include "lobject.hpp"

#include <unordered_map>

using namespace std;

// by reference to:
// https://the-ravi-programming-language.readthedocs.io/en/latest/lua_bytecode_reference.html

// The comment is from lua 5.3 lopcodes.h

/*===========================================================================
  We assume that instructions are unsigned numbers.
  All instructions have an opcode in the first 6 bits.
  Instructions can have the following fields:
    'A' : 8 bits
    'B' : 9 bits
    'C' : 9 bits
    'Ax' : 26 bits ('A', 'B', and 'C' together)
    'Bx' : 18 bits ('B' and 'C' together)
    'sBx' : signed Bx
  A signed argument is represented in excess K; that is, the number
  value is the unsigned value minus K. K is exactly the maximum value
  for that argument (so that -max is represented by 0, and +max is
  represented by 2*max), which is half the maximum for the corresponding
  unsigned argument.
===========================================================================*/

class Instr {
public:
    char           opcode;
    string           name;

    virtual string comment(const Instruction& instr, const ProtoData& ptdb);

    int GetA(const Instruction& instr);
    int GetB(const Instruction& instr);
    int GetC(const Instruction& instr);

    int GetBx(const Instruction& instr);
    int GetSBx(const Instruction& instr);

    int GetAx(const Instruction& instr);

    string GetRDisplay(int ridx, const ProtoData& ptdb);
};

class InstrUnknown : public Instr {
public:
    InstrUnknown();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 0
class InstrMove : public Instr {
public:
    InstrMove();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 1
class InstrLoadK : public Instr {
public:
    InstrLoadK();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 2
class InstrLoadKx : public Instr {
public:
    InstrLoadKx();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 3
class InstrLoadBool : public Instr {
public:
    InstrLoadBool();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 4
class InstrLoadNil : public Instr {
public:
    InstrLoadNil();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 5
class InstrGetUpVal : public Instr {
public:
    InstrGetUpVal ();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 6
class InstrGetTabUp : public Instr {
public:
    InstrGetTabUp();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 7
class InstrGetTable : public Instr {
public:
    InstrGetTable();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 8
class InstrSetTabUp : public Instr {
public:
    InstrSetTabUp();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 9
class InstrSetUpVal : public Instr {
public:
    InstrSetUpVal();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 10
class InstrSetTable : public Instr {
public:
    InstrSetTable();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 11
class InstrNewTable : public Instr {
public:
    InstrNewTable();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 12
class InstrSelf : public Instr {
public:
    InstrSelf();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 13
class InstrAdd : public Instr {
public:
    InstrAdd();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 14
class InstrSub : public Instr {
public:
    InstrSub();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 15
class InstrMul : public Instr {
public:
    InstrMul();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 16
class InstrMod : public Instr {
public:
    InstrMod();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 17
class InstrPow : public Instr {
public:
    InstrPow();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 18
class InstrDiv : public Instr {
public:
    InstrDiv();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 19
class InstrIDiv : public Instr {
public:
    InstrIDiv();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 20
class InstrBAnd : public Instr {
public:
    InstrBAnd();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 21
class InstrBOr : public Instr {
public:
    InstrBOr();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 22
class InstrBXOr : public Instr {
public:
    InstrBXOr();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 23
class InstrShL : public Instr {
public:
    InstrShL();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 24
class InstrShR : public Instr {
public:
    InstrShR();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 25
class InstrUNM : public Instr {
public:
    InstrUNM();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 26
class InstrBNot : public Instr {
public:
    InstrBNot();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 27
class InstrNot : public Instr {
public:
    InstrNot();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 28
class InstrLen : public Instr {
public:
    InstrLen();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 29
class InstrConcat : public Instr {
public:
    InstrConcat();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 30
class InstrJmp : public Instr {
public:
    InstrJmp();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 31
class InstrEQ : public Instr {
public:
    InstrEQ();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 32
class InstrLT : public Instr {
public:
    InstrLT();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 33
class InstrLE : public Instr {
public:
    InstrLE();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 34
class InstrTest : public Instr {
public:
    InstrTest();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 35
class InstrTestSet : public Instr {
public:
    InstrTestSet();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 36
class InstrCall : public Instr {
public:
    InstrCall();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 37
class InstrTailCall : public Instr {
public:
    InstrTailCall();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};


// opcode 38
class InstrReturn : public Instr {
    // Returns to the calling function, with optional return values.
public:
    InstrReturn();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 39
class InstrForPrep : public Instr {
    // FORPREP initializes a numeric for loop
public:
    InstrForPrep();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 40
class InstrForLoop : public Instr {
    // FORLOOP performs an iteration of a numeric for loop
public:
    InstrForLoop();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 41
class InstrTForCall : public Instr {
public:
    InstrTForCall();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 42
class InstrTForLoop : public Instr {
public:
    InstrTForLoop();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 43
class InstrSetList : public Instr {
    // Sets the values for a range of array elements.
public:
    InstrSetList();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 44
class InstrClosure : public Instr {
    // Creates an instance (or closure) of a function prototype.
public:
    InstrClosure();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 45
class InstrVarArg : public Instr {
    // VARARG implements the vararg operator ... in expressions.
public:
    InstrVarArg();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

// opcode 46
class InstrExtraArg : public Instr {
    // ExtraArg pairs with LoadKx to handle LoadK when #constant > 262143 
public:
    InstrExtraArg();
    string comment(const Instruction& instr, const ProtoData& ptdb);
};

class ParserInstr {
    unordered_map<char, Instr*> opcode2Instr;
public:
    ParserInstr();
    ~ParserInstr();

    Instr* parseInstr(Instruction instr);
};

#endif