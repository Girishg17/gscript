#include "token.hpp"
#include <cctype>
#include <vector>
#include <string>
#include <iostream>

class Tokenizer {
    std::string source;
    size_t pos = 0;
    int line = 1;

public:
    Tokenizer(const std::string& src) : source(src) {}

    char peek() {
        return pos < source.size() ? source[pos] : '\0';
    }

    char advance() {
        if (peek() == '\n') line++;
        return source[pos++];
    }

    void skipWhitespace() {
        while (isspace(peek())) advance();
    }

    Token nextToken() {
        skipWhitespace();

        if (pos >= source.size())
            return Token(TokenType::END_OF_FILE, "", line);

        char c = advance();

        // Keywords
        if (isalpha(c)) {
            std::string word;
            word += c;
            while (isalnum(peek())) word += advance();

            if (word == "as") {
                size_t savePos = pos;
                skipWhitespace();

                std::string second;
                while (isalpha(peek())) second += advance();
                if (second == "long") {
                    skipWhitespace();
                    std::string third;
                    while (isalpha(peek())) third += advance();

                    if (third == "as") {
                        return Token(TokenType::AS_LONG_AS, "as long as", line);
                    }
                }

                // If not full "as long as", rewind and treat "as" as identifier
                pos = savePos;
            }

            if (word == "say") return Token(TokenType::SAY, word, line);
            if (word == "if") return Token(TokenType::IF, word, line);
            if (word == "else") return Token(TokenType::ELSE, word, line);
            return Token(TokenType::IDENTIFIER, word, line);
        }

        // Numbers
        if (isdigit(c)) {
            std::string num;
            num += c;
            while (isdigit(peek())) num += advance();
            return Token(TokenType::NUMBER, num, line);
        }

        // Strings
        if (c == '"') {
            std::string str;
            while (peek() != '"' && peek() != '\0') str += advance();
            advance(); // consume closing quote
            return Token(TokenType::STRING, str, line);
        }

        // Symbols
        switch (c) {
            case '>': return Token(TokenType::GREATER, ">", line);
            case '<': return Token(TokenType::LESS, "<", line);
            case '=': return Token(TokenType::EQUAL, "=", line);
            case '{': return Token(TokenType::LBRACE, "{", line);
            case '}': return Token(TokenType::RBRACE, "}", line);
            case ';': return Token(TokenType::SEMICOLON, ";", line);
        }

        return Token(TokenType::UNKNOWN, std::string(1, c), line);
    }

    std::vector<Token> tokenize() {
        std::vector<Token> tokens;
        Token token = nextToken();
        while (token.type != TokenType::END_OF_FILE) {
            tokens.push_back(token);
            token = nextToken();
        }
        tokens.push_back(token); // push EOF
        return tokens;
    }
};
