#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(LOL, test1)
{
    ASSERT_TRUE(1 == 1);
}

TEST(LOL, test2)
{
    ASSERT_FALSE(1 == 1);
}

int main(int argc, char* argv[], char* envp[]) 
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
