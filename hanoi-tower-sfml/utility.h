#pragma once
#include <iostream>

void log(std::string text) {
    std::cout << "LOG: " << text << std::endl;
}

void log_num(std::string text, int num) {
    std::cout << "LOG: " << text << num << std::endl;
}