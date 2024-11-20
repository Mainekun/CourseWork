#include "interpreter.h"

std::map<char, int> opersPriority =
    {
        {'+', 1},
        {'-', 1},
        {'*', 2},
        {'/', 2},
        {'(', 0},
        {')', 0},
        {'[', 0},
        {']', 0},
        {',', 0}
};

Token::operator double()
{
    if (type_ != NUM) throw "wrong access type";
    return std::get<double>(val_);
}

Token::operator char()
{
    if (type_ != OP) throw "wrong access type";
    return std::get<char>(val_);
}

Token::operator std::string()
{
    if (type_ != VEC) throw "wrong access type";
    return std::get<std::string>(val_);
}

//CalcTools::ExtraFuns

Token CalcTools::ExtraFuns::readNum(char*& c)
{
    int dotCount = 0;
    std::string doubleStr = "";
    while (*c && (ifNum(c) || *c == '.'))
    {
        if (*c == '.') dotCount++;
        doubleStr += *(c++);
    }

    if (dotCount > 1) throw "bad num";

    double num = std::stod(doubleStr);
    return Token(num);
}

Token CalcTools::ExtraFuns::readVec(char*& c)
{
    std::string vec = "";
    while (*c && *c != ' ' && !ifOp(c) && *c != '.')
        vec += *(c++);

    return Token(vec);
}

Token CalcTools::ExtraFuns::readOp(char*& c)
{
    char op = *(c++);

    return Token(op);
}

bool CalcTools::ExtraFuns::ifNum(char* c)
{
    return (*c >= '0' && *c <= '9') ||
           (*c == '.' && *(c + 1) >= '0' && *(c + 1) <= '9');
}

bool CalcTools::ExtraFuns::ifVec(char* c)
{
    return (*c >= 'a' && *c <= 'z') || (*c >= 'A' && *c <= 'Z');
}

bool CalcTools::ExtraFuns::ifOp(char* c)
{
    return
        *c == '+' || *c == '-' || *c == '*' ||
        *c == '/' || *c == '(' || *c == ')' ||
        *c == '[' || *c == ']' || *c == ',';
}

//CalcTools

CalcTools::Tokens CalcTools::Tokenize(const char* Cexpr)
{
    char* expr = (char*)Cexpr;

    if (*expr == 0) return {};

    Tokens tokens;

    while (*expr)
    {
        if (ExtraFuns::ifNum(expr))
        {
            Token num = ExtraFuns::readNum(expr);
            tokens.push_back(num);
        }
        else if (ExtraFuns::ifVec(expr))
        {
            Token vec = ExtraFuns::readVec(expr);
            tokens.push_back(vec);
        }
        else if (ExtraFuns::ifOp(expr))
        {
            Token op = ExtraFuns::readOp(expr);
            tokens.push_back(op);
        }
        else if (*expr == ' ' || *expr == '\t' || *expr == '\n' || *expr == '\r')
        {
            expr++;
            continue;
        }
        else
        {
            throw "not in the tokens";
        }
    }

    return tokens;
}

bool CalcTools::CheckPars(Tokens tokens)
{
    std::stack<char> pars;

    for (auto& i : tokens)
    {
        if (i.type() != OP) continue;

        char s = (char)i;

        if (s != '(' && s != ')' &&
            s != '[' && s != ']') continue;

        switch (s)
        {
        case '(':
        case '[':
            pars.push(s);
            break;
        case ')':
            if (pars.empty() || pars.top() != '(')
                return false;
            else
                pars.pop();
            break;
        case ']':
            if (pars.empty() || pars.top() != '[')
                return false;
            else
                pars.pop();
        }
    }


    return pars.empty();
}

CalcTools::Tokens CalcTools::Parse(Tokens a)
{
    if (a.empty()) return {};

    Tokens output;
    std::stack<Token> opStack;

    auto extractStack =
        [](Tokens& to, std::stack<Token>& from) {
            to.push_back(from.top());
            from.pop();
        };

    for (auto& i : a)
    {
        switch (i.type())
        {
        case NUM:
        case VEC:
            output.push_back(i);
            break;
        case OP:
            switch ((char)i)
            {
            case '(':
                opStack.push(i);
                break;
            case ')':
                while (!opStack.empty() &&
                       (char)opStack.top() != '(')
                    extractStack(output, opStack);

                opStack.pop();
                break;
            case '+':
            case '-':
            case '*':
            case '/':
                while (!opStack.empty() &&
                       opersPriority[(char)opStack.top()] >=
                        opersPriority[(char)i])
                    extractStack(output, opStack);

                opStack.push(i);
                break;
            case '[':
                output.push_back(i);
                opStack.push(i);
                break;
            case ',':
                while ((char)opStack.top() != '[')
                    extractStack(output, opStack);

                output.push_back(i);
                break;
            case ']':
                while ((char)opStack.top() != '[')
                    extractStack(output, opStack);

                output.push_back(i);
                opStack.pop();
            }
        }
    }

    while (!opStack.empty())
    {
        if ((char)opStack.top() == '(') throw "illegal expression";
        output.push_back(opStack.top());
        opStack.pop();
    }

    return output;
}
