template <typename T>
class UndirectedEdge {
  public:
  	Vertex<T> *first;
	Vertex<T> *second;
	double weight;
	UndirectedEdge(Vertex<T> *first, Vertex<T> *second, double weight) : first(first), second(second), weight(weight) {}
	UndirectedEdge(Vertex<T> *first, Vertex<T> *second) : first(first), second(second), weight(1) {}
	Vertex<T> *get_other_vertex(Vertex<T> *v) {
		return (v == first) ? second : ((v == second) ? first : nullptr); 
	}
};
