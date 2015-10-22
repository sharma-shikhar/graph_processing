class VertexExtraData {
  public:
	double distance;
	int topological_order;
	VertexExtraData() : distance(0), topological_order(-1) {}
};

template <typename T>
class Vertex {
  public:
  	VertexExtraData *data;
	T value;
	bool explored;
	List<DirectedEdge<T> *> *adjacencyList;
	List<DirectedEdge<T> *> *incomingEdgesList;
	Vertex(T value) : value(value), explored(false) {
		data = new VertexExtraData();
		adjacencyList = new List<DirectedEdge<T> *>;
		incomingEdgesList = new List<DirectedEdge<T> *>;
	}
	static int parser(const std::string &str);
	~Vertex() {delete adjacencyList; delete incomingEdgesList;}
};

template <typename T>
int Vertex<T>::parser(const std::string &str) {
	std::stringstream ss(str);
	T data;
	ss >> data;
	return data;
}
