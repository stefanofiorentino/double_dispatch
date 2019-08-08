#include <iostream>
#include <vector>

// https://gieseanw.wordpress.com/2018/12/29/stop-reimplementing-the-virtual-table-and-start-using-double-dispatch/

// AnimalVisitor.h
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


//// C++17 Only
//// DefaultDoNothingAnimalVisitor.h
////#include "AnimalVisitor.h"
//template<class T>
//struct SingleDoNothingAnimalVisitor : virtual AnimalVisitor
//{
//    using AnimalVisitor::Visit;
//    void Visit(T*) override{}
//};
//
//template<class... T>
//struct MultipleDoNothingAnimalVisitor : public SingleDoNothingAnimalVisitor<T>...
//{
//using SingleDoNothingAnimalVisitor<T>::Visit...;
//};
//
//// strong typedef
//struct DoNothingAnimalVisitor : public MultipleDoNothingAnimalVisitor<Cat, Dog>
//{};
//
//struct CatFilter : DoNothingAnimalVisitor
//{
//    using DoNothingAnimalVisitor::Visit;
//    void Visit(Cat* _cat) override
//    {
//        cats_.push_back(_cat);
//    }
//    std::vector<Cat*> cats_;
//};

// Animal.h
struct AnimalVisitor;
struct Animal
{
    virtual void Visit(AnimalVisitor* _visitor) = 0;
};

// Dog.h
//#include "Animal.h"

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

// Cat.h etc follow Dog.h impl

// ReactionVisitor.h
//#include "AnimalVisitor.h"
//#include "Cat.h"
//#include "Dog.h"
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

// Person.h
//#include "Animal.h"
//#include "ReactionVisitor.h"
struct Person
{
    /*...*/
    void ReactTo(Animal* _animal){
        ReactionVisitor visitor{this};
        _animal->Visit(&visitor);
    }
};

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
    void Visit(Animal* _animal) override
    {
        /*do-nothing*/
    }
    void Visit(Cat* cat) override{
        m_cats.push_back(cat);
    }
    std::vector<Cat*> m_cats;
};

int main ()
{
    Person person;

    Dog dog;
    person.ReactTo(&dog);

    Cat cat;
    person.ReactTo(&cat);

    OnlyCatFilter ocf;
    ocf.Visit(&cat);
    ocf.Visit(&dog);
    std::cout << "visitor encountered " << ocf.m_cats.size() << " cats\n";

    AllButCatFilter abcf;
    abcf.Visit(&cat);
    abcf.Visit(&dog);
    std::cout << "visitor encountered " << abcf.animals_.size() << " non-cats\n";
    return 0;
}