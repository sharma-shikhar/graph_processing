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
	T value;
	bool explored;
	
	VertexExtraData<T> _data;
	VertexExtraData<T> *data = &_data;
	
	List<UndirectedEdge<T> *> _adjacencyList;
	List<UndirectedEdge<T> *> *adjacencyList = &_adjacencyList;
	
	Vertex(T value) : value(value), explored(false) {}
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
