//
// Created by viato on 12/05/2022.
//

#ifndef BLOCCONOTE_UTILS_H
#define BLOCCONOTE_UTILS_H

#include <vector>
#include <iostream>

std::string subString(const std::string& string, int startIndex, int endIndex);

template <typename T>
std::vector<T> pop(const std::vector<T> &list, int index);

#endif //BLOCCONOTE_UTILS_H
