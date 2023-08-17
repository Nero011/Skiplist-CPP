//
// Created by alu on 23-8-17.
//
#include "skiplist.h"
#include <iostream>
#include <string>

using namespace std;

int main(){
    skipList<int, string> skip(5);
    skip.insret(1, "oasndg");
    skip.insret(10, "这里是10");
    skip.insret(18, "18");
    skip.insret(2, "zheli2");
    skip.insret(6, "6");

    return 0;
}