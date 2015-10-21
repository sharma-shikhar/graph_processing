#include <iostream>

//#include "DirectedGraph/DirectedGraph.cpp"
#include "UndirectedGraph/UndirectedGraph.cpp"


int parser(const std::string &str) {
	return std::stoi(str);
}


void disp(UndirectedEdge<int> *e, Vertex<int> *v) {
	if (e) std::cout << "Edge: (" << e->first->value << "," << e->second->value << "), "; 
	if (v) std::cout << "Vertex: " << v->value <<  std::endl;
}


using namespace std;
int main() {
	
	/*
	DirectedGraph<int> d;
	d.init_with_file("input.txt", DirectedGraph<int>::input_line_handler_1, Vertex<int>::parser_1);
	
	std::cout << std::endl;
	d.shortest_path_by_edge_cardinality(d.get_vertex(1));
	std::cout << std::endl;
	
	d.disp();
	*/
	
	
	// Add connected components in undirected graph by BFS and adding label numbers
	
	UndirectedGraph<int> d;
	d.init_with_file("input.txt", UndirectedGraph<int>::input_line_handler_1, Vertex<int>::parser);
	
	std::cout << std::endl;
	d.connected_components();
	std::cout << std::endl;
	
	d.disp();
	
	
	
	
	
	return 0;
}