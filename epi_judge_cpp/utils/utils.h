#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <bitset>

template <typename T>
void printInBinary(T x)
{
    constexpr size_t s = sizeof(T) * 8;

    std::bitset<s> b1{ x };
    std::cout << b1 << std::endl;
}


#endif

