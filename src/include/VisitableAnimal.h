#ifndef DOUBLE_DISPATCH_VISITABLEANIMAL_H
#define DOUBLE_DISPATCH_VISITABLEANIMAL_H

#include "Animal.h"

template<class T>
struct VisitableAnimal : Animal
{
    void Visit(AnimalVisitor* _visitor) override
    {
        _visitor->Visit(static_cast<T*>(this));
    }
};

struct Cat : VisitableAnimal<Cat> {};
struct Dog : VisitableAnimal<Dog> {};

#endif //DOUBLE_DISPATCH_VISITABLEANIMAL_H
