#ifndef LEXER_H
#define LEXER_H

#include <exception>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

namespace VectorLexer {

enum TokenType {
    NAME,
    DOUBLE_VAL,
    SIZE,
    START_SEQ = '(',
    FINISH_SEQ = ')',
    SEPARATOR = ',',
};

class Token
{
    TokenType _type;
    std::variant<std::string, double, unsigned long, char> _val;

    Token(char, TokenType);

public:
    Token(std::string);
    Token(double);
    Token(unsigned long);

    static Token Comma();
    static Token LeftPar();
    static Token RightPar();

    operator double() const;
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
Token scanDouble(const char *&);
Token scanSize(const char *&);

Tokens Tokenize(std::string);

} // namespace VectorLexer

#endif // LEXER_H
