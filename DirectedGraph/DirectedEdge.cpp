template <typename T>
class DirectedEdge {
  public:
  	Vertex<T> *first;
	Vertex<T> *second;
	double weight;
	DirectedEdge(Vertex<T> *first, Vertex<T> *second, double weight) : first(first), second(second), weight(weight) {}
	DirectedEdge(Vertex<T> *first, Vertex<T> *second) : first(first), second(second), weight(1) {}
};
