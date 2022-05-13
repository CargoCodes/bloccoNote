//
// Created by viato on 12/05/2022.
//
#include "utils.h"
#include <vector>

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