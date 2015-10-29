template <typename T>
class Queue {
	List<T> *q;
  public:
	Queue() {
		q = new List<T>();
	}
	bool isEmpty() {return q->isEmpty();}
	T enqueue(T data);
	T dequeue();
};

template <typename T>
T Queue<T>::enqueue(T data) {
	return q->pushBack(data);
}

template <typename T>
T Queue<T>::dequeue() {
	return q->popFront();
}