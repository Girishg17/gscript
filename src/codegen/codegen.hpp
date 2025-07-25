#ifndef CODEGEN_HPP
#define CODEGEN_HPP

// #include "parser/ast.hpp"
#include "../parser/ast.hpp"
#include <vector>
#include <string>
#include <memory>

class CodeGenerator {
public:
    CodeGenerator();
    void generate(const std::vector<std::shared_ptr<ASTNode>>& program);
    void writeToFile(const std::string& filename);

private:
    std::vector<std::string> data;
    std::vector<std::string> text;
    int labelCount = 1;
    int msgCount = 1;

    std::string addString(const std::string& str);
    void emitSay(const SayNode* say);
    void emitIf(const IfNode* ifnode);
    void emitAsLongAs(const AsLongAsNode* node);
};

#endif
