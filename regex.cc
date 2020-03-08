// Regular Expression
// Use nondeterministic finite state automata model 

#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
using namespace std;

class edge {
    int v, w;
public:
    edge(int v, int w)		{ this->v = v; this->w = w; }
    int from()			{ return this->v; }
    int to()			{ return this->w; }
};

class graph {
    unordered_map< int, vector<int> > adj;
    int v;
    int e;
public:
    graph(int v)		{ this->v = v; }
    void addEdge(edge *e)	{ adj[e->from()].push_back(e->to()); e++; } 
    void addEdge(int v, int w)	{ adj[v].push_back(w); e++; }
    vector<int> *get_adjs(int v){ return &adj[v]; }
    int V()			{ return this->v; }
    int E()			{ return this->e; }

    void printEdge(int v)
    {
        vector<int>::iterator itr;

        for ( itr = adj[v].begin() ; itr != adj[v].end() ; itr++ ) {
            cout << "edge " << v << " --> " << *itr << endl;
        }
    }
    void printGraph()
    {
        for ( int i = 0 ; i < V() ; i++ ) {
            printEdge(i);
        }
    }
};

class dfs {
    stack<int> st;
    int *visited;
    void dfs_inter(graph g, int v)
    {
        visited[v] = 1;
        vector<int> *adjs = g.get_adjs(v);
        vector<int>::iterator itr;

        for ( itr = adjs->begin() ; itr != adjs->end() ; itr++ ) {
            if ( !visited[*itr] ) {
                dfs_inter(g,*itr);
            }
        }
    }
public:
    dfs(graph g, int start)
    {
        visited = new int[g.V()];
        for ( int i = 0 ; i < g.V() ; i++ ) {
            visited[i] = 0;
        }
        dfs_inter(g, start);
    }
    dfs(graph g, vector<int> s) 
    {
        visited = new int[g.V()];
        for ( int i = 0 ; i < g.V() ; i++ ) {
            visited[i] = 0;
        }
        vector<int>::iterator itr;
        for ( itr = s.begin() ; itr != s.end() ; itr++ ) {
            dfs_inter(g,*itr);
        }        
    }
    ~dfs()
    {
        delete[] visited;
    }
    int get_visited(int v)	{ return visited[v]; }
};

class regex {
    graph *g;
    int M;
    string ex;
public:
    regex(string ex)
    {
        this->M = ex.length();
        g = new graph(this->M + 1);
        this->ex = ex;
        generate_nfa();
    }
    ~regex()
    {
        delete g;
    }
    void generate_nfa()
    {
        stack<int> st;
        int lp;
        int or_op;

        for ( int i = 0 ; i < M ; i++ ) {
            lp = i;

            if ( ex[i] == '(' || ex[i] == ')' || ex[i] == '*' ) {
                g->addEdge(i,i+1);
            }

            if ( ex[i] == '(' || ex[i] == '|' ) {
                st.push(i);
            }
            else if ( ex[i] == ')' ) {
                or_op = st.top();
                st.pop();

                if ( ex[or_op] == '|' ) {
                    lp = st.top();
                    st.pop();
                    g->addEdge(lp,or_op+1);
                    g->addEdge(or_op,i);
                }
                else {
                    lp = or_op;
                }
            }

            if ( i < M - 1 && ex[i+1] == '*' ) {
                g->addEdge(lp,i+1);
                g->addEdge(i+1,lp);
            }
        }
    }
    int validate(string str)
    {
        int result = 0;

        dfs *traverse = new dfs(*g,0);
        vector<int> *found = new vector<int>;

        for ( int i = 0 ; i < g->V() ; i++ ) {
            if ( traverse->get_visited(i) ) found->push_back(i);
        } 

        for ( int j = 0 ; j < str.length() ; j++ ) {   
            vector<int> temp;
            vector<int>::iterator itr;
            for ( itr = found->begin() ; itr != found->end() ; itr++ ) {
                if ( str[j] == ex[*itr] ) { 
                    temp.push_back(*itr+1);
                }
            }
            delete traverse;
            delete found;
            traverse = new dfs(*g,temp);
            found = new vector<int>;
            for ( int k = 0 ; k < g->V() ; k++ ) {
                if ( traverse->get_visited(k) ) found->push_back(k);
            }            
        }

        vector<int>::iterator itr;
        for ( itr = found->begin() ; itr != found->end() ; itr++ ) {
            if ( *itr == M ) {
                result = 1;
                break;
            }
        }        

        delete traverse;
        delete found;

        return result;
    }
    void print_nfa()
    {
        cout << "--- NFA for Regular Expression " << ex << " ---" << endl;  
        g->printGraph();
        cout << "--- End of NFA for Regular Expression " << ex << " ---" << endl;
    }
};

void test(void)
{
    regex test("((A*B|AC)D)");
    test.print_nfa();
    cout << "Validation Result : " << test.validate("AAAAABD") << " : expected -> 1" << endl;
    cout << "Validation Result : " << test.validate("BD") << " : expected -> 1" << endl;
    cout << "Validation Result : " << test.validate("ACD") << " : expected -> 1" << endl;
    cout << "Validation Result : " << test.validate("AAABCD") << " : expected -> 0" << endl;

    regex test2("((A|B)*|(C|D))");
    test2.print_nfa();
    cout << "Validation Result : " << test2.validate("ABABAB") << " : expected -> 1" << endl;
    cout << "Validation Result : " << test2.validate("ABC") << " : expected -> 0" << endl;
}

int main(void)
{
    test();
    return 0;
}

