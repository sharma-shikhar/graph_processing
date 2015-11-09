#include <iostream>

#include "DirectedGraph/DirectedGraph.cpp"
//#include "UndirectedGraph/UndirectedGraph.cpp"

using namespace std;
int main() {
	
	DirectedGraph<int> d;
	d.initWithFile("input.txt");
	
	d.stronglyConnectedComponents();
	
	d.disp();
	
	
	/*
	MinHeap<int, int> h;
	
	for (int i=9; i>=1; i--) {
		h.insert(i, i);
	}

	h.decreaseKey(-1, 9);
	h.decreaseKey(-2, 5);
	
	
	std::pair<int, int> p = h.extractMin();
	
	cout << p.first << " " << p.second;
	*/
	
	return 0;
}