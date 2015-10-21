template <typename T>
class Node {
  public:
	T data;
	Node<T> *next;
	Node(T data) : data(data), next(nullptr) {}
	Node(T data, Node<T> *next) : data(data), next(next) {}
};

template <typename T>
class List {
    Node<T> *current_node;
  public:
	Node<T> *head;
	Node<T> *tail;
	List() : head(nullptr), tail(nullptr), current_node(nullptr) {}
	~List() {
		Node<T> *n = this->head;
		Node<T> *cur = nullptr;
		while (n) {
			cur  = n;
			n = n->next;
			delete cur;
		}
	}
	bool empty() {return head == nullptr;}

	T push_back(T data);
	T pop_front();

	T traverse_init() {
		this->current_node = this->head;
		
		if (this->current_node)
			return this->current_node->data;
		else
			return nullptr; 
	}

	T traverse_next() {
		if (this->current_node) {
			this->current_node = this->current_node->next;
			if (this->current_node)
				return this->current_node->data;
			else
				return nullptr; 
		}
		else
			return nullptr;
	}
	

	T traverse_current() {
		if (this->current_node)
			return this->current_node->data;
		else
			return nullptr; 
	}
};

template <typename T>
T List<T>::pop_front() {
	if (this->empty()) {
		throw -1;
	}
	else if (this->head == this->tail) {
		T data = this->head->data;
		delete this->head;
		this->head = this->tail = nullptr;
		return data;
	}
	else {
		Node<T> *n = this->head;
		T data = n->data;
		this->head = this->head->next;
		delete n;
		return data; 
	}
}

template <typename T>
T List<T>::push_back(T data) {
	Node<T> *n = new Node<T>(data, nullptr);
	
	if (this->empty()) {
		this->head = this->tail = n;
	}
	else {
		this->tail->next = n;
		this->tail = n;
	}
	
	return n->data;
}