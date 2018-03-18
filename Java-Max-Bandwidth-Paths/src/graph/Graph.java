package graph;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Graph {
	public int vertices;
	public int edge;
	public ArrayList<Edge>[] adj;
	
	public Graph(int vertices) {
		this.vertices = vertices;
		this.edge = 0;
		adj = new ArrayList[vertices + 1];
		for (int i = 1; i <= vertices; i++) {
			adj[i] = new ArrayList<Edge>();
		}
	}
	
	public void addEdge(int start, int end, int weight) {
		Edge e = new Edge(start, end);
		e.weight = weight;
		if (!this.adj[start].contains(e)) {
			this.adj[start].add(e);
			this.adj[end].add(e);
			edge++;
		}
	}
	
	public int getWeight(int start, int end) {
		int result = 0;
		ArrayList<Edge> list = adj[start];
		for (Edge e : list) {
			if (e.end == start) {
				if (e.start == end) {
					result = e.weight;
					break;
				}
			} else {
				if (e.end == end) {
					result = e.weight;
					break;
				}
			}

		}
		return result;
	}
	
	public void addAllPath(int s, int t) {
		List<Edge> temp = new ArrayList<Edge>();
		for (int i = 1; i <= this.vertices; i++) {
			for (Edge e : this.adj[i]){
				temp.add(e);
			} 
		}
		Random rand = new Random();
		int first = 0;
		int last = 0;
		int count = 0;
		for (int i  = 1; i < this.vertices; i++) {
			int start = i;
			int end = i + 1;
			if (start == s || start == t) {
				continue;
			}
			if (end == s || end == t) {
				end++;
			}
			if (end > this.vertices) break;
			
			count ++;
			if (count == 1) {
				first = start;
			}
			if (count == this.vertices - 3) {
				last = end;
			}
			this.addEdge(start, end, rand.nextInt(100));
		}
		this.addEdge(last, t, rand.nextInt(100));
		this.addEdge(s, first, rand.nextInt(100));
	}
}
	