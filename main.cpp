#include <iostream>

//#include "DirectedGraph/DirectedGraph.cpp"
#include "UndirectedGraph/UndirectedGraph.cpp"

using namespace std;
int main() {
	
/*	
	DirectedGraph<int> d;
	d.init_with_file("input.txt", DirectedGraph<int>::input_line_handler_1, Vertex<int>::parser);
	
	std::cout << std::endl;
	d.shortest_path_by_edge_cardinality(d.get_vertex(1));
	std::cout << std::endl;
	
	d.disp();
	
*/	

	UndirectedGraph<int> d;
	d.init_with_file("input.txt", UndirectedGraph<int>::input_line_handler_1, Vertex<int>::parser);
	
	std::cout << std::endl;
	d.connected_components();
	std::cout << std::endl;
	
	d.disp();
	
	
	return 0;
}