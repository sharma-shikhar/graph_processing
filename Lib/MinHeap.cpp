

template <typename K, typename V>
class MinHeap {
	std::vector<std::pair<K,V>> arr;
	
	int par(int ch) {return (ch-1)/2;}
	int l_ch(int par) {return 2*par + 1;}
	int r_ch(int par) {return 2*par + 2;}
	
	void swap(int i, int j);
	
	void max_heapify(int i);
	void bubble_up(int i);
  public:
	int size() {return arr.size();}
	bool empty() {return arr.size() == 0;}
	MinHeap() {}
	std::pair<K,V> insert(std::pair<K,V> p);
	std::pair<K,V> insert(K key, V val);
	std::pair<K,V> extract_min();
	std::pair<K,V> peek_min();
};

template <typename K, typename V>
void MinHeap<K,V>::swap(int i, int j) {
	std::pair<K,V> tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}

template <typename K, typename V>
std::pair<K,V> MinHeap<K,V>::insert(std::pair<K,V> p) {
	arr.push_back(p);
	bubble_up(arr.size() - 1);
	return p;
}

template <typename K, typename V>
std::pair<K,V> MinHeap<K,V>::insert(K key, V val) {
	return this->insert(std::pair<K,V>(key, val));
}

template <typename K, typename V>
std::pair<K,V> MinHeap<K,V>::extract_min() {
	std::pair<K,V> min = arr[0];
	std::pair<K,V> last_el = arr[arr.size()-1];
	arr.pop_back();
	if (arr.size() > 0) {
		arr[0] = last_el;
		max_heapify(0);
	}
	return min;
}

template <typename K, typename V>
std::pair<K,V> MinHeap<K,V>::peek_min() {
	return arr[0];
}

template <typename K, typename V>
void MinHeap<K,V>::max_heapify(int i) {
	int l = l_ch(i);
	int r = r_ch(i);
	int smallest;
	
	if (l >= arr.size() && r >= arr.size()) {
		smallest = i;
	}
	else if (r >= arr.size()) {
		smallest = (arr[l].first < arr[i].first) ? l : i;
	}
	else {
		smallest = (arr[l].first < arr[r].first) ? l : r;
		smallest = (arr[smallest].first < arr[i].first) ? smallest : i;
	}
	
	if (smallest != i) {
		swap(i, smallest);
		max_heapify(smallest);
	}
	
}

template <typename K, typename V>
void MinHeap<K,V>::bubble_up(int i) {
	while (par(i) >= 0 && arr[i].first < arr[par(i)].first) {
		swap(i, par(i));
		i = par(i);
	}
}