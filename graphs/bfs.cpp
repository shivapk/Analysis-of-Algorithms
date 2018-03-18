/*
   Queue
A queue is a simple extension of the stack data type. Whereas the stack is a FILO (first-in last-out) data structure the queue is a FIFO (first-in first-out) data structure. What this means is the first thing that you add to a queue will be the first thing that you get when you perform a pop().

There are four main operations on a queue:

Push – Adds an element to the back of the queue
Pop – Removes the front element from the queue
Front – Returns the front element on the queue
Empty – Tests if the queue is empty or not
In C++, this is done with the STL class queue:

#include <queue>
queue<int> myQueue;

BFS - ALGO
void bfs(node start) {
 queue<node> s;
 s.push(start);
 mark start as visited
 while (s.empty() == false) {
  top = s.front();
  s.pop();

  check for termination condition (have we reached the node we want to?)

  add all of top's unvisited neighbors to the queue
  mark all of top's unvisited neighbors as visited
 }
}
   */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int main (int argc, char *argv[])
{
// assuming nodes start from 0
    int num_nodes,num_edges;
    cout << "enter num of nodes and edges" << endl;
    cin >> num_nodes >> num_edges;
    vector<vector<int> > adj_list(num_nodes, vector<int>());
    bool visited[100] = {false};
    int parent[100] = {-1};
    int distance[100] = {0};
    for (int i = 0; i < num_edges; i++)
    {
        int node1, node2;
        cin >> node1 >> node2;
        adj_list[node1].push_back(node2);
    }
    queue<int> bfs_queue;
    bfs_queue.push(0); // starting node
    visited[0] = true;
    while(!bfs_queue.empty())
    {
         int node = bfs_queue.front();
         bfs_queue.pop();
         cout << node << " dist : " << distance[node] << "  parent : " << parent[node] << endl;

         for (int i = 0; i < adj_list[node].size(); i++)
         {
               int child = adj_list[node][i];
               if (!visited[child])
               {
                  visited[child] = true;
                  bfs_queue.push(child);
                  parent[child] = node;
                  distance[child] = distance[node] + 1;
               }
         } 
    }
    
}
