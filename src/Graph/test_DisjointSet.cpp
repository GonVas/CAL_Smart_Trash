//
// Created by gonvas on 4/7/17.
//


#include "CUTE/cute/cute.h"
#include "CUTE/cute/cute_runner.h"
#include "CUTE/cute/ide_listener.h"
#include "DisjointSet.hpp"
#include <sstream>


void test_InitDisjoint(){

    return;
}

void test_Find(){

    return;
}

void test_Union(){

    return;
}

void test_Uses(){

    return;
}

void runSuite_DisjointSet() {
    cute::suite s;
    s.push_back(CUTE(test_InitDisjoint));
    s.push_back(CUTE(test_Find));
    s.push_back(CUTE(test_Union));
    s.push_back(CUTE(test_Uses));

    cute::ide_listener<> lis;
    cute::makeRunner(lis)(s, "DisjointSet Testing");
}