// Maximum Flow and Min-Cut Ford-Fulkerson

#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
using namespace std;

class FlowEdge {
    int v;
    int w;
    double capacity;
    double flow;
public:
    FlowEdge(int v, int w, double capacity)
    {
        this->v = v;
        this->w = w;
        this->capacity = capacity;
        this->flow = 0;
    }

    int from()					{ return v; }
    int to()					{ return w; }
    int other(int vertex)			{ return ( vertex == v ) ? w : v; }
    double residualCapacityTo(int vertex)
    {
        if ( vertex == v ) return flow;			// backward edge
        return (capacity - flow);			// forward edge
    }
    void addResidualFlowTo(int vertex, double delta)
    {
        if 	( vertex == v ) flow -= delta;		// backward edge
        else if	( vertex == w ) flow += delta;		// forward edge
    }
};

class FlowNetwork {
    int vertices;
    int edges;
    unordered_map< int, vector<FlowEdge *> > adj;

public:
    FlowNetwork(int n)
    {
        edges = 0;
        vertices = n;
    }
    vector<FlowEdge *> *get_adj(int v)
    {
        return &adj[v];
    }
    void addEdge(FlowEdge *e)
    {
        int v = e->from();
        int w = e->to();

        adj[v].push_back(e);
        adj[w].push_back(e);

        edges++;
    }
    int get_v() 				{ return vertices; }
    int get_e()					{ return edges; }
};

class FordFulkerson {
    int *marked;
    FlowEdge **edgeTo;
    double flow_value;
public:
    FordFulkerson(FlowNetwork g, int s, int t)
    {
        flow_value = 0.0;
        marked = new int[g.get_v()];
        edgeTo = new FlowEdge*[g.get_v()];

        while (hasAugumentingPath(g,s,t)) {
            double bottle = 999.0;
    
            for ( int v = t ; v != s ; v = edgeTo[v]->other(v) ) {
                bottle = (edgeTo[v]->residualCapacityTo(v) < bottle) ? edgeTo[v]->residualCapacityTo(v) : bottle;
            }
            
            for ( int v = t ; v != s ; v = edgeTo[v]->other(v) ) {
                edgeTo[v]->addResidualFlowTo(v, bottle);
                //cout << "Visited : " << edgeTo[v]->other(v) << " " << v << endl; 
            }           
            flow_value += bottle; 
            cout << "Found bottle neck : " << bottle << " , Updated Flow : " << flow_value << endl; 
        }
    }
    int hasAugumentingPath(FlowNetwork g, int s, int t)
    {
        for ( int i = 0 ; i < g.get_v() ; i++ ) {
            marked[i] = 0;
            edgeTo[i] = NULL;
        }

        queue<int> q;

        q.push(s);
        marked[s] = 1;

        while ( !q.empty() ) { // BFS
            int v = q.front();
            q.pop();
            cout << "Dequeued : " << v << endl;

            vector<FlowEdge *> *adjs = g.get_adj(v);     
            vector<FlowEdge *>::iterator itr;

            for ( itr = adjs->begin() ; itr != adjs->end() ; itr++ ) {
                int w = (*itr)->other(v);

                if ( (*itr)->residualCapacityTo(w) > 0 && !marked[w] ) {
                    marked[w] = 1;
                    edgeTo[w] = *itr;
                    q.push(w);
                    cout << "Enqueued : " << w << endl;
                }
                else {
                    cout << "Not included : " << w << endl;
                }
            }
        }
        return marked[t];
    }
};

void test(void)
{
    FlowEdge *e1 = new FlowEdge(0,1,10);
    FlowEdge *e2 = new FlowEdge(0,5,15);
    FlowEdge *e3 = new FlowEdge(0,3,5);
    FlowEdge *e4 = new FlowEdge(1,3,4);
    FlowEdge *e5 = new FlowEdge(3,5,4);
    FlowEdge *e6 = new FlowEdge(1,2,9);
    FlowEdge *e8 = new FlowEdge(3,4,8);
    FlowEdge *e7 = new FlowEdge(1,4,15);
    FlowEdge *e9 = new FlowEdge(6,3,6);
    FlowEdge *e10 = new FlowEdge(5,6,16);
    FlowEdge *e11 = new FlowEdge(2,4,15);
    FlowEdge *e12 = new FlowEdge(4,6,15);
    FlowEdge *e13 = new FlowEdge(2,7,10);
    FlowEdge *e14 = new FlowEdge(4,7,10);
    FlowEdge *e15 = new FlowEdge(6,7,10);

    FlowNetwork g(8);

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

    FordFulkerson test(g,0,7);

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
}

int main(void)
{
    test();
    return 0;
}


