package graph;

import java.util.Random;

public class GraphGenerator { 
	public static Graph randomGraph1(int vertices, int degree) {
		if (vertices * degree % 2 != 0) {
			throw new IllegalArgumentException("vertices * degree must be even number");	
		}
		Graph g = new Graph(vertices);
		int[] d = new int[vertices + 1];
		Random rand = new Random();
		while (g.edge < vertices * degree / 2) {
			g = new Graph(vertices);
			d = new int[vertices + 1];
			for (int i = 1; i < g.vertices; i++) {
				int j = 0;
				while(d[i] < degree) {
					if (j++ == 4 * g.vertices) {
						break;
					}
					int end = rand.nextInt(vertices - i) + i + 1;
					if (d[i] < degree && d[end] < degree ) {
						Edge e = new Edge(i, end);
						if (!g.adj[i].contains(e)) {
							g.addEdge(i, end, rand.nextInt(100));
							d[i]++;
							d[end]++;
						}
					}
				}
			}
		}
		return g;
	}

	public static Graph randomGraph2(int vertices, double percentage) {
		Random rand = new Random();
		Graph g = new Graph(vertices);
		for (int start = 1; start <= vertices; start++) {
			for (int end = start + 1; end <= vertices; end++) {
				double randProbability = rand.nextDouble();
				if (randProbability <= percentage) {
					g.addEdge(start, end, rand.nextInt(100));
				}
			}
		}
		return g;
	}
}
