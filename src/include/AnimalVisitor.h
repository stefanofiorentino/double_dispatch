#ifndef DOUBLE_DISPATCH_ANIMALVISITOR_H
#define DOUBLE_DISPATCH_ANIMALVISITOR_H

struct Cat;
struct Dog;
struct Animal;
// ... (other forward declarations)
struct AnimalVisitor
{
    virtual void Visit(Animal*) = 0;
    virtual void Visit(Cat*) = 0;
    virtual void Visit(Dog*) = 0;
    /*...*/
};

#endif //DOUBLE_DISPATCH_ANIMALVISITOR_H
