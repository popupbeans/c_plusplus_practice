// Detect Cyclic Rotation in Linear time using KMP algorithm
// Deterministic Finite State Automata version

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

class pattern_matching {
    string pattern;
    int pattern_length;
    unordered_map<char, vector<int> > dfs;    
public:
    pattern_matching(string pattern)
    {
        this->pattern = pattern;
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

    int rotation_detection(string text)
    {
        if ( pattern_length != text.length() ) return 0;

        int state = 0;
        for ( int i = 0 ; i < text.length() ; i++ ) {
            if ( dfs.find(text[i]) == dfs.end() ) {
                state = 0;
                continue;
            }
            state = dfs[text[i]][state];
        }
        if ( state == pattern_length || state == 0 ) return 0;

        if ( pattern[state] != text[0] ) return 0;

        int prefix_length = text.length() - state;

        for ( int j = 0 ; j < prefix_length ; j++ ) {
            if ( dfs.find(text[j]) == dfs.end() ) {
                return 0;
            }
            state = dfs[text[j]][state];
        }
        if ( state == text.length() ) return 1;

        return 0;
    }
};

void test(void)
{
    string text = "helloworld";
    pattern_matching test("worldhello");
    cout << "Cyclic Rotation Detected (1 : Yes, 0 : No) : " << test.rotation_detection(text) << endl;
}

int main(void)
{
    test();
    return 0;
}

