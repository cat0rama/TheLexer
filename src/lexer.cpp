#include "lexer.hpp"
#include "identifier.hpp"

#include <algorithm>
#include <iostream>

namespace lexer {
Lexer::Lexer() : m_last_char(0), m_next_char(0) {}

Lexer::Lexer(const std::string& t_file_name)
    : m_fstream(t_file_name), m_last_char(0), m_next_char(0) {}

auto Lexer::calculatePosition(const std::string& t_identifier) -> std::streampos {
    /* Finding the position of the token by calculating the string of the m_identifier and the
    position in the file, thereby finding the beginning of the position of the token in the file */
    std::streampos identifier_pos = 0;

    if (m_next_char == EOF) {
        m_fstream.seekg(0, std::ios::end); // Go to end file
        identifier_pos =                   // Calculate position of m_identifier
            m_fstream.tellg() - static_cast<std::streampos>(t_identifier.length());
    } else {
        identifier_pos = m_fstream.tellg() - static_cast<std::streampos>(t_identifier.length());
    }

    return identifier_pos;
}

// Check if char is special symbol
auto Lexer::isSymbol(const char t_sym) const noexcept -> bool {
    return g_symbols.find(t_sym) != g_symbols.end();
}

// Parse keywords
auto Lexer::findKeyword(std::string& t_identifier) -> bool {
    if (std::isalpha(m_last_char)) { // Check if symbol is char
        t_identifier = m_last_char;
        while ((m_next_char = m_fstream.peek()) != EOF && m_next_char != '\n' &&
               m_next_char != ' ' && !isSymbol(m_next_char)) {
            if (std::isalnum((m_last_char = m_fstream.get()))) {
                t_identifier.push_back(m_last_char); // Push identifier character
            }
        }
        m_token_data.m_token = Token::T_IDENTIFIER;
        m_token_data.m_file_ptr_pos = calculatePosition(m_identifier);
        if (auto find_tok = g_identifiers_en.find(m_identifier);
            find_tok != g_identifiers_en.end()) {
            m_token_data.m_token = find_tok->second; // Get token from map
        } else {
            m_token_data.m_data =
                std::move(m_identifier); // If token is identifier, we will save it
        }
        return true;
    }
    return false;
}

// Parse number
auto Lexer::findNumber(std::string& t_identifier) -> bool {
    if (std::isdigit(m_last_char)) { // Check if symbol is number
        t_identifier = m_last_char;
        while ((m_next_char = m_fstream.peek()) != EOF && m_next_char != '\n' &&
               m_next_char != ' ') {
            if (std::isdigit((m_last_char = m_fstream.get())) || m_last_char == '.') {
                t_identifier.push_back(m_last_char); // Push number character
            }
        }
        m_token_data.m_data = std::strtod(t_identifier.c_str(), nullptr); // String to double
        m_token_data.m_token = Token::T_NUMBER;

        for (const auto& fn : m_error_func) {
            if (!fn(t_identifier, m_token_data)) {
                break;
            }
        }

        m_token_data.m_file_ptr_pos = calculatePosition(m_identifier);
        return true;
    }
    return false;
}

// Find special symbol from map
auto Lexer::findSymbol() noexcept -> bool {
    if (auto token = g_symbols.find(m_last_char); token != g_symbols.end()) {
        m_token_data.m_file_ptr_pos = calculatePosition((std::string() += m_last_char));
        m_token_data.m_token = token->second;
        return true;
    }
    return false;
}

// Parse comment
auto Lexer::findComment() noexcept -> bool {
    if (m_last_char == '/') { // Parse comment for skip it, but save read ptr position
        while ((m_next_char = m_fstream.peek()) != EOF && m_next_char != '\n' &&
               m_next_char != '\r') {
            m_last_char =
                m_fstream.get(); // Get symbol from file for skip it, but save file ptr position
            continue;
        }
        m_token_data.m_token = Token::T_COMMENT;
        return true;
    }
    return false;
}

// Overload operator() for checking istream object
Lexer::operator bool() const noexcept { return m_fstream.is_open(); }

// Open file for parse
auto Lexer::openFile(const std::string& t_file_name) noexcept -> Code {
    if (m_fstream.is_open()) {
        m_fstream.close();
    }

    m_fstream.open(t_file_name, std::ios::in);

    if (!m_fstream.is_open()) {
        return Code::FILE_OPEN_ERROR;
    }
    return Code::SUCCES;
}

// Close file
void Lexer::closeFile() noexcept { m_fstream.close(); }

auto Lexer::operator->() const noexcept -> const TokenData* { return &m_token_data; }

// Get tokens from file
auto Lexer::getNextToken() -> Token {
    while (m_fstream) {
        if (m_next_char == EOF || m_fstream.peek() == EOF) { // Parse end of file
            clearData();
            return (m_token_data.m_token = Token::T_EOF);
        }

        m_last_char = m_fstream.get();
        if (std::isspace(m_last_char)) { // Skip space
            continue;
        } else if (findKeyword(m_identifier)) { // Parse keyword
            return m_token_data
                .m_token; // Return some word if token doesnt find else return IDENTIFIER
        } else if (findSymbol()) {
            return m_token_data.m_token;
        } else if (findNumber(m_identifier)) { // Parse number
            return m_token_data.m_token;
        } else if (findComment()) { // Parse comment for skip it, but save read ptr position
            clearData();
            return m_token_data.m_token;
        }
    }

    return Token::T_NULL; // Return null if no aviable another token values
}

auto Lexer::getLastTokenData() const -> const TokenData& {
    return m_token_data; // Get token data(token, value(std::variant<double, string>), file ptr
                         // position)
}

// Clear data
auto Lexer::clearData() noexcept -> void {
    m_token_data.m_file_ptr_pos = 0;
    m_token_data.m_data = {};
}

auto Lexer::loadErrorFunctions(const error_handlers& t_errors) -> void {
    for (const auto& fn : t_errors) {
        m_error_func.push_back(fn);
    }
}

} // namespace lexer
