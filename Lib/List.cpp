template <typename T>
class Node {
  public:
	T data;
	Node<T> *prev;
	Node<T> *next;
	Node(T data) : data(data), prev(nullptr), next(nullptr) {}
	Node(T data, Node<T> *prev, Node<T> *next) : data(data), prev(prev), next(next) {}
};

template <typename T>
class List {
    Node<T> *current_node;
  	Node<T> *head;
	Node<T> *tail;
	int _size;
  public:
	List() : head(nullptr), tail(nullptr), current_node(nullptr), _size(0) {}
	~List() {
		Node<T> *n = this->head;
		Node<T> *cur = nullptr;
		while (n) {
			cur = n;
			n = n->next;
			delete cur;
		}
		_size = 0;
	}
	bool isEmpty() {return head == nullptr;}
	int size() {return _size;}

	T pushBack(T data);
	T popFront();
	Node<T> * moveToFront(Node<T> *);
	
	Node<T> * traverseInitPack() {
		return (this->current_node = this->head);
	}

	T traverseInit() {
		this->current_node = this->head;
		
		if (this->current_node)
			return this->current_node->data;
		else
			return nullptr; 
	}

	Node<T> * traverseNextPack() {
		if (this->current_node)
			return (this->current_node = this->current_node->next);
		else
			return nullptr;
	}

	T traverseNext() {
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
	
	Node<T> * traverseCurrentPack() {
		return this->current_node;
	}

	T traverseCurrent() {
		if (this->current_node)
			return this->current_node->data;
		else
			return nullptr; 
	}
};

template <typename T>
T List<T>::popFront() {
	if (this->isEmpty()) {
		throw -1;
	}
	else if (this->head == this->tail) {
		T data = this->head->data;
		delete this->head;
		this->head = this->tail = nullptr;
		_size--;
		return data;
	}
	else {
		Node<T> *n = this->head;
		T data = n->data;
		this->head = this->head->next;
		this->head->prev = nullptr;
		delete n;
		_size--;
		return data; 
	}
}

template <typename T>
T List<T>::pushBack(T data) {
	Node<T> *n = new Node<T>(data, tail, nullptr);
	
	if (this->isEmpty()) {
		this->head = this->tail = n;
	}
	else {
		this->tail->next = n;
		this->tail = n;
	}
	_size++;
	return n->data;
}

template <typename T>
Node<T> * List<T>::moveToFront(Node<T> *node_to_move) {
	if (!node_to_move) {
		throw -1;
	}
	
	if (node_to_move == this->head) {
		// do nothing
	}
	else if (node_to_move == this->tail) {
		this->tail = this->tail->prev;
		this->tail->next = nullptr;
		
		node_to_move->prev = nullptr;
		node_to_move->next = this->head;
		this->head->prev = node_to_move;
		this->head = node_to_move;
	}
	else {
		node_to_move->prev->next = node_to_move->next;
		node_to_move->next->prev = node_to_move->prev;
		
		node_to_move->prev = nullptr;
		node_to_move->next = this->head;
		this->head->prev = node_to_move;
		this->head = node_to_move;
	}
	
	return node_to_move;
}