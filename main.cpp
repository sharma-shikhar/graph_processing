#include <iostream>

#include "DirectedGraph/DirectedGraph.cpp"
//#include "UndirectedGraph/UndirectedGraph.cpp"

using namespace std;
int main() {

	
	
	DirectedGraph<int> d;
	d.initWithFile("input.txt");
	
	d.stronglyConnectedComponents();
	
	d.disp();
	
	
	
	return 0;
}