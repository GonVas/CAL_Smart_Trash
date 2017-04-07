#include "CUTE/cute/cute.h"
#include "CUTE/cute/cute_runner.h"
#include "CUTE/cute/ide_listener.h"
#include "Graph.h"
#include "TestPriQueue.cpp"
#include "TestGraph.cpp"
#include "test_DisjointSet.cpp"
#include <algorithm>
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

    //TSP_graph.add_GhostVertex(1,5);

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


//    ASSERT_EQUAL(real_ans, get<0>(TSP_path));
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

    vector<pair<int, int>> excluded, included;

    Graph<int> Test_graph = TSP_smallTestGraph();

    TSP_path = Test_graph.TSP_bruteForce(1,1);

    ASSERT_EQUAL_DELTA(17.5, Test_graph.TSP_BB_lowerbound(excluded, included), 0.1);

    excluded.push_back(pair<int,int>(2,3));
    included.push_back(pair<int,int>(1,5));

    ASSERT_EQUAL_DELTA(20.5, Test_graph.TSP_BB_lowerbound(excluded, included), 0.1);

    excluded.clear(); excluded.push_back(pair<int,int>(1,3));
    included.clear();

    ASSERT_EQUAL_DELTA(18.0, Test_graph.TSP_BB_lowerbound(excluded, included), 0.1);

    excluded.clear(); excluded.push_back(pair<int,int>(1,5)); excluded.push_back(pair<int,int>(1,3));
    included.clear(); included.push_back(pair<int,int>(1,4)); included.push_back(pair<int,int>(1,2));

    ASSERT_EQUAL_DELTA(18.0, Test_graph.TSP_BB_lowerbound(excluded, included), 0.1);

    excluded.clear(); excluded.push_back(pair<int,int>(1,3));
    included.clear(); included.push_back(pair<int,int>(1,5)); included.push_back(pair<int,int>(1,3));

    ASSERT_EQUAL_DELTA(21.0, Test_graph.TSP_BB_lowerbound(excluded, included), 0.1);

    included.clear(); excluded.clear();

    test_Graph = Test_Graph_9();

    TSP_graph = test_Graph.makeTSP();

    for(int i = 1; i< TSP_graph.getNumVertex()+1 ;i++) {
            double res = get<1>(TSP_graph.TSP_bruteForce(i, i));
            ASSERT_LESS_EQUAL(TSP_graph.TSP_BB_lowerbound(excluded, included), res);
    }
}

void test_GreadyAlgorithm(){

    Graph<int> test_Graph = Test_Graph_9();

    Graph<int> TSP_graph = test_Graph.makeTSP();

    pair<vector<int>,double> TSP_Path = TSP_graph.TSP_Gready(1, 5);

    ASSERT_EQUAL(get<0>(TSP_Path).size(), TSP_graph.getNumVertex()+1);

    ASSERT_EQUAL(get<0>(TSP_Path).at(get<0>(TSP_Path).size()-1), 5);

    ASSERT_EQUAL(get<0>(TSP_Path).at(0), 1);

    for(int path_point : get<0>(TSP_Path))
        if(path_point!= 1 || path_point != 5){
        bool in = false;
        for(int i = 0; i < TSP_graph.getVertexSet().size(); i++)
            if(path_point == TSP_graph.getVertexSet().at(i)->getInfo())
                in = true;
        ASSERT_EQUAL(true, in);
    }

    test_Graph = TSP_smallTestGraph();

    TSP_Path = test_Graph.TSP_Gready(1, 1);

    ASSERT_EQUAL(get<0>(TSP_Path).size(), test_Graph.getNumVertex()+1);

    ASSERT_EQUAL(get<0>(TSP_Path).at(get<0>(TSP_Path).size()-1), 1);

    ASSERT_EQUAL(get<0>(TSP_Path).at(0), 1);

    for(int path_point : get<0>(TSP_Path))
        if(path_point!= 1 ){
            bool in = false;
            for(int i = 0; i < TSP_graph.getVertexSet().size(); i++)
                if(path_point == TSP_graph.getVertexSet().at(i)->getInfo())
                    in = true;
            ASSERT_EQUAL(true, in);
        }


}

///@todo LowerBound : Finish lower bound function to a working one with the minimal spanning tree
void test_GoodLowerBound(){

    Graph<int> test_Graph = Test_Graph_9();

    Graph<int> TSP_graph = test_Graph.makeTSP();

    vector<pair<int, int>> excluded, included;

    for(int i = 1; i< TSP_graph.getNumVertex()+1 ;i++) {
        for (int j = 1; j < TSP_graph.getNumVertex() + 1; j++) {
            cout << "Testing with i: " << i << "  j: " << j << endl;
            double res = get<1>(TSP_graph.TSP_bruteForce(i, j));
            ASSERT_LESS_EQUAL(TSP_graph.TSP_BB_lowerbound(excluded, included), res);
        }
    }
}

///@todo Branch&Bound : Finish the function branch and bound using the lower bound function
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
    ASSERT_EQUAL(42, get<1>(TSP_path));

    Graph<int> Test_graph = TSP_smallTestGraph();
    TSP_path = Test_graph.TSP_bruteForce(1,1);

    real_ans.push_back(1); real_ans.push_back(3); real_ans.push_back(2); real_ans.push_back(5); real_ans.push_back(4);
    real_ans.push_back(1);

    ASSERT_EQUAL(real_ans, get<0>(TSP_path));
    ASSERT_EQUAL(19, get<1>(TSP_path));

    return;
}

///@todo MinimalSpanTree: Finish the minimal Spanning tree with Burovka Algorithm (for use with B&B)

void test_minimalSpanTree(){

    Graph<int> test_Graph = Test_Graph_9();

    Graph<int> TSP_graph = test_Graph.makeTSP();

    pair<vector<int>,double> mini_span = TSP_graph.minSpanningTree();

    ASSERT_EQUAL(TSP_graph.getNumVertex(), get<0>(mini_span).size());

    for(auto vertex: TSP_graph.getVertexSet()){
        bool in = false;
        for(auto v : get<0>(mini_span))
            if(vertex->getInfo() == v)
                in = true;
        ASSERT_EQUAL(true, in);
    }

}

void test_PathReconstruction(){

    Graph<int> test_Graph = Test_Graph_9();

    vector<int> trash_cans; trash_cans.push_back(1);  trash_cans.push_back(4);  trash_cans.push_back(6); trash_cans.push_back(5); trash_cans.push_back(8);

    Graph<int> TSPres = test_Graph.makeTSPres(trash_cans);

    ASSERT_EQUAL(trash_cans.size(), TSPres.getNumVertex());

    for(auto vertex: TSPres.getVertexSet()) {
        bool kill = false;
        if (vertex->getInfo() != 1 && vertex->getInfo() != 4 && vertex->getInfo() != 6 && vertex->getInfo() != 5 && vertex->getInfo() != 8  )
            kill = true;
        ASSERT_EQUAL(false, kill);
    }

    pair<vector<int>, double> path = TSPres.getPathRecons(1,5);

    stringstream ss;

    ss.str("");
    for(unsigned int i = 0; i < get<0>(path).size(); i++) {
        ss << get<0>(path)[i] << " ";
    }
    ASSERT_EQUAL("1 8 7 6 5 ", ss.str());

}

///@todo Implement DisjointSet : for use in the Brosudal minimal spanning tree

////@todo Implement User Interface: Take the User input (algorithm selection) and make a run from start to finsh with a OPSTM

///@todo (Optional) Tabu Search : Implement the genetic algorithm Tabu search for the TSP problem

 void test_floydWarshall() {
Graph<int> myGraph = CreateTestGraph();

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
ASSERT_EQUAL("7 6 4 3 1 ", ss.str());
}

void runSuite_GraphAlgorithms() {
    cute::suite s;
    //s.push_back(CUTE(test_bellmanFord));
    s.push_back(CUTE(test_dijkstra));
    s.push_back(CUTE(test_TotalWeightFrom));
    s.push_back(CUTE(test_makeSymetric));
    s.push_back(CUTE(test_TSPmaker));
    s.push_back(CUTE(test_TSPBruteForce));
   // s.push_back(CUTE(test_LowerBound));
  //  s.push_back(CUTE(test_GoodLowerBound));
  //  s.push_back(CUTE(test_TSPBranchBound));
    s.push_back(CUTE(test_floydWarshall));
    s.push_back(CUTE(test_GreadyAlgorithm));
    s.push_back(CUTE(test_minimalSpanTree));
    s.push_back(CUTE(test_PathReconstruction));

    cute::ide_listener<> lis;
    cute::makeRunner(lis)(s, "Graph Algorithms Testing");
}

int main() {
    runSuite_PriQueue();
    runSuite_DisjointSet();
    runSuite_Graph();
    runSuite_GraphAlgorithms();
    return 0;
}
