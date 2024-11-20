#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <vector>
#include <variant>
#include <string>
#include <cassert>
#include <stack>
#include <map>
#include "vectorLib/vector.h"

enum TokenType
{
    NUM,
    VEC,
    OP
};

class Token
{
    TokenType type_;
    std::variant<char, double, std::string> val_;
public:

    Token(char op) : type_(OP), val_(op) {}
    Token(std::string vec) : type_(VEC), val_(vec) {}
    Token(double num) : type_(NUM), val_(num) {}

    TokenType type() const { return type_; }

    operator double();//
    operator char();//
    operator std::string();//

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
#define _vec(name) Token(# name)
//Token _num(double num) { return Token(num); }



namespace CalcTools
{
    using Tokens = std::vector<Token>;

    namespace ExtraFuns
    {
        Token readNum(char*&);
        Token readVec(char*&);
        Token readOp(char*&);
        bool ifNum(char*);
        bool ifVec(char*);
        bool ifOp(char*);//


    }

    Tokens Tokenize(const char*);
    bool CheckPars(Tokens);
    Tokens Parse(Tokens);

}

#endif // INTERPRETER_H
