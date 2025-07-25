#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

enum class TokenType {
    SAY,
    IF,
    ELSE,
    IDENTIFIER,
    STRING,
    NUMBER,
    GREATER,
    LESS,
    EQUAL,
    LBRACE,
    RBRACE,
    SEMICOLON,
    UNKNOWN,
    END_OF_FILE,
    AS_LONG_AS
};

struct Token {
    TokenType type;
    std::string value;
    int line;

    Token(TokenType type, const std::string& value, int line)
        : type(type), value(value), line(line) {}
};

#endif
