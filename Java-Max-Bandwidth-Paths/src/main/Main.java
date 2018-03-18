package main;

import java.util.Random;
import graph.Graph;
import graph.GraphGenerator;

public class Main{
	public static void main(String[] args) {
		Random rand = new Random();
		Graph[] rdg1 = new Graph[5];
		Graph[] rdg2 = new Graph[5];
		for (int i = 0; i < 5; i++ ) {
			rdg1[i] = GraphGenerator.randomGraph1(5000, 8);
			rdg2[i] = GraphGenerator.randomGraph2(5000, 0.2);
		}
		System.out.println("the graph generation is done!");
		
		System.out.println("");
		System.out.println("Start the test:");
		for (int i = 0; i < 5; i++ ) {
			System.out.println("");
			System.out.println(i + 1 + " graph pair");
			for (int j = 0; j < 5; j++) {
				System.out.println("");
				System.out.println(j + 1  + " pair of (s,t) of graph pair " + (i + 1));
				int s = rand.nextInt(5000);
				int t = rand.nextInt(5000);
				rdg1[i].addAllPath(s, t);
				rdg2[i].addAllPath(s, t);
				
				System.out.println("");
				long start1 = System.currentTimeMillis();
				RoutingAlgorithms.algo1(rdg1[i], s, t);
				long end1   = System.currentTimeMillis();
				long total1 = end1 - start1;
				System.out.println("Algorithm 1 on G1 for vertices" + " ("+ s + "," + t + ")" + " is: " + total1 + " ms");
				
				long start2 = System.currentTimeMillis();
				RoutingAlgorithms.algo2(rdg1[i], s, t);
				long end2   = System.currentTimeMillis();
				long total2 = end2 - start2;
				System.out.println("Algorithm 2 on G1 for vertices" + " ("+ s + "," + t + ")" + " is: " + total2 + " ms");
				
				long start3 = System.currentTimeMillis();
				RoutingAlgorithms.algo3(rdg1[i], s, t);
				long end3   = System.currentTimeMillis();
				long total3 = end3 - start3;
				System.out.println("Algorithm 3 on G1 for vertices" + " ("+ s + "," + t + ")" + " is: " + total3 + " ms");

				System.out.println("");
				long start4 = System.currentTimeMillis();
				RoutingAlgorithms.algo1(rdg2[i], s, t);
				long end4   = System.currentTimeMillis();
				long total4 = end4 - start4;
				System.out.println("Algorithm 1 on G2 for vertices" + " ("+ s + "," + t + ")" + " is: " + total4 + " ms");
				
				long start5 = System.currentTimeMillis();
				RoutingAlgorithms.algo2(rdg2[i], s, t);
				long end5   = System.currentTimeMillis();
				long total5 = end5 - start5;
				System.out.println("Algorithm 2 on G2 for vertices" + " ("+ s + "," + t + ")" + " is: " + total5 + " ms");
				
				long start6 = System.currentTimeMillis();
				RoutingAlgorithms.algo3(rdg2[i], s, t);
				long end6   = System.currentTimeMillis();
				long total6 = end6 - start6;
				System.out.println("Algorithm 3 on G2 for vertices" + " ("+ s + "," + t + ")" + " is: " + total6 + " ms");
			}
			System.out.println("");
			System.out.println("*************************************");
		}
	}
}
