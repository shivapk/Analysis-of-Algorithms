package main;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Set;
import java.util.Stack;

import graph.Edge;
import graph.Graph;
import heap.HeapSort;
import heap.MaxHeap;

public class RoutingAlgorithms {
	public static void algo1(Graph g, int s, int t) {
		int[] bandwidth = new int[g.vertices + 1];
		int[] dad = new int[g.vertices + 1];
		int[] status = new int[g.vertices + 1];
		
		dad[s] = 0;
		bandwidth[s] = 101;
		status[s] = 2;
		ArrayList<Edge> newfringe = g.adj[s];
		for (Edge e: newfringe) {
			int end = e.end;
			if (s == e.end) {
				end = e.start;
			}
			status[end] = 1;
			dad[end] = s;
			bandwidth[end] = g.getWeight(s, end);
		}

		while (status[t] != 2) {
			int maxFringe = findMax(bandwidth, status);
			status[maxFringe] = 2;
			ArrayList<Edge> list = g.adj[maxFringe];
			for (Edge e: list) {
				int end = e.end;
				if (maxFringe == e.end) {
					end = e.start;
				}
				
				int endWeight = Math.min(bandwidth[maxFringe], g.getWeight(maxFringe, end));
				
				if (status[end] == 0){
					status[end] = 1;
					dad[end] = maxFringe;
					bandwidth[end] = endWeight;

				} else if (status[end] == 1 && 
						endWeight > bandwidth[end]) {
					dad[end] = maxFringe;
					bandwidth[end] = endWeight;
				}
			}
		}
	}

	public static void algo2(Graph g, int s, int t){
		int[] bandwidth = new int[g.vertices + 1];
		int[] dad = new int[g.vertices + 1];
		int[] status = new int[g.vertices + 1];
		MaxHeap h = new MaxHeap(g);

		dad[s] = 0;
		bandwidth[s] = 101;
		status[s] = 2;
		ArrayList<Edge> newfringe = g.adj[s];
		for (Edge e: newfringe) {
			int end = e.end;
			if (s == end) {
				end = e.start;
			}
			status[end] = 1;
			dad[end] = s;
			bandwidth[end] = g.getWeight(s, end);
			h.insert(end, bandwidth[end]);
		}

		while (status[t] != 2) {
		    int maxFringe = h.maximum();
			h.delete(maxFringe);
			status[maxFringe] = 2;
			
			ArrayList<Edge> fringeList = g.adj[maxFringe];
			for (Edge e: fringeList) {
				int end = e.end;
				if(maxFringe == e.end) {
					end = e.start;
				}
				int endWeight = Math.min(bandwidth[maxFringe], g.getWeight(maxFringe, end));
				
				if (status[end] == 0) {
					status[end] = 1; 
					bandwidth[end] = endWeight;
					h.insert(end,bandwidth[end]);
					dad[end] = maxFringe;
				}
				else if (status[end] == 1 && endWeight > bandwidth[end]) { 
					h.delete(end);
					dad[end] = maxFringe;
					bandwidth[end] = endWeight;
					h.insert(end,bandwidth[end]);
				}
			}
		}
	}
	
	public static void algo3(Graph g, int s, int t) {
		Graph g1 = new Graph(g.vertices);
	
		List<Edge> temp = new ArrayList<Edge>();
		for (int i = 0; i < g.vertices; i++) {
			for (Edge e : g.adj[i+1]){
				temp.add(e);
			} 
		}
		Set<Edge> hs = new HashSet<Edge>();
		hs.addAll(temp);
		Edge[] edges = hs.toArray(new Edge[hs.size()]);
		
		int[] D = new int[g.vertices + 1]; 
		int[] R = new int[g.vertices + 1];
		makeSet(g.vertices, D, R);
		
		for (int i = g.edge - 1; i >= 0 ;i--) {
			Edge e = edges[i];
			int r1 = find(e.start,D);
			int r2 = find(e.end,D);
			if (r1 != r2 ){
				g1.addEdge(e.start, e.end, e.weight);
				union(R, D, r1, r2);
			}
		}
		traverse(s, t, g1);
	}
	
	private static void makeSet(int vertices, int[] D, int[] R) {
		for (int i = 1; i <= vertices; i++) {
			D[i] =  0;
			R[i] =  0;
		}
	}
	
	private static int find(int vertex, int[] D) {
		int cur = vertex;
		while(D[cur] != 0) {
			cur = D[cur];		
		}
		return cur;
	}
	
	private static void union(int[] R, int[] D, int u, int v) {
		if (R[u] > R[v]) {
			D[v] = u;
		} else if (R[u] < R[v]) {
			D[u] = v;
		} else {
			D[v] = u;
			R[u]++;
		}
	}
	
	private static int findMax(int[] bandwidth, int[] status ) {
		int index = 0;
		int max = 0;
		for (int i = 1; i < status.length;i++) {
			if (status[i] == 1 && bandwidth[i] > max) {
				index = i;
				max = bandwidth[i];
			}
		}
		return index;
	}
	
	private static void traverse(int s, int t, Graph g) {
		LinkedList<Integer> queue = new LinkedList<Integer>();
		int[] dad = new int[g.vertices+1];
		int[] color = new int[g.vertices+1];
		int[] bandwidth = new int[g.vertices+1];
		Arrays.fill(color, 0);
		
		color[s] = 1;
		queue.add(s);
		bandwidth[s] = 101;
		while(queue.size() != 0){
			int u = queue.poll();
			if (u != t) {
				
				for (Edge e : g.adj[u]) {
					int end = e.end;
					if (end == u) {
						end = e.start;
					}
					if (color[end] != 1) {
						queue.add(end);
						color[end] = 1;
						dad[end] = u;
					}
					
					if (e.weight < bandwidth[u]) {
						bandwidth[end] = e.weight;
					} else {
						bandwidth[end] = bandwidth[u];
					}
				}
			}
		}
	}
}
