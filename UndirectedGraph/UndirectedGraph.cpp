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
	
	static void input_line_handler_1(UndirectedGraph<T> *g, std::string &line, std::function<T(const std::string &)> parser);
		
	List<Vertex<T> *> *vertices;
	List<UndirectedEdge<T> *> *edges;
	std::unordered_map<T, Vertex<T> *> mapper;
	
	bool vertex_exists(const T &val) {
		return mapper.find(val) != mapper.end();
	}
	Vertex<T> *get_vertex(const T &val) {
		return mapper[val];
	}
	
	Vertex<T> *create_vertex(T value) {
		return new Vertex<T>(value);
	}
	Vertex<T> *insert_vertex(Vertex<T> *v) {
		return vertices->push_back(v);
	}
	UndirectedEdge<T> *add_edge_to_adjacency_list(UndirectedEdge<T> *e, Vertex<T> *v) {
		v->adjacencyList->push_back(e);
	}
	
	UndirectedEdge<T> *create_edge(Vertex<T> *v1, Vertex<T> *v2) {
		return new UndirectedEdge<T>(v1, v2);
	}
	UndirectedEdge<T> *insert_edge(UndirectedEdge<T> *e) {
		return edges->push_back(e);
	}
	Vertex<T> *get_or_create_vertex(T val);
	UndirectedGraph() {
		vertices = new List<Vertex<T> *>();
		edges = new List<UndirectedEdge<T> *>();
	}
	void init_with_file(const std::string filename, std::function<void(UndirectedGraph<T> *, std::string &, std::function<T(const std::string &)>)> input_line_handler, std::function<T(const std::string &)> parser);
	void mark_all_vertices_unexplored();
	void bfs_from(Vertex<T> *s, std::function<void(UndirectedEdge<T> *, Vertex<T> *)> handle_edge_and_vertex);
	void shortest_path_by_edge_cardinality(Vertex<T> *s);
	
	void connected_components();
	
	void disp();
};

template <typename T>
void UndirectedGraph<T>::input_line_handler_1(UndirectedGraph<T> *g, std::string &line, std::function<T(const std::string &)> parser) {
	trim(line);
	if (line.size() == 0) return;
	
	std::size_t tab_pos = line.find('\t');
	
	if (tab_pos != std::string::npos) { // got two vertices 
		T vData = parser(line.substr(0, tab_pos));
		T wData = parser(line.substr(tab_pos + 1));
		
		Vertex<T> *v = g->get_or_create_vertex(vData);
		Vertex<T> *w = g->get_or_create_vertex(wData);
		
		UndirectedEdge<T> *e = g->insert_edge(g->create_edge(v, w));
		g->add_edge_to_adjacency_list(e, v);
		g->add_edge_to_adjacency_list(e, w);
	}
	else {
		T vertexData = parser(line);
		g->get_or_create_vertex(vertexData);
	}
}


template <typename T>
Vertex<T> * UndirectedGraph<T>::get_or_create_vertex(T val) {
	if (!vertex_exists(val)) {
		return mapper[val] = insert_vertex(create_vertex(val));
	}
	else {
		return mapper[val];
	}
}

template <typename T>
void UndirectedGraph<T>::init_with_file(const std::string filename, std::function<void(UndirectedGraph<T> *, std::string &, std::function<T(const std::string &)>)> input_line_handler, std::function<T(const std::string &)> parser) {
	std::string line;
	std::ifstream myfile(filename);
	
	if (!myfile.is_open()) {
		throw -1;
	}
	else {
		while (getline(myfile, line)) {
			input_line_handler(this, line, parser);
		}
	}
	
}

template <typename T>
void UndirectedGraph<T>::mark_all_vertices_unexplored() {
	Vertex<T> *v = vertices->traverse_init();
	while (v) {		
		v->explored = false;
		v = vertices->traverse_next();
	}
}

template <typename T>
void UndirectedGraph<T>::bfs_from(Vertex<T> *s, std::function<void(UndirectedEdge<T> *, Vertex<T> *)> handle_edge_and_vertex) {
	Queue<Vertex<T> *> *q = new Queue<Vertex<T> *>();
	
	q->enqueue(s);
	handle_edge_and_vertex(nullptr, s);
	s->explored = true;
	
	while (!q->empty()) {
		Vertex<T> *v = q->dequeue();
		
		UndirectedEdge<T> *edge = v->adjacencyList->traverse_init();
		while (edge) {
			Vertex<T> *adjacent_vertex = edge->get_other_vertex(v); 
			if (adjacent_vertex->explored == false) {
				q->enqueue(adjacent_vertex);
				handle_edge_and_vertex(edge, adjacent_vertex);
				adjacent_vertex->explored = true;
			}
			edge = v->adjacencyList->traverse_next();
		}
		
	}
}


template <typename T>
void UndirectedGraph<T>::shortest_path_by_edge_cardinality(Vertex<T> *s) {
	mark_all_vertices_unexplored();
	
	bfs_from(s, 
		[] (UndirectedEdge<T> *edge, Vertex<T> *vertex) -> void {
			if (edge == nullptr) // seed vertex
				vertex->data->distance = 0;
			else
				vertex->data->distance = edge->get_other_vertex(vertex)->data->distance + 1;
		}
	);
}


template <typename T>
void UndirectedGraph<T>::connected_components() {
	mark_all_vertices_unexplored();
	
	Vertex<T> *v = vertices->traverse_init();
	
	int component_number = 0;
	std::function<void(UndirectedEdge<T> *edge, Vertex<T> *vertex)> assign_component_number =
		[&component_number] (UndirectedEdge<T> *edge, Vertex<T> *vertex) -> void {
					vertex->data->component_number = component_number;
		};
		
	while (v) {
		if (!v->explored) {
			bfs_from(v, assign_component_number);
			component_number++;
		}
		
		v = vertices->traverse_next();
	}
	
}

template <typename T>
void UndirectedGraph<T>::disp() {
	
	Vertex<T> *v = vertices->traverse_init();
	
	while (v) {		
		std::cout << "V" << v->value << ", X" << v->explored << ", D" << v->data->distance << ", C" << v->data->component_number << ", Adj:";
		
		UndirectedEdge<T> *edge = v->adjacencyList->traverse_init();
		while (edge) {
			std::cout << edge->get_other_vertex(v)->value << " ";
			edge = v->adjacencyList->traverse_next();
		}
		
		v = vertices->traverse_next();
		std::cout << std::endl;
	}
	
}