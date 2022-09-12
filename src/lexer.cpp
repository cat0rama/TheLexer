#include "identifier.hpp"
#include "lexer.hpp"

#include <algorithm>

namespace stxa
{
    Lexer::Lexer(): m_token_data({Token::T_NULL, 0, {}})
    {   }

    Lexer::Lexer(const std::string& t_file_name) noexcept : 
    m_fstream(t_file_name), m_token_data({Token::T_NULL, 0, {}})
    {   }

    Lexer::operator bool() const noexcept
    {
        return m_fstream.is_open();
    }

    // Open file for parse
    auto Lexer::openFile(const std::string& t_file_name) noexcept -> Code
    {
        if (m_fstream.is_open()) {
            m_fstream.close();
        }

        m_fstream.open(t_file_name, std::ios::in);

        if (!m_fstream.is_open()) {
            return Code::FILE_OPEN_ERROR;
        }

        return Code::SUCCES;
    }

    // Get tokens from file
    auto Lexer::getNextToken() -> Token
    {
        while (m_fstream.get(m_last_char)) {
            std::string identifier;

            if (std::isspace(m_last_char)) {
                continue;
            }

            if (std::isalpha(m_last_char)) {
                identifier = m_last_char;

                while (std::isalnum((m_last_char = m_fstream.get()))) {
                    identifier.push_back(m_last_char);
                }

                auto find_tok = identifiers_en.find(identifier);
                if (find_tok != identifiers_en.end()) {
                    /* Finding the position of the token by calculating the string of the identifier and the position 
                    in the file, thereby finding the beginning of the position of the token in the file */
                    m_token_data.m_file_ptr_pos = 
                    m_fstream.tellg() - static_cast<std::streampos>(identifier.size());
                    m_token_data.m_token = find_tok->second;
                    return m_token_data.m_token;
                }
            }

            if (std::isdigit(m_last_char)) {
                    m_token_data.m_file_ptr_pos = m_fstream.tellg();   // Get start number position
                    std::string number_str;

                    do {
                        number_str.push_back(m_last_char);
                        m_last_char = m_fstream.get();
                    } while (std::isdigit(m_last_char) || m_last_char == '.');

                    if (std::count_if(number_str.begin(), number_str.end(), 
                       [&number_str](char &c) { return c == '.'; } ) > 1) 
                    {
                        m_token_data.m_data = {};   // Nulling std::variant
                        return Token::T_ERROR;   // If find number with two and more points, return error
                    }
                    m_token_data.m_data = std::strtod(number_str.c_str(), nullptr);   // String to double
                    return Token::T_NUMBER;
            }

            if (m_last_char == '/') {
                std::string comment;
                m_token_data.m_file_ptr_pos = m_fstream.tellg();   // Get start comment position

                while ((m_last_char = m_fstream.get()) != '\n' && m_last_char != '\r') {
                    comment.push_back(m_last_char);
                }
                m_token_data.m_data = std::move(comment);
                return Token::T_COMMENT;
            }

            if (m_last_char == EOF) {
                m_token_data.m_file_ptr_pos = m_fstream.tellg();   // Get last position of file
                m_token_data.m_data = {};
                return Token::T_EOF;
            }
        }

        return Token::T_NULL;
    }

    auto Lexer::getLastTokenData() const -> const TokenData&
    {
       return m_token_data;   // Get token data(token, value(std::variant<double, string>), file ptr position)
    }
}
