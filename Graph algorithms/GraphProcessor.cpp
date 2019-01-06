#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <list>

using namespace std;

unordered_map<int,vector<int> > G;
unordered_map<int,bool> visited;
unordered_map<int,bool> connected_components;
int rows = 0;
unordered_map<int,vector<int> > WeightList;

void Tokenize(string line, vector<string> & tokens, string delimiters){
    string token = "";
    string OneCharString = " ";
    for (int i=0; i<line.size(); i++)
        if (find(delimiters.begin(), delimiters.end(), line[i])!=delimiters.end()) // line[i] is one of the delimiter characters
        {
            if (token != "")
                tokens.push_back(token);
            token = "";
        }
        else
        {
            OneCharString[0] = line[i];
            token +=OneCharString;
        }
    
    if (token != "")
        tokens.push_back(token);
}

vector<int> BFS(int v)
{
    vector<int> ret;
    queue<int> q;
    q.push(v);
    visited[v] = true;
    while (!q.empty()){
        int u = q.front();
        q.pop();
        ret.push_back(u);
        for (int i=0; i< WeightList[u].size(); i++){
            if (visited[WeightList[u][i]])
                continue;
            q.push(WeightList[u][i]);
            visited[WeightList[u][i]] = true;

        }
    }
    return ret;
}

bool findCycle(int main, int parent, vector<int>& cycle)
{
    visited[main] = true;
    cycle.push_back(main);
    vector<int> x = WeightList[main];
    for (int i=0; i<x.size(); i++)
    {
        if(!visited[x[i]])
        {
            if (findCycle(x[i], main, cycle))
                return true;
        }
        else if (x[i] != parent)
            return true;
    }
    return false;
}

int main(int argc, char** argv)
{
    if (argc!=2)
    {
        cout <<"Invalid Input" << endl;
        return 1;
    }
    
    fstream inf;
    inf.open(argv[1]);
    string line;
    while (getline(inf,line).good()){
        vector<string> tokens;
        Tokenize(line, tokens, " \t");
        for (int i = 0; i < tokens.size(); ++i)
        {
            int a = atoi(tokens[i].c_str());
            G[rows].push_back(a);
            if (!(a==0))
                WeightList[rows].push_back(i);
        }
        rows++;
    }
    inf.close();

    visited.clear();
    cout << "Connected components:" << endl;
    for (int i=0; i<rows; i++)
    {
        if ( connected_components[i] == false)
        {
            vector<int> children = BFS(i);
            sort (children.begin(), children.end());
            cout << "{";
            for (int i = 0; i < children.size()-1; ++i)
            {
                cout << children[i] << ",";
            }
            cout << children[children.size()-1] <<"}" <<"\n";

            for (int i=0; i<children.size(); i++)
                connected_components[children[i]] = true;
        }
    }

    visited.clear();
    vector<int> cycle;
    int i;
    for (i=0; i<rows; i++)
    {
        if (!visited[i])
        {
            if (findCycle(i, -1, cycle))
            {
                cout << "A cycle: " ;
                for (int j=0; j<cycle.size(); j++)
                {
                    cout << cycle[j] << " ";
                }
                cout << endl;
                break;
                
            }
        }
    }
    if (i == rows)
        cout << "No cycles" << endl;
    
    visited.clear();
    cout<< "Edges in minimum spanning trees:" << endl;
    for (int i = 0; i < rows; i++)
    {
        int min_weight = 500;
        int min_vertex=0;
        int T = 0;
        
        vector<int> x = G[i];
        for (int j=0; j<x.size(); j++)
        {
            if (x[j] == 0)
            {
                T++;
                continue;
            }
            if (x[j]< min_weight && (visited[i]==false || visited[T]==false))
            {
                min_vertex = T;
                min_weight = x[j];
            }
            T++;
        }
        
        if (min_weight == 500)
            continue;
        
        if(i < min_vertex)
            cout << i << " " << min_vertex << endl;
        else
            cout << min_vertex << " " << i << endl;
        
        visited[i] = true;
        visited[min_vertex] = true;
    }
    
    return 0;
}
