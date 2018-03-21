#include <iostream>
#include <list>
#include <vector>
#include <limits>
#include <stack>
#include <algorithm>

using namespace std;

class Graph {
	public:
		int V;
		int E; //TODO might not need this in implementation
		//list<int> *adj_list;
		vector< list<int> > adj_list;

		vector<int> low;
		vector<int> d;
		vector<int> vertex_info; //TODO make linear search for less memory?
		//vertex_info is:
		//  -2 if vertex isn't on stack
		//  -1 if vertex is on stack
		//  n > -1 if vertex is part of a SCC, where n is the root of the SCC.

		stack <int> L;
		int curr_d;
		
		// TODO make above private + gets and sets?

		Graph(int V);
		void add_edge(int u, int v);
		void tarjan_visit(int u);
		void tarjan();

};


Graph::Graph(int V)
{
	this->V = V;
	low = vector<int>(V, 0);
	d = vector<int>(V, INT_MAX);
	vertex_info = vector<int>(V, -2);
	adj_list = vector< list<int> >(V);
	   
}

void Graph::add_edge(int u, int v) {
	if (u > 0  && v > 0) {
		adj_list[u-1].push_back(v-1);
	}
	else {
		cout << "EROOR: u and v must be atleast 1." << endl;
	}
}
void Graph::tarjan_visit(int u) {
	low[u] = curr_d;
	d[u] = curr_d;
	curr_d++;
	L.push(u);
	vertex_info[u] = -1;
	for (int v : adj_list[u]) {
		if (d[v] == INT_MAX || vertex_info[v] == -1) {
			if (d[v] == INT_MAX) {
				tarjan_visit(v);
			}
			low[u] = min(low[u], low[v]);
		}
	}
	
	if (d[u] == low[u]) {

		int v = L.top();
		L.pop();
		vertex_info[v] = u;
		while (u != v ) {
			v = L.top();
			L.pop();
			vertex_info[v] = u;
		}
	}

}

void Graph::tarjan() {
	curr_d = 0;
	for (int i = 0; i < d.size(); i++) {
		if (d[i] == INT_MAX) {
			tarjan_visit(i);
		}
	}

}

int main()
{
	int i, N, M, u, v;

	cin >> N; //Num of vertex
	cin >> M; //Num of edges
		
	Graph graph(N);

	for (i = 0; i < M; i++) {
		cin >> u >> v;
		graph.add_edge(u, v);
	}

	graph.tarjan();

	cin >> i;

	return 0;
}