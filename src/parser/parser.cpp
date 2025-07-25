#include "parser.hpp"
#include <stdexcept>
#include <iostream>

// === Token Utilities ===

Token Parser::peek() {
    return tokens[current];
}

Token Parser::advance() {
    if (current < tokens.size()) current++;
    return tokens[current - 1];
}

bool Parser::check(TokenType type) {
    return peek().type == type;
}

bool Parser::match(TokenType type) {
    if (check(type)) {
        advance();
        return true;
    }
    return false;
}

// === Main Entry ===

std::vector<std::shared_ptr<ASTNode>> Parser::parseProgram() {
    std::vector<std::shared_ptr<ASTNode>> program;

    while (!check(TokenType::END_OF_FILE)) {
        auto stmt = parseStatement();
        if (stmt) {
            program.push_back(stmt);
        }
    }

    return program;
}

// === Grammar Rules ===

std::shared_ptr<ASTNode> Parser::parseStatement() {
    if (match(TokenType::SAY)) {
        return parseSay();
    } else if (match(TokenType::IF)) {
        return parseIf();
    }else if (match(TokenType::AS_LONG_AS)) { 
        return parseAsLongAs(); 
    }
    else {
        std::cerr << "Unknown statement at line " << peek().line << "\n";
        advance();
        return nullptr;
    }
}

std::shared_ptr<SayNode> Parser::parseSay() {
    if (!check(TokenType::STRING)) {
        throw std::runtime_error("Expected string after 'say'");
    }
    std::string message = advance().value;

    // Optional: require semicolon
    if (!match(TokenType::SEMICOLON)) {
        throw std::runtime_error("Expected ';' after say statement");
    }

    return std::make_shared<SayNode>(message);
}

std::shared_ptr<ExpressionNode> Parser::parseExpression() {
    // Expect IDENTIFIER OP NUMBER (e.g., age > 18)
    std::string left = advance().value;

    if (!(match(TokenType::GREATER) || match(TokenType::LESS) || match(TokenType::EQUAL))) {
        throw std::runtime_error("Expected comparison operator in expression");
    }

    std::string op = tokens[current - 1].value;

    if (!check(TokenType::NUMBER)) {
        throw std::runtime_error("Expected number after operator");
    }

    std::string right = advance().value;

    return std::make_shared<ExpressionNode>(left, op, right);
}

std::shared_ptr<IfNode> Parser::parseIf() {
    auto condition = parseExpression();

    if (!match(TokenType::LBRACE)) {
        throw std::runtime_error("Expected '{' after if condition");
    }

    auto ifNode = std::make_shared<IfNode>(condition);

    // Parse statements inside the if block
    while (!check(TokenType::RBRACE) && !check(TokenType::END_OF_FILE)) {
        auto stmt = parseStatement();
        if (stmt) {
            ifNode->body.push_back(stmt);
        }
    }

    if (!match(TokenType::RBRACE)) {
        throw std::runtime_error("Expected '}' to close if block");
    }

    return ifNode;
}

std::shared_ptr<AsLongAsNode> Parser::parseAsLongAs() {
    auto condition = parseExpression();

    if (!match(TokenType::LBRACE)) {
        throw std::runtime_error("Expected '{' after as long as condition");
    }

    auto node = std::make_shared<AsLongAsNode>(condition);

    // Parse statements inside the block
    while (!check(TokenType::RBRACE) && !check(TokenType::END_OF_FILE)) {
        auto stmt = parseStatement();
        if (stmt) {
            node->body.push_back(stmt);
        }
    }

    if (!match(TokenType::RBRACE)) {
        throw std::runtime_error("Expected '}' to close as long as block");
    }

    return node;
}
