// Suffix Sort for longest common substring detection
// Use Radix Sort (MSD)
// Lower case characters only

#include <string>
#include <iostream>
using namespace std;

string my_strcpy(string buf, int shift_digit);
int charAt(string buf[], int index, int digit);
void radix_sort(string buf[], int num, int len);
void radix_sort(int digit, string buf[], string aux[], int start, int end);
void print(string buf[], int num);
int lcw(string a, string b);
void suffix_sort(string buf);

string my_strcpy(string buf, int shift_digit)
{
    int len = buf.length();   
    return buf.substr(shift_digit,len - shift_digit);
}

int charAt(string buf[], int index, int digit)
{
    if ( buf[index].length() < (digit + 1) ) return -1;
    return buf[index].at(digit) - 'a';
}

void radix_sort(string buf[],int num)
{
    string *aux = new string[num];
    radix_sort(0,buf,aux,0,num);
    delete[] aux;
}

void radix_sort(int digit, string buf[], string aux[], int start, int end)
{
    if ( (end - 1) <= start) return;

    int *count = new int[64];
    for ( int i = 0 ; i <= 63 ; i++ ) count[i] = 0;
    for ( int j = start ; j < end ; j++ ) count[charAt(buf,j,digit) + 2]++;
    for ( int k = 2 ; k <= 63 ; k++ ) count[k] += count[k - 1];
    for ( int l = start ; l < end ; l++ ) {
        aux[start + count[charAt(buf,l,digit) + 1]++] = buf[l];
    }
    for ( int m = start ; m < end ; m++ ) buf[m] = aux[m];

    for ( int n = 1 ; n <= 63 ; n++ ) {
        radix_sort(digit + 1, buf, aux, start + count[n-1], start + count[n]);
    }

    delete[] count;
}

void print(string buf[], int num)
{
    for ( int i = 0; i < num ; i++ ) {
        cout << i + 1 << " : " << buf[i].length() << " : " << buf[i] << endl;
    }
}

int lcw(string a, string b)
{
    int shorter = a.length() > b.length() ? b.length() : a.length();

    int i = 0;
    for ( ; i < shorter ; i++ ) {
        if ( a[i] != b[i] ) break;
    }

    return i;
}

void suffix_sort(string buf)
{
    int buf_len = buf.length();

    string *bin = new string[buf_len];

    for ( int i = 0 ; i < buf_len ; i++ ) {
        bin[i] = my_strcpy(buf,i);
    }

    radix_sort(bin,buf_len);

    int max = 0;
    string max_string;
    for ( int i = 0 ; i < buf_len - 1 ; i++ ) {
        int common_len = lcw(bin[i],bin[i+1]);

        if ( common_len > max ) {
            max = common_len;
            max_string = bin[i].substr(0,common_len);
        }
    }

    cout << "Longest Common Sub String : " << max_string << "(" << max_string.length() << ")" << endl;
}

void test(void)
{
    string buf = 
"gwhsvfkqjhqkjfheirugyibvsejrughviufdajhvkdshvagkjdshiwueytqitpywetgfhkwfhksjgajhasbvjsdhgfjshdgfjdhsbvhdjgsfjhsdgfjehgfureivhbesdfytbeuytbsauyfctvbeauyvbaeuiycasvaekjhtbcsuvyvbsuibvcusaybeacwvuiytvbcuerysbvwueiytsvbwueysbvweirudbhdsbhqdbvghrqdsbiqdqwwvabvbaeyvakevbaeisydvtabewiuytrwgcfgasyucgekaisufgaquwieytkasgfceliaugvwiugtaewiusshjevrgauskbvbsyevgwrabkryueabcertwyubcvkrtuwaeybvagkuaeotvbwquybvdgubevirtybnebvvvitybvywwbzxyufgcerbvrtyuiopkjhgfdsoiuytrewmjhnbgtcdgvhybtiueeeeghsbvgvwaeiugvberkuytgbevruygeyrgverliusurbveiughfeijbvefkhgkwejhfwifueqhoipwqytgfrdygftreytgfhbgvfyfuiwefbbbzbsfmfghwefghwejkqgfjhgqhvfhjwfejkfvewhjkfvehwjhfgewjhkvfehjwvfjkqwefhqvkjvhkghviufdajhvkdshvagkjdshiwueytqitpywetgfhkwfhksjgajhasbvjsdhgfjshdgfjdhsbvhdjgsfjhsdgfjehgfureivhbesdfytbeuytbsauyfjgzhahqwertyuioasdfghjzxcvbnwertyuiopoiuyghjkjhgfghjmnbvcjhgfjhgfuytrhgfdhgfdtreejrgeiuhgfjdkfhgueirhfgebdgfjehgfureivhbeurbveiughfeijbvefkhgkwejhfwifueqhoipwqyfuiwefbbbzbsfmfghwefghwejkqgfjhgqhvfhjwfejkfvewhjkfvehwjhfgewjhkvfehjwjvbnvejrughviufdajhvkdshvagkjdshiwueytqitpywetgfhkwfhksjgajhasbvjsdhgfjshdgfjdhsbvhdjgsfjhsdgfjehgfureivhbesdfytbeuytbsauyfctvbeauyvbaeuiycasvaekjhtbcsuvyvbsuibvcusaybeacwvuiytvbcuerysbvwueiytsvbwueysbvweirudbhdsbhqdbvghrqdsbiqdqwwvabvbaeyvakevbaeisydvtabewiuytrwgcfgasyucgekaisufgaquwieytkasgfceliaugvwiugtaewiusshjevrgauskbvbsyevgwrabkryueabcertwyubcvkrtuwaeybvagkuaeotvbwquybvdgubevirtybnebvvvitybvywwbzxyufgcerbvrtyuiopkjhgfdsoiuytrewmjhnbgtcdgvhybtiueeeeghsbvgvwaeiugvberkuytgbevruygeyrgverliusurbveiughfeijbvefkhgkwejhfwifueqhoipwqytgfrdygftreytgfhbgvfyfuiwefbbbzbsfmfghwefghwejkqgfjhgqhvfhjwfejkfvewhjkfvehwjhfgewjhkvfehjwvfjkqwefhqvkjvhkghviufdajhvkdshvagkjdshiwueytqitpywetgfhkwfhksjgajhasbvjsdhgfjshdgfjdhsbvhdjgsfjhsdgfjehgfureivhbesdfytbeuytbsauyfctvbeauyvbaeuiycasvaekjhtbcsuvyvbsuibvcusaybeacwvuiytvbcuerysbvwueiytsvbwueysbvweirudbhdsbhqdbvghrqdsbiqdqwwvabvbaeyvakevbaeisydvtabewiuytrwgcfgasyucgekaisufgaquwieytkasgfceliaugvwiugtaewiusshjevrgauskbvbsyevgwrabkryueabcertwyubcvkrtuwaeybvagkuaeotvbwquybvdgubevirtybnebvvvitybqfvehjwvfhjewvfehwjfvuybqueybgktubvuweyvbwuyesbcysebcvuyesrtbhertwepqvcbwxcvdyzbveuigbeurgiwuerufgwiewbiuquetrewtperugreuigbverub";

    suffix_sort(buf);
}

int main(void)
{
    test();
    return 0;
}