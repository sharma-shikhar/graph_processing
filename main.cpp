#include <iostream>

#include "DirectedGraph/DirectedGraph.cpp"
//#include "UndirectedGraph/UndirectedGraph.cpp"

using namespace std;
int main() {
	/*
	DirectedGraph<int> d;
	d.initWithFile("input.txt");
	
	d.stronglyConnectedComponents();
	
	d.disp();
	*/
	
	
	MinHeap<int, int> h;
	
	for (int i=9; i>=1; i--) {
		h.insert(i, i);
	}
	
	h.disp();
	
	return 0;
}