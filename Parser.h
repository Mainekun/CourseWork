#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"
#include "vectorLib/vector.h"

using namespace VectorLexer;

namespace VectorParser {

using Vectors = std::vector<VecLib::Vector>;

enum ParseState {
    NONE = 0,
    NAME_ENTERED = 1,
    SIZE_ENTERED = 2,
    START_ELEMENTS = 4,
    ELEMENT = 8,
    SEP = 16,
    FINISH_ELEMENTS = 32,
};

Vectors Parse(Tokens);

} // namespace VectorParser

#endif // PARSER_H
