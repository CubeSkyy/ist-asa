#include <iostream>
#include <list>
#include <vector>
#include <limits>

using namespace std;

class Graph {
	public:
		int V;
		int E; //TODO might not need this in implementation
		list<int> *adj_list;
		vector<int> low;
		vector<int> d;
		int curr_d = 0;
		
		// TODO make above private + gets and sets?

		Graph(int V);
		void add_edge(int u, int v);
		void tarjan_visit(int u);
		void tarjan();

};


Graph::Graph(int V)
{
	this->V = V;
	this->low = vector<int>(V, 0);
	this->d = vector<int>(V, INT_MAX);
	this->adj_list = new list<int>[V];
	   
}

void Graph::add_edge(int u, int v){
	adj_list[u].push_back(v);
}

void Graph::tarjan_visit(int u) {
	this->low[u] = this->curr_d;
	this->d[u] = this->curr_d;
	this->curr_d++;
	//TODO finish tarjan visit
}

void Graph::tarjan() {
	//TODO base tarjan

}

int main()
{
	int i;
	Graph test(10);

	for (int i = 0; i < test.V; i++) {
		test.tarjan_visit(i);
	}
	cout << "low:" << endl;
	for (int i : test.low)
		cout << "i: " << i << endl;
	cout << "d:" << endl;
	for (int i : test.d)
		cout << "i: " << i << endl;

	

	cin >> i;
	return 0;
}