#ifndef PARSER_HPP
#define PARSER_HPP

#include "../lexer/token.hpp"
#include "ast.hpp"
#include <vector>
#include <memory>
#include <string>

class Parser {
    std::vector<Token> tokens;
    size_t current = 0;

public:
    Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

    // Parse the full program
    std::vector<std::shared_ptr<ASTNode>> parseProgram();

private:
    // Helpers
    Token peek();
    Token advance();
    bool match(TokenType type);
    bool check(TokenType type);

    // Grammar rules
    std::shared_ptr<ASTNode> parseStatement();
    std::shared_ptr<ASTNode>parseGrab();
    std::shared_ptr<ASTNode> parseSay();
    std::shared_ptr<IfNode> parseIf();
    std::shared_ptr<ExpressionNode> parseExpression();
};

#endif
