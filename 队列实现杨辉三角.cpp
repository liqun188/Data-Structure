//李群 2019212340
//使用队列实现杨辉三角 
#include <iostream>

using namespace std;

template <class T>  //队列的实现 
class queue {
private:
	struct node{
		T data;
		node *pre;
		node *next;
	};
	int _size;
	node *head, *tail;
public:
	queue() {
		head = tail = new node;
		_size = 0;
	}
	
	bool pop(T &x) {
		if(_size == 0) return false;
		x = head->data;
		head = head->pre;
		if(head){
			delete (head->next);
			head->next = NULL;
		}else{
			tail = NULL;
		}
		_size--;
		return true;
	}
	
	bool push(T x) {
		node *tmp;
		tmp = new node;
		if(tmp == NULL) return false;
		tmp->data = x;
		if(tail)  tail->pre = tmp;
		tmp->pre = NULL;
		tmp->next = tail;
		tail = tmp;
		if(_size == 0) head = tmp;
		_size++;
		return true;
	}
	
	int size() {
		return _size;
	}
	
	bool front(T &x) {
		if(_size == 0) return false;
		x = head->data;
		return true;
	}
	
	bool back(T &x) {
		if(_size == 0) return false;
		x = tail->data;
		return true;
	}
	
	bool empty() {
		return !_size;
	}
	
	~queue() {
		while(!empty()) {
			T tmp;
			pop(tmp);
		}
	}
};

int main() {
	int n;
	cin >> n;
	queue<int> q;
	q.push(1);
	for(int i = 1; i < n; i++) {    //输出第i行并构造第i+1行 
		q.push(1);
		for(int j = 1; j < i; j++) {
			int x, y;
			q.pop(x);
			cout << x << ' ';
			q.front(y);
			q.push(x + y);
		}
		int x;
		q.pop(x);
		cout << x << endl;
		q.push(1);
	}
	while(!q.empty()) {    //输出最后一行 
		int x;
		q.pop(x);
		cout << x << ' ';
	}
	return 0;
}
	
