// https://gieseanw.wordpress.com/2018/12/29/stop-reimplementing-the-virtual-table-and-start-using-double-dispatch/

#include <gtest/gtest.h>
#include "include/odr.h"

TEST(DoubleDispatch, AuthorWandBoxDemo)
{
    Person person;

    Dog dog;
    person.ReactTo(&dog);

    Cat cat;
    person.ReactTo(&cat);

    OnlyCatFilter ocf;
    ocf.Visit(&cat);
    ocf.Visit(&dog);
    ASSERT_EQ(1u, ocf.m_cats.size());

    AllButCatFilter abcf;
    abcf.Visit(&cat);
    abcf.Visit(&dog);
    ASSERT_EQ(1u, abcf.animals_.size());
}