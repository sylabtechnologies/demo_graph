// snakes_ladders.cpp : find shortest path via BFS
// https://www.hackerrank.com/challenges/the-quickest-way-up/problem

#include "stdafx.h"
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <fstream>
using namespace std;

typedef vector<int> Myvec;
typedef list<int> Mylist;
typedef map<int, int> Mymap;

ifstream myinput;
bool first_input = true;
int ri() {
	if (first_input) { first_input = false; myinput.open("sample.txt", ios::in); if (!myinput) exit(1); }
	int x; myinput >> x; return x;
}

class Graph
{
public:
	Graph(int n);
	~Graph();
	void add_edge(int, int);
	int get_vertices() const;
	int get_bfs(int);

private:
	int _num_vert;
	Mylist *adj_list;				// pointer to adjaceny lists
	Myvec  visited;
	Myvec  distance;
};

Graph::Graph(int v)
{
	this->_num_vert = v;
	adj_list = new Mylist[v];

	for (int i = 0; i < v; i++)
	{
		visited.push_back(0);
		distance.push_back(0);
	}
}

Graph::~Graph()
{
	delete[] adj_list;
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

// find bfs shortest reach
int Graph::get_bfs(int start)
{
	// make it null based
	start--;

	Mylist bfs_queue;							// create BFS queue

	// mark/enque current node
	visited[start] = 1;
	bfs_queue.push_back(start);

	while (!bfs_queue.empty())
	{
		int s;

		// deque the front vertice
		s = bfs_queue.front();
		bfs_queue.pop_front();

		// then query all adjacent vertices, if not visited, enqueue it
		for (auto iter = adj_list[s].begin(); iter != adj_list[s].end(); ++iter)
		{
			if (visited[*iter] == 0)
			{
				visited[*iter] = 1;
				distance[*iter] = distance[s] + 1;
				bfs_queue.push_back(*iter);
			}
		}
	}

	// see distance-99
	if (visited[99] == 0)
		return -1;
	else
		return distance[99];
}

int main()
{
	int t = ri();

	for (int a0 = 0; a0 < t; a0++) {
		int n = ri();

		Mymap ladder;
		Mymap snake;
		for (int ladders_i = 0;ladders_i < n;ladders_i++)
		{
			int x = ri();
			int y = ri();
			ladder[x] = y;
		}

		int m = ri();
		for (int snakes_i = 0;snakes_i < m;snakes_i++)
		{
			int x = ri();
			int y = ri();
			snake[x] = y;
		}

		// construct equal weight graph for 100 squares
		Graph g(100);
		for (int i = 1; i < 101; i++)
		{
			for (int dice = 1; dice < 7; dice++)
			{
				if (i + dice > 100) break;

				int j = i + dice;
				auto iter1 = ladder.find(j);
				if (iter1 != ladder.end())
				{
					g.add_edge(i, iter1->second);
					continue;
				}

				auto iter2 = snake.find(j);
				if (iter2 != snake.end())
				{
					g.add_edge(i, iter2->second);
					continue;
				}

				g.add_edge(i, j);
			}
		}

		cout <<  g.get_bfs(1) << endl;
	}
	return 0;
}
