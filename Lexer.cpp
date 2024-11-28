#include "Lexer.h"

VectorLexer::Token::Token(char sym, TokenType type)
    : _type(type)
    , _val(sym)
{}

VectorLexer::Token::Token(double val)
    : _type(DOUBLE_VAL)
    , _val(val)
{}

VectorLexer::Token::Token(std::string name)
    : _type(NAME)
    , _val(name)
{}

VectorLexer::Token::Token(unsigned long val)
    : _type(SIZE)
    , _val(val)
{}

VectorLexer::Token VectorLexer::Token::Comma()
{
    return Token(',', SEPARATOR);
}
VectorLexer::Token VectorLexer::Token::LeftPar()
{
    return Token('(', START_SEQ);
}
VectorLexer::Token VectorLexer::Token::RightPar()
{
    return Token(')', FINISH_SEQ);
}

VectorLexer::Token::operator double() const
{
    if (_type != DOUBLE_VAL)
        throw " ";
    return std::get<double>(_val);
}
VectorLexer::Token::operator std::string() const
{
    if (_type != NAME)
        throw " ";
    return std::get<std::string>(_val);
}
VectorLexer::Token::operator unsigned long() const
{
    if (_type != SIZE)
        throw " ";
    return std::get<unsigned long>(_val);
}
VectorLexer::Token::operator char() const
{
    if (_type != SEPARATOR && _type != START_SEQ && _type != FINISH_SEQ)
        throw " ";
    return std::get<char>(_val);
}

VectorLexer::TokenType VectorLexer::Token::Type() const
{
    return _type;
}

VectorLexer::Tokens VectorLexer::Tokenize(std::string expr)
{
    if (expr.empty())
        return {};

    Tokens result;

    const char *curr = expr.c_str();
    while (*curr) {
        if (isLetter(*curr)) {
            Token name = scanName(curr);
            result.push_back(name);
        } else if (*curr == '[') {
            Token size = scanSize(curr);
            result.push_back(size);
        } else if (isDigit(*curr) || (*curr == '-' && isDigit(curr[1]))) {
            Token elem = scanDouble(curr);
            result.push_back(elem);
        } else if (*curr == '(') {
            Token start = Token::LeftPar();
            result.push_back(start);
            curr++;
        } else if (*curr == ')') {
            Token finish = Token::RightPar();
            result.push_back(finish);
            curr++;
        } else if (*curr == ',') {
            Token comma = Token::Comma();
            result.push_back(comma);
            curr++;
        } else if (isSpacing(*curr)) {
            curr++;
            continue;
        }
        //else if (isEnddef(*curr))
        //{
        //    while(*curr && *curr != '\n') curr++;
        //    if (*curr =='\n') curr++;
        //}
        else
            throw "unknown lexema";
    }

    return result;
}

bool VectorLexer::isLetter(const char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}
bool VectorLexer::isDigit(const char c)
{
    return c >= '0' && c <= '9';
}
bool VectorLexer::isSpacing(const char c)
{
    return c == ' ' || c == '\t' || c == '\n';
}
//bool isEnddef(const char c)
//{
//    return c == '\n';
//}
VectorLexer::Token VectorLexer::scanName(const char *&s)
{
    std::string name;
    while (*s && (isLetter(*s) || isDigit(*s) || *s == '_'))
        name += *(s++);
    return Token(name);
}
VectorLexer::Token VectorLexer::scanSize(const char *&s)
{
    s++;
    std::string size = "";
    while (*s && *s != ']')
    {
        if (!isDigit(*s))
            throw " ";
        size += *(s++);
    }
    s++;

    if (size.empty()) throw " ";
    return Token(std::stoul(size));
}
VectorLexer::Token VectorLexer::scanDouble(const char *&s)
{
    std::string elem = "";
    while (*s && (isDigit(*s) || *s == '.' || *s == '-'))
        elem += *(s++);
    return Token(std::stod(elem));
}
