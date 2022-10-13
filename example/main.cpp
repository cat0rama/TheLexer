#include <error.hpp>
#include <lexer.hpp>
#include <logger.hpp>
#include <token.hpp>

using namespace lexer;

int main(int argc, char* argv[], char* envp[]) 
{
    Lexer lx("file.txt");

    if (lx) {
        while (lx->m_token != Token::T_EOF) {
            lx.getNextToken();
            if (lx->m_token == Token::T_EXTERN) {
                LOG_INFO("FIND FUNC!");
            }
        }
    } else {
        LOG_CRITICAL("file not open");
    }

    return 0;
}
