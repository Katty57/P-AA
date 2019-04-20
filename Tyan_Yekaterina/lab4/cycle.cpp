#include <iostream>
#include <string>
#include <vector>

using namespace std;

void preFunc(string pat, int* pi)
{
    pi[0] = 0;
    int len = 0;
    for(int i = 1; i < pat.length();)
    {
        if(pat[i] == pat[len])
        {
            pi[i] = ++len;
            i++;
        }
        else
        {
            if(len != 0)
                len = pi[len - 1];
            else
            {
                pi[i] = len;
                i++;
            }
        }
    }
}

void kmp(string pat, string txt, int* pi, int pat_len)
{
    preFunc(pat, pi);
    int i = 0, j = pi[pat.length() - 1];
    while(j <= pat_len)
    {
        if(txt[i] == pat[j])
        {
            i++;
            j++;
        }
        if(j == pat_len)
        {
            int dif;
            dif = pat_len - i;
            cout << txt.length() - dif << endl;
            return;
        }else
            if(txt[i] != pat[j])
            {
                break;
            }
    }
    cout << "-1" << endl;
}

int main()
{
    string pat, txt;
    cin >> txt >> pat;
    int pat_len = pat.length();
    pat = pat + '@' + txt;
    int* pi = new int[pat.length()];
    if(pat_len > txt.length())
        cout << "-1" << endl;
    else
        kmp(pat, txt, pi, pat_len);
    delete [] pi;
    return 0;
}
