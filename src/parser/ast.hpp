#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>
#include <memory>

// Base class
struct ASTNode {
    virtual ~ASTNode() = default;
};

// Statement: say "text";
struct SayNode : public ASTNode {
    std::string message;
    SayNode(const std::string& msg) : message(msg) {}
};

// Expression: like x > 18
struct ExpressionNode : public ASTNode {
    std::string left;
    std::string op;
    std::string right;

    ExpressionNode(const std::string& l, const std::string& o, const std::string& r)
        : left(l), op(o), right(r) {}
};

// if condition { ... }
struct IfNode : public ASTNode {
    std::shared_ptr<ExpressionNode> condition;
    std::vector<std::shared_ptr<ASTNode>> body;

    IfNode(std::shared_ptr<ExpressionNode> cond) : condition(cond) {}
};
//as long as condition { ... }
struct AsLongAsNode : public ASTNode {
    std::shared_ptr<ExpressionNode> condition;
    std::vector<std::shared_ptr<ASTNode>> body;

    AsLongAsNode(std::shared_ptr<ExpressionNode> cond) : condition(cond) {}
};

#endif
