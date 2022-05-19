//
// Created by viato on 12/05/2022.
//
#include "utils.h"
#include <iostream>
#include <vector>

std::string subString(const std::string& string, int startIndex, int endIndex) {
    if(startIndex >= 0 and startIndex < string.length() and endIndex >= 0 and endIndex < string.length()){
        std::string returnstring;

        for(int i = startIndex; i < endIndex; i++){
            returnstring += string[i];
        }
        return returnstring;
    } else
        throw std::out_of_range("Index out of range");
}

template <typename T>
std::vector<T> pop(const std::vector<T> &list, int index) {
    std::vector<T> returnList;
    for(int i = 0; i < list.size(); i++){
        if(i != index){
            returnList.push_back(list[i]);
        }
    }
    return returnList;
}

