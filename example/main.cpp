#include <iostream>
#include <iomanip>
#include <string>
#include <type_traits>
#include <lexer.hpp>

using namespace lexer;

class ExampleParser : public Lexer {
  public:
    ExampleParser(std::string t_file_name) : Lexer(t_file_name) {
        getNextToken();
    }

    ~ExampleParser() = default;

  public:
  // Get value from std::variant with type casting from double to T and string if needed
    template <typename T> const T getValue() const noexcept {
        if constexpr (std::is_integral_v<T> || std::is_floating_point_v<T>) {
            return static_cast<T>(std::get<double>(getLastTokenData().m_data.value_or(0)));
        } else {
            return std::get<std::string>(getLastTokenData().m_data.value_or("none"));
        }
    }
};

int main(int argc, char* argv[], char* envp[]) {
    ExampleParser example("example.txt");

    //std::cout << std::setprecision(5) << example.getValue<float>();
    std::cout << example.getValue<std::string>();
}
