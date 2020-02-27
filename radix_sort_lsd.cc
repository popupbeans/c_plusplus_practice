// Radix Sort, LSD (Least Significant Digit First)
// Lower case characters only

#include <string>
#include <iostream>
using namespace std;

void radix_sort(string buf[], int num);
void print(string buf[], int num);

void radix_sort(string buf[], int num)
{
    int len = buf[0].length();
    string *aux = new string[num];
    int *count = new int[256+1];

    for ( int digit = len - 1 ; digit >= 0 ; digit-- ) {
        for ( int i = 0 ; i <= 256 ; i++ ) count[i] = 0;
        for ( int j = 0 ; j < num ; j++ ) count[buf[j].at(digit) - 'a' + 1]++;
        for ( int k = 1 ; k <= 256 ; k++ ) count[k] += count[k-1];
        for ( int l = 0 ; l < num ; l++ ) {
            aux[count[buf[l].at(digit) - 'a']++] = buf[l];
        }     
        for ( int m = 0 ; m < num ; m++ ) buf[m] = aux[m];
    }
}

void print(string buf[], int num)
{
    for ( int i = 0; i < num ; i++ ) {
        cout << buf[i] << endl;
    }
}

void test(void)
{
    string buf[] = {
        "abc","zbd","ffe","ghw","ofg",
        "hdf","wiu","hiu","gab","cdh",
        "woe","ihf","owi","heg","rej",
        "hge","rlq","iue","gvi","giv",
        "zag","agg","akh","sfz"
    };
    int num = 24;

    radix_sort(buf,num);

    print(buf,num);
}

int main(void)
{
    test();
    return 0;
}
