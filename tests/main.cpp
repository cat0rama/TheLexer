#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <lexer.hpp>

using namespace lexer;

TEST(Tokens, numbers_test)
{
    Lexer file("numbers.txt");

    ASSERT_EQ(file.operator bool(), true);

    file.getNextToken();

    EXPECT_EQ(4, file.getValue<int>());

    file.getNextToken();
    
    EXPECT_EQ(78, file.getValue<int>());

    file.getNextToken();

    EXPECT_EQ(98823, file.getValue<int>());

    file.getNextToken();

    EXPECT_EQ(342332198, file.getValue<int>());

    file.getNextToken();

    EXPECT_FLOAT_EQ(3843.2349f, file.getValue<float>());

    file.getNextToken();

    EXPECT_FLOAT_EQ(213.983f, file.getValue<float>());

    file.getNextToken();

    EXPECT_DOUBLE_EQ(987.394830, file.getValue<double>());

    file.getNextToken();

    EXPECT_DOUBLE_EQ(312.23343139, file.getValue<double>());

    // проверка на равенство
    //EXPECT_STREQ("ddw", "ddw"); // для строк
    //EXPECT_EQ(2, 2 + 0); // для чисел
}

TEST(Tokens, tokens_test)
{
    
}

TEST(Tokens, symbols_test)
{

}


TEST(Tokens, tokens_positions_test)
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
