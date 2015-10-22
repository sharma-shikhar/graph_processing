#include <iostream>

#include "DirectedGraph/DirectedGraph.cpp"
//#include "UndirectedGraph/UndirectedGraph.cpp"

using namespace std;
int main() {

	DirectedGraph<int> d;
	d.init_with_file("input.txt");
	
	
	d.strongly_connected_components();
	
	d.disp();

	return 0;
}