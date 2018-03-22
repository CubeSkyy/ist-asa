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
		int d; 
		int low;
		bool is_on_stack;

		Vertex(int i);
};


Vertex::Vertex(int i) {

	id = i;
	d = -1; //Base comparition value (since d, id, low, >= 0)
	SCC_id = -1; //id of the SCC that contains this vertex. 
	low = -1;
	is_on_stack = false;
}


class Graph {

	public:
		int V;
		int curr_d;
		int SCC_count;
		vector< list<Vertex*> > adj_list;
		vector<Vertex*> vertex_vector; 
		stack <int> L;
		set<tuple<int, int>> SCC_conections;

		Graph(int V);
		void add_edge(int u, int v);
		void tarjan_visit(int u);
		void tarjan();
};


Graph::Graph(int V){

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
		adj_list[u - 1].push_back(vertex_vector[v - 1]); //Subtract 1 to u and v so id matches the data structures indexes, this is undone in output process
	}
	else {
		cout << "ERROR: u and v must be atleast 1." << endl;
	}
}


void Graph::tarjan_visit(int u) {

	Vertex* u_ptr = vertex_vector[u];
	u_ptr->low = curr_d;
	u_ptr->d = curr_d;
	curr_d++;
	L.push(u);
	u_ptr->is_on_stack = true;

	for (Vertex *v : adj_list[u]) {
		if (v->d == -1 || v->is_on_stack == true) {
			if (v->d == -1) {
				tarjan_visit(v->id);
			}
			u_ptr->low = min(u_ptr->low, v->low);
		}
	}

	if (u_ptr->d == u_ptr->low) {

		int v = L.top();;
		list<Vertex*> SCC_list_temp; //List to save SCC vertex of current iteration to update SCC_id later
		int SCC_min_id = vertex_vector[v]->id;
		SCC_count++;

		do {
			v = L.top();
			L.pop();
			vertex_vector[v]->is_on_stack = false;
			SCC_list_temp.push_back(vertex_vector[v]);
			SCC_min_id = min(SCC_min_id, vertex_vector[v]->id); //SCC id will be the lowest id of the SCC vertices

		} while (u != v);

		for(Vertex* v: SCC_list_temp){ //Set SCC id to all the vertices of the SCC
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


int main(){

	int N, M;

	cin >> N; //Num of vertex
	cin >> M; //Num of edges

	Graph graph(N);

	int u, v;

	for (int i = 0; i < M; i++) {
		cin >> u >> v;
		graph.add_edge(u, v);
	}

	graph.tarjan();

	for (int u = 0; u < graph.V; u++) {        
		for(Vertex* v : graph.adj_list[u]){
			int u_SCC_id = graph.vertex_vector[u]->SCC_id;
			int v_SCC_id = v->SCC_id;

			if (u_SCC_id != v_SCC_id) { //If u and v are in diferent SCC's adds connection.
				graph.SCC_conections.insert(make_tuple(u_SCC_id, v_SCC_id)); //Insert grants sorting and non duplicate values in O(log N) where N is the current set size.
			}
		}
	}

	cout << graph.SCC_count << endl;
	cout << graph.SCC_conections.size() << endl; // O(1)

	for (tuple<int, int> t : graph.SCC_conections) {
		cout << get<0>(t) + 1  << " " << get<1>(t) + 1 << endl; //Set is a binary tree, so printing sorted elements is linear with set size.
	}

	return 0;
}