// Minimun Spanning Tree - Practice

#include <unordered_map>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

class edge {
    int v,w;
    double weight;
public:
    edge(int v, int w, double weight)	{ this->v = v; this->w = w; this->weight = weight; }
    int either()			{ return v; }
    int another(int v)			{ return (v == this->w) ? this->v : this->w;  }
    int compareTo(edge *that)
    {
        if (this->weight < that->weight) return -1;
        else if (this->weight < that->weight) return 1;

        return 0;
    }
    double get_weight()
    {
        return weight;
    }
    edge *get_edge()
    {
        return this;
    }
    void print()
    {
        cout << v << " " << w << " " << endl;
    }
};

class graph {
    int v;
    unordered_map< int, vector<edge *> > adj;
    vector<edge *> edges;
public:
    graph(int v)
    {
        this->v = v;
    }
    ~graph()
    {

    }
    void addEdge(edge *e)
    {
        int v = e->either();
        int w = e->another(v);

        adj[v].push_back(e);
        adj[w].push_back(e);

        edges.push_back(e);
    }

    vector<edge *> *get_adj(int v)
    {
        return &adj[v];
    }

    vector<edge *> *get_edges()
    {
        return &edges;
    } 
    int vertex()
    {
        return adj.size();
    }
    int e()
    {
        return edges.size();
    }
};

class Prim_Lazy_MST {
    map<edge *, double> pq;  // binary heap
    int *marked;
    queue<edge *> mst;       // array
public:
    Prim_Lazy_MST(graph g)
    {
        marked = new int[g.vertex()];

        for ( int i = 0 ; i < g.vertex() ; i++ )
            marked[i] = 0;

        visit(g,0);

        while ( !pq.empty() && mst.size() < (g.vertex() - 1) ) {
            map<edge *, double>::iterator itr = pq.begin();
            int v = itr->first->either();
            int w = itr->first->another(v);

            pq.erase(itr->first);

            if ( marked[v] && marked[w] ) continue;
            mst.push(itr->first);
            if ( !marked[v] ) visit(g,v);
            if ( !marked[w] ) visit(g,w);
        }
    }
    void visit(graph g, int v)
    {
        vector<edge *> *edges = g.get_adj(v);
        vector<edge *>::iterator itr = edges->begin();

        marked[v] = 1;

        while (itr != edges->end()) {
            pq[*itr] = (*itr)->get_weight();
            itr++;
        }   
    }
    void print()
    {
        while (!mst.empty()) {
            edge *temp = mst.front();
            
            cout << temp->either() << " " << temp->another(temp->either()) << " " << temp->get_weight() << endl;
            mst.pop();
        }
    }
};

class Prim_Eager_MST {
    map<double, int> pq;
    unordered_map<int, edge *> map_index;
    int *marked;
    queue<edge *> mst;
public:
    Prim_Eager_MST(graph g)
    {
        marked = new int[g.vertex()];

        for ( int i = 0 ; i < g.vertex() ; i++ )
            marked[i] = 0;

        visit(g,0);

        while ( !map_index.empty() && mst.size() < (g.vertex() - 1) ) {

            map<double, int>::iterator itr = pq.begin();
            int v = itr->second;
            edge *e_temp = map_index[v];
            int w = e_temp->another(v);

            pq.erase(itr->first);

            if ( marked[v] && marked[w] ) continue;

            mst.push(e_temp);

            if ( !marked[v] ) visit(g,v);
            if ( !marked[w] ) visit(g,w);
        }
    }
    void visit(graph g, int v) // update priority queue
    {
        marked[v] = 1;

        vector<edge *> *edges = g.get_adj(v);
        vector<edge *>::iterator itr = edges->begin();

        while (itr != edges->end()) { // iterate for all w connected with v
            int w = (*itr)->another(v);

            pq[(*itr)->get_weight()] = w;
      
            if ( map_index.find(w) != map_index.end() ) {
                if ( map_index[w]->get_weight() > (*itr)->get_weight() ) {
                    map_index[w] = *itr;
                }
            }
            else {
                map_index[w] = *itr;
            }
            
            itr++;
        }   
    }
    void print()
    {
        while (!mst.empty()) {
            edge *temp = mst.front();
            
            cout << temp->either() << " " << temp->another(temp->either()) << " " << temp->get_weight() << endl;
            mst.pop();
        }
    }
};

void test(void)
{
    graph g(16);

    edge *e1 = new edge(0,7,0.16);
    edge *e2 = new edge(2,3,0.17);
    edge *e3 = new edge(1,7,0.19);
    edge *e4 = new edge(0,2,0.26);
    edge *e5 = new edge(5,7,0.28);
    edge *e6 = new edge(1,3,0.29);
    edge *e7 = new edge(1,5,0.32);
    edge *e8 = new edge(2,7,0.34);
    edge *e9 = new edge(4,5,0.35);
    edge *e10 = new edge(1,2,0.36);
    edge *e11 = new edge(4,7,0.37);
    edge *e12 = new edge(0,4,0.38);
    edge *e13 = new edge(6,2,0.40);
    edge *e14 = new edge(3,6,0.52);
    edge *e15 = new edge(6,0,0.58);
    edge *e16 = new edge(6,4,0.93);

    g.addEdge(e1);
    g.addEdge(e2);
    g.addEdge(e3);
    g.addEdge(e4);
    g.addEdge(e5);
    g.addEdge(e6);
    g.addEdge(e7);
    g.addEdge(e8);
    g.addEdge(e9);
    g.addEdge(e10);
    g.addEdge(e11);
    g.addEdge(e12);
    g.addEdge(e13);
    g.addEdge(e14);
    g.addEdge(e15);
    g.addEdge(e16);

    cout << "MST by Prim Lazy algorithm" << endl;
    Prim_Lazy_MST mst1(g);
    mst1.print();

    cout << "MST by Prim Eager algorithm" << endl;
    Prim_Eager_MST mst2(g);
    mst2.print();

    delete e1;
    delete e2;
    delete e3;
    delete e4;
    delete e5;
    delete e6;
    delete e7;
    delete e8;
    delete e9;
    delete e10;
    delete e11;
    delete e12;
    delete e13;
    delete e14;
    delete e15;
    delete e16;
}

int main(void)
{
    test();
    return 0;
}

