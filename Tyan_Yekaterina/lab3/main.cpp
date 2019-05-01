#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

class flow
{
public:
    flow(int n = 0)
    {
        edge = new int*[n];
        for(int i = 0; i < n; i++)
        {
            edge[i] = new int[n];
            for(int j = 0; j < n; j++)
            {
                edge[i][j] = 0;
            }
        }
        up_down_edge = new int*[n];
        for(int i = 0; i < n; i++)
        {
            up_down_edge[i] = new int[n];
            for(int j = 0; j < n; j++)
            {
                up_down_edge[i][j] = 0;
            }
        }
        char s, t;
        cin >> s;
        cin >> t;
        if(s == t)
        {
            cout << "Wrong input!" << endl;
            return;
        }
        vertex.push_back(s);
        vertex.push_back(t);
        for(int i = 0; i < n; i++)
        {
            char b, e;
            int w, j, k;
            cin >> b >> e >> w;
            if(b != e)
            {
                j = find(vertex.begin(), vertex.end(), b) - vertex.begin();
                if(j == vertex.size())
                {
                    vertex.push_back(b);
                    j = vertex.size() - 1;
                }
                k = find(vertex.begin(), vertex.end(), e) - vertex.begin();
                if(k == vertex.size())
                {
                    vertex.push_back(e);
                    k = vertex.size() - 1;
                }
                edge[j][k] = w;
                
            }else{
                cout << "Wrong input!" << endl;
                return;
            }
        }
        edge_out = new int*[n];
        for(int i = 0; i < n; i++)
        {
            edge_out[i] = new int[n];
            for(int j = 0; j < n; j++){
                edge_out[i][j] = -1;
                if(edge[i][j] > 0)
                {
                    edge_out[i][j] = 0;
                }
            }
        }
    }
    
    void path(vector<int> &p)
    {
        bool vis[vertex.size()];
        for(int i = 0; i < vertex.size(); i++)
            vis[i] = false;
        stack<int> indiv;
        indiv.push(0);
        do
        {
            vector<char> arr;
            int top_vertex = indiv.top();
            p.push_back(top_vertex);
            if(top_vertex == 1)
                return;
            vis[top_vertex] = true;
            int k = arr.size();
            for(int i = 1; i < vertex.size(); i++)
            {
                if(vis[i] == false && (edge[top_vertex][i] > 0 || up_down_edge[top_vertex][i] > 0))
                {
                    arr.push_back(vertex[i]);
                }
            }
            if(arr.size() == k)
            {
                int i = indiv.top();
                indiv.pop();
                p.pop_back();
                while(!indiv.empty() && !p.empty() && (edge[indiv.top()][i] > 0 || up_down_edge[indiv.top()][i] > 0))
                {
                    if(indiv.top() == 1)
                    {
                        if(p.back() != 1)
                            p.push_back(1);
                        return;
                    }
                    p.pop_back();
                    i = indiv.top();
                    indiv.pop();
                }
            }else{
                sort(arr.begin(), arr.end());
                for(int i = arr.size() - 1; i >= 0; i--)
                {
                    indiv.push(find(vertex.begin(), vertex.end(), arr[i]) - vertex.begin());
                }
            }
        }
        while(!indiv.empty());
        return;
    }
    
    int ford_fulk()
    {
        vector<int> p;
        int res_flow = 0;
        do
        {
            vector<int> edge_flow;
            p.clear();
            path(p);
            if(p.empty())
                return res_flow;
            for(int i = 0; i < p.size() - 1; i++)
            {
                if(edge[p[i]][p[i + 1]] > 0)
                    edge_flow.push_back(edge[p[i]][p[i + 1]]);
                else
                    edge_flow.push_back(up_down_edge[p[i]][p[i + 1]]);
            }
            int minim = (*min_element(edge_flow.begin(), edge_flow.end()));
            res_flow += minim;
            for(int i = 0; i < p.size() - 1; i++)
            {
                up_down_edge[p[i + 1]][p[i]] += minim;
                edge[p[i]][p[i + 1]] -= minim;
                if(edge[p[i]][p[i + 1]] < 0)
                {
                    edge[p[i]][p[i + 1]] = -1;
                    up_down_edge[p[i + 1]][p[i]] = -1;
                }
                if(edge_out[p[i]][p[i + 1]] != -1)
                    edge_out[p[i]][p[i + 1]] +=minim;
                if(edge[p[i]][p[i + 1]] == 0){
                    edge[p[i]][p[i + 1]] = -1;
                    up_down_edge[p[i + 1]][p[i]] = -1;
                }
            }
        }
        while(!p.empty());
        return res_flow;
    }
    
    void print(int n)
    {
        for(int i = 0; i< vertex.size(); i++)
        {
            for(int j =0 ; j < vertex.size(); j++)
            {
                if(edge_out[i][j] > -1)
                {
                    if(edge_out[j][i] > 0)
                    {
                        edge_out[j][i] = abs(edge_out[j][i] - edge_out[i][j]);
                        edge_out[i][j] = 0;
                    }
                    auto tmp = make_tuple(vertex[i], vertex[j], edge_out[i][j]);
                    out_in.push_back(tmp);
                }
            }
        }
        sort(out_in.begin(), out_in.end());
        for(int i = 0; i < n; i++)
        {
            cout << get<0>(out_in[i]) << ' ' << get<1>(out_in[i]) << ' ' << get<2>(out_in[i]) << endl;
        }
    }
    
    ~flow()
    {
        int n = sizeof(edge[0]) /  sizeof(int);
        for(int i = 0; i < n; i++)
        {
            delete edge[i];
        }
        delete edge;
        for(int i = 0; i < n; i++)
        {
            delete up_down_edge[i];
        }
        delete up_down_edge;
        for(int i = 0; i < n; i++)
        {
            delete edge_out[i];
        }
        delete edge_out;
    }
    
private:
    int** edge;
    int** up_down_edge;
    vector< char > vertex;
    int** edge_out;
    vector<tuple<char,char,int>> out_in;
};

int main()
{
    int n;
    cin >> n;
    flow F(n);
    int max_flow = F.ford_fulk();
    if(max_flow == 0)
        return 0;
    cout << max_flow << endl;
    F.print(n);
    return 0;
}
