#ifndef DOUBLE_DISPATCH_PERSON_H
#define DOUBLE_DISPATCH_PERSON_H

#include "Animal.h"
#include "ReactionVisitor.h"
struct Person
{
    void ReactTo(Animal* _animal){
        ReactionVisitor visitor{this};
        _animal->Visit(&visitor);
    }
};

#endif //DOUBLE_DISPATCH_PERSON_H
