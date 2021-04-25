#include <iostream>
#include <memory>
#include <ostream>

#include "ccompiler.hpp"
#include "io.hpp"

const char* path = "../FormalGrammars/pasc/hello.pas";
int main(int argc, char **args)
{
    using namespace pasc;
    if (argc == 2) {
        path = args[1];
    }
    auto io = std::make_shared<IO>(path);
    auto compiler = std::make_unique<Compiler>(io);
    compiler->compile();
    std::cout << "Compilation finished. Found errors: " << io->get_errors_size() << std::endl;
    for (auto error : io->get_errors()) {
        std::cout << error.to_string() << std::endl;
    }
    return(0);
}
