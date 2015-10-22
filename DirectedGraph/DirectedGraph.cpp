#include <fstream>
#include <unordered_map>
#include "header.hpp"
#include "../Lib/List.cpp"
#include "../Lib/Queue.cpp"
#include "../Lib/string_funcs.cpp"
#include "Vertex.cpp"
#include "DirectedEdge.cpp"


template <typename T>
class DirectedGraph {
	public:
	
	static void input_line_handler_1(DirectedGraph<T> *g, std::string &line, std::function<T(const std::string &)> parser);
	
	List<Vertex<T> *> *vertices;
	List<DirectedEdge<T> *> *edges;
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
	DirectedEdge<T> *add_edge_to_adjacency_list(DirectedEdge<T> *e, Vertex<T> *v) {
		v->adjacencyList->push_back(e);
	}
	DirectedEdge<T> *add_edge_to_incoming_edges_list(DirectedEdge<T> *e, Vertex<T> *v) {
		v->incomingEdgesList->push_back(e);
	}
	
	DirectedEdge<T> *create_edge(Vertex<T> *v1, Vertex<T> *v2) {
		return new DirectedEdge<T>(v1, v2);
	}
	DirectedEdge<T> *insert_edge(DirectedEdge<T> *e) {
		return edges->push_back(e);
	}
	Vertex<T> *get_or_create_vertex(T val);
	DirectedGraph() {
		vertices = new List<Vertex<T> *>();
		edges = new List<DirectedEdge<T> *>();
	}
	
	void init_with_file(const std::string filename, std::function<void(DirectedGraph<T> *, std::string &, std::function<T(const std::string &)>)> input_line_handler = DirectedGraph<T>::input_line_handler_1, std::function<T(const std::string &)> parser = Vertex<T>::parser);
	
	void mark_all_vertices_unexplored();
	void bfs_from(Vertex<T> *s, std::function<void(DirectedEdge<T> *, Vertex<T> *)> handle_edge_and_vertex = nullptr);
	void dfs_from(Vertex<T> *s, std::function<void(DirectedEdge<T> *, Vertex<T> *)> handle_edge_and_vertex = nullptr, std::function<void(Vertex<T> *)> run_end = nullptr);
	void rev_dfs_from(Vertex<T> *s, std::function<void(DirectedEdge<T> *, Vertex<T> *)> handle_edge_and_vertex = nullptr, std::function<void(Vertex<T> *)> run_end = nullptr);
	
	void shortest_path_by_edge_cardinality(Vertex<T> *s);
	void topological_sorting();
	
	void disp();
};


template <typename T>
void DirectedGraph<T>::input_line_handler_1(DirectedGraph<T> *g, std::string &line, std::function<T(const std::string &)> parser) {
	trim(line);
	if (line.size() == 0) return;
	
	std::size_t tab_pos = line.find('\t');
	
	if (tab_pos != std::string::npos) { // got two vertices 
		T vData = parser(line.substr(0, tab_pos));
		T wData = parser(line.substr(tab_pos + 1));
		
		Vertex<T> *v = g->get_or_create_vertex(vData);
		Vertex<T> *w = g->get_or_create_vertex(wData);
		
		DirectedEdge<T> *e = g->insert_edge(g->create_edge(v, w));
		g->add_edge_to_adjacency_list(e, v);
		g->add_edge_to_incoming_edges_list(e, w);
	}
	else {
		T vertexData = parser(line);
		g->get_or_create_vertex(vertexData);
	}
}

template <typename T>
Vertex<T> * DirectedGraph<T>::get_or_create_vertex(T val) {
	if (!vertex_exists(val)) {
		return mapper[val] = insert_vertex(create_vertex(val));
	}
	else {
		return mapper[val];
	}
}

template <typename T>
void DirectedGraph<T>::init_with_file(const std::string filename, std::function<void(DirectedGraph<T> *, std::string &, std::function<T(const std::string &)>)> input_line_handler, std::function<T(const std::string &)> parser) {
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
void DirectedGraph<T>::mark_all_vertices_unexplored() {
	Vertex<T> *v = vertices->traverse_init();
	while (v) {		
		v->explored = false;
		v = vertices->traverse_next();
	}
}

template <typename T>
void DirectedGraph<T>::bfs_from(Vertex<T> *s, std::function<void(DirectedEdge<T> *, Vertex<T> *)> handle_edge_and_vertex) {
	Queue<Vertex<T> *> *q = new Queue<Vertex<T> *>();
	
	q->enqueue(s);
	if (handle_edge_and_vertex) handle_edge_and_vertex(nullptr, s);
	s->explored = true;
	
	while (!q->empty()) {
		Vertex<T> *v = q->dequeue();
		
		DirectedEdge<T> *edge = v->adjacencyList->traverse_init();
		while (edge) {
			Vertex<T> *adjacent_vertex = edge->second; 
			if (adjacent_vertex->explored == false) {
				q->enqueue(adjacent_vertex);
				if (handle_edge_and_vertex) handle_edge_and_vertex(edge, adjacent_vertex);
				adjacent_vertex->explored = true;
			}
			edge = v->adjacencyList->traverse_next();
		}
		
	}
}

template <typename T>
void DirectedGraph<T>::dfs_from(Vertex<T> *s, std::function<void(DirectedEdge<T> *, Vertex<T> *)> handle_edge_and_vertex, std::function<void(Vertex<T> *)> run_end) {
	if (handle_edge_and_vertex) handle_edge_and_vertex(nullptr, s);
	s->explored = true;
	
	Vertex<T> *v = s;
	DirectedEdge<T> *edge = v->adjacencyList->traverse_init();
	while (edge) {
		Vertex<T> *adjacent_vertex = edge->second;
		if (adjacent_vertex->explored == false) {
			dfs_from(adjacent_vertex, handle_edge_and_vertex, run_end);
		}
		edge = v->adjacencyList->traverse_next();
	}
	
	if (run_end) run_end(s);
}

template <typename T>
void DirectedGraph<T>::rev_dfs_from(Vertex<T> *s, std::function<void(DirectedEdge<T> *, Vertex<T> *)> handle_edge_and_vertex, std::function<void(Vertex<T> *)> run_end) {
	if (handle_edge_and_vertex) handle_edge_and_vertex(nullptr, s);
	s->explored = true;
	
	Vertex<T> *v = s;
	DirectedEdge<T> *edge = v->incomingEdgesList->traverse_init();
	while (edge) {
		Vertex<T> *adjacent_vertex = edge->first; 
		if (adjacent_vertex->explored == false) {
			rev_dfs_from(adjacent_vertex, handle_edge_and_vertex, run_end);
		}
		edge = v->incomingEdgesList->traverse_next();
	}
	
	if (run_end) run_end(s);
}

template <typename T>
void DirectedGraph<T>::topological_sorting() {
	mark_all_vertices_unexplored();
	int topological_number = vertices->size();
	
	std::function<void(Vertex<T> *)> assign_topological_number =
		[&topological_number] (Vertex<T> *v) -> void {
					v->data->data1 = --topological_number;
		};
	
	Vertex<T> *v = vertices->traverse_init();
	while (v) {
		if (v->explored == false) {
			dfs_from(v, nullptr, assign_topological_number);
		}
		
		v = vertices->traverse_next();
	}
}



template <typename T>
void DirectedGraph<T>::shortest_path_by_edge_cardinality(Vertex<T> *s) {
	mark_all_vertices_unexplored();
	
	bfs_from(s, 
	[] (DirectedEdge<T> *edge, Vertex<T> *vertex) -> void {
		if (edge == nullptr) { // seed vertex
			vertex->data->data2 = 0;
		} else {
			vertex->data->data2 = edge->first->data->data2 + 1;
		}
	}
	);
}

template <typename T>
void DirectedGraph<T>::disp() {
	
	Vertex<T> *v = vertices->traverse_init();
	
	while (v) {		
		std::cout << "V" << v->value << ", X" << v->explored << ", D1:" << v->data->data1 << ", D2:" << v->data->data2 << ", Adj:";
		
		DirectedEdge<T> *edge = v->adjacencyList->traverse_init();
		while (edge) {
			std::cout << edge->second->value << " ";
			edge = v->adjacencyList->traverse_next();
		}
		
		std::cout << ", Inc:";
		edge = v->incomingEdgesList->traverse_init();
		while (edge) {
			std::cout << edge->first->value << " ";
			edge = v->incomingEdgesList->traverse_next();
		}
		
		v = vertices->traverse_next();
		std::cout << std::endl;
	}
	
}