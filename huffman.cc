// Huffman encoding
// Lower case characters only

#include <iostream>
#include <string>
#include <map>
#include <queue>
using namespace std;

#define R 32

class node {
    char ch;
    int freq;
    node *left;
    node *right;
public:
    node(char ch, int freq, node *left, node *right)
    {
        this->ch = ch;
        this->freq = freq;
        this->left = left;
        this->right = right;
    }
    int is_leaf()	{ return this->left == NULL && this->right == NULL; }
    int get_freq()	{ return this->freq; }
    char get_ch()	{ return this->ch; }
    node *get_left()	{ return left; }
    node *get_right()	{ return right; }
};

class huffman {
    int frequency[R];
    node *root;
public:
    huffman(string str)
    {
        get_frequency(str);
        root = gen_huffman_trie(str);
    }
    ~huffman()
    {
        delete_huffman(root);
    }
    void delete_huffman(node *p)
    {
        if (p) {
            delete_huffman(p->get_left());
            delete_huffman(p->get_right());
            delete p;
        }
    }
    void get_frequency(string str)
    {
        for ( int i  = 0 ; i < R ; i ++ ) {
            frequency[i] = 0;
        }
        for ( int j = 0 ; j < str.length() ; j++ ) {
            frequency[str[j] - 'a']++;
        }
    }
    node *gen_huffman_trie(string str)
    {
        multimap<int, node *> pq;

        for ( int i = 0 ; i < R ; i++ ) {
            if ( frequency[i] > 0 ) 
                pq.insert(pair<int, node *>(frequency[i],new node(i+'a',frequency[i],NULL,NULL)));
        }
        while ( pq.size() > 1 ) {
            multimap<int, node *>::iterator itr_x = pq.begin();
            node *x = itr_x->second;
            pq.erase(itr_x);
            multimap<int, node *>::iterator itr_y = pq.begin();
            node *y = itr_y->second;
            pq.erase(itr_y);
            
            int freq_sum = x->get_freq() + y->get_freq();
            pq.insert(pair<int, node *>(freq_sum,new node('\0',freq_sum,x,y)));
        }

        return pq.begin()->second;
    }
    void print_huffman()
    {
        queue<int> q;
        print_huffman(root->get_left(),0,q);
        print_huffman(root->get_right(),1,q);
    }
    void print_huffman(node *p, int bit, queue<int> q)
    {
        q.push(bit);
        if ( p->is_leaf() ) {
            cout << p->get_ch() << "(" << frequency[p->get_ch() - 'a'] << ") : ";
            int length = q.size();
            for ( int i = 0 ; i < length ; i++ ) {
                int b = q.front();
                q.pop();
                cout << b;
                q.push(b);                
            }
            cout << endl;
        }
        else {
            print_huffman(p->get_left(),0,q);
            print_huffman(p->get_right(),1,q);
        }
        q.pop();
    }
};

void test(void)
{
    huffman test("abracdabrdaabracdbraz");
    test.print_huffman();
}

int main(void)
{
    test();
    return 0;
}
