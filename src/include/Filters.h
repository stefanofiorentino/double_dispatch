#ifndef DOUBLE_DISPATCH_FILTERS_H
#define DOUBLE_DISPATCH_FILTERS_H

#include <vector>
#include "VisitableAnimal.h"

struct DefaultAnimalVisitor : AnimalVisitor
{
    void Visit(Animal*) override{}
    void Visit(Cat* _cat) override{Visit(static_cast<Animal*>(_cat));}
    void Visit(Dog* _dog) override {Visit(static_cast<Animal*>(_dog));}
};

struct AllButCatFilter : DefaultAnimalVisitor
{
    using DefaultAnimalVisitor::Visit;
    void Visit(Animal* _animal) override
    {
        animals_.push_back(_animal);
    }
    void Visit(Cat*) override{/*intentionally left empty*/}
    std::vector<Animal*> animals_;
};

struct OnlyCatFilter : DefaultAnimalVisitor
{
    using DefaultAnimalVisitor::Visit;
    void Visit(Animal*) override
    {
        /*do-nothing*/
    }
    void Visit(Cat* cat) override{
        m_cats.push_back(cat);
    }
    std::vector<Cat*> m_cats;
};

#endif //DOUBLE_DISPATCH_FILTERS_H
