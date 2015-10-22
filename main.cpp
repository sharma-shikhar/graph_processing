#include <iostream>

#include "DirectedGraph/DirectedGraph.cpp"
//#include "UndirectedGraph/UndirectedGraph.cpp"

using namespace std;
int main() {

	DirectedGraph<int> d;
	d.init_with_file("input.txt");
	
	
	int number = 0;
	std::function<void(DirectedEdge<int> *, Vertex<int> *)> labeler = [&number] (DirectedEdge<int> *e, Vertex<int> *v) -> void {
		//cout << "Handling " << v->value << " ";
		v->data->data1 = number++;
		
	};
	
	d.rev_dfs_from(d.get_vertex(3), labeler);
	
	d.disp();
	
	
	return 0;
}