#include <iostream>

#include "DirectedGraph/DirectedGraph.cpp"
//#include "UndirectedGraph/UndirectedGraph.cpp"

using namespace std;
int main() {

	/*
	
	DirectedGraph<int> d;
	d.init_with_file("input.txt");
	
	d.strongly_connected_components();
	
	d.disp();
	
	*/
	
	MinHeap<int, string> h;
	
	h.insert(3, "three");
	h.insert(5, "five");
	h.insert(1, "one");
	h.insert(7, "seven");
	h.insert(4, "four");
	h.insert(8, "eight");
	h.insert(2, "two");
	
	int n;
	string s;
	
	while (!h.empty()) {
		tie(n, s) = h.extract_min();
		cout << n << " " << s << endl;
	}
	
	return 0;
}