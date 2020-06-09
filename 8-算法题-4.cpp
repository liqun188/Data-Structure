//��Ⱥ 2019212340 
#include <iostream>
#include <queue>

using namespace std;

struct Node {    //��Ŀ�����Ľ��洢��ʽ  
	int order;
	Node *lc, *rc, *p;
};

Node *getTree(int n);    //��������n�У�ÿ������������������n���������ı�ţ������������Ҷ��� 

void vis(Node *root);   //�������㷨��ʹ�ö���ʵ�� 

int main() {
	int n;
	Node *root;
	cin >> n;    //���ĸ��� 
	root = getTree(n);    //����n�������� 
	vis(root);
	return 0;
}

Node *getTree(int n) {
	Node **map;
	map = new Node* [n+1];    //ӳ������ڴ洢n�����Ĵ洢��ַ 
	for(int i = 0; i <= n; i++)
		map[i] = NULL;
	for(int i = 1; i <= n; i++) {    //����n�еĹ�ϵ 
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
	for(int i = 1; i <= n; i++) {    //����Ѱ�Ҹ��ڵ㣨û�и��ڵ�Ľ�㣩 
		if(map[i]->p == NULL) {
			root = map[i];
			break;
		}
	}
	delete[] map;    //ɾ��ӳ��� 
	return root;
}

void vis(Node *root) {    //�������㷨ʵ�֣�ʹ�ö��н��а������ 
	queue<Node*> q;
	q.push(root);    //�����ڵ���� 
	while(!q.empty()) {
		Node *cur;
		cur = q.front();
		q.pop();
		cout << cur->order << ' ';    //������׽�㣬����������������� 
		if(cur->lc)  q.push(cur->lc);
		if(cur->rc)  q.push(cur->rc);
	}
	cout << endl;
}
//Sample��
//12          ��ʮ������㣩 
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
