/*

   Data Structure - Stack
A stack is one of the simplest data structures available. There are four main operations on a stack:

Push – Adds an element to the top of the stack
Pop – Removes the top element from the stack
Top – Returns the top element on the stack
Empty – Tests if the stack is empty or not
In C++, this is done with the STL class stack:

#include <stack>
std::stack<int> myStack;

DFS - 
According to wikipedia, there are basically two differences in implementation of DFS and BFS.
They are:
1)DFS uses stack while BFS uses queue.(this I understand).

2)DFS delays checking whether a vertex has been discovered until the vertex is popped from the stack rather than making this check before pushing the vertex.

Recursive Algo
dfs(node current) {
 mark current as visited;
 visit all of current's unvisited neighbors by calling dfs(neighbor)
}

Iterative ALgo
dfs(node start) {
 stack<node> s;
 s.push(start);
 while (s.empty() == false) {
  top = s.top();
  s.pop();

  if (top is not marked as visited) {
   check for termination condition (have we reached the node we want to?)

   mark top as visited;
   add all of top's neighbors to the stack.
  }
 }
}

 SIDE NOTE on memory
 Sidenote:
Stack memory is used whenever you call a function; the variables to the function are pushed onto the stack by the compiler for you. When using a recursive function, the variables keep getting pushed on until the function returns. Also any variables the compiler needs to save between function calls must be pushed onto the stack as well. This makes it somewhat difficult to predict if you will run into stack difficulties. I recommend using the explicit Depth First search for every situation you are at least somewhat concerned about recursion depth.

In this problem we may recurse a maximum of 600 * 400 times (consider the empty grid initially, and what the depth first search will do, it will first visit 0,0 then 1,0, then 2,0, then 3,0 … until 599, 0. Then it will go to 599, 1 then 598, 1, then 597, 1, etc. until it reaches 599, 399. This will push 600 * 400 * 2 integers onto the stack in the best case, but depending on what your compiler does it may in fact be more information. Since an integer takes up 4 bytes we will be pushing 1,920,000 bytes of memory onto the stack, which is a good sign we may run into trouble
*/   
#include <iostream>
#include <vector>
#include <stack>
using namespace std;
void dfs(vector<vector<int> > adj_list, int start, bool visited[], int parents[]);
void dfs_stack(vector<vector<int> > adj_list, int num_nodes);
int main(int argc, char *argv[])
{
   int num_nodes, num_edges;
   cin >> num_nodes >> num_edges;
   vector<vector<int> > adj_list(num_nodes, vector<int>());
   for (int i = 0; i < num_edges; i++)
   {
      int num1, num2;
      cin >> num1 >> num2;
      adj_list[num1].push_back(num2);
   }
   bool visited[100] = {false};
   int parents[100] = {-1};
   dfs(adj_list, 0, visited, parents);
   cout << endl;
   dfs_stack(adj_list, num_nodes);
   cout << endl;
}
void dfs(vector<vector<int> > adj_list, int start, bool visited[], int parents[])
{
   visited[start] = true;
   cout << start << " parents : " << parents[start] << endl;
   for (int i = 0; i < adj_list[start].size(); i++)
   {
      if (!visited[adj_list[start][i]])
      {
         parents[adj_list[start][i]] = start;
         dfs(adj_list, adj_list[start][i], visited, parents);
      }
   }
}

void dfs_stack(vector<vector<int> > adj_list, int num_nodes)
{
    stack<int> dfs_stack;
    dfs_stack.push(0);
    bool visited[100] = {false};
    int parents[100] = {-1};
    while (!dfs_stack.empty())
    {
        int node = dfs_stack.top();
        dfs_stack.pop();
        if (!visited[node])
        {
            cout << node << " parents : " << parents[node] << endl;
            visited[node] = true;
            for (int i = 0; i < adj_list[node].size(); i++)
            {
                    dfs_stack.push(adj_list[node][i]);
                    parents[adj_list[node][i]] = node;
            }

        }
    }
}

