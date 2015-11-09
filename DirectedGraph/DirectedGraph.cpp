#include <fstream>
#include <unordered_map>
#include <vector>
#include "header.hpp"
#include "../Lib/List.cpp"
#include "../Lib/Queue.cpp"
#include "../Lib/string_funcs.cpp"
#include "../Lib/MinHeap.cpp"
#include "Vertex.cpp"
#include "DirectedEdge.cpp"


template <typename T>
class DirectedGraph {
	public:
	
	static void inputLineHandler1(DirectedGraph<T> *g, std::string &line, std::function<T(const std::string &)> parser);
	
	List<Vertex<T> *> _vertices;
	List<Vertex<T> *> *vertices = &_vertices;
	
	List<DirectedEdge<T> *> _edges;
	List<DirectedEdge<T> *> *edges = &_edges;
	
	std::unordered_map<T, Vertex<T> *> valueToVertexMapper;
	
	bool vertex_exists(const T &val) {
		return valueToVertexMapper.find(val) != valueToVertexMapper.end();
	}
	Vertex<T> *getVertex(const T &val) {
		return valueToVertexMapper[val];
	}
	
	Vertex<T> *createVertex(T value) {
		return new Vertex<T>(value);
	}
	Vertex<T> *insertVertex(Vertex<T> *v) {
		return vertices->pushBack(v);
	}
	DirectedEdge<T> *addEdgeToAdjacencyList(DirectedEdge<T> *e, Vertex<T> *v) {
		v->adjacencyList->pushBack(e);
	}
	DirectedEdge<T> *addEdgeToIncomingEdgesList(DirectedEdge<T> *e, Vertex<T> *v) {
		v->incomingEdgesList->pushBack(e);
	}
	
	DirectedEdge<T> *createEdge(Vertex<T> *v1, Vertex<T> *v2) {
		return new DirectedEdge<T>(v1, v2);
	}
	DirectedEdge<T> *insertEdge(DirectedEdge<T> *e) {
		return edges->pushBack(e);
	}
	Vertex<T> *getOrCreateVertex(T val);
	
	DirectedGraph() {}
	
	void initWithFile(const std::string filename, std::function<void(DirectedGraph<T> *, std::string &, std::function<T(const std::string &)>)> inputLineHandler = DirectedGraph<T>::inputLineHandler1, std::function<T(const std::string &)> parser = Vertex<T>::parser);
	
	void markAllVerticesUnexplored();
	void breadthFirstSearch(Vertex<T> *s, std::function<void(DirectedEdge<T> *, Vertex<T> *)> handleEdgeAndVertex = nullptr);
	void depthFirstSearch(Vertex<T> *s, std::function<void(DirectedEdge<T> *, Vertex<T> *)> handleEdgeAndVertex = nullptr, std::function<void(Vertex<T> *)> run_end = nullptr);
	void reverseDepthFirstSearch(Vertex<T> *s, std::function<void(DirectedEdge<T> *, Vertex<T> *)> handleEdgeAndVertex = nullptr, std::function<void(Vertex<T> *)> run_end = nullptr);
	
	void shortestPathByEdgeCardinality(Vertex<T> *s);
	void topologicalSorting();
	void stronglyConnectedComponents(); 
	
	void disp();
};


template <typename T>
void DirectedGraph<T>::inputLineHandler1(DirectedGraph<T> *g, std::string &line, std::function<T(const std::string &)> parser) {
	trim(line);
	if (line.size() == 0) return;
	
	std::size_t tab_pos = line.find('\t');
	
	if (tab_pos != std::string::npos) { // got two vertices 
		T vData = parser(line.substr(0, tab_pos));
		T wData = parser(line.substr(tab_pos + 1));
		
		Vertex<T> *v = g->getOrCreateVertex(vData);
		Vertex<T> *w = g->getOrCreateVertex(wData);
		
		DirectedEdge<T> *e = g->insertEdge(g->createEdge(v, w));
		g->addEdgeToAdjacencyList(e, v);
		g->addEdgeToIncomingEdgesList(e, w);
	}
	else {
		T vertexData = parser(line);
		g->getOrCreateVertex(vertexData);
	}
}

template <typename T>
Vertex<T> * DirectedGraph<T>::getOrCreateVertex(T val) {
	if (!vertex_exists(val)) {
		return valueToVertexMapper[val] = insertVertex(createVertex(val));
	}
	else {
		return valueToVertexMapper[val];
	}
}

template <typename T>
void DirectedGraph<T>::initWithFile(const std::string filename, std::function<void(DirectedGraph<T> *, std::string &, std::function<T(const std::string &)>)> inputLineHandler, std::function<T(const std::string &)> parser) {
	std::string line;
	std::ifstream myfile(filename);
	
	if (!myfile.is_open()) {
		throw -1;
	}
	else {
		while (getline(myfile, line)) {
			inputLineHandler(this, line, parser);
		}
	}
	
}

template <typename T>
void DirectedGraph<T>::markAllVerticesUnexplored() {
	for (Vertex<T> *v = vertices->traverseInit(); v; v = vertices->traverseNext())
		v->explored = false;
}

template <typename T>
void DirectedGraph<T>::breadthFirstSearch(Vertex<T> *s, std::function<void(DirectedEdge<T> *, Vertex<T> *)> handleEdgeAndVertex) {
	Queue<Vertex<T> *> *q = new Queue<Vertex<T> *>();
	
	q->enqueue(s);
	if (handleEdgeAndVertex) handleEdgeAndVertex(nullptr, s);
	s->explored = true;
	
	while (!q->isEmpty()) {
		Vertex<T> *v = q->dequeue();
		
		for (DirectedEdge<T> *edge = v->adjacencyList->traverseInit(); edge; edge = v->adjacencyList->traverseNext()) {
			Vertex<T> *adjacent_vertex = edge->second; 
			if (!adjacent_vertex->explored) {
				q->enqueue(adjacent_vertex);
				if (handleEdgeAndVertex) handleEdgeAndVertex(edge, adjacent_vertex);
				adjacent_vertex->explored = true;
			}
		}
	}
	
}

template <typename T>
void DirectedGraph<T>::depthFirstSearch(Vertex<T> *s, std::function<void(DirectedEdge<T> *, Vertex<T> *)> handleEdgeAndVertex, std::function<void(Vertex<T> *)> run_end) {
	if (handleEdgeAndVertex) handleEdgeAndVertex(nullptr, s);
	s->explored = true;
	
	Vertex<T> *v = s;
	
	for (DirectedEdge<T> *edge = v->adjacencyList->traverseInit(); edge; edge = v->adjacencyList->traverseNext()) {
		Vertex<T> *adjacent_vertex = edge->second;
		if (!adjacent_vertex->explored)
			depthFirstSearch(adjacent_vertex, handleEdgeAndVertex, run_end);
	}
	
	if (run_end) run_end(s);
}

template <typename T>
void DirectedGraph<T>::reverseDepthFirstSearch(Vertex<T> *s, std::function<void(DirectedEdge<T> *, Vertex<T> *)> handleEdgeAndVertex, std::function<void(Vertex<T> *)> run_end) {
	if (handleEdgeAndVertex) handleEdgeAndVertex(nullptr, s);
	s->explored = true;
	
	Vertex<T> *v = s;
	
	for (DirectedEdge<T> *edge = v->incomingEdgesList->traverseInit(); edge; edge = v->incomingEdgesList->traverseNext()) {
		Vertex<T> *adjacent_vertex = edge->first; 
		if (!adjacent_vertex->explored)
			reverseDepthFirstSearch(adjacent_vertex, handleEdgeAndVertex, run_end);
	}
	
	if (run_end) run_end(s);
}

template <typename T>
void DirectedGraph<T>::topologicalSorting() {
	markAllVerticesUnexplored();
	int topological_number = vertices->size();
	
	std::function<void(Vertex<T> *)> assign_topological_number =
		[&topological_number] (Vertex<T> *v) -> void {
					v->data->data1 = --topological_number;
		};
	
	
	for (Vertex<T> *v = vertices->traverseInit(); v; v = vertices->traverseNext()) {
		if (!v->explored)
			depthFirstSearch(v, nullptr, assign_topological_number);
	}
	
}


template <typename T>
void DirectedGraph<T>::stronglyConnectedComponents() {
	// Kosaraju's Two Pass Algorithm for finding Strongly Connected Components
	
	////////////////////////////////////////////////////////////
	// run DFS  on the reverse graph
	markAllVerticesUnexplored();
	std::vector<Vertex<T> *> vertices_ordered;
	
	std::function<void(Vertex<T> *)> add_vertex_to_list =
		[&vertices_ordered] (Vertex<T> *v) -> void {
					vertices_ordered.push_back(v);
		};
	
	for (Vertex<T> *v = vertices->traverseInit(); v; v = vertices->traverseNext()) {
		if (!v->explored)
			reverseDepthFirstSearch(v, nullptr, add_vertex_to_list);
	}
	
	/////////////////////////////////////////////////////////////
	// run DFS again on the original graph according to vertices_ordered
	markAllVerticesUnexplored();

	Vertex<T> *leader;
	std::function<void(DirectedEdge<T> *, Vertex<T> *)> leader_labeler = 
		[&leader] (DirectedEdge<T> *e, Vertex<T> *v) -> void {
			v->data->data3 = leader;
		};
	
	
	for (int i=vertices_ordered.size()-1; i>=0; i--) {
		if (!vertices_ordered[i]->explored) {
			leader = vertices_ordered[i];
			depthFirstSearch(leader, leader_labeler);
		}
	}
	
}

template <typename T>
void DirectedGraph<T>::shortestPathByEdgeCardinality(Vertex<T> *s) {
	markAllVerticesUnexplored();
	
	breadthFirstSearch(s, 
	[] (DirectedEdge<T> *edge, Vertex<T> *vertex) -> void {
		if (edge == nullptr) // seed vertex
			vertex->data->data2 = 0;
		else
			vertex->data->data2 = edge->first->data->data2 + 1;
	}
	);
}

template <typename T>
void DirectedGraph<T>::disp() {
	
	for (Vertex<T> *v = vertices->traverseInit(); v; v = vertices->traverseNext()) {		
		
		std::cout << "V" << v->value << ", X" << v->explored << ", D1:" << v->data->data1 << ", D2:" << v->data->data2 << ", D3:" << v->data->data3->value << ", Adj:";
				
		for (DirectedEdge<T> *edge = v->adjacencyList->traverseInit(); edge; edge = v->adjacencyList->traverseNext())
			std::cout << edge->second->value << " ";
		
		std::cout << ", Inc:";
		
		for (DirectedEdge<T> *edge = v->incomingEdgesList->traverseInit(); edge; edge = v->incomingEdgesList->traverseNext())
			std::cout << edge->first->value << " ";
		
		std::cout << std::endl;
	}
	
}