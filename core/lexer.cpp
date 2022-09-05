#include "lexer.hpp"

#include <exception>
#include <iostream>
#include <algorithm>

namespace stxa
{
    Lexer::Lexer(const char* t_file_name) : m_fstream(t_file_name, std::ios_base::in)
    {
        if (!m_fstream.is_open()) {
            throw std::runtime_error("error to open file");
        }
    }

    // Get object instance
    auto Lexer::getInstance(const char* t_file_name) -> Lexer&
    {
        static Lexer instance(t_file_name);
        return instance;
    }

    // Get tokens from file
    auto Lexer::getNextToken() -> Token
    {
        char last_char = 0;

        while (m_fstream.get(last_char)) {
            if (std::isspace(last_char)) {
                continue;
            }

            if (std::isalpha(last_char)) {
                m_identifier = last_char;

                while (std::isalnum((last_char = m_fstream.get()))) {
                    m_identifier.push_back(last_char);
                }

                auto find_tok = identifiers.find(m_identifier);
                if (find_tok != identifiers.end()) {
                    m_current_token = find_tok->second;
                    return m_current_token;
                }
            }

            if (std::isdigit(last_char) || last_char == '.') {
                    std::string number_str;
                    do {
                        number_str.push_back(last_char);
                        last_char = m_fstream.get();
                    } while (std::isdigit(last_char) || last_char == '.');

                    if (std::count_if(number_str.begin(), number_str.end(), 
                       [&number_str](char &c) { return c == '.'; } ) > 1) 
                    {
                        // Replace with logging system
                        std::cout << "unable to parse number with two points." << std::endl;
                        return Token::T_ERROR;
                    }

                    m_num_value = std::strtod(number_str.c_str(), nullptr);
                    return Token::T_NUMBER;
            }

            if (last_char == EOF) {
                return Token::T_EOF;
            }
        }

        return Token::T_NULL;
    }
}
