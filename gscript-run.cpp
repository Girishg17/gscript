// gscript-run.cpp

#include <cstdlib>
#include <iostream>
#include <string>
#include <filesystem>

std::string stripExtension(const std::string& path) {
    size_t slash = path.find_last_of('/');
    size_t dot = path.find_last_of('.');
    if (dot == std::string::npos) dot = path.size();
    return path.substr(slash + 1, dot - slash - 1);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: gsc <source.gscript>\n";
        return 1;
    }

    // std::string inputFile = argv[1];
    std::string inputFile = std::filesystem::absolute(argv[1]);
    std::string outputBase = stripExtension(inputFile);

    std::string asmFile = "build/" + outputBase + ".asm";
    std::string objFile = "build/" + outputBase + ".o";
    std::string binFile = "build/" + outputBase;

    std::cout << "📘 Compiling " << inputFile << " → " << asmFile << "\n";
    std::string compileCmd = "./build/gscript " + inputFile + " " + asmFile;
    if (std::system(compileCmd.c_str()) != 0) return 1;

    std::cout << "⚙️  Assembling → " << objFile << "\n";
    std::string asmCmd = "nasm -f elf64 " + asmFile + " -o " + objFile;
    if (std::system(asmCmd.c_str()) != 0) return 1;

    std::cout << "🔗 Linking → " << binFile << "\n";
    std::string linkCmd = "ld -o " + binFile + " " + objFile;
    if (std::system(linkCmd.c_str()) != 0) return 1;

    std::cout << "🚀 Running " << binFile << "...\n\n";
    return std::system(binFile.c_str());
}
