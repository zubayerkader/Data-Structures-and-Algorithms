#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class edge{
public:
	int u_; // one end of the edge
	int v_; // the other end of the edge
	int w_; // weight of the edge
	
	edge(int u, int v, int w):u_(u),v_(v),w_(w){}
	bool operator<(const edge& rhs) const { return w_>rhs.w_;}
	friend ostream & operator<<(ostream & out,const edge& e){
		out << e.u_ << " " << e.v_;
	}
};


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

void readGreaph(char* file_name, vector<vector<int>>& G, int& n){
	fstream inf;
	inf.open(file_name);

	string line;
	while (getline(inf,line).good()){
		vector<string> tokens;
		Tokenize(line, tokens, " \t");	
		if (tokens.size()==0)
			break;
		if ((n!=0)&&(tokens.size()!=n))
			break;
		n = tokens.size();
		vector<int> row;
		for (int i=0; i< tokens.size(); i++)
			row.push_back(atoi(tokens[i].c_str())); 
		G.push_back(row);
	}
	if (G.size()!=n)
		cout <<"bad graph file!" << endl;
	inf.close();
}

void DFS(int v, const vector<vector<int>>& G, int n, vector<bool>& visited, vector<int>& parent, vector<int>& ret){
	visited[v] = true;
	ret.push_back(v);
	for (int i=0; i< n; i++){
		if ((G[v][i]!=0) && (!visited[i])){
			parent[i] = v;
			DFS(i, G, n, visited, parent, ret);

		}
	}	
}

vector<int> get_reverse_path(int u, int v, const vector<vector<int>>& G, const vector<int>& parent){
	vector<int> ret;
	ret.push_back(v);
	while (v!=u){
		v = parent[v];
		// to deal with u and v in different connected components
		if (v==-1)
			break;
		ret.push_back(v);
	}
	// to deal with u and v in different connected components
	if (v==-1)
		return vector<int>();
	return ret;
}

void print_all_components(const vector<vector<int>>& G, int n){
	vector<int> output;
	vector<bool> visited;
	vector<int> parent;	
        for (int i=0; i<n; i++){
                parent.push_back(-1);
                visited.push_back(false);
        }

	cout << "Connected components:" << endl;	

	for (int i=0; i<n; i++){
		if (!visited[i]){
			vector<int> component;
			DFS(i, G, n, visited, parent, component);
			sort(component.begin(), component.end());
			cout << "{" ;
			for (int ctr=0; ctr< component.size()-1; ctr++)
				cout << component[ctr] << ",";			
			cout << component[component.size()-1] << "}" << endl;
		}			
	}
}


void print_path(int u, int v, const vector<vector<int>> & G, int n){
	vector<int> component;
        vector<bool> visited;
        vector<int> parent;
        for (int i=0; i<n; i++){
                parent.push_back(-1);
                visited.push_back(false);
        }

        DFS(u, G, n, visited, parent, component);
	vector<int> path = get_reverse_path(u, v, G, parent);
        for (int i=path.size()-1; i>=0; i--)
        	cout << path[i] << " ";
        cout << endl;
}

void Kruskal(const vector<vector<int>>& G, int n){

	vector<edge> MSF; // Minimum spanning forest
	int cycle_u = -1, cycle_v = -1;

	vector<int> component_id;
	for (int i=0; i<n; i++)
		component_id.push_back(i);

	priority_queue<edge> Q;

	for (int i=0; i<n; i++)
		for (int j=i+1; j<n; j++)
			if (G[i][j]!=0)
				Q.push(edge(i,j,G[i][j]));
			


	
	while (!Q.empty()){
		edge e = Q.top();
		Q.pop();
		int c1 = component_id[e.u_];
		int c2 = component_id[e.v_];
		if (c1!=c2){
			MSF.push_back(e);
			// merge the two components // not super-efficient!
			for (auto itr=component_id.begin(); itr!=component_id.end(); itr++)
				if (*itr == c1)
					*itr = c2;		
		}
		else{
			cycle_u = e.u_;
			cycle_v = e.v_;
		}
	}

	if (cycle_u==-1)
		cout << "No cycles" << endl;
	else{
		// remove the edge that causes a cycle from the graph. If we find a path between the two ends of that edge now, that will be a cycle!
		vector<vector<int>> G2 = G;
		G2[cycle_u][cycle_v]=0;
		G2[cycle_v][cycle_u]=0;
		cout << "A cycle: ";
		print_path(cycle_u, cycle_v, G2, n);	
	}

	cout << "Edges in minimum spanning trees:" << endl;

	for (auto itr=MSF.begin(); itr!= MSF.end(); itr++)
		cout << *itr << endl;

}


int main(int argc, char** argv){
	vector<vector<int>> G;
	int n;
	readGreaph(argv[1], G, n);
	print_all_components(G, n);
	Kruskal(G,n);
	return 0;
}

