class VertexExtraData {
  public:
	int data1;
	double data2;
	VertexExtraData() : data1(-1), data2(-1) {}
};

template <typename T>
class Vertex {
  public:
  	VertexExtraData *data;
	T value;
	bool explored;
	List<UndirectedEdge<T> *> *adjacencyList;
	Vertex(T value) : value(value), explored(false) {
		data = new VertexExtraData();
		adjacencyList = new List<UndirectedEdge<T> *>;
	}
	static int parser(const std::string &str);
	~Vertex() {delete adjacencyList;}
};

template <typename T>
int Vertex<T>::parser(const std::string &str) {
	std::stringstream ss(str);
	T data;
	ss >> data;
	return data;
}
