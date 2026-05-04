//
// Created by Rija on 4/14/2026.
//

#include "console_output.h"
#include <iostream>
#include <string>

int main() {

#ifdef _WIN32
    std::string cmd = "cmd /C dir";
#else
    std::string cmd = "ls";
#endif

    std::cout << command_output_get(cmd) << '\n';

    return 0;
}