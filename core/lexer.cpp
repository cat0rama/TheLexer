#include "lexer.hpp"

#include <exception>
#include <iostream>

namespace stxa
{
    Lexer::Lexer(const char* t_file_name) : m_fstream(t_file_name, std::ios_base::in)
    {
        if (!m_fstream.is_open()) {
            throw std::runtime_error("error to open file");
        }
    }

    auto Lexer::getInstance(const char* t_file_name) -> Lexer&
    {
        static Lexer instance(t_file_name);
        return instance;
    }

    auto Lexer::getToken() -> Token
    {
        char last_char = 0;

        while (m_fstream.get(last_char)) {
            if (std::isspace(last_char)) {
                continue;
            }

            if (std::isalpha(last_char)) {
                m_identifier.push_back(last_char);

                auto find_tok = identifiers.find(m_identifier);
                // write parse for numbers
                // fix parse tokens
                if (find_tok != identifiers.end()) {
                    return find_tok->second;
                }
            }

            if (last_char == EOF) {
                return Token::T_EOF;
            }
        }

        return Token::T_NULL;
    }
}
