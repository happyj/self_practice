#include "stdio.h"
#include "gtest/gtest.h"

int func(int a, int b)
{
	return a - b;
}

TEST(func1, case1)
{
	EXPECT_EQ(0, func(1, 1));
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
