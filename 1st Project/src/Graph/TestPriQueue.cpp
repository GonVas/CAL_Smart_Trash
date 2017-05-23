//
// Created by gonvas on 3/31/17.
//

#include "CUTE/cute/cute.h"
#include "CUTE/cute/cute_runner.h"
#include "CUTE/cute/ide_listener.h"
#include "PriQueue.hpp"
#include <sstream>


void test_Creation(){

    PriQueue<int, int> pq;

    pq.setLess_op(true);
    ASSERT_EQUAL(true, pq.isLess_op());
    pq.setLess_op(false);
    ASSERT_EQUAL(false, pq.isLess_op());
    ASSERT_EQUAL(0, pq.size());
    pq.addWithPriority(1, 3);
    ASSERT_EQUAL(1, pq.size());
    pq.addWithPriority(2, 4);
    ASSERT_EQUAL(2, pq.size());
    pq.addWithPriority(3, 5);
    ASSERT_EQUAL(3, pq.size());
    ASSERT_EQUAL(true, pq.isHeap());

    return;
}

void test_MinHeap(){
    PriQueue<int, int> pq;
    pq.setLess_op(true);
    ASSERT_EQUAL(true, pq.isLess_op());
    pq.addWithPriority(1, 6);
    pq.addWithPriority(2, 4);
    pq.addWithPriority(3, 5);
    pq.addWithPriority(4, 1);
    pq.addWithPriority(5, 3);
    ASSERT_EQUAL(true, pq.isHeap());
    ASSERT_EQUAL(5, pq.size());
    ASSERT_EQUAL(4, pq.peakTop());
    ASSERT_EQUAL(4, pq.extractTop());
    ASSERT_EQUAL(4, pq.size());
    ASSERT_EQUAL(5, pq.peakTop());
    ASSERT_EQUAL(true, pq.isHeap());

    return;
}

void test_MaxHeap(){
    PriQueue<int, int> pq;
    pq.setLess_op(false);
    ASSERT_EQUAL(false, pq.isLess_op());
    pq.addWithPriority(1, 6);
    pq.addWithPriority(2, 4);
    pq.addWithPriority(3, 5);
    pq.addWithPriority(4, 1);
    pq.addWithPriority(5, 3);
    ASSERT_EQUAL(true, pq.isHeap());
    ASSERT_EQUAL(5, pq.size());
    ASSERT_EQUAL(1, pq.peakTop());
    ASSERT_EQUAL(1, pq.extractTop());
    ASSERT_EQUAL(4, pq.size());
    ASSERT_EQUAL(3, pq.peakTop());
    ASSERT_EQUAL(true, pq.isHeap());
    return;
}

void test_AddWithPri(){

    PriQueue<int, int> pq;
    pq.setLess_op(false);
    ASSERT_EQUAL(false, pq.isLess_op());
    pq.addWithPriority(1, 6);
    pq.addWithPriority(2, 4);
    pq.addWithPriority(3, 5);
    pq.addWithPriority(4, 1);
    pq.addWithPriority(5, 3);
    ASSERT_EQUAL(5, pq.size());
    ASSERT_EQUAL(1, pq.peakTop());
    ASSERT_EQUAL(1, pq.extractTop());
    ASSERT_EQUAL(4, pq.size());
    ASSERT_EQUAL(3, pq.peakTop());

    ASSERT_EQUAL(4, pq.size());
    ASSERT_EQUAL(3, pq.peakTop());
    ASSERT_EQUAL(3, pq.extractTop());
    ASSERT_EQUAL(3, pq.size());
    ASSERT_EQUAL(2, pq.peakTop());

    pq.addWithPriority(8, 14);
    pq.addWithPriority(9, 0);
    ASSERT_EQUAL(5, pq.size());
    ASSERT_EQUAL(8, pq.peakTop());
    ASSERT_EQUAL(8, pq.extractTop());
    ASSERT_EQUAL(4, pq.size());

    PriQueue<int, int> pq2;
    pq2.setLess_op(true);
    ASSERT_EQUAL(true, pq2.isLess_op());
    pq2.addWithPriority(1, 6);
    pq2.addWithPriority(2, 4);
    pq2.addWithPriority(3, 5);
    pq2.addWithPriority(4, 1);
    pq2.addWithPriority(5, 3);
    ASSERT_EQUAL(5, pq2.size());
    ASSERT_EQUAL(4, pq2.peakTop());
    ASSERT_EQUAL(4, pq2.extractTop());
    ASSERT_EQUAL(4, pq2.size());
    ASSERT_EQUAL(5, pq2.peakTop());

    ASSERT_EQUAL(4, pq2.size());
    ASSERT_EQUAL(5, pq2.peakTop());
    ASSERT_EQUAL(5, pq2.extractTop());
    ASSERT_EQUAL(3, pq2.size());
    ASSERT_EQUAL(2, pq2.peakTop());

    pq2.addWithPriority(8, 14);
    pq2.addWithPriority(9, 0);
    ASSERT_EQUAL(5, pq2.size());
    ASSERT_EQUAL(9, pq2.peakTop());
    ASSERT_EQUAL(9, pq2.extractTop());
    ASSERT_EQUAL(4, pq2.size());

    return;
}

void test_DeacreaseWithPri(){

    PriQueue<int, int> pq;
    pq.setLess_op(true);
    ASSERT_EQUAL(true, pq.isLess_op());
    pq.addWithPriority(1, 6);
    pq.addWithPriority(2, 4);
    pq.addWithPriority(3, 5);
    pq.addWithPriority(4, 1);
    pq.addWithPriority(5, 3);
    ASSERT_EQUAL(true, pq.isHeap());
    ASSERT_EQUAL(5, pq.size());
    ASSERT_EQUAL(4, pq.peakTop());
    pq.decreasePriority(4, 7);
    ASSERT_EQUAL(5, pq.peakTop());
    ASSERT_EQUAL(5, pq.size());
    pq.decreasePriority(3, 9);
    ASSERT_EQUAL(5, pq.peakTop());
    ASSERT_EQUAL(5, pq.size());
    pq.decreasePriority(5, 10);
    ASSERT_EQUAL(2, pq.peakTop());
    ASSERT_EQUAL(2, pq.extractTop());
    ASSERT_EQUAL(4, pq.size());

    ASSERT_EQUAL(true, pq.isHeap());

    return;
}

void test_Erase(){

    PriQueue<int, float> pq;
    pq.setLess_op(true);
    ASSERT_EQUAL(true, pq.isLess_op());
    pq.addWithPriority(1, 6.6);
    pq.addWithPriority(2, 4.2);
    pq.addWithPriority(3, 5.45);
    pq.addWithPriority(4, 1.5);
    pq.addWithPriority(5, 3.4);
    ASSERT_EQUAL(true, pq.isHeap());
    ASSERT_EQUAL(5, pq.size());
    ASSERT_EQUAL(4, pq.peakTop());

    ASSERT_EQUAL(true, pq.eraseElem(2));
    ASSERT_EQUAL(4, pq.size());
    ASSERT_EQUAL(4, pq.peakTop());

    ASSERT_EQUAL(false, pq.eraseElem(2));
    ASSERT_EQUAL(true, pq.eraseElem(4));
    ASSERT_EQUAL(3, pq.size());
    ASSERT_EQUAL(5, pq.peakTop());
}

void test_DifferentTypes(){

    PriQueue<int, float> pq;
    pq.setLess_op(true);
    ASSERT_EQUAL(true, pq.isLess_op());
    pq.addWithPriority(1, 6.6);
    pq.addWithPriority(2, 4.2);
    pq.addWithPriority(3, 5.45);
    pq.addWithPriority(4, 1.5);
    pq.addWithPriority(5, 3.4);
    ASSERT_EQUAL(true, pq.isHeap());
    ASSERT_EQUAL(5, pq.size());
    ASSERT_EQUAL(4, pq.peakTop());
    pq.decreasePriority(4, 7.2);
    ASSERT_EQUAL(5, pq.peakTop());
    ASSERT_EQUAL(5, pq.size());
    pq.decreasePriority(3, 9.7);
    ASSERT_EQUAL(5, pq.peakTop());
    ASSERT_EQUAL(5, pq.size());
    pq.decreasePriority(5, 10.3);
    ASSERT_EQUAL(2, pq.peakTop());
    ASSERT_EQUAL(2, pq.extractTop());
    ASSERT_EQUAL(4, pq.size());

    ASSERT_EQUAL(true, pq.isHeap());

    PriQueue<char, float> pq2;
    pq2.setLess_op(true);
    ASSERT_EQUAL(true, pq2.isLess_op());
    pq2.addWithPriority('a', 6.6);
    pq2.addWithPriority('b', 4.2);
    pq2.addWithPriority('c', 5.45);
    pq2.addWithPriority('d', 1.5);
    pq2.addWithPriority('e', 3.4);
    ASSERT_EQUAL(true, pq2.isHeap());
    ASSERT_EQUAL(5, pq2.size());
    ASSERT_EQUAL('d', pq2.peakTop());
    pq2.decreasePriority('d', 7);
    ASSERT_EQUAL('e', pq2.peakTop());
    ASSERT_EQUAL(5, pq2.size());
    pq2.decreasePriority('c', 9);
    ASSERT_EQUAL('e', pq2.peakTop());
    ASSERT_EQUAL(5, pq2.size());
    pq2.decreasePriority('e', 10);
    ASSERT_EQUAL('b', pq2.peakTop());
    ASSERT_EQUAL('b', pq2.extractTop());
    ASSERT_EQUAL(4, pq2.size());

    ASSERT_EQUAL(true, pq2.isHeap());

    return;
}
void runSuite_PriQueue() {
    cute::suite s;
    s.push_back(CUTE(test_Creation));
    s.push_back(CUTE(test_MinHeap));
    s.push_back(CUTE(test_MaxHeap));
    s.push_back(CUTE(test_AddWithPri));
    s.push_back(CUTE(test_DeacreaseWithPri));
    s.push_back(CUTE(test_DifferentTypes));
    s.push_back(CUTE(test_Erase));

    cute::ide_listener<> lis;
    cute::makeRunner(lis)(s, "PriQueue Testing");
}