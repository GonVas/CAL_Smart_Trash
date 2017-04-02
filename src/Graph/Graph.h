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

using namespace std;

template <class T> class Edge;
template <class T> class Graph;

const int NOT_VISITED = 0;
const int BEING_VISITED = 1;
const int DONE_VISITED = 2;
const int INT_INFINITY = std::numeric_limits<int>::max();

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
    Vertex<T> * getDest(){
        return this->dest;
    }

    //===============================
    inline bool operator==(const Edge<T> &rhs) {
        if (this->weight == rhs.weight && this->dest == rhs.dest)
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
