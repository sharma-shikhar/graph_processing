#include <iostream>

#include "DirectedGraph/DirectedGraph.cpp"
//#include "UndirectedGraph/UndirectedGraph.cpp"

using namespace std;
int main() {
	
	DirectedGraph<int> d;
	d.initWithFile("input.txt");
	
	d.shortestPathFrom(d.getVertex(1));
	
	//d.stronglyConnectedComponents();
	
	d.disp();
	
	return 0;
}