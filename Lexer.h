#ifndef LEXER_H
#define LEXER_H

#include <exception>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>
#include "vectorLib/vector.h"

namespace VectorLexer {

enum TokenType {
    NAME,
    VAL,
    SIZE,
    START_SEQ = '(',
    FINISH_SEQ = ')',
    SEPARATOR = ',',
};

class Token
{
    TokenType _type;
    std::variant<std::string, e_type, unsigned long, char> _val;

    Token(char, TokenType);

public:
    Token(std::string);
    Token(e_type);
    Token(unsigned long);

    static Token Comma();
    static Token LeftPar();
    static Token RightPar();

    operator e_type() const;
    operator std::string() const;
    operator unsigned long() const;
    operator char() const;

    TokenType Type() const;
};

using Tokens = std::vector<Token>;

bool isLetter(const char);
bool isDigit(const char);
bool isSpacing(const char);
//bool isEnddef(const char);
Token scanName(const char *&);
Token scanNum(const char *&);
Token scanSize(const char *&);

Tokens Tokenize(std::string);

} // namespace VectorLexer

#endif // LEXER_H
