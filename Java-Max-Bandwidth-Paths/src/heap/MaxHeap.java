package heap;

import java.lang.Math;
import java.util.Arrays;

import graph.Graph;

public class MaxHeap {
	int[] vertices;
	int[] values;
	int[] pos;
	int size = 0;
	
	public MaxHeap(int number) {
		vertices = new int[number + 1];
		values = new int[number + 1];
		pos = new int[number + 1];
		for (int i = 1; i <= number; i++) { 
			vertices[i] = 0;
			values[i] = 0;
			pos[i] = 0;
		}
	}
	
	public MaxHeap(Graph g) {
		vertices = new int[g.vertices + 1];
		values = new int[g.vertices + 1];
		pos = new int[g.vertices + 1];
		for (int i = 1; i <=g.vertices; i++){ 
			vertices[i] = 0;
			values[i] = 0;
			pos[i] = 0;
		}
	}
	
	public int maximum(){
		return vertices[1];
	}
	
	public void insert(int vertex, int value){
		size++;
		vertices[size] = vertex;
		pos[vertex] = size; 
		values[vertex] = value;
		heapify(size);
	}
	
	public void delete(int vertex) {
		int position = pos[vertex];
		swap(position, size);
		vertices[size] = 0;
		pos[vertex] = 0;
		size--;
		heapify(position);
	}
	
	private void heapify(int position) {
		int father = position / 2;
		int lson = 2 * position;
		int rson = 2 * position + 1;
		int vertex = vertices[position];
		if (position > 1 && values[vertex] >= values[vertices[father]]) {
			swap(position, father);
			heapify(father);
		} else if (lson == size && values[vertex] < values[vertices[lson]]) {
			swap(position, lson);
			return;
		} else if (rson <= size && values[vertex] < Math.max(values[vertices[lson]], values[vertices[rson]])) {
			if (values[vertices[lson]] >= values[vertices[rson]]) {
				swap(position, lson );
				heapify(lson);
			} else {
				swap(position, rson);
				heapify(rson);
			}
		}
		else return;
	}
	
	public String getValues() {
		return  Arrays.toString(values);
	}
	
	public String getVertices() {
		return  Arrays.toString(vertices);
	}

	private void swap (int position1,int position2) {
		int vertex1 = vertices[position1];
		int vertex2 = vertices[position2];
		int temp = vertex1;
		vertices[position1] = vertex2;
		vertices[position2] = temp;
		int tempPos = pos[vertex1];
		pos[vertex1] = pos[vertex2];
		pos[vertex2] = tempPos;		
	}
}
