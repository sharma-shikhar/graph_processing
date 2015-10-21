template <typename T>
class Queue {
	List<T> *q;
  public:
	Queue() {
		q = new List<T>();
	}
	bool empty() {return q->empty();}
	T enqueue(T data);
	T dequeue();
};

template <typename T>
T Queue<T>::enqueue(T data) {
	return q->push_back(data);
}

template <typename T>
T Queue<T>::dequeue() {
	return q->pop_front();
}