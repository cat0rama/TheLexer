#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#include <lexer.hpp>

using namespace lexer;

TEST(Tokens, numbers_test) {
    Lexer file("numbers.txt");

    EXPECT_EQ(file.operator bool(), true);

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
}

TEST(Tokens, nums_tokens_test) {
    Lexer file("numbers&tokens.txt");

    EXPECT_EQ(file.operator bool(), true);

    auto& data = file.getLastTokenData();

    file.getNextToken();

    EXPECT_EQ(Token::T_FUNC, data.m_token);

    file.getNextToken();

    EXPECT_EQ(Token::T_EXTERN, data.m_token);

    file.getNextToken();

    EXPECT_EQ(Token::T_NAME, data.m_token);

    file.getNextToken();

    EXPECT_EQ(Token::T_NUMBER, data.m_token);

    file.getNextToken();

    EXPECT_EQ(Token::T_IDENTIFIER, data.m_token);

    file.getNextToken();

    EXPECT_EQ(Token::T_NUMBER, data.m_token);

    file.getNextToken();

    EXPECT_EQ(Token::T_AGE, data.m_token);

    file.getNextToken();

    EXPECT_EQ(Token::T_IDENTIFIER, data.m_token);
}

TEST(Tokens, symbols_test) {
    Lexer file("symbols.txt");

    EXPECT_EQ(file.operator bool(), true);

    auto& data = file.getLastTokenData();

    file.getNextToken();

    EXPECT_EQ(Token::T_SEMICOLON, data.m_token);

    file.getNextToken();

    EXPECT_EQ(Token::T_OBRACKET, data.m_token);

    file.getNextToken();

    EXPECT_EQ(Token::T_CBRACKET, data.m_token);

    file.getNextToken();

    EXPECT_EQ(Token::T_COMMA, data.m_token);

    file.getNextToken();

    EXPECT_EQ(Token::T_EQUAL, data.m_token);
}

TEST(Tokens, tokens_positions_test) {
    Lexer file("tokens.txt");

    EXPECT_EQ(file.operator bool(), true);

    auto& data = file.getLastTokenData();

    file.getNextToken();

    EXPECT_EQ(0, data.m_file_ptr_pos);

    file.getNextToken();

    EXPECT_EQ(6, data.m_file_ptr_pos);

    file.getNextToken();

    EXPECT_EQ(12, data.m_file_ptr_pos);

    file.getNextToken();

    EXPECT_EQ(19, data.m_file_ptr_pos);
}

TEST(Errors, all_errors_test) {
    using namespace std::string_literals;

    Lexer file("errors.343txt");

    file.loadErrorFunctions({[](std::string& str, TokenData& data) -> bool {
        if (std::count_if(str.begin(), str.end(), [](char c) { return c == '.'; }) >
            1) // Count dots in string
        {
            data.m_data = "more than one point found. {0}"s; // Error transmission
            data.m_token = Token::T_ERROR; // If find number with two and more points, return error
            return false;
        }
        return true;
    }});

    EXPECT_EQ(file.operator bool(), false);

    file.openFile("errors.txt");

    EXPECT_EQ(file.operator bool(), true);

    file.getNextToken();

    EXPECT_EQ(file.getLastTokenData().m_token, Token::T_ERROR);
}

int main(int argc, char* argv[], char* envp[]) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
