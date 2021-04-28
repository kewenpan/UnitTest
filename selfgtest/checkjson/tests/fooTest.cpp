//
// Created by blithepan on 2020/8/13.
//

#include "fooTest.h"

#include <gtest/gtest.h>

#include "../../src/foo.h"

TEST(foo, add)
{
ASSERT_TRUE(add(8,6) == 16) << "add is not 16";
}

TEST(foo, add2)
{
ASSERT_TRUE(add(8,6) == 14) << "add is 14";
}