#ifndef VECTORITEM_H
#define VECTORITEM_H

#include <vectorLib/vector.h>
#include <QVariant>

class VectorItem
{
    std::string _name;
    Vector* _vec;
public:
    VectorItem();
    VectorItem(Vector*, std::string = "");

    std::string name() const;
    Vector* vec() const;
    void setName(std::string);
    void setVec(Vector);

    VectorItem operator=(VectorItem&);
};
Q_DECLARE_METATYPE(VectorItem*)


#endif // VECTORITEM_H
