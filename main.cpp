//
// Created by alu on 23-8-17.
//
#include "skiplist.h"
#include <iostream>
#include <string>

using namespace std;



int main(){
    skipList<char, string> skip(5);
    skip.insret('a', "oasndg");
    skip.insret('b', "这里是10");
    skip.insret('v', "18");
    skip.insret('i', "zheli2");
    skip.insret('d', "6");


    skip.search('a');
    skip.search('d');

    skip.del('a');

    skip.search('a');


    return 0;
}