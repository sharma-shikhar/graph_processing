template <typename T>
class VertexExtraData {
  public:
	
	int data_int_1;
	double data_double_1;
	Vertex<T> *data_pointer_to_vertex_1;
	
	VertexExtraData() : data_int_1(-1), data_double_1(-1), data_pointer_to_vertex_1(nullptr) {}
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
