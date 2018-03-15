// forest.cpp : create even tree
// https://www.hackerrank.com/challenges/even-tree/problem

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <iterator>
#include <algorithm>
#include <fstream>
using namespace std;

int ri() {
	int x; cin >> x; return x;
}

typedef list<int> Mylist;
typedef vector<int> Myvec;

class Graph
{
public:
	Graph(int n);
	~Graph();
	void add_edge(int, int);
	int get_vertices() const;
	void get_dfs(int);
	int even_nodes;

private:
	int _num_vert;
	Mylist *adj_list;				// pointer to adjaceny lists
	Myvec  *visited;

private:
	int  count_nodes(int);
};

Graph::Graph(int v)
{
	even_nodes = 0;
	this->_num_vert = v;
	adj_list = new Mylist[v];
	visited = new Myvec(v, -1);
}

Graph::~Graph()
{
	delete[] adj_list;
	delete visited;
}

int Graph::get_vertices() const
{
	return this->_num_vert;
}

void Graph::add_edge(int v, int w)
{
	// make it null-based
	v--; w--;

	adj_list[v].push_back(w);
}

void Graph::get_dfs(int v)
{
	(*visited)[v] = 1;
	// cout << v + 1 << " ";

	for (auto iter = adj_list[v].begin(); iter != adj_list[v].end(); ++iter)
	{
		if ((*visited)[*iter] < 0)
		{
			// cout << count_nodes(*iter) << " ";
			int temp = count_nodes(*iter);
			if (temp % 2 == 0) even_nodes++;
		}
	}
}

int Graph::count_nodes(int v)
{
	int result = 1;

	Myvec current(_num_vert, -1);
	current[v] = 1;

	for (auto iter = adj_list[v].begin(); iter != adj_list[v].end(); ++iter)
	{
		if (current[*iter] < 0)
			result += count_nodes(*iter);
	}

	return result;
}

int main()
{
	int tree_nodes;
	int tree_edges;

	tree_nodes = ri();
	tree_edges = ri();

	vector<int> tree_from(tree_edges);
	vector<int> tree_to(tree_edges);

	for (int tree_itr = 0; tree_itr < tree_edges; tree_itr++) {
		tree_from[tree_itr] = ri();
		tree_to[tree_itr] = ri();
	}

	Graph g(tree_nodes);
	for (int tree_itr = 0; tree_itr < tree_edges; tree_itr++)
	{
		g.add_edge(tree_to[tree_itr], tree_from[tree_itr]);
	}

	for (int node_itr = 0; node_itr < tree_nodes; node_itr++)
		g.get_dfs(node_itr);

	cout << g.even_nodes << endl;

	return 0;
}

