template <typename T>
class VertexExtraData {
  public:
  	int data1;
	double data2;
	Vertex<T> *data3;
	VertexExtraData() : data1(-1), data2(-1), data3(nullptr) {}
};

template <typename T>
class Vertex {
  public:
  	VertexExtraData<T> *data;
	T value;
	bool explored;
	List<DirectedEdge<T> *> *adjacencyList;
	List<DirectedEdge<T> *> *incomingEdgesList;
	Vertex(T value) : value(value), explored(false) {
		data = new VertexExtraData<T>();
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
