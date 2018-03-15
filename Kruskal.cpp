// implement Kruskal: https://www.hackerrank.com/challenges/kruskalmstrsub/problem

#include "stdafx.h"
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <iterator>
#include <algorithm>
#include <fstream>
using namespace std;

ifstream myinput;
bool first_input = true;
int ri() {
	if (first_input) { first_input = false; myinput.open("sample.txt", ios::in); if (!myinput) exit(1); }
	int x; myinput >> x; return x;
}

struct Node {int node; int weight; };
struct Edge { int x; int y; int weight; };
typedef list<Node> Mylist;
typedef vector<Edge> Edlist;
typedef vector<int> I_Vec;

class Graph
{
public:
	Graph(int n);
	~Graph();
	int get_vertices() const;
	void add_edge(int, Node);
	Edlist sorted_edges();
	// int kruskal_mst();

private:
	int _num_vert;
	Mylist *adj_list;				// pointer to adjaceny lists
};

Graph::Graph(int v)
{
	this->_num_vert = v;
	adj_list = new Mylist[v];
}

Graph::~Graph()
{
	delete[] adj_list;
}

int Graph::get_vertices() const
{
	return this->_num_vert;
}

// insert in non-decreasing order
void Graph::add_edge(int v, Node w)
{
	// make it null-based
	v--; w.node--;

	adj_list[v].push_back(w);
}

// print all edges!
Edlist Graph::sorted_edges()
{
	Edlist result;

	// auto increased = [](const Edge& a, const Edge& b) -> bool \
	// { if (a.weight > b.weight) return true; return false; };

	for (int i = 0; i < _num_vert; i++)
	{
		for (auto iter = adj_list[i].begin(); iter != adj_list[i].end(); ++iter)
		{
			Edge temp;
			temp.x = i;
			temp.y = iter->node;
			temp.weight = iter->weight;

			// insert in non-decreasing order
			Edlist::iterator edge_itr;
			for (edge_itr = result.begin(); edge_itr != result.end(); ++edge_itr)
			{
				if (edge_itr->weight == temp.weight)
					if (edge_itr->x + edge_itr->y > temp.x + temp.y) break;

				if (edge_itr->weight > temp.weight) break;
			}

			if (edge_itr == result.end())
				result.push_back(temp);
			else
				result.insert(edge_itr, temp);
		}
	}

	return result;
}

bool is_cycle(Graph&, Edlist, Edge);

int main()
{
	int n; int m;
	n = ri(); m = ri();

	Graph g(n);
	for (int edges_i = 0; edges_i < m; edges_i++)
	{
		int x, y, w;
		Node temp;

		x = ri(); y = ri(); w = ri();

		temp.node = y; temp.weight = w;
		g.add_edge(x, temp);
	}

	Edlist edges = g.sorted_edges();

	int vert_count = 0, mst_weight = 0;
	Edlist kruskal;
	for (auto iter = edges.begin(); iter != edges.end(); ++iter)
	{
		if (kruskal.empty())
		{
			kruskal.push_back(*iter);
			vert_count++;
			mst_weight += iter->weight;
		}
		else
		{
			if (!is_cycle(g, kruskal, *iter))
			{
				kruskal.push_back(*iter);
				vert_count++;
				mst_weight += iter->weight;
			}
		}

		if (vert_count == m - 1) break;
	}

	cout << mst_weight << endl;

    return 0;
}

// find subset of i
int cycle_find(const I_Vec& parent, int i)
{
	if (parent[i] == -1) return i;

	return cycle_find(parent, parent[i]);
}

// unite two subsets
void cycle_union(I_Vec& parent, int x, int y)
{
	int xset = cycle_find(parent, x);
	int yset = cycle_find(parent, y);
	parent[xset] = yset;
}

// find cycle in graph
bool is_cycle(Graph& mygraph, Edlist edges, Edge new_edge)
{
	I_Vec parent(mygraph.get_vertices(), -1);
	
	edges.push_back(new_edge);
	for (auto iter = edges.begin(); iter != edges.end(); ++iter)
	{
		int x = cycle_find(parent, iter->x);
		int y = cycle_find(parent, iter->y);

		if (x == y) return true;

		cycle_union(parent, x ,y); 
	}

	return false;
}

