package heap;

import graph.Edge;

public class HeapSort {
	public Edge[] sort(Edge[] edges) {
		int n = edges.length;
		for (int i = n - 1 ; i >= 0; i--) {
			heapify(edges, n, i);
		}
		for (int i = n - 1 ; i >= 0; i--) {
			Edge temp = edges[0];
			edges[0] = edges[i];
			edges[i] = temp;
			heapify(edges, i, 0);
		}
		return edges;    
	}
	
	public void heapify(Edge[] edges, int n, int i) {
		int largest = i;
		int lson = 2 * i;
		int rson = 2 * i + 1;
		if (lson < n && edges[lson].weight > edges[largest].weight) {
			largest = lson;
		}
		if (rson < n && edges[rson].weight > edges[largest].weight) {
			largest = rson;
		}
		if (largest != i) {
			Edge temp = edges[i];
			edges[i] = edges[largest];
			edges[largest] = temp;
			heapify(edges,n,largest);
		}	
	}
}
