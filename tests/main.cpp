#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <lexer.hpp>

using namespace lexer;

TEST(Numbers, numbers_test)
{
    Lexer file("numbers.txt");

    ASSERT_EQ(file.operator bool(), true);

    // проверка на равенство
    EXPECT_STREQ("ddw", "ddw"); // для строк
    EXPECT_EQ(2, 2 + 0); // для чисел
}

TEST(Tokens, tokens_test)
{
    
}

TEST(Errors, all_errors_test)
{

}

int main(int argc, char* argv[], char* envp[]) 
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
