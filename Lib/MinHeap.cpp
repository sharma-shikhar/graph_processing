

template <typename K, typename V>
class MinHeap {
	std::vector<std::pair<K,V>> arr;
	std::unordered_map<V, int> elementToIndexMapper;
	
	int par(int ch) {return (ch-1)/2;}
	int l_ch(int par) {return 2*par + 1;}
	int r_ch(int par) {return 2*par + 2;}
	
	void swap(int i, int j);
	
	int maxHeapify(int i);
	int bubbleUp(int i);
	
	void updateElementIndexInMapper(V element, int index) {elementToIndexMapper[element] = index;}
	void deleteElementFromMapper(V element) {elementToIndexMapper.erase(element);}
	void insertElementInMapper(V element, int index) {elementToIndexMapper[element] = index;}
  public:
	int size() {return arr.size();}
	bool isEmpty() {return arr.size() == 0;}
	bool elementExists(V element) {return elementToIndexMapper.find(element) != elementToIndexMapper.end();}
	
	MinHeap() {}
	std::pair<K,V> insert(std::pair<K,V> p);
	std::pair<K,V> insert(K key, V val);
	std::pair<K,V> extractMin();
	std::pair<K,V> peekMin();
	void disp();
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
	insertElementInMapper(p.second, arr.size()-1);
	bubbleUp(arr.size() - 1);
	return p;
}

template <typename K, typename V>
std::pair<K,V> MinHeap<K,V>::insert(K key, V val) {
	return this->insert(std::pair<K,V>(key, val));
}

template <typename K, typename V>
std::pair<K,V> MinHeap<K,V>::extractMin() {
	std::pair<K,V> min = arr[0];
	std::pair<K,V> last_el = arr[arr.size()-1];
	arr.pop_back();
	if (arr.size() > 0) {
		arr[0] = last_el;
		maxHeapify(0);
	}
	deleteElementFromMapper(min.second);
	return min;
}

template <typename K, typename V>
std::pair<K,V> MinHeap<K,V>::peekMin() {
	return arr[0];
}

template <typename K, typename V>
int MinHeap<K,V>::maxHeapify(int i) {
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
		updateElementIndexInMapper(arr[i].second, i);
		updateElementIndexInMapper(arr[smallest].second, smallest);
		return maxHeapify(smallest);
	}
	
	return i;
}

template <typename K, typename V>
int MinHeap<K,V>::bubbleUp(int i) {
	while (par(i) >= 0 && arr[i].first < arr[par(i)].first) {
		swap(i, par(i));
		updateElementIndexInMapper(arr[i].second, i);
		updateElementIndexInMapper(arr[par(i)].second, par(i));
		i = par(i);
	}
	return i;
}