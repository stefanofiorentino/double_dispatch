#ifndef DOUBLE_DISPATCH_ANIMAL_H
#define DOUBLE_DISPATCH_ANIMAL_H

struct AnimalVisitor;
struct Animal
{
    virtual void Visit(AnimalVisitor* _visitor) = 0;
};

#endif //DOUBLE_DISPATCH_ANIMAL_H
