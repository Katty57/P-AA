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

void kmp(string pat, string txt, int* pi)
{
    preFunc(pat, pi);
    vector<int> answer;
    int i = 0, j = 0;
    while(i < txt.length())
    {
        if(txt[i] == pat[j])
        {
            i++;
            j++;
        }
        if(j == pat.length())
        {
            answer.push_back(i - j);
            j = pi[j - 1];
        }else
            if(txt[i] != pat[j])
            {
                if(j != 0)
                    j = pi[j - 1];
                else
                {
                    i++;
                }
            }
    }
    if(answer.empty())
        cout << "-1";
    else
        for(int m = 0; m < answer.size(); m++){
            cout << answer[m];
            if(m != answer.size() - 1)
                cout << ',';
        }
    cout << endl;
}

int main()
{
    string pat, txt;
    cin >> pat >> txt;
    int pi[pat.length()];
    if(pat.length() > txt.length())
        cout << "-1" << endl;
    else
        kmp(pat, txt, pi);
    return 0;
}
