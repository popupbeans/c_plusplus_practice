// Collect Words with Prefix using Trie

#include <iostream>
#include <unordered_map>
#include <queue>
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
        node *tmp = get(str,0,&root, NULL);

        if ( !tmp ) return -1;
        return tmp->get_value();
    }
    node *get(string str, int digit, node *link, string *hit)
    {
        if ( !link->get_next(str[digit]) ) return NULL;

        if ( hit && link->get_next(str[digit])->get_value() >= 0 ) {
            *hit = str.substr(0,digit + 1);
        }

        if ( str.length() == (digit + 1) ) {
            return link->get_next(str[digit]);
        }
        return get(str, digit + 1, link->get_next(str[digit]), hit);
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

    void traverse(queue<string> *q)
    {
        traverse(&root, "", q);
    }
    void traverse(node *link, string prefix, queue<string> *q)
    {
        if ( link->get_value() >= 0 ) q->push(prefix);
        auto itr = link->get_linked()->begin();
        while ( itr != link->get_linked()->end() ) {
            traverse(itr->second, prefix + itr->first, q);
            itr++;
        }        
    }

    void keysWithPrefix(string prefix, queue<string> *q)
    {
        node *tmp = get(prefix,0,&root, NULL);
        traverse(tmp, prefix, q);
    }

    string getLongestPrefix(string key)
    {
        string hit;
        node *tmp = get(key,0,&root, &hit);

        return hit;
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
    string str13 = "history";

    test.put(str1,1);
    test.put(str2,2);
    test.put(str3,3);
    test.put(str4,4);
    test.put(str5,5);
    test.put(str6,6);
    test.put(str7,7);
    test.put(str8,8);
    test.put(str9,9);
    test.put(str10,10);
    test.put(str11,11);
    test.put(str12,12);
    test.put(str13,13);

    queue<string> q;
    test.traverse(&q);

    cout << "== traverse test ==" << endl;
    while ( !q.empty() ) {
        cout << q.front() << endl;
        q.pop();
    }

    string s = "ha";
    cout << "== prefix search test with " << s << " ==" << endl;
    test.keysWithPrefix(s,&q);
    while ( !q.empty() ) {
        cout << q.front() << endl;
        q.pop();
    }

    s = "s";
    cout << "== prefix search test with " << s << " ==" << endl;
    test.keysWithPrefix(s,&q);
    while ( !q.empty() ) {
        cout << q.front() << endl;
        q.pop();
    }

    s = "superwoman";
    cout << "== find longest prefix of " << s << " ==" << endl;
    cout << test.getLongestPrefix(s) << endl;

    s = "historybook";
    cout << "== find longest prefix of " << s << " ==" << endl;
    cout << test.getLongestPrefix(s) << endl;
}

int main(void)
{
    test();
    return 0;
}



