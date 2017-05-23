//
// Created by gonvas on 4/7/17.
//


#include "CUTE/cute/cute.h"
#include "CUTE/cute/cute_runner.h"
#include "CUTE/cute/ide_listener.h"
#include "DisjointSet.hpp"
#include <sstream>


void test_InitDisjoint(){

    int a = 3;
    float b = 4.3;

    DisjointSet<int> dis_set(&a);
    DisjointSet<float> dis_set1(&b);

    ASSERT_EQUAL(3, *dis_set.get_parent());
    ASSERT_EQUAL_DELTA(4.3, *dis_set1.get_parent(), 0.001);

    return;
}

void test_MakeSet(){

    vector<int *> elems;
    int a = 1; int b = 2; int c = 3; int d = 4; int e = 5;
    elems.push_back(&a); elems.push_back(&b); elems.push_back(&c); elems.push_back(&d); elems.push_back(&e);

    vector<DisjointSet<int>> disj =  DisjointSet<int>::make_Set(elems);

    int i = 1;
    for(auto DisjointSet : disj) {
        ASSERT_EQUAL(i, *DisjointSet.get_parent());
        ASSERT_EQUAL(*elems[i-1], *DisjointSet.get_parent());
        ASSERT_EQUAL(0, DisjointSet.get_rank());
        i++;
    }

    return;
}

void test_Union(){

    vector<int *> elems;
    int a = 1; int b = 2; int c = 3; int d = 4; int e = 5;
    elems.push_back(&a); elems.push_back(&b); elems.push_back(&c); elems.push_back(&d); elems.push_back(&e);

    vector<DisjointSet<int>> disj =  DisjointSet<int>::make_Set(elems);
    //(1)   (2)   (3)   (4)   (5)
    //1,0   2,0   3,0   4,0   5,0
    DisjointSet<int>::Union(&disj[0], &disj[1]);
    //(1  ,  2)   (3)   (4)   (5)
    // 1,1  1,0   3,0   4,0   5,0

    ASSERT_EQUAL(1, *disj[0].get_parent());
    ASSERT_EQUAL(1, disj[0].get_rank());
    ASSERT_EQUAL(1, *disj[1].get_parent());
    ASSERT_EQUAL(0, disj[1].get_rank());

    for (int i = 2; i <disj.size() ; ++i) {
        ASSERT_EQUAL(i+1, *disj[i].get_parent());
        ASSERT_EQUAL(0, disj[i].get_rank());
    }

    DisjointSet<int>::Union(&disj[0], &disj[1]);
    //(1  ,  2)   (3)   (4)   (5)
    // 1,1  1,0   3,0   4,0   5,0

    //nothing changes

    ASSERT_EQUAL(1, *disj[0].get_parent());
    ASSERT_EQUAL(1, disj[0].get_rank());
    ASSERT_EQUAL(1, *disj[1].get_parent());
    ASSERT_EQUAL(0, disj[1].get_rank());

    for (int i = 2; i <disj.size() ; ++i) {
        ASSERT_EQUAL(i+1, *disj[i].get_parent());
        ASSERT_EQUAL(0, disj[i].get_rank());
    }

    DisjointSet<int>::Union(&disj[0], &disj[4]);
    //(1  ,  2  ,  5)   (3)   (4)
    // 1,2  1,0   1,0   3,0   4,0

    ASSERT_EQUAL(1, *disj[0].get_parent());
    ASSERT_EQUAL(2, disj[0].get_rank());
    ASSERT_EQUAL(1, *disj[1].get_parent());
    ASSERT_EQUAL(0, disj[1].get_rank());
    ASSERT_EQUAL(1, *disj[4].get_parent());
    ASSERT_EQUAL(0, disj[1].get_rank());

    for (int i = 2; i <disj.size() -1; ++i) {
        ASSERT_EQUAL(i+1, *disj[i].get_parent());
        ASSERT_EQUAL(0, disj[i].get_rank());
    }

    DisjointSet<int>::Union(&disj[1], &disj[3]);
    //(1  ,  2  ,  5  ,  4)   (3)
    // 1,2  1,1   1,0   1,0   3,0

    ASSERT_EQUAL(1, *disj[0].get_parent());
    ASSERT_EQUAL(2, disj[0].get_rank());
    ASSERT_EQUAL(1, *disj[1].get_parent());
    ASSERT_EQUAL(1, disj[1].get_rank());
    ASSERT_EQUAL(1, *disj[4].get_parent());
    ASSERT_EQUAL(0, disj[4].get_rank());
    ASSERT_EQUAL(1, *disj[3].get_parent());
    ASSERT_EQUAL(0, disj[3].get_rank());

    ASSERT_EQUAL(3, *disj[2].get_parent());
    ASSERT_EQUAL(0, disj[2].get_rank());

    return;
}


void runSuite_DisjointSet() {
    cute::suite s;
    s.push_back(CUTE(test_InitDisjoint));
    s.push_back(CUTE(test_Union));
    s.push_back(CUTE(test_MakeSet));

    cute::ide_listener<> lis;
    cute::makeRunner(lis)(s, "DisjointSet Testing");
}