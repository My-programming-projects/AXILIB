

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

TEST(Constructors, default_constructor)
{
    axilib::Matrix<int> m;

    EXPECT_EQ(m.rows(), 0);
    EXPECT_EQ(m.cols(), 1);
}

