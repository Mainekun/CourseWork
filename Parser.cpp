#include "Parser.h"

VectorParser::Vectors VectorParser::Parse(Tokens tokens)
{
    if (tokens.empty()) return {};

    //if (tokens[0].Type() != NAME) throw std::logic_error("No name");
    //if (tokens[1].Type() != SIZE) throw std::logic_error("No size in \'[]\'");
    //if (tokens[2].Type() != START_SEQ) throw std::logic_error("No starting array \'(\'");
    //if (tokens.back().Type() != FINISH_SEQ) throw std::logic_error("No ending array \')\'");

    long state = NONE;

    Vectors result;

    std::string name;
    unsigned long size;
    std::vector<double> elements;

    for (auto i = tokens.begin(); i != tokens.end(); i++)
    {
        switch(i->Type())
        {
        case NAME:
            if (state & NAME_ENTERED) throw "Name already defined";
            name = (std::string)(*i);
            state = state | NAME_ENTERED;
            break;
        case SIZE:
            if (state & SIZE_ENTERED) throw "Size already defined";
            if (!(state & NAME_ENTERED)) throw "Name was not defined";
            size = (unsigned long)(*i);
            state = state | SIZE_ENTERED;
            break;

        case START_SEQ:
            if (!(state & NAME_ENTERED)) throw "Name was not defined";
            if (!(state & SIZE_ENTERED)) throw "Size was not defined";
            if (state & START_ELEMENTS) throw "Extra \'(\'";
            state = state | START_ELEMENTS;
            break;

        case DOUBLE_VAL:
            if (!(state & NAME_ENTERED)) throw "Name was not defined";
            if (!(state & SIZE_ENTERED)) throw "Size was not defined";
            if (!(state & START_ELEMENTS)) throw "Vector was not defined";
            if (state & ELEMENT) throw "Value was already written";
            if (!(state & START_ELEMENTS) && !(state & SEP)) throw "Need separator between elements";
            elements.push_back((double)(*i));
            state = state | ELEMENT; state = state & ~(SEP | FINISH_ELEMENTS);
            break;

        case SEPARATOR:
            if (!(state & NAME_ENTERED)) throw "Name was not defined";
            if (!(state & SIZE_ENTERED)) throw "Size was not defined";
            if (!(state & START_ELEMENTS)) throw "Vector was not defined";
            if (!(state & ELEMENT)) throw "Value was not found";
            // if (state & SEP) throw
            state = state | SEP; state = state & ~ELEMENT;
            break;

        case FINISH_SEQ:
            if (state != (NAME_ENTERED | SIZE_ENTERED | START_ELEMENTS | ELEMENT)) throw "record is formed bad";
            if (size != elements.size()) throw "Size does not match the amount of elements";
            result.push_back(Vector(name, size, elements.data()));
            state = NONE;
            elements.clear();
            size = 0;
            name = "";
        }
    }

    return result;
}
