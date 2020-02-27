// Radix Sort, MSD (Most Significant Digit First)
// Lower case characters only

#include <string>
#include <iostream>
using namespace std;

int charAt(string buf[], int index, int digit);
void radix_sort(string buf[], int num);
void radix_sort(int digit, string buf[], string aux[], int start, int end);
void print(string buf[], int num);

int charAt(string buf[], int index, int digit)
{
    if ( buf[index].length() < (digit + 1) ) return -1;
    return buf[index].at(digit);
}

void radix_sort(string buf[], int num)
{
    string *aux = new string[num];
    radix_sort(0,buf,aux,0,num);
    delete[] aux;
}

void radix_sort(int digit, string buf[], string aux[], int start, int end)
{
    if ( (end - 1) <= start) return;

    int *count = new int[256 + 2];
    for ( int i = 0 ; i <= 257 ; i++ ) count[i] = 0;
    for ( int j = start ; j < end ; j++ ) count[charAt(buf,j,digit) - 'a' + 2]++;
    for ( int k = 2 ; k <= 257 ; k++ ) count[k] += count[k - 1];
    for ( int l = start ; l < end ; l++ ) {
        aux[start + count[charAt(buf,l,digit) - 'a' + 1]++] = buf[l];
    }
    for ( int m = start ; m < end ; m++ ) buf[m] = aux[m];

    for ( int n = 1 ; n <= 256 ; n++ ) {
        radix_sort(digit + 1, buf, aux, start + count[n-1], start + count[n]);
    }

    delete[] count;
}

void print(string buf[], int num)
{
    for ( int i = 0; i < num ; i++ ) {
        cout << i + 1 << " : " << buf[i] << endl;
    }
}

void test(void)
{
    string buf[] = {
        "abcrekh","zbfdjkbhd","ffedfsd","ghksjbw","ofkjkhhjhkg",
        "hjvjqgjhgdf","wskdkhdkjhb","hijkqhjkhdfl","gak","c",
        "w","i","aaaaaaa","hldjkhwdjkj","rakqjhwkhqkj",
        "khqkhakhkhhgq","rlkjdkwhj","iukhkshdkk","gkjhksjhdkjh","gkhksjdhkshhb",
        "zjkhkhakhakhaj","akjhkasiushiauhihkqhgj","akjhkqhakjhjb","skjhkajhafj"
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