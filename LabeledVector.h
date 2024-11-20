#ifndef LABELEDVECTOR_H
#define LABELEDVECTOR_H

#include <QVariant>
#include "vectorLib/vector.h"

struct LabeledVector
{
    std::string name;
    Vector vec;
};

Q_DECLARE_METATYPE(LabeledVector*)

#endif // LABELEDVECTOR_H
