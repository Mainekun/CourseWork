#include "interpreter.h"

std::map<char, int> opersPriority
    = {{'+', 1},
       {'-', 1},
       {'*', 2},
       {'/', 2},
       {'(', 0},
       {')', 0},
       {'[', 0},
       {']', 0},
       {',', 0},
       {'|', 1},
       {'&', 2},
       {'%', 3},
       {'$', 3},
       {'>', 3},
       {'<', 3},
       {'~', 3},
       {'#', 2},
       {'^', 2}
};

// '\' - sumElems
// '&' - prodElems
// '%' - module
// '$' - at
// 'a' - ascending sort
// 'd' - descending sort
// 'r' - reverse
// '#' - GCD
// '^' - LCM

CalcTools::Token::operator e_type()
{
    if (type_ != NUM)
        throw "wrong access type";
    return std::get<e_type>(val_);
}

CalcTools::Token::operator char()
{
    if (type_ != OP)
        throw "wrong access type";
    return std::get<char>(val_);
}

CalcTools::Token::operator std::string()
{
    if (type_ != VEC)
        throw "wrong access type";
    return std::get<std::string>(val_);
}

CalcTools::Token::operator VecLib::Vector()
{
    if (type_ != VECOBJ)
        throw "wrong access type";
    return std::get<VecLib::Vector>(val_);
}

void CalcTools::Token::operator =(CalcTools::Token a)
{
    this->type_ = a.type_;
    this->val_ = a.val_;
}
//CalcTools::ExtraFuns

CalcTools::Token CalcTools::ExtraFuns::readNum(char *&c)
{
    ul minus = 0;
    ul dota = 0;
    std::string numStr = "";
    while (*c && (ifNum(c) || *c == '-')) {
        if (*c == '-')
            minus++;
        if (*c == '.')
            dota++;
        numStr += *(c++);
    }

    if (minus > 1)
        throw "too many \'-\' symbols in num";
    if (dota > 1)
        throw "too many \'.\' symbols in num";

    e_type num = std::stod(numStr);
    return Token(num);
}

CalcTools::Token CalcTools::ExtraFuns::readVec(char *&c)
{
    std::string vec = "";
    while (*c && *c != ' ' && !ifOp(c) && *c != '.')
        vec += *(c++);

    return Token(vec);
}

CalcTools::Token CalcTools::ExtraFuns::readOp(char *&c)
{
    char op = *(c++);

    return Token(op);
}

bool CalcTools::ExtraFuns::ifNum(char *c)
{
    return (*c >= '0' && *c <= '9') || (*c == '-' && *(c+1) >= '0' && *(c+1) <= '9');
}

bool CalcTools::ExtraFuns::ifVec(char *c)
{
    return (*c >= 'a' && *c <= 'z') || (*c >= 'A' && *c <= 'Z');
}

bool CalcTools::ExtraFuns::ifOp(char *c)
{
    return *c == '+' || *c == '-' || *c == '*' || *c == '/' || *c == '(' || *c == ')' || *c == '['
           || *c == ']' || *c == ',' || *c == '|' || *c == '&' || *c == '%'
           || *c == '$' || *c == '<' || *c == '>' || *c == '~' || *c == '#' || *c == '^';
    // '\' - sumElems
    // '&' - prodElems
    // '%' - module
    // '$' - at
    // '<' - ascending sort
    // '>' - descending sort
    // '~' - reverse
}

//CalcTools

CalcTools::Tokens CalcTools::Tokenize(const char *Cexpr)
{
    char *expr = (char *) Cexpr;

    if (*expr == 0)
        return {};

    Tokens tokens;

    while (*expr) {
        if (ExtraFuns::ifNum(expr)) {
            Token num = ExtraFuns::readNum(expr);
            tokens.push_back(num);
        } else if (ExtraFuns::ifVec(expr)) {
            Token vec = ExtraFuns::readVec(expr);
            tokens.push_back(vec);
        } else if (ExtraFuns::ifOp(expr)) {
            Token op = ExtraFuns::readOp(expr);
            tokens.push_back(op);
        } else if (*expr == ' ' || *expr == '\t' || *expr == '\n' || *expr == '\r') {
            expr++;
            continue;
        } else {
            throw "not in the tokens";
        }
    }

    return tokens;
}

bool CalcTools::CheckPars(Tokens tokens)
{
    std::stack<char> pars;

    for (auto &i : tokens) {
        if (i.type() != OP)
            continue;

        char s = (char) i;

        if (s != '(' && s != ')' && s != '[' && s != ']')
            continue;
//[(])
        switch (s) {
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
    if (a.empty())
        return {};

    Tokens output;
    std::stack<CalcTools::Token> opStack;
    int commaCount = 0;

    auto extractStack = [](Tokens &to, std::stack<CalcTools::Token> &from) {
        to.push_back(from.top());
        from.pop();
    };

    for (auto &i : a) {
        switch (i.type()) {
        case NUM:
        case VEC:
            output.push_back(i);
            break;
        case OP:
            switch ((char) i) {
            case '(':
                opStack.push(i);
                break;
            case ')':
                while (!opStack.empty() && (char) opStack.top() != '(')
                    extractStack(output, opStack);

                opStack.pop();
                break;
            case '+':
            case '-':
            case '*':
            case '/':
                while (!opStack.empty()
                       && opersPriority[(char) opStack.top()] >= opersPriority[(char) i])
                    extractStack(output, opStack);

                opStack.push(i);
                break;
            case '[':
                output.push_back(i);
                opStack.push(i);
                break;
            case ',':
                while ((char) opStack.top() != '[')
                    extractStack(output, opStack);
                commaCount++;
                break;
            case ']':
                while ((char) opStack.top() != '[')
                    extractStack(output, opStack);

                output.push_back(Token((e_type)commaCount + 1));
                output.push_back(Token('p'));

                commaCount = 0;

                opStack.pop();
                break;
            case '|':
            case '&':
            case '%':
            case '$':
            case '<':
            case '>':
            case '~':
            case '#':
            case '^':
                opStack.push(i);
            }
        case VECOBJ:
            break;
        }

    }

    // '\' - sumElems
    // '&' - prodElems
    // '%' - module
    // '$' - at
    // 'a' - ascending sort
    // 'd' - descending sort
    // 'r' - reverse
    // '#' - GCD
    // '^' - LCR

    while (!opStack.empty()) {
        if ((char) opStack.top() == '(')
            throw "illegal expression: pls check parenthessis";
        output.push_back(opStack.top());
        opStack.pop();
    }

    return output;
}

bool CalcTools::isVec(const CalcTools::Token& a)
{
    return a.type() == VEC || a.type() == VECOBJ;
}

bool CalcTools::isNum(const CalcTools::Token& a)
{
    return a.type() == NUM;
}

CalcTools::Token CalcTools::Calculator(CalcTools::Tokens& expr, VectorListModel* db)
{
    if (expr.empty()) throw "got an empty expr";

    std::stack<CalcTools::Token> stack;

    CalcTools::Tokens vars;

    auto extractSingle = [](std::stack<CalcTools::Token>& stack,CalcTools::Tokens& vars)mutable
    {
        vars.push_back(stack.top());
        stack.pop();
    };

    auto extractBinary = [](std::stack<CalcTools::Token>& stack,CalcTools::Tokens& vars)mutable
    {
        vars.push_back(stack.top());
        stack.pop();
        vars.push_back(stack.top());
        stack.pop();
    };



#define first vars[0]
#define second vars[1]
#define fVec ((VecLib::Vector)vars[0])
#define sVec ((VecLib::Vector)vars[1])

    for (auto& i : expr)
    {
        switch (i.type())
        {
        case IntTokenType::NUM:
        case IntTokenType::VECOBJ:
            stack.push(i);
            break;
        case IntTokenType::VEC:
            stack.push(
                CalcTools::Token(db->find((std::string)i))
                );
            break;
        case IntTokenType::OP:
            switch ((char)i)
            {
            case '+':
                extractBinary(stack, vars);
                if (CalcTools::isVec(first) && CalcTools::isVec(second))
                {
                    stack.push(fVec + sVec);
                }
                else if (CalcTools::isNum(first) && CalcTools::isNum(second))
                {
                    stack.push(CalcTools::Token((e_type)first + (e_type)second));
                }
                else throw "invalid arguments";
                vars.clear();
                break;
            case '-':
                extractBinary(stack, vars);


                if (CalcTools::isVec(first) && CalcTools::isVec(second))
                {
                    stack.push(sVec - fVec);
                }
                else if (CalcTools::isNum(first) && CalcTools::isNum(second))
                {
                    stack.push(CalcTools::Token((e_type)second - (e_type)first));
                }
                else throw "invalid arguments";
                vars.clear();
                break;
            case '*':
                //Умножение коммутативно
                //Поэтому все варианты подходят
                extractBinary(stack, vars);
                if (CalcTools::isVec(first) && CalcTools::isVec(second))
                {
                    stack.push(fVec.scalarProd(sVec));
                }
                else if (CalcTools::isNum(first) && CalcTools::isNum(second))
                {
                    stack.push(CalcTools::Token((e_type)first * (e_type)second));
                }
                else if (CalcTools::isVec(first) && CalcTools::isNum(second))
                {
                    stack.push(fVec * (e_type)second);
                }
                else if (CalcTools::isVec(second) && CalcTools::isNum(first))
                {
                    stack.push(sVec * (e_type)first);
                }
                else throw "invalid arguments";
                vars.clear();
                break;
            case '/':
                //Деление некоммутативно, поэтому рассматривает только
                //Vec / e_type и e_type / e_type
                extractBinary(stack, vars);
                if (CalcTools::isNum(first) && CalcTools::isNum(second))
                {
                    stack.push(CalcTools::Token((e_type)second / (e_type)first));
                }
                else if (CalcTools::isVec(second) && CalcTools::isNum(first))
                {
                    stack.push(sVec / (e_type)first);
                }
                else throw "invalid arguments";
                vars.clear();
                break;
            case '|':
                extractSingle(stack, vars);

                stack.push(
                    ((VecLib::Vector)first).elementsSum()
                    );

                vars.clear();

                break;

            case '&':
                extractSingle(stack, vars);

                stack.push(
                    ((VecLib::Vector)first).elementsProd()
                    );

                vars.clear();

                break;

            case '%':
                extractSingle(stack, vars);

                stack.push(
                    ((VecLib::Vector)first).module()
                    );

                vars.clear();

                break;
            case '$':
                extractBinary(stack, vars);

                stack.push(
                    ((VecLib::Vector)second).at((ul)((e_type)first))
                    );

                vars.clear();

                break;
            case '<':
                extractSingle(stack, vars);

                //блять пиши свою сортироовку мудак ебучий

                stack.push(fVec.AscSort());
                vars.clear();

                break;
            case '>':
                extractSingle(stack, vars);

                //ну блять надеюсь ты не забыл про лямбды сравнения

                stack.push(fVec.DesSort());
                vars.clear();

                break;
            case '~':
                extractSingle(stack, vars);

                //напиши ещё блять ревёрс ёбаный
                stack.push(VecLib::Vector(fVec).reverse());

                vars.clear();

                break;
            case '#': //GCD

                extractBinary(stack, vars);

                stack.push(VecLib::NOD(fVec, sVec));

                vars.clear();

                break;
            case '^':

                extractBinary(stack, vars);

                stack.push(VecLib::NOK(fVec, sVec));

                vars.clear();

                break;

            //ноды
            // '\' - sumElems
            // '&' - prodElems
            // '%' - module
            // '$' - at
            // '<' - ascending sort
            // '>' - descending sort
            // '~' - reverse
            // '#' - GCD
            // '^' - LCM
            case 'p':
                //Векторное произведение
                extractSingle(stack, vars);

                int amount = (e_type)vars[0];

                std::vector<VecLib::Vector> vecs;
                for (int i = 0; i < amount; i++){
                    vecs.push_back(stack.top());
                    stack.pop();
                }

                stack.push(VecLib::vectorProduct(vecs));
                vars.clear();
                break;

            }
        }

    }

    return stack.top();
}

#undef first
#undef second
#undef fVec
#undef sVec
