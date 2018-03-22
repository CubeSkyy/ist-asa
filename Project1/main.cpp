#include <iostream>
#include <list>
#include <vector>
#include <limits>
#include <stack>
#include <algorithm>
#include<set>
#include<tuple>

using namespace std;


class Vertex {
	public:
		int id;
		int SCC_id;
		int d; //Base comparition values (since d,low >= 0)
		int low;
		bool is_on_stack;

		Vertex(int i);

};


Vertex::Vertex(int i) {
	id = i;
	SCC_id = -1;
	d = -1;
	low = -1;
	is_on_stack = false;

}

class Graph {
	public:
		int V;
		int E; //TODO might not need this in implementation
		//list<int> *adj_list;
		vector< list<Vertex*> > adj_list;
		stack <int> L;
		int curr_d;
		// TODO make above private + gets and sets?
		vector<Vertex*> vertex_vector;
		Graph(int V);
		void add_edge(int u, int v);
		void tarjan_visit(int u);
		void tarjan();
		int SCC_count;
		set<tuple<int, int>> SCC_conections;

};


Graph::Graph(int V)
{
	this->V = V;
	SCC_count = 0;
	adj_list = vector< list<Vertex*> >(V);
	vertex_vector = vector<Vertex*>(V);
	for (int i = 0; i < V; i++) {
		vertex_vector[i] = new Vertex(i);
	}
	   
}

void Graph::add_edge(int u, int v) {
	if (u > 0 && v > 0) {
		adj_list[u - 1].push_back(vertex_vector[v - 1]);

	}
	else {
		cout << "ERROR: u and v must be atleast 1." << endl;
	}
}
void Graph::tarjan_visit(int u) {
	Vertex* u_vertex = vertex_vector[u];
	u_vertex->low = curr_d;
	u_vertex->d = curr_d;
	curr_d++;
	L.push(u);
	u_vertex->is_on_stack = true;
	for (list<Vertex*>::iterator it = adj_list[u].begin(); it != adj_list[u].end(); ++it) {
		Vertex* v = (*it);
	//}
	//for (Vertex *v : adj_list[u]) {
		if (v->d == -1 || v->is_on_stack == true) {
			if (v->d == -1) {
				tarjan_visit(v->id);
			}
			u_vertex->low = min(u_vertex->low, v->low);
		}
	}
	if (u_vertex->d == u_vertex->low) {
		SCC_count++;
		list<Vertex*> SCC_list_temp;
		int v = L.top();
		int SCC_min_id = vertex_vector[v]->id;
		L.pop();
		vertex_vector[v]->is_on_stack = false;
		//vertex_vector[v]->SCC_id = u;
		SCC_list_temp.push_back(vertex_vector[v]);
		SCC_min_id = min(SCC_min_id, vertex_vector[v]->id);
		while (u != v ) {
			v = L.top();
			L.pop();
			vertex_vector[v]->is_on_stack = false;
			//vertex_vector[v]->SCC_id = u;
			SCC_list_temp.push_back(vertex_vector[v]);
			SCC_min_id = min(SCC_min_id, vertex_vector[v]->id);
		}
		for (list<Vertex*>::iterator it = SCC_list_temp.begin(); it != SCC_list_temp.end(); ++it) {
			Vertex* v = (*it);
			v->SCC_id = SCC_min_id;
		}

	}

}

void Graph::tarjan() {
	curr_d = 0;
	for (int i = 0; i < V; i++) {
		if (vertex_vector[i]->d == -1) {
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

	for (int i = 0; i < graph.V; i++) {
		for (list<Vertex*>::iterator it = graph.adj_list[i].begin(); it != graph.adj_list[i].end(); ++it) {
			Vertex* v = (*it);
			int v_SCC_id = v->SCC_id;
			if (graph.vertex_vector[i]->SCC_id != v_SCC_id) {

				graph.SCC_conections.insert(make_tuple(graph.vertex_vector[i]->SCC_id, v_SCC_id));
			}
		}
	}

	cout << graph.SCC_count << endl;
	cout << graph.SCC_conections.size() << endl;
	for (tuple<int, int> t : graph.SCC_conections) {
		cout << get<0>(t) + 1  << " " << get<1>(t) + 1 << endl;
	}

	cin >> i;

	return 0;
}