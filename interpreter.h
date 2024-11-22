#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "vectorLib/vector.h"
#include <cassert>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <variant>
#include <vector>
#include "vectorLib/vector.h"
#include "vectorlistmodel.h"

enum IntTokenType { NUM, VEC, OP, VECOBJ };

namespace CalcTools {

class Token
{
    IntTokenType type_;
    std::variant<char, double, std::string, VecLib::Vector> val_;

public:
    Token(char op)
        : type_(OP)
        , val_(op)
    {}
    Token(std::string vec)
        : type_(VEC)
        , val_(vec)
    {}
    Token(double num)
        : type_(NUM)
        , val_(num)
    {}
    Token(VecLib::Vector a)
        : type_(VECOBJ)
        , val_(a)
    {}

    IntTokenType type() const { return type_; }

    void operator=(Token);

    operator double();      //
    operator char();        //
    operator std::string(); //
    operator VecLib::Vector();

    //bool operator==(Token& a)
    //{
    //    if (a.type_ != type_) return false;
    //
    //    switch (type_)
    //    {
    //    case NUM:
    //        return (double)*this == (double)a;
    //    case VEC:
    //        return (std::string)*this == (std::string)a;
    //    case OP:
    //        return (char)*this == (char)a;
    //    }
    //
    //    return false;
    //}
};

#define _plus Token('+')
#define _minus Token('_')
#define _mult Token('*')
#define _div Token('/')
#define _leftC Token('(')
#define _rightC Token(')')
#define _leftS Token('[')
#define _rightS Token(']')
#define _comma Token(',')
#define _vec(name) Token(#name)
//Token _num(double num) { return Token(num); }

using Tokens = std::vector<Token>;

namespace ExtraFuns {
Token readNum(char *&);
Token readVec(char *&);
Token readOp(char *&);
bool ifNum(char *);
bool ifVec(char *);
bool ifOp(char *); //

} // namespace ExtraFuns

Tokens Tokenize(const char *);
bool CheckPars(Tokens);
Tokens Parse(Tokens);
bool isVec(Token);
bool isNum(Token);
Token Calculator(Tokens&, VectorListModel*);

} // namespace CalcTools

#endif // INTERPRETER_H
