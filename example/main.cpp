#include <iomanip>
#include <iostream>
#include <optional>
#include <string>
#include <type_traits>
#include <logger.hpp>
#include <lexer.hpp>

using namespace lexer;

class ExampleParser : public Lexer {
  public:
    ExampleParser(std::string t_file_name) : Lexer(t_file_name) {}

    ~ExampleParser() = default;
    
private:
    std::string parseName();

    std::string parseAge();
public:
    // Get value from std::variant with type casting from double to T(integral or real) and string
    // if needed
    template <typename T> auto getValue() const -> const T {
        if constexpr ((std::is_integral_v<T> || std::is_floating_point_v<T>)) {
            return static_cast<T>(std::get<double>(getLastTokenData().m_data.value_or(0)));
        } else {
            return std::get<std::string>(getLastTokenData().m_data.value_or("null")).c_str();
        }
    }

    // Processing cycle
    auto entryPoint() -> const Code
    {
        if (!(*this)) {
            LOG_CRITICAL("file doesnt exist");
            return Code::FILE_OPEN_ERROR;
        }

        auto &data = getLastTokenData();

        do {
            getNextToken();

            if (data.m_token == Token::T_NAME) {
                //parse name
            } else if (data.m_token == Token::T_ERROR) {
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
