/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <cmath>
#include <limits>
#include <list>
#include <queue>
#include <vector>
#include <map>
#include "PriQueue.hpp"
#include <string>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <cstdlib>
#include "DisjointSet.hpp"
#include <random>
#include<ctime>

#include <random>

typedef std::mt19937 rng_type;
std::uniform_int_distribution<rng_type::result_type> udist(0, 700000);
rng_type rng;

using namespace std;

template <class T> class Edge;
template <class T> class Graph;

const int NOT_VISITED = 0;
const int BEING_VISITED = 1;
const int DONE_VISITED = 2;
const int INT_INFINITY = std::numeric_limits<int>::max();

mutex lck_edge;

/*
template <class T>
struct edgePQCompare
{
    bool operator()(const Edge<T>& l, const Edge<T>& r)
    {
        return l.getWeight() < r.getWeight();
    }
};*/

/*
 * ================================================================================================
 * Class Vertex
 * ================================================================================================
 */
template <class T> class Vertex {
    T info;
    vector<Edge<T>> adj;
    bool visited;
    bool processing;
    int indegree;
    int dist;

    int trash = -1;
    bool trash_picked = false;

    Vertex<T> * parent;

public:
    Vertex(T in);
    friend class Graph<T>;

    void addEdge(Vertex<T> *dest, double w);
    bool removeEdgeTo(Vertex<T> *d);
    T getEdgeDis(Vertex<T>* s, Vertex<T>* d);

    T getInfo() const;
    void setInfo(T info);

    int getDist() const;
    int getIndegree() const;

    vector<Edge<T>> get_adj(){
        return this->adj;
    }

    Vertex *path;

//===============================
    inline bool operator==(const Vertex<T> &rhs) {
        if (this->info != rhs.info || this->adj.size() != rhs.adj.size() ||
            this->indegree != rhs.indegree || this->dist != rhs.dist)
            return false;

        for (size_t i = 0; i < this->adj.size(); i++) {
            if (!(this->adj.at(i) == rhs.adj.at(i)))
                return false;
        }
        return true;
    }


    inline bool same(const Vertex<T> &rhs) {
        if (this->info != rhs.info || this->adj.size() != rhs.adj.size() ||
            this->indegree != rhs.indegree || this->dist != rhs.dist)
            return false;
        return true;
    }

    //===============================
};

template <class T> struct vertex_greater_than {
    bool operator()(Vertex<T> *a, Vertex<T> *b) const {
        return a->getDist() > b->getDist();
    }
};

template <class T> bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
    d->indegree--; // adicionado do exercicio 5
    typename vector<Edge<T>>::iterator it = adj.begin();
    typename vector<Edge<T>>::iterator ite = adj.end();
    while (it != ite) {
        if (it->dest == d) {
            adj.erase(it);
            return true;
        } else
            it++;
    }
    return false;
}

// atualizado pelo exerc�cio 5
template <class T>
Vertex<T>::Vertex(T in)
        : info(in), visited(false), processing(false), indegree(0), dist(0) {
    path = nullptr;
}

template <class T> void Vertex<T>::addEdge(Vertex<T> *dest, double w) {
    Edge<T> edgeD(dest, w);
    adj.push_back(edgeD);
}

template <class T> T Vertex<T>::getInfo() const { return this->info; }

template <class T> int Vertex<T>::getDist() const { return this->dist; }

template <class T> void Vertex<T>::setInfo(T info) { this->info = info; }

template <class T> int Vertex<T>::getIndegree() const { return this->indegree; }

/* ================================================================================================
 * Class Edge
 * ================================================================================================
 */
template <class T> class Edge {
    Vertex<T> *dest;
    double weight;

public:
    Edge(Vertex<T> *d, double w);
    friend class Graph<T>;
    friend class Vertex<T>;
    Vertex<T> * getDest() const{
        return this->dest;
    }
    double getWeight() const{
        return this->weight;
    }

    //===============================
    inline bool operator==(const Edge<T> &rhs) {
        if (this->weight == rhs.weight && this->dest == rhs.dest)
            return true;
        return false;
    }

    inline bool same(const Edge<T> &rhs) {
        if (this->weight == rhs.weight && this->dest->getInfo() == rhs.dest->getInfo())
            return true;
        return false;
    }

    inline bool less(const Edge<T> &rhs) {
        if(this->weight < rhs.weight)
            return true;
        else
            return false;
    }

   friend inline bool operator< (const Edge<T> &lhs, const Edge<T> &rhs){
        return (lhs.weight >= rhs.weight);
    }

    bool isEdgeIn(vector<pair<T,T>> exluded, T origin){
        for(auto p_edge : exluded)
            if(this->dest->getInfo() == get<1>(p_edge) && origin == get<0>(p_edge) || this->dest->getInfo() == get<0>(p_edge) && origin == get<1>(p_edge) )
                return true;
        return false;
    }

    //===============================
};
template <class T> Edge<T>::Edge(Vertex<T> *d, double w) : dest(d), weight(w) {}

template<class T>
struct Comparator : public std::binary_function<T,T,bool>
{
    const pair<T,int> & operator()(const pair<T,int>& o1, const pair<T,int>& o2)
    {
        if(get<1>(o1) > get<1>(o2))
            return o1;
        else
            return o2;
    }
};


/* ================================================================================================
 * Class Graph
 * ================================================================================================
 */
template <class T> class Graph {
    vector<Vertex<T> *> vertexSet;
    void dfs(Vertex<T> *v, vector<T> &res) const;

    // exercicio 5
    int numCycles;
    void dfsVisit(Vertex<T> *v);
    void dfsVisit();
    void getPathTo(Vertex<T> *origin, list<T> &res);

    int ** W;   //weight
    int ** P;   //path

    map<pair<T,T>, vector<T>> path_reconstruc;

    T * ghost_node;
    T ghost_node_info;

public:
    bool addVertex(const T &in);
    bool addEdge(const T &sourc, const T &dest, double w);
    bool removeVertex(const T &in);
    bool removeEdge(const T &sourc, const T &dest);
    vector<T> dfs() const;
    vector<T> bfs(Vertex<T> *v) const;
    int maxNewChildren(Vertex<T> *v, T &inf) const;
    vector<Vertex<T> *> getVertexSet() const;
    int getNumVertex() const;

    // exercicio 5
    Vertex<T> *getVertex(const T &v) const;
    void resetIndegrees();
    vector<Vertex<T> *> getSources() const;
    int getNumCycles();
    vector<T> topologicalOrder();
    vector<T> getPath(const T &origin, const T &dest);
    void unweightedShortestPath(const T &v);
    bool isDAG();



    pair<vector<T>,double> minSpanningTree2(){

        vector<T> final;
        double final_dis = 0.0;

        /*
        KRUSKAL(G):
        1 final = ∅
        2 foreach v ∈ G.V: //Graph vertices
        3    MAKE-SET(v)
        4 foreach (u, v) in G.E ordered by weight(u, v), increasing:   // G.E Graph edges
        5    if FIND-SET(u) ≠ FIND-SET(v):
        6       final = final ∪ {(u, v)}
        7       UNION(u, v)
        8 return final
        */


        vector<T> verts_info;
        vector<T *> pverts;
        for(auto vertex: this->getVertexSet()) {
            verts_info.push_back(vertex->info);
            pverts.push_back(&(verts_info.at(verts_info.size()-1)));
        }

        auto Set = DisjointSet<T>::make_Set( pverts);
        PriQueue<pair<T,T>, double> edges_sort; int edge_numb = 0;

        for(auto vertex : this->getVertexSet())
            for(auto edge : vertex->adj) {
                edges_sort.addWithPriority(pair<T,T>(vertex->info, edge.dest->info), edge.weight);
                edge_numb++;
            }

        map<T, bool> exist;
        for(auto vert : this->getVertexSet())
            exist[vert->info] = false;

        for (int i = 0; i < edge_numb; ++i) {
            pair<T, T> top_edge = edges_sort.peakTop();
            if (*Set[top_edge.first - 1].get_parent() != *Set[top_edge.second - 1].get_parent()) {
                if (final.empty()) {
                    final.push_back(top_edge.first); exist[top_edge.first] = true;
                    final.push_back(top_edge.second); exist[top_edge.second] = true;
                    final_dis += this->getEdge(top_edge.first, top_edge.second);
                } else {
                      if(!exist[top_edge.first]) {
                        final.push_back(top_edge.first);
                        exist[top_edge.first] = true;
                    }
                    else if(!exist[top_edge.second]) {
                        final.push_back(top_edge.second);
                        exist[top_edge.second] = true;
                    }
                    else
                        final_dis -= edges_sort.getCriteria(top_edge);
                    final_dis += edges_sort.getCriteria(top_edge);
                }
                DisjointSet<T>::Union(&(Set[top_edge.first - 1]), &(Set[top_edge.second - 1]));
            }
            edges_sort.extractTop();
        }

        return pair<vector<T>,double>(final, final_dis);

    }

    void initVisited(){
        for(auto vertex : this->getVertexSet())
            vertex->visited = false;
    }

    pair<vector<T>,double> TSP_Gready(T s, T dest){
        double res = 0.0;
        vector<T> final_path;

        this->initVisited();
        Vertex<T> * vertex_to_look;

        vector<Vertex<T>*> p_final_path;

        p_final_path.push_back( this->getVertex(s));
        p_final_path.at(0)->visited = true;
        for(int i = 0; i < this->getNumVertex() -2 ; i++) {
            vertex_to_look = p_final_path.at(p_final_path.size() - 1);
            PriQueue<Edge<T>, double> v_edges;
            for (auto edge: vertex_to_look->adj)
                if(edge.dest->visited == false && edge.dest->info != dest &&edge.dest->info != s )
                    v_edges.addWithPriority(edge, edge.weight);
            p_final_path.push_back(v_edges.peakTop().dest);
        //    cout << "  Added from " << p_final_path[p_final_path.size()-2]->info << " to " << p_final_path[p_final_path.size()-1]->info << " dis : " << v_edges.peakTop().weight;
            res += v_edges.extractTop().weight;
            vertex_to_look->visited = true;
        }

        for(int i = 0; i < p_final_path.size(); i++)
            final_path.push_back(p_final_path.at(i)->info);

       // if(s != dest)
            final_path.push_back(dest);

        double initres =res;
        res += this->getEdge(final_path.at(final_path.size()-2), dest);
       // cout << "Addes to  final " << res -initres << endl;

       // cout << "Distance is : " << res << endl;
        return pair<vector<T>,double>(final_path, res);
    }

    int edgeCost(int vOrigIndex, int vDestIndex)
    {
        if(vertexSet[vOrigIndex] == vertexSet[vDestIndex])
            return 0;

        for(unsigned int i = 0; i < vertexSet[vOrigIndex]->adj.size(); i++)
        {
            if(vertexSet[vOrigIndex]->adj[i].dest == vertexSet[vDestIndex])
                return vertexSet[vOrigIndex]->adj[i].weight;
        }

        return INT_INFINITY;
    }

    void floydWarshallShortestPath(){
        W = new int * [vertexSet.size()];
        P = new int * [vertexSet.size()];
        for(unsigned int i = 0; i < vertexSet.size(); i++)
        {
            W[i] = new int[vertexSet.size()];
            P[i] = new int[vertexSet.size()];
            for(unsigned int j = 0; j < vertexSet.size(); j++)
            {
                W[i][j] = edgeCost(i,j);
                P[i][j] = -1;
            }
        }


        for(unsigned int k = 0; k < vertexSet.size(); k++)
            for(unsigned int i = 0; i < vertexSet.size(); i++)
                for(unsigned int j = 0; j < vertexSet.size(); j++)
                {
                    //se somarmos qualquer coisa ao valor INT_INFINITY, ocorre overflow, o que resulta num valor negativo, logo nem convém considerar essa soma
                    if(W[i][k] == INT_INFINITY || W[k][j] == INT_INFINITY)
                        continue;

                    int val = min ( W[i][j], W[i][k]+W[k][j] );
                    if(val != W[i][j])
                    {
                        W[i][j] = val;
                        P[i][j] = k;
                    }
                }

    }

    pair<T,T> genGarageLand(){
        int garage_i = (rand() % this->getNumVertex());
        int landfill_i;
        do{
            landfill_i = (rand() % this->getNumVertex());
        }while (garage_i == landfill_i);

        T garage = this->getVertexSet()[garage_i]->info;
        T landfill = this->getVertexSet()[landfill_i]->info;

        return pair<T,T>(garage,landfill);
    }

    void genTrashcans(pair<T,T> land_garage){

        int how_many = (this->getNumVertex() -2)/3;

        vector<T> generated;
        for (int i = 0; i < how_many; ++i) {
            T gen;
            do{
               gen = this->getVertexSet()[rand() % this->getNumVertex()]->info;
            } while(gen == land_garage.first || gen == land_garage.second || find(generated.begin(), generated.end(), gen)!= generated.end() );
            generated.push_back(gen);
        }
        for(auto gened : generated){
            this->getVertex(gened)->trash = 50;
        }

    }

vector<T> getfloydWarshallPath(const T &origin, const T &dest){

    int originIndex = -1, destinationIndex = -1;

    for(unsigned int i = 0; i < vertexSet.size(); i++)
    {
        if(vertexSet[i]->info == origin)
            originIndex = i;
        if(vertexSet[i]->info == dest)
            destinationIndex = i;

        if(originIndex != -1 && destinationIndex != -1)
            break;
    }


    vector<T> res;

    //se nao foi encontrada solucao possivel, retorna lista vazia
    if(W[originIndex][destinationIndex] == INT_INFINITY)
        return res;

    res.push_back(vertexSet[originIndex]->info);

    //se houver pontos intermedios...
    if(P[originIndex][destinationIndex] != -1)
    {
        int intermedIndex = P[originIndex][destinationIndex];

        getfloydWarshallPathAux(originIndex, intermedIndex, res);

        res.push_back(vertexSet[intermedIndex]->info);

        getfloydWarshallPathAux(intermedIndex,destinationIndex, res);
    }

    res.push_back(vertexSet[destinationIndex]->info);


    return res;
}

    pair<vector<T>, double > solveTruckRun(T begin, T end, vector<T> points){

        points.push_back(begin);
        points.push_back(end);

        auto gready_res = (this->makeTSPres(points).TSP_Gready(begin, end));

        vector<T> final_path;


        for (int i = 1; i < gready_res.first.size(); ++i) {
            vector<T> reco_path = this->getPathRecons(gready_res.first.at(i-1), gready_res.first.at(i)).first;
            for(auto t : reco_path)
                final_path.push_back(t);
        }

        return pair<vector<T>, double>(gready_res.first,gready_res.second);

    }

    map<T, vector<pair<vector<T>,double>>>  solveTruck(pair<T,T> garage_land, vector<T> trucks){

        map<T, vector<pair<vector<T>, double >>> trucks_runs;

        int numb_trash_cans = this->getNumVertex()-2;

        while(true)
        for(auto truck : trucks) {
            int truck_cap = truck;
            vector<T> trash_to_run;
            for (auto trash_can : this->getVertexSet())
                if (trash_can->info != garage_land.first && trash_can->info != garage_land.second &&
                    trash_can->trash_picked == false) {
                    if(truck_cap >= trash_can->trash) {
                        truck_cap -= trash_can->trash;
                        trash_to_run.push_back(trash_can->info);
                        trash_can->trash_picked = true;
                        numb_trash_cans--;
                    }
                }
            if(trucks_runs.find(truck) == trucks_runs.end()) {
                vector<pair<vector<T>, double >> run;
                auto solve = this->solveTruckRun(garage_land.first, garage_land.second, trash_to_run);
                run.push_back(solve);
                trucks_runs[truck] = run;
            }
            else
                trucks_runs[truck].push_back(this->solveTruckRun(garage_land.second, garage_land.second, trash_to_run));
            if (numb_trash_cans <= 0)
                return  trucks_runs;
        }

    }

    Graph<T> makeTSPres_trash(pair<T,T> garage_land){
        vector<T> trash_cans;
        trash_cans.push_back(garage_land.first);

        for(auto vert : vertexSet)
            if(vert->trash != -1)
                trash_cans.push_back(vert->info);

        trash_cans.push_back(garage_land.second);

        return this->makeTSPres(trash_cans);

    }

    Graph<T> makeTSPres(vector<T> trash_cans){

        Graph<T> TSPgraph;
        this->path_reconstruc.clear();
        this->makeSymetric();
        for(auto vertex : trash_cans)
            TSPgraph.addVertex(vertex);

        for(auto vertex : trash_cans){
            this->dijkstraShortestPath(vertex);
            double total_weight = 0;
            for(auto sub_vertex : trash_cans) {
                if(sub_vertex != vertex) {
                    total_weight = this->getTotalWeightfromPath(vertex, sub_vertex);
                    pair<T,T> from_to = pair<T,T>(vertex, sub_vertex) ;
                    vector<T> from_to_path = this->getPath(vertex, sub_vertex);
                    TSPgraph.path_reconstruc.insert(pair<pair<T,T>, vector<T>>(from_to, from_to_path));
                    TSPgraph.addEdge( vertex, sub_vertex , total_weight);
                }
            }
        }
        return TSPgraph;
    }

    pair<vector<T>, double> getPathRecons(T s, T dest){
        vector<T> final_path;

        final_path = this->path_reconstruc[pair<T,T>(s, dest)];

        return pair<vector<T>,double>(final_path, this->getEdge(s, dest));
    }


void getfloydWarshallPathAux(int index1, int index2, vector<T> & res)
{
    if(P[index1][index2] != -1)
    {
        getfloydWarshallPathAux(index1, P[index1][index2], res);

        res.push_back(vertexSet[P[index1][index2]]->info);

        getfloydWarshallPathAux(P[index1][index2],index2, res);
    }
}

    int add_GhostVertex(T s, T end){

        int numb = this->getNumVertex();
        this->ghost_node_info = numb+1;
        this->addVertex(numb+1);

        for(auto vertex : this->getVertexSet())
            if(vertex->info != numb+1) {
                if (vertex->info == s || vertex->info == end) {
                    this->addEdge(numb + 1, vertex->info, 0);
                    this->addEdge(vertex->info, numb + 1, 0);
                } else {
                    this->addEdge(numb + 1, vertex->info, INT_INFINITY);
                    this->addEdge(vertex->info, numb + 1, INT_INFINITY);
                }
            }
        return numb+1;
    }
    T last_vertexinfo(){
        return this->getVertexSet().at(this->getNumVertex())->info;
    }

    void revert_GhostNode(){
        for(auto vertex: this->getVertexSet())
            if(vertex->info !=this->ghost_node_info) {
                this->removeEdge(vertex->info, this->ghost_node_info);
                this->removeEdge(this->ghost_node_info, vertex->info);
            }
        this->removeVertex(this->ghost_node_info);
        }

    void make_ClassicTSP(T begin, T end){

    }

    inline double path_dis(T begin, T end, vector<T> vpath){
        double total = 0.0;
        for (int i = 1; i < vpath.size(); ++i) {
            total += this->getEdge(vpath.at(i - 1), vpath.at(i));
        }
        total += this->getEdge(begin, vpath.at(0));
        total += this->getEdge(vpath.at(vpath.size()-1), end);
        return total;
    }

    double TSP_BB_lowerbound2(vector<pair<T,T>> exclude_edges, vector<pair<T,T>> include_edges){
        double ans = 0.0;

        for(auto Tpair : include_edges)
            exclude_edges.push_back(Tpair);

        for(auto vertex:this->vertexSet) {
            priority_queue<Edge<T>> s_edges;
            for (auto edge: vertex->adj) {
                if (!edge.isEdgeIn(exclude_edges, vertex->info))
                    s_edges.push(edge);
            }
            int left = 2;

            double init_ans = ans;

            for(int i = 0 ; i<  include_edges.size(); i++ )
                if(get<0>(include_edges.at(i)) == vertex->info || get<1>(include_edges.at(i)) == vertex->info){
                    ans += this->getEdge(get<0>(include_edges[i]), get<1>(include_edges.at(i)) );
                     left--;
                }

            for (int i = 0; i < left; ++i) {
                ans += s_edges.top().weight;
                s_edges.pop();
            }
        }

        return ans*0.5;
    }

    pair<vector<T>, double> minSpanningTree(T ex_vertex, vector<pair<T,T>> ex_edge, vector<pair<T,T>> in_edge){
        vector<T> final_path; double final_dis = 0.0;
        map<T,bool> exists;
        //Init map of existing
        for(auto vertex: this->getVertexSet())
            exists[vertex->info] = false;

        //Make disjoint sets
        vector<T> verts_info;
        vector<T *> pverts;
        for(auto vertex: this->getVertexSet()) {
        vertex->parent = vertex;
        }

        auto dis_set = DisjointSet<T>::make_Set( pverts);

        //include mandatory edges
        for(auto p_edge : in_edge){
            final_path.push_back(p_edge.first); final_path.push_back(p_edge.second);
            exists[p_edge.first] = true; exists[p_edge.first] = true;
            final_dis += this->getEdge(p_edge.first, p_edge.second);
            cout << "Mandatoy" << endl;
//            DisjointSet<T>::Union(&dis_set[p_edge.first - 1], &dis_set[p_edge.first - 2]);
        }

        //sort edges
        PriQueue<pair<T,T>, double> edges_sort; int edge_numb = 0;
        for(auto vertex : this->getVertexSet())
            for(auto edge : vertex->adj) {
                edges_sort.addWithPriority(pair<T,T>(vertex->info, edge.dest->info), edge.weight);
                edge_numb++;
            }

        for(int i = 0; i < edge_numb; i++) {
            pair<T, T> p_edge = edges_sort.extractTop();
            if (find(ex_edge.begin(), ex_edge.end(), p_edge) == ex_edge.end() &&
              //      this->getVertex(p_edge.first)->parent != this->getVertex(p_edge.second)->parent &&
                (dis_set[p_edge.first - 1].get_parent()) != (dis_set[p_edge.second - 1].get_parent()) &&
                    (p_edge.first != ex_vertex && p_edge.second != ex_vertex)  ){

            //    if(final_path.size() == this->getNumVertex())
             //       break;

              /*
                if (!exists[p_edge.first]) {
                    final_path.push_back(p_edge.first);
                    exists[p_edge.first] = true;
                     DisjointSet<T>::Union(&(dis_set[p_edge.first - 1]), &(dis_set[p_edge.second - 1]));

                }
                if (!exists[p_edge.second]) {
                    final_path.push_back(p_edge.second);
                    exists[p_edge.second] = true;
                    //final_dis += this->getEdge(p_edge.first, p_edge.second);
//                    cout << "Added : " << p_edge.first << "   " << p_edge.second << "  dis: " << this->getEdge(p_edge.first, p_edge.second) << endl;

                    DisjointSet<T>::Union(&(dis_set[p_edge.first - 1]), &(dis_set[p_edge.second - 1]));

                }
                */
             //   cout << "Same set : " << ((dis_set[p_edge.first - 1]).get_parent()) << "   " << ((dis_set[p_edge.second - 1]).get_parent()) << endl;

                final_dis += this->getEdge(p_edge.first, p_edge.second);
                cout << "Added : " << p_edge.first << "   " << p_edge.second << "  dis: " << this->getEdge(p_edge.first, p_edge.second) << endl;
               // DisjointSet<T>::Union(&(dis_set[p_edge.first - 1]), &(dis_set[p_edge.second - 1]));

             //   cout<< "First Parent : " << (this->getVertex(p_edge.first)->parent)->info << "  Second Parent : " << (this->getVertex(p_edge.second)->parent)->info << endl;

              //  this->getVertex(p_edge.second)->parent = this->getVertex(p_edge.first)->parent;
              //  this->getVertex(p_edge.first)->parent = this->getVertex(p_edge.second)->parent;

               // cout<< " \n First Parent : " << (this->getVertex(p_edge.first)->parent)->info << "  Second Parent : " << (this->getVertex(p_edge.second)->parent)->info << endl;

         //       cout << "Same set : " << ((dis_set[p_edge.first - 1]).get_parent()) << "   " << ((dis_set[p_edge.second - 1]).get_parent()) << endl;
                DisjointSet<T>::Union(&(dis_set[p_edge.first - 1]), &(dis_set[p_edge.second - 1]));
                if (!exists[p_edge.second]) {
                    final_path.push_back(p_edge.second);
                    exists[p_edge.second] = true;
                }
                if (!exists[p_edge.first]) {
                    final_path.push_back(p_edge.first);
                    exists[p_edge.first] = true;
                }

            }
        }
        return pair<vector<T>, double>(final_path, final_dis);
    }

    double TSP_BB_lowerbound(vector<pair<T,T>> exclude_edges, vector<pair<T,T>> include_edges){
//        double ans = get<1>(this->minSpanningTree());
        /*

        for(auto Tpair : include_edges)
            exclude_edges.push_back(Tpair);

        set<double> trees;

        for(auto vertex:this->vertexSet) {
            priority_queue<Edge<T>> s_edges;
            for (auto edge: vertex->adj) {
                if (!edge.isEdgeIn(exclude_edges, vertex->info))
                    s_edges.push(edge);
            }
            int left = 2;
           // ans = get<1>(this->minSpanningTree());
            double init_ans = ans;

           ans += s_edges.top().weight; s_edges.pop();
            ans += s_edges.top().weight; s_edges.pop();
            trees.insert(ans);
        }
 */
      //  auto end = trees.rend();
      //  ++end;
        return 0.5;
    }

    double tabu_swap(vector<T> & cities , map<pair<T,T>,double> &tabu_list, double max_path, T begin , T end) {

        int city1, city2;
        double curr;

        rng_type::result_type const seedval = getpid(); // get this from somewhere
        rng.seed(seedval);

        vector<T> temp_cities = cities;
        pair<T,T> city_pair;
        bool invalid;
        do {
            temp_cities = cities;
            rng_type::result_type random_number1  = udist(rng);
            rng_type::result_type random_number2  = udist(rng);
            city1 = (random_number1 % (cities.size()-2)) + 1;
            city2 = (random_number2 % (cities.size()-2)) + 1;
            T temp = temp_cities[city1];
            temp_cities[city1] = temp_cities[city2];
            temp_cities[city2] = temp;
            curr = this->path_dis(begin, end, temp_cities);
            city_pair = pair<T,T>(temp_cities[city1] , temp_cities[city2]);
            if(tabu_list.find( city_pair) == tabu_list.end())
                tabu_list[city_pair] = 0;

            if(curr < max_path)
                double reswfefwef = 0.0;

            invalid  = false;

            if(abs(city1-city2) <= 1)
                invalid = true;
            if(curr > max_path )
                invalid = true;
            if(tabu_list[city_pair] > 0)
                invalid = true;

        }
            while(invalid);

        for(auto const &p_cities: tabu_list)
            if(p_cities.second != 0)
                p_cities.second == p_cities.second -1;

        tabu_list[city_pair] = 2;

        cities = temp_cities;

        return curr;
    }


    pair<vector<T>, double> tabu_search(T begin, T end, int inter_numb){




        auto gready = this->TSP_Gready(begin, end);
        vector<T> cities = gready.first;

        map<pair<T,T>,double> tabu_list;

        double max_path = gready.second;

        cout << "Started with : " << max_path << endl;

        double change_path_dis;
        for (int i = 0; i < inter_numb; ++i)
            max_path = this->tabu_swap(cities, tabu_list, max_path, begin , end);

        return pair<vector<T>, double>(cities,max_path);
    }

    //http://lcm.csa.iisc.ernet.in/dsa/node187.html#fig:tspbb
    //http://stackoverflow.com/questions/22985590/calculating-the-held-karp-lower-bound-for-the-traveling-salesmantsp
    //http://lcm.csa.iisc.ernet.in/dsa/node187.html
    //https://ocw.mit.edu/courses/sloan-school-of-management/15-053-optimization-methods-in-management-science-spring-2013/tutorials/MIT15_053S13_tut10.pdf
    //https://web.archive.org/web/20160520165234/http://lcm.csa.iisc.ernet.in/dsa/node187.html
    //https://en.wikipedia.org/wiki/Travelling_salesman_problem#Related_problems
    //http://stackoverflow.com/questions/22985590/calculating-the-held-karp-lower-bound-for-the-traveling-salesmantsp
    //http://ijair.jctjournals.com/oct2012/t121015.pdf
    //https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
    //http://artint.info/html/ArtInt_63.html
    //https://optimization.mccormick.northwestern.edu/index.php/Branch_and_bound_(BB)

    pair<vector<T>,double> TSP_BranchBound(T begin , T end) {
        vector<T> cities, max_path_cities;
        vector<pair<T,T>> excluded, included;

        PriQueue<pair<pair<T,T>,bool>, double> waiting_nodes; //Priqueue with a exclusion and inclusion and bound

        double best_sol = 999999999999999999999999.9; //LOL
        double best_bound = this->TSP_BB_lowerbound(excluded, included);
        //Priqueue with a node and its bound

/*
        //Put root node
        waiting_nodes.addWithPriority();
        while(PriQueue.size() != 0){

        }
*/
        return pair<vector<T>,double>(max_path_cities, 10.0);
    }

    pair<vector<T>,double> TSP_bruteForce(T begin , T end){

        if(begin != end ) {
            begin = this->add_GhostVertex(begin, end);
            end = begin;
        }

        cout << "Begin: " << begin << " End : " << end << endl;
        vector<T> cities, max_path_cities;

        for (auto vertex : this->vertexSet)
            if(vertex->info != begin && vertex->info != end )
                cities.push_back(vertex->info);

        double max_path = 0.0;
        sort(cities.begin(), cities.end());
        do {
            double path_dis = this->path_dis(begin, end, cities);
           // cout << "Path: ";
           // for (auto city: cities)
           //     cout << city <<" ";
           // cout << "   Distance : " << path_dis << endl;
            if(path_dis < max_path || max_path < 0.1) {
                max_path = path_dis;
                max_path_cities = cities;
            }

        } while (next_permutation(cities.begin(), cities.end()));

        max_path_cities.push_back(end);
        vector<T> final_answer; final_answer.push_back(begin);
        final_answer.insert(final_answer.end(), max_path_cities.begin(), max_path_cities.end());
        this->revert_GhostNode();
        return pair<vector<T>, double>(final_answer,max_path);
    }

    void addVertexFull(Vertex<T>* newone){
        this->vertexSet.push_back(newone);
    }

    double getEdge(T source, T dest){

        for (auto edge : this->getVertex(source)->adj)
            if (edge.dest->info == dest)
                return edge.weight;

        return 0.0;
    }

    inline string fillPath(map<T,T> prev, T target) {
        string res = "";
        T v = target;
        while(true){
            v = prev[v];
           // cout << "In Loop" << endl;
            if(v == -1 || v == 0){
            //    cout << "GOT OUT" << endl;
                break;
            }
            //res+= "<-";
            res += std::to_string(v);
            res += " ";
            //res+= "|";
            //cout << "LOOPED, vertex is:"  << std::to_string(v) << endl;
        }
        return res;
    }

    void dijkstraShortestPath(T source) {
        map<T, double> dis;
        map<T, T> prev;

        PriQueue<T, double> Q;

        for (int i = 0; i < this->vertexSet.size(); i++) {
            T info = this->vertexSet[i]->info;
            if (info != source) {
                dis.insert(pair<T, int>(info, INT_INFINITY));
                prev.insert(pair<T, T>(info, -1));
            }
            else
                dis[source] = 0;

            Q.addWithPriority(info, dis[info]);
        }

        while(Q.size() != 0) {

            T u_top = Q.extractTop();
            Vertex<T>* u =  this->getVertex(u_top);

            for(int i = 0; i < u->adj.size(); i++) {
                Vertex<T> * v = u->adj.at(i).dest;
                double alt = dis[u->info] + u->adj.at(i).weight;
                if (alt < dis[v->info]) {
                    dis[v->info] = alt;
                    prev[v->info] = u->info;
                    Q.decreasePriority(v->info, alt);
                }
            }

        }
        for(auto v : this->getVertexSet())
            v->path = getVertex(prev[v->info]);

        return;
    }

    Graph<T> makeTSP(){
        Graph<T> TSPgraph;
        this->makeSymetric();
        for(auto vertex : this->getVertexSet())
            TSPgraph.addVertex(vertex->info);

        for(auto vertex : this->getVertexSet()){
            this->dijkstraShortestPath(vertex->info);
            double total_weight = 0;
            for(auto sub_vertex : this->getVertexSet()) {
                if(sub_vertex != vertex) {
                    total_weight = this->getTotalWeightfromPath(vertex->info, sub_vertex->info);
                    TSPgraph.addEdge( vertex->info ,sub_vertex->info, total_weight);
                }
            }
        }
        return TSPgraph;
    }



   static void thr_Djistra(T vertex, Graph<T> * TSP_graph , Graph<T> otherGraph) {


            otherGraph.dijkstraShortestPath(vertex);
            double total_weight = 0;
            for(auto sub_vertex : otherGraph.getVertexSet()) {
                if(sub_vertex->info != vertex) {
                    total_weight = otherGraph.getTotalWeightfromPath(vertex, sub_vertex->info);
                    lck_edge.lock();
                    TSP_graph->addEdge( vertex ,sub_vertex->info, total_weight);
                    lck_edge.unlock();
                }
            }

    }


    Graph<T> makeTSPThreaded(){

        Graph<T> TSPgraph;
        this->makeSymetric();
        for(auto vertex : this->getVertexSet())
            TSPgraph.addVertex(vertex->info);

        int max_threads = 6;
        int vertex_left = this->getNumVertex();

        thread threads[vertex_left];

        for(int j = 0; j < vertex_left; j++){
            Graph<T> other = *this;
            threads[j] = thread(&(Graph::thr_Djistra), this->getVertexSet()[j]->info, &TSPgraph, other);

        }

        for(int i = 0; i < vertex_left; i++)
            threads[i].join();


        return TSPgraph;
    }

    void makeSymetric(){
        for(auto vertex : this->vertexSet)
            for(auto edge : vertex->adj) {
                bool add = true;
                for (auto dest_edge : edge.dest->get_adj()) {
                    if (dest_edge.dest == vertex)
                        add = false;
                }
                if(add)
                    edge.dest->addEdge(vertex, edge.weight);
            }
        return;
    }

    double getTotalWeightfromPath(T source, T dest) {
        if(source == dest)
            return 0.0;

        double res = 0.0;

        vector<T> total_path = this->getPath(source, dest);

        if(total_path.size() == 1)
            for(auto edge : (this->getVertex(dest)->adj))
                if(edge.dest == getVertex(source))
                    return edge.weight;

        for (int i = 1; i < total_path.size(); ++i) {
            for(auto edge : (this->getVertex(total_path[i-1]))->adj){
                if(edge.dest->info == getVertex(total_path[i])->info)
                    res += edge.weight;
        }}

        if(res != 0.0 )
            return res;

        return -1.0;

    }

    bool hasConnection(T first, T second) {
        for (auto edge : this->getVertex(first)->adj)
            if (edge.dest->info == second)
                return true;
        return false;
    }
//===============================

    inline bool operator==(const Graph<T> &rhs) {
        if (this->vertexSet.size() != rhs.vertexSet.size())
            return false;

        for (size_t i = 0; i < this->vertexSet.size(); i++) {
            if (this->vertexSet.at(i)->info != rhs.vertexSet.at(i)->info ||
                this->vertexSet.at(i)->adj.size() != rhs.vertexSet.at(i)->adj.size())
                return false;
            for (size_t j = 0; j < this->vertexSet.at(i)->adj.size(); j++)
                if (this->vertexSet.at(i)->adj.at(j).dest->info !=
                    rhs.vertexSet.at(i)->adj.at(j).dest->info)
                    return false;
        }

        return true;
    }
//===============================
}
;

template <class T> int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}
template <class T> vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return vertexSet;
}

template <class T> int Graph<T>::getNumCycles() {
    numCycles = 0;
    dfsVisit();
    return this->numCycles;
}

template <class T> bool Graph<T>::isDAG() { return (getNumCycles() == 0); }

template <class T> bool Graph<T>::addVertex(const T &in) {
    typename vector<Vertex<T> *>::iterator it = vertexSet.begin();
    typename vector<Vertex<T> *>::iterator ite = vertexSet.end();
    for (; it != ite; it++)
        if ((*it)->info == in)
            return false;
    Vertex<T> *v1 = new Vertex<T>(in);
    vertexSet.push_back(v1);
    return true;
}

template <class T> bool Graph<T>::removeVertex(const T &in) {
    typename vector<Vertex<T> *>::iterator it = vertexSet.begin();
    typename vector<Vertex<T> *>::iterator ite = vertexSet.end();
    for (; it != ite; it++) {
        if ((*it)->info == in) {
            Vertex<T> *v = *it;
            vertexSet.erase(it);
            typename vector<Vertex<T> *>::iterator it1 = vertexSet.begin();
            typename vector<Vertex<T> *>::iterator it1e = vertexSet.end();
            for (; it1 != it1e; it1++) {
                (*it1)->removeEdgeTo(v);
            }

            typename vector<Edge<T>>::iterator itAdj = v->adj.begin();
            typename vector<Edge<T>>::iterator itAdje = v->adj.end();
            for (; itAdj != itAdje; itAdj++) {
                itAdj->dest->indegree--;
            }
            delete v;
            return true;
        }
    }
    return false;
}

template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    typename vector<Vertex<T> *>::iterator it = vertexSet.begin();
    typename vector<Vertex<T> *>::iterator ite = vertexSet.end();
    int found = 0;
    Vertex<T> *vS, *vD;
    while (found != 2 && it != ite) {
        if ((*it)->info == sourc) {
            vS = *it;
            found++;
        }
        if ((*it)->info == dest) {
            vD = *it;
            found++;
        }
        it++;
    }
    if (found != 2)
        return false;
    vD->indegree++;
    vS->addEdge(vD, w);

    return true;
}

template <class T> bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
    typename vector<Vertex<T> *>::iterator it = vertexSet.begin();
    typename vector<Vertex<T> *>::iterator ite = vertexSet.end();
    int found = 0;
    Vertex<T> *vS, *vD;
    while (found != 2 && it != ite) {
        if ((*it)->info == sourc) {
            vS = *it;
            found++;
        }
        if ((*it)->info == dest) {
            vD = *it;
            found++;
        }
        it++;
    }
    if (found != 2)
        return false;

    vD->indegree--;

    return vS->removeEdgeTo(vD);
}

template <class T> vector<T> Graph<T>::dfs() const {
    typename vector<Vertex<T> *>::const_iterator it = vertexSet.begin();
    typename vector<Vertex<T> *>::const_iterator ite = vertexSet.end();
    for (; it != ite; it++)
        (*it)->visited = false;
    vector<T> res;
    it = vertexSet.begin();
    for (; it != ite; it++)
        if ((*it)->visited == false)
            dfs(*it, res);
    return res;
}

template <class T> void Graph<T>::dfs(Vertex<T> *v, vector<T> &res) const {
    v->visited = true;
    res.push_back(v->info);
    typename vector<Edge<T>>::iterator it = (v->adj).begin();
    typename vector<Edge<T>>::iterator ite = (v->adj).end();
    for (; it != ite; it++)
        if (it->dest->visited == false) {
            dfs(it->dest, res);
        }
}

template <class T> vector<T> Graph<T>::bfs(Vertex<T> *v) const {
    vector<T> res;
    queue<Vertex<T> *> q;
    q.push(v);
    v->visited = true;
    while (!q.empty()) {
        Vertex<T> *v1 = q.front();
        q.pop();
        res.push_back(v1->info);
        typename vector<Edge<T>>::iterator it = v1->adj.begin();
        typename vector<Edge<T>>::iterator ite = v1->adj.end();
        for (; it != ite; it++) {
            Vertex<T> *d = it->dest;
            if (d->visited == false) {
                d->visited = true;
                q.push(d);
            }
        }
    }
    return res;
}

template <class T> int Graph<T>::maxNewChildren(Vertex<T> *v, T &inf) const {
    vector<T> res;
    queue<Vertex<T> *> q;
    queue<int> level;
    int maxChildren = 0;
    inf = v->info;
    q.push(v);
    level.push(0);
    v->visited = true;
    while (!q.empty()) {
        Vertex<T> *v1 = q.front();
        q.pop();
        res.push_back(v1->info);
        int l = level.front();
        level.pop();
        l++;
        int nChildren = 0;
        typename vector<Edge<T>>::iterator it = v1->adj.begin();
        typename vector<Edge<T>>::iterator ite = v1->adj.end();
        for (; it != ite; it++) {
            Vertex<T> *d = it->dest;
            if (d->visited == false) {
                d->visited = true;
                q.push(d);
                level.push(l);
                nChildren++;
            }
        }
        if (nChildren > maxChildren) {
            maxChildren = nChildren;
            inf = v1->info;
        }
    }
    return maxChildren;
}

template <class T> Vertex<T> *Graph<T>::getVertex(const T &v) const {
    for (unsigned int i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->info == v)
            return vertexSet[i];
    return nullptr;
}

template <class T> void Graph<T>::resetIndegrees() {
    // colocar todos os indegree em 0;
    for (unsigned int i = 0; i < vertexSet.size(); i++)
        vertexSet[i]->indegree = 0;

    // actualizar os indegree
    for (unsigned int i = 0; i < vertexSet.size(); i++) {
        // percorrer o vector de Edges, e actualizar indegree
        for (unsigned int j = 0; j < vertexSet[i]->adj.size(); j++) {
            vertexSet[i]->adj[j].dest->indegree++;
        }
    }
}

template <class T> vector<Vertex<T> *> Graph<T>::getSources() const {
    vector<Vertex<T> *> buffer;
    for (unsigned int i = 0; i < vertexSet.size(); i++) {
        if (vertexSet[i]->indegree == 0)
            buffer.push_back(vertexSet[i]);
    }
    return buffer;
}

template <class T> void Graph<T>::dfsVisit() {
    typename vector<Vertex<T> *>::const_iterator it = vertexSet.begin();
    typename vector<Vertex<T> *>::const_iterator ite = vertexSet.end();
    for (; it != ite; it++)
        (*it)->visited = false;
    it = vertexSet.begin();
    for (; it != ite; it++)
        if ((*it)->visited == false)
            dfsVisit(*it);
}

template <class T> void Graph<T>::dfsVisit(Vertex<T> *v) {
    v->processing = true;
    v->visited = true;
    typename vector<Edge<T>>::iterator it = (v->adj).begin();
    typename vector<Edge<T>>::iterator ite = (v->adj).end();
    for (; it != ite; it++) {
        if (it->dest->processing == true)
            numCycles++;
        if (it->dest->visited == false) {
            dfsVisit(it->dest);
        }
    }
    v->processing = false;
}

template <class T> vector<T> Graph<T>::topologicalOrder() {
    // vector com o resultado da ordenacao
    vector<T> res;

    // verificar se � um DAG
    if (getNumCycles() > 0) {
        // cout << "Ordenacao Impossivel!" << endl;
        return res;
    }

    // garantir que os "indegree" estao inicializados corretamente
    this->resetIndegrees();

    queue<Vertex<T> *> q;

    vector<Vertex<T> *> sources = getSources();
    while (!sources.empty()) {
        q.push(sources.back());
        sources.pop_back();
    }

    // processar fontes
    while (!q.empty()) {
        Vertex<T> *v = q.front();
        q.pop();

        res.push_back(v->info);

        for (unsigned int i = 0; i < v->adj.size(); i++) {
            v->adj[i].dest->indegree--;
            if (v->adj[i].dest->indegree == 0)
                q.push(v->adj[i].dest);
        }
    }

    // testar se o procedimento foi bem sucedido
    if (res.size() != vertexSet.size()) {
        while (!res.empty())
            res.pop_back();
    }

    // garantir que os "indegree" ficam atualizados ao final
    this->resetIndegrees();

    return res;
}

template <class T> vector<T> Graph<T>::getPath(const T &origin, const T &dest) {

    list<T> buffer;
    Vertex<T> *v = getVertex(dest);

    // cout << v->info << " ";
    buffer.push_front(v->info);
    while (v->path != nullptr && v->path->info != origin) {
        v = v->path;
        buffer.push_front(v->info);
    }
    if (v->path != nullptr)
        buffer.push_front(v->path->info);

    vector<T> res;
    while (!buffer.empty()) {
        res.push_back(buffer.front());
        buffer.pop_front();
    }

    if(this->hasConnection(res[0], res[1]))
        return res;
    reverse(res.begin(), res.end());
    return res;
}

template <class T> void Graph<T>::unweightedShortestPath(const T &s) {

    for (unsigned int i = 0; i < vertexSet.size(); i++) {
        vertexSet[i]->path = nullptr;
        vertexSet[i]->dist = INT_INFINITY;
    }

    Vertex<T> *v = getVertex(s);
    v->dist = 0;
    queue<Vertex<T> *> q;
    q.push(v);

    while (!q.empty()) {
        v = q.front();
        q.pop();
        for (unsigned int i = 0; i < v->adj.size(); i++) {
            Vertex<T> *w = v->adj[i].dest;
            if (w->dist == INT_INFINITY) {
                w->dist = v->dist + 1;
                w->path = v;
                q.push(w);
            }
        }
    }
}

#endif /* GRAPH_H_ */
