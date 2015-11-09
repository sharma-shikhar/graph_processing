#include <fstream>
#include <unordered_map>
#include "header.hpp"
#include "../Lib/List.cpp"
#include "../Lib/Queue.cpp"
#include "Vertex.cpp"
#include "UndirectedEdge.cpp"
#include "../Lib/string_funcs.cpp"

template <typename T>
class UndirectedGraph {
	public:
	
	static void inputLineHandler1(UndirectedGraph<T> *g, std::string &line, std::function<T(const std::string &)> parser);
		
	List<Vertex<T> *> _vertices;
	List<Vertex<T> *> *vertices = &_vertices;
	
	List<UndirectedEdge<T> *> _edges;
	List<UndirectedEdge<T> *> *edges = &_edges;
	
	std::unordered_map<T, Vertex<T> *> valueToVertexMapper;
	
	bool vertexExists(const T &val) {
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
	UndirectedEdge<T> *addEdgeToAdjacencyList(UndirectedEdge<T> *e, Vertex<T> *v) {
		v->adjacencyList->pushBack(e);
	}
	
	UndirectedEdge<T> *createEdge(Vertex<T> *v1, Vertex<T> *v2) {
		return new UndirectedEdge<T>(v1, v2);
	}
	UndirectedEdge<T> *insertEdge(UndirectedEdge<T> *e) {
		return edges->pushBack(e);
	}
	Vertex<T> *getOrCreateVertex(T val);
	
	UndirectedGraph() {}
	
	void initWithFile(const std::string filename, std::function<void(UndirectedGraph<T> *, std::string &, std::function<T(const std::string &)>)> inputLineHandler = UndirectedGraph<T>::inputLineHandler1, std::function<T(const std::string &)> parser = Vertex<T>::parser);
	void markAllVerticesUnexplored();
	void breadthFirstSearch(Vertex<T> *s, std::function<void(UndirectedEdge<T> *, Vertex<T> *)> handleEdgeAndVertex = nullptr);
	void depthFirstSearch(Vertex<T> *s, std::function<void(UndirectedEdge<T> *, Vertex<T> *)> handleEdgeAndVertex = nullptr, std::function<void(Vertex<T> *)> run_end = nullptr);
	void shortestPathByEdgeCardinality(Vertex<T> *s);
	
	void connectedComponents();
	
	void disp();
};

template <typename T>
void UndirectedGraph<T>::inputLineHandler1(UndirectedGraph<T> *g, std::string &line, std::function<T(const std::string &)> parser) {
	trim(line);
	if (line.size() == 0) return;
	
	std::size_t tab_pos = line.find('\t');
	
	if (tab_pos != std::string::npos) { // got two vertices 
		T vData = parser(line.substr(0, tab_pos));
		T wData = parser(line.substr(tab_pos + 1));
		
		Vertex<T> *v = g->getOrCreateVertex(vData);
		Vertex<T> *w = g->getOrCreateVertex(wData);
		
		UndirectedEdge<T> *e = g->insertEdge(g->createEdge(v, w));
		g->addEdgeToAdjacencyList(e, v);
		g->addEdgeToAdjacencyList(e, w);
	}
	else {
		T vertexData = parser(line);
		g->getOrCreateVertex(vertexData);
	}
}


template <typename T>
Vertex<T> * UndirectedGraph<T>::getOrCreateVertex(T val) {
	if (!vertexExists(val)) {
		return valueToVertexMapper[val] = insertVertex(createVertex(val));
	}
	else {
		return valueToVertexMapper[val];
	}
}

template <typename T>
void UndirectedGraph<T>::initWithFile(const std::string filename, std::function<void(UndirectedGraph<T> *, std::string &, std::function<T(const std::string &)>)> inputLineHandler, std::function<T(const std::string &)> parser) {
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
void UndirectedGraph<T>::markAllVerticesUnexplored() {
	for (Vertex<T> *v = vertices->traverseInit(); v; v = vertices->traverseNext()) {
		v->explored = false;
	}
}

template <typename T>
void UndirectedGraph<T>::breadthFirstSearch(Vertex<T> *s, std::function<void(UndirectedEdge<T> *, Vertex<T> *)> handleEdgeAndVertex) {
	Queue<Vertex<T> *> *q = new Queue<Vertex<T> *>();
	
	q->enqueue(s);
	if (handleEdgeAndVertex) handleEdgeAndVertex(nullptr, s);
	s->explored = true;
	
	while (!q->isEmpty()) {
		Vertex<T> *v = q->dequeue();
		
		for (UndirectedEdge<T> *edge = v->adjacencyList->traverseInit(); edge; edge = v->adjacencyList->traverseNext()) {
			Vertex<T> *adjacent_vertex = edge->getOtherVertex(v); 
			
			if (!adjacent_vertex->explored) {
				q->enqueue(adjacent_vertex);
				if (handleEdgeAndVertex) handleEdgeAndVertex(edge, adjacent_vertex);
				adjacent_vertex->explored = true;
			}
		
		}	
	}
	
}

template <typename T>
void UndirectedGraph<T>::depthFirstSearch(Vertex<T> *s, std::function<void(UndirectedEdge<T> *, Vertex<T> *)> handleEdgeAndVertex, std::function<void(Vertex<T> *)> run_end) {
	if (handleEdgeAndVertex) handleEdgeAndVertex(nullptr, s);
	s->explored = true;
	
	Vertex<T> *v = s;
	
	for (UndirectedEdge<T> *edge = v->adjacencyList->traverseInit(); edge; edge = v->adjacencyList->traverseNext()) {
		Vertex<T> *adjacent_vertex = edge->getOtherVertex(v); 
		if (!adjacent_vertex->explored)
			depthFirstSearch(adjacent_vertex, handleEdgeAndVertex, run_end);
	}
	
	if (run_end) run_end();
}

template <typename T>
void UndirectedGraph<T>::shortestPathByEdgeCardinality(Vertex<T> *s) {
	markAllVerticesUnexplored();
	
	breadthFirstSearch(s, 
		[] (UndirectedEdge<T> *edge, Vertex<T> *vertex) -> void {
			if (edge == nullptr) // seed vertex
				vertex->data->data2 = 0;
			else
				vertex->data->data2 = edge->getOtherVertex(vertex)->data->data2 + 1;
		}
	);
}


template <typename T>
void UndirectedGraph<T>::connectedComponents() {
	markAllVerticesUnexplored();
	
	int component_number = 0;
	std::function<void(UndirectedEdge<T> *edge, Vertex<T> *vertex)> assign_component_number =
		[&component_number] (UndirectedEdge<T> *edge, Vertex<T> *vertex) -> void {
					vertex->data->data1 = component_number;
		};
		
	for (Vertex<T> *v = vertices->traverseInit(); v; v = vertices->traverseNext()) {
		if (!v->explored) {
			breadthFirstSearch(v, assign_component_number);
			component_number++;
		}
	}
	
}

template <typename T>
void UndirectedGraph<T>::disp() {
	
	for (Vertex<T> *v = vertices->traverseInit(); v; v = vertices->traverseNext()) {		
		std::cout << "V" << v->value << ", X" << v->explored << ", D1:" << v->data->data1 << ", D2:" << v->data->data2 << ", D3:" << v->data->data3->value << ", Adj:";
		
		for (UndirectedEdge<T> *edge = v->adjacencyList->traverseInit(); edge; edge = v->adjacencyList->traverseNext())
			std::cout << edge->getOtherVertex(v)->value << " ";
		
		std::cout << std::endl;
	}
	
}