package graph;

public class Edge {
	public int start;
	public int end;
	public int weight;
	
	public Edge(int start, int end) {
		if (start < end) {
			this.start = start;
			this.end = end;
		} else {
			this.start = end;
			this.end = start;
		}
	}
	
	@Override
	public boolean equals(Object obj) {
		if (this == obj) {
			return true;
		}
		if (obj == null) {
			return false;
		}
		if (getClass() != obj.getClass()) {
			return false;
		}
		Edge other = (Edge) obj;
		if (end != other.end) {
			return false;
		}
		if (start != other.start) {
			return false;
		}
		return true;
	}
	
	public void addWeight(int weight) {
		this.weight = weight;
	}
	
	public String toString() {
		return start + "-" + end;
	}
}
