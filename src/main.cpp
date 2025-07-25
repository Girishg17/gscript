// #include "lexer/tokenizer.cpp"
// #include <fstream>
// #include <sstream>
// #include <iostream>

// int main(int argc, char** argv) {
//     if (argc < 2) {
//         std::cerr << "Usage: " << argv[0] << " <filename>\n";
//         return 1;
//     }

//     std::ifstream file(argv[1]);
//     if (!file.is_open()) {
//         std::cerr << "Failed to open file: " << argv[1] << "\n";
//         return 1;
//     }

//     std::stringstream buffer;
//     buffer << file.rdbuf();
//     std::string source = buffer.str();

//     std::cout << "Source: " << source << "\n"; // ✅ TEMP DEBUG: See if file is read

//     Tokenizer tokenizer(source);
//     std::vector<Token> tokens = tokenizer.tokenize();

//     for (const Token& token : tokens) {
//         std::cout << "Token: " << (int)token.type << ", Value: " << token.value << ", Line: " << token.line << "\n";
//     }

//     return 0;
// }


#include "lexer/tokenizer.cpp"
#include "parser/parser.hpp"
#include "parser/ast.hpp"
#include "codegen/codegen.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>

void printAST(const std::shared_ptr<ASTNode>& node, int indent = 0) {
    std::string space(indent, ' ');

    if (auto say = std::dynamic_pointer_cast<SayNode>(node)) {
        std::cout << space << "Say: \"" << say->message << "\"\n";
    }
    else if (auto ifnode = std::dynamic_pointer_cast<IfNode>(node)) {
        std::cout << space << "If Condition: "
                  << ifnode->condition->left << " "
                  << ifnode->condition->op << " "
                  << ifnode->condition->right << "\n";
        std::cout << space << "{\n";
        for (const auto& stmt : ifnode->body) {
            printAST(stmt, indent + 2);
        }
        std::cout << space << "}\n";
    }
    else if (auto aslongas = std::dynamic_pointer_cast<AsLongAsNode>(node)) { // <-- Add this block
        std::cout << space << "AsLongAs Condition: "
                  << aslongas->condition->left << " "
                  << aslongas->condition->op << " "
                  << aslongas->condition->right << "\n";
        std::cout << space << "{\n";
        for (const auto& stmt : aslongas->body) {
            printAST(stmt, indent + 2);
        }
        std::cout << space << "}\n";
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << argv[1] << "\n";
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();

    Tokenizer tokenizer(source);
    std::vector<Token> tokens = tokenizer.tokenize();

    Parser parser(tokens);
    auto program = parser.parseProgram();

    std::cout << "\n=== AST ===\n";
    for (const auto& stmt : program) {
        printAST(stmt);
    }
    CodeGenerator gen;
    gen.generate(program);
    // gen.writeToFile("build/output.asm");
    std::string outputAsmFile = "build/output.asm";
    if (argc >= 3) {
    outputAsmFile = argv[2];
    }
    gen.writeToFile(outputAsmFile);

    std::cout << "✅ Assembly written to build/output.asm\n";

    return 0;
}

