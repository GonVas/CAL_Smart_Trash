#include "CUTE/cute/cute.h"
#include "CUTE/cute/cute_runner.h"
#include "CUTE/cute/ide_listener.h"
#include "Graph.h"
#include "TestPriQueue.cpp"
#include "TestGraph.cpp"
#include "PriQueue.hpp"
#include <sstream>
#include <utility>

using namespace std;

// void test_bellmanFord() {
/*	Graph<int> myGraph = CreateTestGraph();

        //para testar o metodo unweightedShortestPath
        myGraph.bellmanFordShortestPath(3);

        vector<Vertex<int>* > vs = myGraph.getVertexSet();

        stringstream ss;
        for(unsigned int i = 0; i < vs.size(); i++) {
                ss << vs[i]->getInfo() << "<-";
                if ( vs[i]->path != NULL )  ss << vs[i]->path->getInfo();
                ss << "|";
        }

        ASSERT_EQUAL("1<-3|2<-1|3<-|4<-2|5<-4|6<-3|7<-5|", ss.str());

        myGraph.bellmanFordShortestPath(1);
        vector<int> path = myGraph.getPath(1, 7);
        ss.str("");
        for(unsigned int i = 0; i < path.size(); i++) {
                ss << path[i] << " ";
        }
        ASSERT_EQUAL("1 2 4 5 7 ", ss.str());

        myGraph.bellmanFordShortestPath(5);
        path = myGraph.getPath(5, 6);
        ss.str("");
        for(unsigned int i = 0; i < path.size(); i++) {
                ss << path[i] << " ";
        }
        ASSERT_EQUAL("5 7 6 ", ss.str());


        myGraph.bellmanFordShortestPath(7);
        path = myGraph.getPath(7, 1);
        ss.str("");
        for(unsigned int i = 0; i < path.size(); i++) {
                ss << path[i] << " ";
        }
        ASSERT_EQUAL("7 6 4 3 1 ", ss.str());
*/
//}

void test_dijkstra() {
    Graph<int> myGraph = CreateTestGraph();

    //para testar o metodo unweightedShortestPath
    myGraph.dijkstraShortestPath(3);

    vector<Vertex<int>* > vs = myGraph.getVertexSet();

    stringstream ss;
    for(unsigned int i = 0; i < vs.size(); i++) {
        ss << vs[i]->getInfo() << "<-";
        if ( vs[i]->path != NULL )  ss << vs[i]->path->getInfo();
        ss << "|";
    }

    ASSERT_EQUAL("1<-3|2<-1|3<-|4<-2|5<-4|6<-3|7<-5|", ss.str());

    myGraph.dijkstraShortestPath(1);

    ss.str("");
    for(unsigned int i = 0; i < vs.size(); i++) {
        ss << vs[i]->getInfo() << "<-";
        if ( vs[i]->path != NULL )  ss << vs[i]->path->getInfo();
        ss << "|";
    }

    ASSERT_EQUAL("1<-|2<-1|3<-4|4<-2|5<-4|6<-4|7<-5|", ss.str());

    vector<int> path = myGraph.getPath(1, 7);
    ss.str("");
    for(unsigned int i = 0; i < path.size(); i++) {
        ss << path[i] << " ";
    }
    ASSERT_EQUAL("1 2 4 5 7 ", ss.str());

    myGraph.dijkstraShortestPath(5);
    path = myGraph.getPath(5, 6);
    ss.str("");
    for(unsigned int i = 0; i < path.size(); i++) {
        ss << path[i] << " ";
    }
    ASSERT_EQUAL("5 7 6 ", ss.str());

    myGraph.dijkstraShortestPath(7);
    path = myGraph.getPath(7, 1);
    ss.str("");
    for(unsigned int i = 0; i < path.size(); i++) {
        ss << path[i] << " ";
    }
    ASSERT_EQUAL("7 6 4 3 1 ", ss.str());

    Graph<int> Test_Graph = Test_Graph_9();
    Test_Graph.dijkstraShortestPath(1);
    path = Test_Graph.getPath(1, 5);
    ss.str("");
    for(unsigned int i = 0; i < path.size(); i++) {
        ss << path[i] << " ";
    }
    ASSERT_EQUAL("1 8 7 6 5 ", ss.str());

    Test_Graph.dijkstraShortestPath(1);
    path = Test_Graph.getPath(1, 3);
    ss.str("");
    for(unsigned int i = 0; i < path.size(); i++) {
        ss << path[i] << " ";
    }
    ASSERT_EQUAL("1 2 3 ", ss.str());

    Test_Graph.dijkstraShortestPath(1);
    path = Test_Graph.getPath(1, 9);
    ss.str("");
    for(unsigned int i = 0; i < path.size(); i++) {
        ss << path[i] << " ";
    }
    ASSERT_EQUAL("1 2 3 9 ", ss.str());

    Test_Graph.dijkstraShortestPath(1);
    path = Test_Graph.getPath(1, 7);
    ss.str("");
    for(unsigned int i = 0; i < path.size(); i++) {
        ss << path[i] << " ";
    }
    ASSERT_EQUAL("1 8 7 ", ss.str());

}

void test_TotalWeightFrom(){
    Graph<int> Test_Graph = Test_Graph_9();
    Test_Graph.dijkstraShortestPath(1);

    ASSERT_EQUAL_DELTA(9.0, Test_Graph.getTotalWeightfromPath(1,7), 0.1);
    ASSERT_EQUAL_DELTA(8.0, Test_Graph.getTotalWeightfromPath(1,8), 0.1);
    ASSERT_EQUAL_DELTA(14.0, Test_Graph.getTotalWeightfromPath(1,9), 0.1);
    ASSERT_EQUAL_DELTA(21.0, Test_Graph.getTotalWeightfromPath(1,5), 0.1);
    ASSERT_EQUAL_DELTA(11.0, Test_Graph.getTotalWeightfromPath(1,6), 0.1);

    Test_Graph.dijkstraShortestPath(9);

    Test_Graph.makeSymetric();

    ASSERT_EQUAL_DELTA(6.0, Test_Graph.getTotalWeightfromPath(9,7), 0.1);
    ASSERT_EQUAL_DELTA(7.0, Test_Graph.getTotalWeightfromPath(9,8), 0.1);

    Test_Graph.dijkstraShortestPath(7);

    ASSERT_EQUAL_DELTA(1.0, Test_Graph.getTotalWeightfromPath(7,8), 0.1);
    ASSERT_EQUAL_DELTA(9.0, Test_Graph.getTotalWeightfromPath(7,1), 0.1);

    ASSERT_EQUAL_DELTA(0.0, Test_Graph.getTotalWeightfromPath(9,9), 0.1);

}

void test_makeSymetric(){
    Graph<int> test_Graph = Test_Graph_9();

    test_Graph.makeSymetric();

    ASSERT_EQUAL(9, test_Graph.getNumVertex());

    for(auto vertex : test_Graph.getVertexSet()) {
        for(auto edge : vertex->get_adj()){
            bool is_there = false;
            for(auto dest_edge : edge.getDest()->get_adj())
                if(dest_edge.getDest() == vertex)
                    is_there = true;
            ASSERT_EQUAL(true, is_there);
        }
    }

    return;
}

void test_TSPmaker(){

    Graph<int> test_Graph = Test_Graph_9();

    Graph<int> TSP_graph = test_Graph.makeTSP();

    ASSERT_EQUAL(9, TSP_graph.getNumVertex());

    for(auto vertex : TSP_graph.getVertexSet())
       ASSERT_EQUAL(TSP_graph.getNumVertex() -1 , vertex->get_adj().size());

    // 9 -> 1 = 14
    ASSERT_EQUAL_DELTA(14.0, TSP_graph.getEdge(9,1), 0.1);
    ASSERT_EQUAL_DELTA(14.0, TSP_graph.getEdge(1,9), 0.1);

    // 2 -> 4 = 15
    ASSERT_EQUAL_DELTA(15.0, TSP_graph.getEdge(2,4), 0.1);
    ASSERT_EQUAL_DELTA(15.0, TSP_graph.getEdge(4,2), 0.1);

    // 1 -> 5 = 21
    ASSERT_EQUAL_DELTA(21.0, TSP_graph.getEdge(1,5), 0.1);
    ASSERT_EQUAL_DELTA(21.0, TSP_graph.getEdge(5,1), 0.1);

    // 6 -> 2 = 12
    ASSERT_EQUAL_DELTA(12.0, TSP_graph.getEdge(6,2), 0.1);
    ASSERT_EQUAL_DELTA(12.0, TSP_graph.getEdge(2,6), 0.1);

    // 9 -> 3 = 2
    ASSERT_EQUAL_DELTA(2.0, TSP_graph.getEdge(9,3), 0.1);
    ASSERT_EQUAL_DELTA(2.0, TSP_graph.getEdge(3,9), 0.1);

    return;
}

void test_TSPBruteForce(){

    Graph<int> test_Graph = Test_Graph_9();

    Graph<int> TSP_graph = test_Graph.makeTSP();

    pair<vector<int>,double> TSP_path = TSP_graph.TSP_bruteForce(1,5);

    /*
    cout << "\n";
    for(auto city: get<0>(TSP_path))
        cout << city-1 << " ";

    cout << " Min Distance : " << (get<1>(TSP_path)) << endl;
    */

    vector<int> real_ans;
    real_ans.push_back(1); real_ans.push_back(2); real_ans.push_back(8); real_ans.push_back(7); real_ans.push_back(6);
    real_ans.push_back(3); real_ans.push_back(9); real_ans.push_back(4); real_ans.push_back(5);

    ASSERT_EQUAL(real_ans, get<0>(TSP_path));
    ASSERT_EQUAL(42, get<1>(TSP_path));
    real_ans.clear();

    Graph<int> Test_graph = TSP_smallTestGraph();

    TSP_path = Test_graph.TSP_bruteForce(1,1);

    real_ans.push_back(1); real_ans.push_back(3); real_ans.push_back(2); real_ans.push_back(5); real_ans.push_back(4);
    real_ans.push_back(1);

    ASSERT_EQUAL(real_ans, get<0>(TSP_path));
    ASSERT_EQUAL(19, get<1>(TSP_path));
    real_ans.clear();

    return;
}

void test_LowerBound(){
    Graph<int> test_Graph = Test_Graph_9();

    Graph<int> TSP_graph = test_Graph.makeTSP();

    pair<vector<int>,double> TSP_path = TSP_graph.TSP_bruteForce(1,5);

    vector<Edge<int>> excluded;

      ASSERT_LESS_EQUAL(TSP_graph.TSP_BB_lowerbound(excluded), 43);
      ASSERT_GREATER_EQUAL(TSP_graph.TSP_BB_lowerbound(excluded), 38);

    Graph<int> Test_graph = TSP_smallTestGraph();

    TSP_path = Test_graph.TSP_bruteForce(1,1);

   // ASSERT_LESS_EQUAL(Test_graph.TSP_BB_lowerbound(get<0>(TSP_path)), 19);
   // ASSERT_GREATER_EQUAL(Test_graph.TSP_BB_lowerbound(get<0>(TSP_path)), 16);

    ASSERT_EQUAL_DELTA(17.5, Test_graph.TSP_BB_lowerbound(excluded), 0.1);


}

void test_TSPBranchBound(){

    Graph<int> test_Graph = Test_Graph_9();

    Graph<int> TSP_graph = test_Graph.makeTSP();

    pair<vector<int>,double> TSP_path = TSP_graph.TSP_BranchBound(1,5);

    /*
    for(auto city: get<0>(TSP_path))
        cout << city-1 << " ";

    cout << " Min Distance : " << (get<1>(TSP_path)) << endl;
    */

    vector<int> real_ans;
    real_ans.push_back(1); real_ans.push_back(2); real_ans.push_back(8); real_ans.push_back(7); real_ans.push_back(6);
    real_ans.push_back(3); real_ans.push_back(9); real_ans.push_back(4); real_ans.push_back(5);

    ASSERT_EQUAL(real_ans, get<0>(TSP_path));
    ASSERT_EQUAL(107, get<1>(TSP_path));

    return;
}

// void test_floydWarshall() {
/*Graph<int> myGraph = CreateTestGraph();

//para testar o metodo unweightedShortestPath
myGraph.floydWarshallShortestPath();

stringstream ss;

vector<int> path = myGraph.getfloydWarshallPath(1, 7);
ss.str("");
for(unsigned int i = 0; i < path.size(); i++) {
        ss << path[i] << " ";
}
ASSERT_EQUAL("1 2 4 5 7 ", ss.str());

path = myGraph.getfloydWarshallPath(5, 6);
ss.str("");
for(unsigned int i = 0; i < path.size(); i++) {
        ss << path[i] << " ";
}
ASSERT_EQUAL("5 7 6 ", ss.str());


path = myGraph.getfloydWarshallPath(7, 1);
ss.str("");
for(unsigned int i = 0; i < path.size(); i++) {
        ss << path[i] << " ";
}
ASSERT_EQUAL("7 6 4 3 1 ", ss.str());*/
//}

void runSuite_GraphAlgorithms() {
    cute::suite s;
    //s.push_back(CUTE(test_bellmanFord));
    s.push_back(CUTE(test_dijkstra));
    s.push_back(CUTE(test_TotalWeightFrom));
    s.push_back(CUTE(test_makeSymetric));
    s.push_back(CUTE(test_TSPmaker));
    s.push_back(CUTE(test_TSPBruteForce));
    s.push_back(CUTE(test_TSPBranchBound));
    s.push_back(CUTE(test_LowerBound));
    //s.push_back(CUTE(test_floydWarshall));

    cute::ide_listener<> lis;
    cute::makeRunner(lis)(s, "Graph Algorithms Testing");
}

int main() {
    runSuite_PriQueue();
    runSuite_Graph();
    runSuite_GraphAlgorithms();
    return 0;
}
