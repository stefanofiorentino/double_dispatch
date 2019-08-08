#ifndef DOUBLE_DISPATCH_REACTIONVISITOR_H
#define DOUBLE_DISPATCH_REACTIONVISITOR_H

#include <iostream>
#include "AnimalVisitor.h"

struct Person;
struct ReactionVisitor : public AnimalVisitor
{
    explicit ReactionVisitor(Person* _person) : person_{_person}
    {}
    void Visit(Animal*) override {/*do-nothing*/}
    void Visit(Cat*) override {
        std::puts(__PRETTY_FUNCTION__);
    }
    void Visit(Dog*) override {
        std::puts(__PRETTY_FUNCTION__);
    }
    Person* person_ = nullptr;
};

#endif //DOUBLE_DISPATCH_REACTIONVISITOR_H
