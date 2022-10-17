#include <iomanip>
#include <iostream>
#include <lexer.hpp>
#include <logger.hpp>
#include <type_traits>

using namespace lexer;

class ExampleParser : public Lexer {
  public:
    ExampleParser(std::string t_file_name) : Lexer(t_file_name) {}

    ~ExampleParser() = default;

  private:
    std::optional<std::string> parseName() {
        return {};
    }
    
    std::optional<int> parseAge() {
        return {};
    }

  public:
    // Processing cycle
    auto entryPoint() -> const Code {
        if (!(*this)) {
            LOG_CRITICAL("file doesnt exist");
            return Code::FILE_OPEN_ERROR;
        }

        auto& data = getLastTokenData();

        do {
            getNextToken();

            if (data.m_token == Token::T_NAME) {
                //parseName();
            } else if (data.m_token == Token::T_AGE) {
                //parseAge();
            } else if (data.m_token == Token::T_ERROR) {
                getValue<std::string>();
                LOG_CRITICAL("{0} {1}", getValue<std::string>(), data);
            }

        } while (data.m_token != Token::T_EOF);

        return Code::SUCCES;
    }
};

int main(int argc, char* argv[], char* envp[]) {
    ExampleParser example("example.txt");

    return static_cast<int>(example.entryPoint());
}
