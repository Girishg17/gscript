#include "codegen.hpp"
#include <fstream>

CodeGenerator::CodeGenerator() {
    text.push_back("section .text");
    text.push_back("global _start");
    text.push_back("_start:");
}

std::string CodeGenerator::addString(const std::string& str) {
    std::string label = "msg" + std::to_string(msgCount++);
    std::string line = label + " db \"" + str + "\", 10, 0";
    data.push_back(line);
    return label;
}

void CodeGenerator::emitSay(const SayNode* say) {
    std::string label = addString(say->message);
    int len = say->message.size() + 1;

    text.push_back("    mov rax, 1");
    text.push_back("    mov rdi, 1");
    text.push_back("    mov rsi, " + label);
    text.push_back("    mov rdx, " + std::to_string(len));
    text.push_back("    syscall\n");
}

void CodeGenerator::emitIf(const IfNode* ifnode) {
    auto cond = ifnode->condition;
    std::string lbl_true = "label" + std::to_string(labelCount++);
    std::string lbl_end = "label" + std::to_string(labelCount++);

    // Assume left is "age", right is number
    // Set age manually to 20
    text.push_back("    mov rbx, 20  ; age");

    text.push_back("    cmp rbx, " + cond->right);

    std::string jump;
    if (cond->op == ">") jump = "jg";
    else if (cond->op == "<") jump = "jl";
    else if (cond->op == "==") jump = "je";
    else jump = "jne";  // fallback

    text.push_back("    " + jump + " " + lbl_true);
    text.push_back("    jmp " + lbl_end);

    text.push_back(lbl_true + ":");

    for (const auto& stmt : ifnode->body) {
        if (auto say = dynamic_cast<SayNode*>(stmt.get())) {
            emitSay(say);
        }
    }

    text.push_back(lbl_end + ":");
}

void CodeGenerator::generate(const std::vector<std::shared_ptr<ASTNode>>& program) {
    for (const auto& stmt : program) {
        if (auto say = dynamic_cast<SayNode*>(stmt.get())) {
            emitSay(say);
        }
        else if (auto sayVar = dynamic_cast<SayVarNode*>(stmt.get())) {
            emitSayVar(sayVar);
        }
        else if(auto grab = dynamic_cast<GrabNode*>(stmt.get())) {
            emitGrab(grab);
        }
        else if (auto ifnode = dynamic_cast<IfNode*>(stmt.get())) {
            emitIf(ifnode);
        }
    }

    text.push_back("    mov rax, 60");
    text.push_back("    xor rdi, rdi");
    text.push_back("    syscall");
}

void CodeGenerator::writeToFile(const std::string& filename) {
    std::ofstream out(filename);
    out << "section .data\n";
    for (const auto& line : data) out << line << "\n";
    for (const auto& line : text) out << line << "\n";
    // std::ofstream out(filename);
    // out << "section .data\n";
    // for (const auto& line : data) out << line << "\n";
    // out << "\nsection .text\n";
    // for (const auto& line : text) out << line << "\n";
    // out.close();
}


void CodeGenerator::emitSayVar(const SayVarNode* sayVar) {
    // For demonstration, print a hardcoded value for the variable
    // In a real implementation, you'd look up the variable's value
    text.push_back("    mov rax, 1");
    text.push_back("    mov rdi, 1");
    text.push_back("    mov rsi, var_" + sayVar->varName);
    text.push_back("    mov rdx, 3"); // adjust length as needed
    text.push_back("    syscall\n");
}
void CodeGenerator::emitGrab(const GrabNode* grab) {
    //   text.push_back("    ; grab " + grab->varName + " = " + grab->value);
    // For demonstration, just print a message
    // text.push_back("    mov rax, 1");
    // text.push_back("    mov rdi, 1");
    // text.push_back("    mov rsi, msg_grab");
    // text.push_back("    mov rdx, 12"); // length of "Grabbed!\n"
    // text.push_back("    syscall\n");
    // printf("    ; grab %s = %s\n", grab->varName.c_str(), grab->value.c_str());
    // data.push_back("var_" + grab->varName + " dq " + grab->value);
    data.push_back("var_" + grab->varName + " db \"" + grab->value + "\", 10, 0");
}
