//李群 2019212340 
#include <iostream>
#include <queue>

using namespace std;

struct Node {    //题目描述的结点存储方式  
	int order;
	Node *lc, *rc, *p;
};

Node *getTree(int n);    //读入树，n行，每行三个数（均不超过n，代表树的标号），结点和其左右儿子 

void vis(Node *root);   //第四题算法，使用队列实现 

int main() {
	int n;
	Node *root;
	cin >> n;    //结点的个数 
	root = getTree(n);    //读入n个结点的树 
	vis(root);
	return 0;
}

Node *getTree(int n) {
	Node **map;
	map = new Node* [n+1];    //映射表，用于存储n个结点的存储地址 
	for(int i = 0; i <= n; i++)
		map[i] = NULL;
	for(int i = 1; i <= n; i++) {    //读入n行的关系 
		int p, l, r;
		cin >> p >> l >> r;
		if(!map[p]) {
			map[p] = new Node;
			map[p]->p = NULL;
		}
		map[p]->order = p;
		if(l && !map[l]) {
			map[l] = new Node;
			map[l]->p = map[p];
		}
		if(r && !map[r]) {
			map[r] = new Node;
			map[r]->p = map[p];
		}
		map[p]->lc = map[l];
		map[p]->rc = map[r];
	}
	Node *root;
	for(int i = 1; i <= n; i++) {    //用于寻找根节点（没有父节点的结点） 
		if(map[i]->p == NULL) {
			root = map[i];
			break;
		}
	}
	delete[] map;    //删除映射表 
	return root;
}

void vis(Node *root) {    //第四题算法实现，使用队列进行按层输出 
	queue<Node*> q;
	q.push(root);    //将根节点入队 
	while(!q.empty()) {
		Node *cur;
		cur = q.front();
		q.pop();
		cout << cur->order << ' ';    //输出队首结点，并将其两个儿子入队 
		if(cur->lc)  q.push(cur->lc);
		if(cur->rc)  q.push(cur->rc);
	}
	cout << endl;
}
//Sample：
//12          （十二个结点） 
//1 2 3   
//2 4 0   
//3 5 6    
//4 7 8   
//5 0 0   
//6 0 9   
//7 0 0   
//8 10 11
//9 0 0   
//10 12 0  
//11 0 0  
//12 0 0   
