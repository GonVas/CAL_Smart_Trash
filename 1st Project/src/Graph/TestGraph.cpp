//
// Created by gonvas on 4/1/17.

//


/*
 *
 *
 *
 *
 *
 */

#include "CUTE/cute/cute.h"
#include "CUTE/cute/cute_runner.h"
#include "CUTE/cute/ide_listener.h"
#include "Graph.h"

using namespace std;

Graph<int> CreateTestGraph() {
    Graph<int> myGraph;

    for (int i = 1; i < 8; i++)
        myGraph.addVertex(i);

    myGraph.addEdge(1, 2, 2);
    myGraph.addEdge(1, 4, 7);
    myGraph.addEdge(2, 4, 3);
    myGraph.addEdge(2, 5, 5);
    myGraph.addEdge(3, 1, 2);
    myGraph.addEdge(3, 6, 5);
    myGraph.addEdge(4, 3, 1);
    myGraph.addEdge(4, 5, 1);
    myGraph.addEdge(4, 6, 6);
    myGraph.addEdge(4, 7, 4);
    myGraph.addEdge(5, 7, 2);
    myGraph.addEdge(6, 4, 3);
    myGraph.addEdge(7, 6, 4);

    return myGraph;
}

Graph<int> Test_Graph_9() {
    Graph<int> myGraph;

    for (int i = 1; i < 10; i++)
        myGraph.addVertex(i);

    myGraph.addEdge(1, 2, 4);
    myGraph.addEdge(1, 8, 8);

    myGraph.addEdge(2, 3, 8);
    myGraph.addEdge(2, 8, 11);

    myGraph.addEdge(3, 6, 4);
    myGraph.addEdge(3, 9, 2);
    myGraph.addEdge(3, 4, 7);

    myGraph.addEdge(4, 6, 14);
    myGraph.addEdge(4, 5, 9);

    myGraph.addEdge(8, 9, 7);
    myGraph.addEdge(8, 7, 1);

    myGraph.addEdge(9, 7, 6);

    myGraph.addEdge(6, 5, 10);

    myGraph.addEdge(7, 6, 2);

    return myGraph;
}

Graph<int> TSP_smallTestGraph(){
    Graph<int> myGraph;

    for (int i = 1; i < 6; i++)
        myGraph.addVertex(i);

    myGraph.addEdge(1, 2, 3);
    myGraph.addEdge(1, 3, 4);
    myGraph.addEdge(1, 4, 2);
    myGraph.addEdge(1, 5, 7);

    myGraph.addEdge(2, 3, 4);
    myGraph.addEdge(2, 4, 6);
    myGraph.addEdge(2, 5, 3);
    myGraph.addEdge(2, 1, 3);

    myGraph.addEdge(3, 1, 4);
    myGraph.addEdge(3, 2, 4);
    myGraph.addEdge(3, 4, 5);
    myGraph.addEdge(3, 5, 8);

    myGraph.addEdge(4, 1, 2);
    myGraph.addEdge(4, 2, 6);
    myGraph.addEdge(4, 3, 5);
    myGraph.addEdge(4, 5, 6);

    myGraph.addEdge(5, 1, 7);
    myGraph.addEdge(5, 2, 3);
    myGraph.addEdge(5, 3, 8);
    myGraph.addEdge(5, 4, 6);

    return myGraph;
}

void Test_TSPsmallgraph(){
    Graph<int> myGraph = TSP_smallTestGraph();

    ASSERT_EQUAL(5, myGraph.getNumVertex());

    ASSERT_EQUAL(4, myGraph.getVertexSet()[0]->get_adj().size());
    ASSERT_EQUAL(4, myGraph.getVertexSet()[1]->get_adj().size());
    ASSERT_EQUAL(4, myGraph.getVertexSet()[2]->get_adj().size());
    ASSERT_EQUAL(4, myGraph.getVertexSet()[3]->get_adj().size());
    ASSERT_EQUAL(4, myGraph.getVertexSet()[4]->get_adj().size());

    return;
}

void test_equalEdge() {
  //  std::cout << " Starting equalEdge test. ";
    Vertex<int> v1(5);
    Vertex<int> v2(5);
    Vertex<int> v3(4);

    Edge<int> e1(&v1, 5);
    Edge<int> e2(&v1, 5);
    Edge<int> e3(&v2, 5);
    ASSERT_EQUAL(true, e1 == e2);
    ASSERT_EQUAL(false, e1 == e3);

    ASSERT_EQUAL(true, e1.same(e2));
    ASSERT_EQUAL(true, e1.same(e3));
}

void test_equalVertex() {
   // std::cout << " Starting equalVertex test. ";
    Vertex<int> v1(5);
    Vertex<int> v2(5);
    Vertex<int> v3(4);

    Vertex<bool> v4(true);
    Vertex<bool> v5(false);
    Vertex<bool> v6(true);

    ASSERT_EQUAL(true, v1 == v2);
    ASSERT_EQUAL(false, v1 == v3);
    ASSERT_EQUAL(true, v4 == v6);
    ASSERT_EQUAL(false, v5 == v4);
    v1.addEdge(&v2, 5);

    ASSERT_EQUAL(false, v1 == v2);
    v2.addEdge(&v2, 5);
    ASSERT_EQUAL(true, v1 == v2);
    v2.addEdge(&v3, 3);
    v2.addEdge(&v1, 4);
    ASSERT_EQUAL(false, v1 == v2);
}

void test_equalGraph() {
    //std::cout << " Starting equalGraph test. ";

    Graph<int> myGraph = CreateTestGraph();

    Graph<int> graph1;

    graph1.addVertex(1);
    graph1.addVertex(2);
    graph1.addVertex(3);
    graph1.addVertex(4);
    graph1.addVertex(5);
    graph1.addVertex(6);
    graph1.addVertex(7);

    graph1.addEdge(1, 2, 2);
    graph1.addEdge(1, 4, 7);
    ASSERT_EQUAL(false, myGraph == graph1);
    graph1.addEdge(2, 4, 3);
    graph1.addEdge(2, 5, 5);
    graph1.addEdge(3, 1, 2);
    graph1.addEdge(3, 6, 5);
    graph1.addEdge(4, 3, 1);
    graph1.addEdge(4, 5, 1);
    graph1.addEdge(4, 6, 6);
    graph1.addEdge(4, 7, 4);
    graph1.addEdge(5, 7, 2);
    ASSERT_EQUAL(false, myGraph == graph1);
    graph1.addEdge(6, 4, 3);
    graph1.addEdge(7, 6, 4);
    ASSERT_EQUAL(true, myGraph == graph1);
}

void runSuite_Graph() {
    cute::suite s;
    s.push_back(CUTE(test_equalEdge));
    s.push_back(CUTE(test_equalVertex));
    s.push_back(CUTE(test_equalGraph));
    s.push_back(CUTE(TSP_smallTestGraph));

    cute::ide_listener<> lis;
    cute::makeRunner(lis)(s, "Graph Testing");
}