#include <iomanip>
#include <iostream>
#include <lexer.hpp>
#include <logger.hpp>
#include <type_traits>
#include <algorithm>

using namespace lexer;

class ExampleParser : public Lexer {
  public:

    ExampleParser(std::string t_file_name) : Lexer(t_file_name) {}
    ~ExampleParser() = default;

  private:
    // Parse example token "name". Example: name = Alex
    auto parseName() -> Code {
        if (getNextToken() != Token::T_EQUAL) {
            m_error_str = "expected: '='"s;
            return Code::SYMBOL_ERROR;
        }

        if (getNextToken() != Token::T_IDENTIFIER) {
            m_error_str = "expected: 'identifier'"s;
            return Code::TOKEN_ERROR;
        }

        return Code::SUCCES;
    }

    // Parse example token "age". Example: age = 34
    auto parseAge() -> Code {
        if (getNextToken() != Token::T_EQUAL) {
            m_error_str = "expected: '='"s;
            return Code::SYMBOL_ERROR;
        }

        if (getNextToken() != Token::T_NUMBER) {
            m_error_str = "expected: 'number'"s;
            return Code::TOKEN_ERROR;
        }

        return Code::SUCCES;
    }

  public:
    // Processing cycle
    auto entryPoint() -> const Code {
        if (!(*this)) {
            LOG_CRITICAL("file doesnt exist");
            return Code::FILE_OPEN_ERROR;
        }

        auto& data = getLastTokenData();

        // Parse tokens
        do {
            getNextToken();

            if (data.m_token == Token::T_NAME) {
                if (auto code = parseName(); code < Code::SUCCES) {
                    LOG_CRITICAL("{0}. {1}. code: {2}", m_error_str, data,
                                 std::to_string((int)code));
                    return code;
                }
                LOG_INFO("name found: {0}", getValue<std::string>());
            } else if (data.m_token == Token::T_AGE) {
                if (auto code = parseAge(); code < Code::SUCCES) {
                    LOG_CRITICAL("{0}. {1}. code: {2}", m_error_str, data,
                                 std::to_string((int)code));
                    return code;
                }
                LOG_INFO("name found: {0}", getValue<int>());
            } else if (data.m_token == Token::T_ERROR) {
                LOG_CRITICAL("{0}. {1}", getValue<std::string>(), data);
                return Code::UNKNOWN_ERROR;
            }

        } while (data.m_token != Token::T_EOF);

        return Code::SUCCES;
    }

  private:
    std::string m_error_str;
    Code m_error_code;
};

int main(int argc, char* argv[], char* envp[]) {
    ExampleParser example("example.txt");
    
    // Load functions which check some errors
    example.loadErrorFunctions({[](std::string& str, TokenData& data) -> bool {
        if (std::count_if(str.begin(), str.end(),
                          [](char c) { return c == '.'; }) > 1) // Count dots in string
        {
            data.m_data = "more than one point found. {0}"s; // Error transmission
            data.m_token =
                Token::T_ERROR; // If find number with two and more points, return error
            return false;
        }
        return true;
    }});

    return static_cast<int>(example.entryPoint());
}
