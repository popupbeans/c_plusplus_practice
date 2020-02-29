// Trie practice
// Lower case characters only

#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

class node {
    int value;
    unordered_map<char, node *> next;
public:
    node()				{ value = -1; }
    void set_value(int value)		{ this->value = value; }
    int get_value()			{ return this->value; }
    void set_next(char c, node *link)
    {  
        next[c] = link;
    }
    node *get_next(char c)
    {
        if ( next.find(c) == next.end() ) // still child not exist
            return NULL;
        return next[c];
    }
    int get_next_num()
    {
        return next.size();
    }
    void remove(char c)
    {
        delete next[c];
        next.erase(c);
    }
    unordered_map<char, node *> *get_linked()
    {
        return &next;
    }
};

class trie {
    node root;
public:
    int put(string str, int value)
    {
        return put(str, 0, value, &root);
    }
    int put(string str, int digit, int value, node *link)
    {
        if ( !link->get_next(str[digit]) ) {
            node *tmp = new node;
            link->set_next(str[digit],tmp);
        }
        if ( str.length() == (digit + 1) ) {
            link->get_next(str[digit])->set_value(value);
            return value;
        }
        return put(str, digit + 1, value, link->get_next(str[digit]));
    }

    int get(string str)
    {
        return get(str,0,&root);
    }
    int get(string str, int digit, node *link)
    {
        if ( !link->get_next(str[digit]) ) return -1;
        if ( str.length() == (digit + 1) ) {
            return link->get_next(str[digit])->get_value();
        }
        return get(str, digit + 1, link->get_next(str[digit]));
    }

    int del(string str)
    {
        return del(str,0,&root);
    }
    int del(string str, int digit, node *link)
    {
        if ( !link->get_next(str[digit]) ) return -1; 
        if ( str.length() == (digit + 1) ) {
            if ( link->get_next(str[digit])->get_value() < 0 ) return -1;
 
            if ( !link->get_next(str[digit])->get_next_num() ) {
                link->remove(str[digit]);
                return 1;
            }
            link->get_next(str[digit])->set_value(-1);
            return 0;
        }
        int result = del(str,digit + 1, link->get_next(str[digit]));  
        if ( result <= 0 ) return result;

        if ( link->get_next(str[digit])->get_next_num() == 0 && 
             link->get_next(str[digit])->get_value() < 0 ) {
            link->remove(str[digit]);
            return 1;
        } 
        return 0;    
    }
    void rel()
    {
        rel(&root);
    }
    void rel(node *link)
    {
        auto itr = link->get_linked()->begin();
        while ( itr != link->get_linked()->end() ) {
            rel(itr->second);
            cout << itr->first << endl;
            delete itr->second;
            itr++;
        }
    }

    ~trie()
    {
        rel();
    }
};

void test(void)
{
    trie test;

    string str1 = "hello";
    string str2 = "hail";
    string str3 = "holoscope";
    string str4 = "her";
    string str5 = "his";
    string str6 = "happy";
    string str7 = "she";
    string str8 = "ship";
    string str9 = "super";
    string str10= "sea";
    string str11= "sound";
    string str12= "the";

    test.put(str1,1);
    test.put(str2,2);
    test.put(str3,3);
    test.put(str4,4);
    test.put(str6,6);
    test.put(str7,7);
    test.put(str8,8);
    test.put(str10,10);
    test.put(str12,12);

    cout << "-- put/get test --" << endl;
    cout << test.get(str1) << " <- expected : 1" << endl;
    cout << test.get(str2) << " <- expected : 2" << endl;
    cout << test.get(str3) << " <- expected : 3" << endl;
    cout << test.get(str4) << " <- expected : 4" << endl;
    cout << test.get(str5) << " <- expected : -1" << endl;
    cout << test.get(str6) << " <- expected : 6" << endl;
    cout << test.get(str7) << " <- expected : 7" << endl;
    cout << test.get(str8) << " <- expected : 8" << endl;
    cout << test.get(str9) << " <- expected : -1" << endl;
    cout << test.get(str10)<< " <- expected : 10" << endl;
    cout << test.get(str12)<< " <- expected : 12" << endl;

    test.put(str9,9);
    cout << test.get(str9) << " <- expected : 9" << endl;

    cout << "-- del test --" << endl;    
    cout << test.del(str11) << " <- expected : -1" << endl;
    cout << test.del(str10) << " <- expected : 0" << endl;
    cout << test.del(str12) << " <- expected : 1" << endl;

    cout << test.get(str10)<< " <- expected : -1" << endl;
    cout << test.get(str11)<< " <- expected : -1" << endl;
    cout << test.get(str12)<< " <- expected : -1" << endl;
}

int main(void)
{
    test();
    return 0;
}



