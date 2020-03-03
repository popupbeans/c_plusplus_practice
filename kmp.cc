// Knuth, Morris, Pratt Pattern matching algorithm
// Deterministic Finite State Automata

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

class pattern_matching {
    int pattern_length;
    unordered_map<char, vector<int> > dfs;    
public:
    pattern_matching(string pattern)
    {
        pattern_length = pattern.length();

        for ( int i = 0 ; i < pattern.length() ; i++ ) {
            if ( !dfs[pattern[i]].size() ) dfs[pattern[i]].push_back(0);
        }
        dfs[pattern[0]].at(0) = 1;

        for ( int x = 0 , j = 1 ; j < pattern.length() ; j++ ) {
            unordered_map< char, vector<int> >::iterator itr = dfs.begin();
            while ( itr != dfs.end() ) {
                char c = itr->first;
                dfs[c].push_back(0);
                dfs[c][j] = dfs[c][x];   
                itr++;
            }
            dfs[pattern[j]][j] = j + 1;
            x = dfs[pattern[j]].at(x);
        }
        
    }

    int search(string text)
    {
        int state = 0;
        for ( int i = 0 ; i < text.length() - pattern_length ; i++ ) {
            if ( dfs.find(text[i]) == dfs.end() ) {
                state = 0;
                continue;
            }
            state = dfs[text[i]][state];

            if ( state == pattern_length ) return (i - pattern_length + 1);
        }
        return -1;
    }
};

void test(void)
{
    string text = "qljhalbjkzxabababababacbfglsfighlodhbjklfkrgababacrigfgfhwkefkvwashdjvbkeaugf";
    pattern_matching test("ababac");
    cout << "Position of matched string : " << test.search(text) << endl;
}

int main(void)
{
    test();
    return 0;
}

