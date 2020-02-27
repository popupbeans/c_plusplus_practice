// Dijkstra Algorithm - Practice

#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
using namespace std;

class DirectedEdge {
    int v, w;
    double weight;
public:
    DirectedEdge(int v, int w, double weight)
    {
        this->v = v;
        this->w = w;
        this->weight = weight;
    }
    int from()					{ return v; }
    int to()					{ return w; }
    double get_weight()				{ return weight; }
    void print(void)
    {
        cout << v << " -- " << weight << " --> " << w << endl;
    }
};

class EdgeWeightedDigraph {
    int n;
    unordered_map< int, vector<DirectedEdge *> > adj;
    unordered_map<DirectedEdge *, double> edges;

public:
    EdgeWeightedDigraph(int n)	{ this->n = n; }
    void AddEdge(DirectedEdge *e)
    {
        int v = e->from();
        int w = e->to();
        adj[v].push_back(e); 
        edges[e] = e->get_weight();
    }
    vector<DirectedEdge *> *get_adj(int v)	{ return &adj[v]; }
    int get_edges()				{ return edges.size(); }
    int get_vertice()				{ return n; }
};

class ShortestPath {
    int n;
    double *distTo;
    DirectedEdge **edgeTo;
    map<double, int> pq;

public:
    ShortestPath(EdgeWeightedDigraph dg, int s)
    {
        int v = s;
        n = dg.get_vertice();
        distTo = new double[n];
        edgeTo = new DirectedEdge*[n];

        for ( int i = 0 ; i < dg.get_vertice() ; i++ ) {
            distTo[i] = 9999;
        }

        pq[0.0] = v;
        distTo[v] = 0;
        edgeTo[v] = NULL;

        int count = 0;

        while ( !pq.empty() ) {

            v = pq.begin()->second;
            pq.erase(pq.begin());
            count++;
            
            vector<DirectedEdge *> *adj = dg.get_adj(v);
            vector<DirectedEdge *>::iterator itr = adj->begin();

            while ( itr != adj->end() ) {
                relex((*itr));
                itr++;
            }            
        }
        cout << count << endl;
    }
    void relex(DirectedEdge *e)
    {
        int v = e->from();
        int w = e->to();

        if ( distTo[w] > distTo[v] + e->get_weight() ) {
            pq.erase(distTo[w]);

            distTo[w] = distTo[v] + e->get_weight();
            cout << "dist to w : " << w << " " << distTo[w] << endl;
            edgeTo[w] = e;

            pq[distTo[w]] = w;
        }
    }
    void print()
    {
        for ( int i = 0 ; i < n ; i++ ) {
            cout << i << " : " << distTo[i] << endl;
        }
    }
    ~ShortestPath()
    {
        delete distTo;
        delete edgeTo;
    }
};

void test(void)
{
    DirectedEdge *e1 = new DirectedEdge(0,1,5.0);
    DirectedEdge *e2 = new DirectedEdge(0,4,9.0);
    DirectedEdge *e3 = new DirectedEdge(0,7,8.0);
    DirectedEdge *e4 = new DirectedEdge(1,2,12.0);
    DirectedEdge *e5 = new DirectedEdge(1,3,15.0);

    DirectedEdge *e6 = new DirectedEdge(1,7,4.0);
    DirectedEdge *e7 = new DirectedEdge(2,3,3.0);
    DirectedEdge *e8 = new DirectedEdge(2,6,11.0);
    DirectedEdge *e9 = new DirectedEdge(3,6,9.0);
    DirectedEdge *e10 = new DirectedEdge(4,5,4.0);

    DirectedEdge *e11 = new DirectedEdge(4,6,20.0);
    DirectedEdge *e12 = new DirectedEdge(4,7,5.0);
    DirectedEdge *e13 = new DirectedEdge(5,2,1.0);
    DirectedEdge *e14 = new DirectedEdge(5,6,13.0);
    DirectedEdge *e15 = new DirectedEdge(7,5,6.0);

    DirectedEdge *e16 = new DirectedEdge(7,2,7.0);

    EdgeWeightedDigraph g(8);

    g.AddEdge(e1);
    g.AddEdge(e2);
    g.AddEdge(e3);
    g.AddEdge(e4);
    g.AddEdge(e5);

    g.AddEdge(e6);
    g.AddEdge(e7);
    g.AddEdge(e8);
    g.AddEdge(e9);
    g.AddEdge(e10);

    g.AddEdge(e11);
    g.AddEdge(e12);
    g.AddEdge(e13);
    g.AddEdge(e14);
    g.AddEdge(e15);

    g.AddEdge(e16);

    ShortestPath sp(g,0);
    sp.print();

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


