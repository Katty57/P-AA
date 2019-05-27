#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

struct vertex
{
    int num_pat = 0;
    vector <int> arr;
    int suff_link = -1;
    char symbol;
    int parent = -1;
};

class bor
{
public:
    void make_suf(int num){
        int i = num;
        int tmp = bohr[i].parent;
        while(true){
            if(tmp == 0){
                bohr[i].suff_link = 0;
                break;
            }
            int k = 0;
            for(k = 0; k < bohr[bohr[tmp].suff_link].arr.size(); k++){
                if(bohr[bohr[bohr[tmp].suff_link].arr[k]].symbol == bohr[i].symbol){
                    bohr[i].suff_link = bohr[bohr[tmp].suff_link].arr[k];
                    break;
                }
            }
            if(k == bohr[bohr[tmp].suff_link].arr.size()){
                tmp = bohr[tmp].parent;
            }else
                break;
        }
    }
    bor(string p)
    {
        struct vertex root;
        root.suff_link = 0;
        root.parent = 0;
        bohr.push_back(root);
        pats.push_back(p);
        int it;
        int curr_v = 0;
        for(int j = 0; j < p.length(); j++)
        {
            if(bohr[curr_v].arr.empty())
            {
                it = 0;
            }else{
                int k;
                for(k = 0; k < bohr[curr_v].arr.size(); k++){
                    if(bohr[bohr[curr_v].arr[k]].symbol == p[j]){
                        it = bohr[curr_v].arr[k];
                        break;
                    }
                }
                if(k == bohr[curr_v].arr.size() &&  bohr[bohr[curr_v].arr[k - 1]].symbol != p[j]){
                    it = -1;
                }
            }
            if(it == 0 || it == -1)
            {
                struct vertex node;
                node.symbol = p[j];
                node.parent = curr_v;
                bohr.push_back(node);
                bohr[curr_v].arr.push_back(bohr.size() - 1);
                it = bohr.size() - 1;
            }
            curr_v = it;
            if(j == p.size() - 1){
                bohr[curr_v].num_pat = 1;
            }
        }
        for(int i = 1; i < bohr.size(); i++){
            make_suf(i);
        }
    }
    void cout_prev(int index, int str_index){
        while(index != 0){
            if(bohr[index].num_pat != 0){
                cout  << str_index + 2 - pats[bohr[index].num_pat - 1].length() << endl;
            }
            index = bohr[index].suff_link;
        }
    }
    void searching(string t, char joker)
    {
        int cur_v = 0;
        for(int i = 0; i < t.length(); i++){
            int j = -1;
            int tmp = cur_v;
            for(j = 0; j < bohr[cur_v].arr.size(); j++)
            {
                if(bohr[bohr[cur_v].arr[j]].symbol == t[i]){
                    if(bohr[bohr[cur_v].arr[j]].num_pat != 0){
                        cout << i + 2 - pats[bohr[bohr[cur_v].arr[j]].num_pat - 1].length() << endl;
                    }
                    cout_prev(bohr[bohr[cur_v].arr[j]].suff_link, i);
                    tmp = bohr[cur_v].arr[j];
                    break;
                }else if(bohr[bohr[cur_v].arr[j]].symbol == joker)
                {
                    if(bohr[bohr[cur_v].arr[j]].num_pat != 0){
                        cout << i + 2 - pats[bohr[bohr[cur_v].arr[j]].num_pat - 1].length() << endl;
                    }
                    cout_prev(bohr[bohr[cur_v].arr[j]].suff_link, i);
                    tmp = bohr[cur_v].arr[j];
                    break;
                }
            }
            if(j == bohr[cur_v].arr.size()){
                if(cur_v != 0){
                    tmp = bohr[cur_v].suff_link;
                    i--;
                }
            }else
                if(bohr[cur_v].arr.empty()){
                    tmp = bohr[cur_v].suff_link;
                    i--;
                }
            cur_v = tmp;
        }
    }
private:
    vector<struct vertex> bohr;
    vector<string> pats;
};

int main()
{
    string t,p;
    char j;
    cin >> t >> p >> j;
    bor B(p);
    B.searching(t, j);
    return 0;
}
