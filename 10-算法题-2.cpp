#include <iostream>

using namespace std;

struct Edge {    //�ߵĶ���
	char u, v;    //u->v 
	struct Edge* unext, * vnext;    //��һ���� 
};

struct Node {    //��Ķ��壬������Ҫ��̬��ɾ�㣬��Ҫ����������
	char data;    //��� 
	Edge* first;    //��һ���� 
	Node* next;    //��һ���� 
};

struct Graph{    //ͼ�Ķ���
	Node* head;
};

bool InsertVex(Graph& G, char v);  //��ͼG�����ӵ�v

bool InsertArc(Graph& G, char u, char v); //��ͼG�����ӱ�(u,v) 

bool DeleteArc(Graph& G, char u, char v) ;    //ɾ���� 

bool DeleteVex(Graph& G, char v);  //ɾ�����

bool CreatGraph(Graph& G, int n, int m);  //����n���㣬m���ߵ�ͼ 

void GraphShow(Graph& G); //���ͼ 

bool GraphDestory(Graph& G);  //����ͼ 
	

int main() {    //���������
	Graph G = {NULL};
	int n, m;
	cin >> n >> m;
	CreatGraph(G, n, m);    //������ͼ 
	cout << "===========================\n";
	GraphShow(G);    //�����ͼ 
	cout << "===========================\n";	

	char u, v;  
	cin >> u;    //����һ�����u��ɾ���� 
	DeleteVex(G, u);
	cout << "===========================\n";
	GraphShow(G);
	cout << "===========================\n";
	
	cin >> u >> v;    //����һ���ߣ�u��v����ɾ���� 
	DeleteArc(G, u, v);
	cout << "===========================\n";
	GraphShow(G);
	cout << "===========================\n";
	
	GraphDestory(G);    //����ͼ 
	GraphShow(G);
	return 0;
}

bool InsertVex(Graph& G, char v) {  //��ͼG�����ӵ�v
	Node* now = G.head;
	while (now) {
		if (now->data == v)  return false;    //�����V���ڣ���ӵ�ʧ�� 
		now = now->next;
	}
	now = new Node;    //������ 
	now->data = v;
	now->first = NULL;     
	now->next = G.head;
	G.head = now;
	return true;
}

bool InsertArc(Graph& G, char u, char v) {    //��ͼG�����ӱ�(u,v) 
	if(u > v)  swap(u, v);    //��u<v��������� 
	Node* tmp = G.head;
	Node* unow = NULL;
	Node* vnow = NULL;
	int cnt = 0;
	while (tmp) {
		if (tmp->data == u || tmp->data == v)  cnt++;
		if (tmp->data == u)  unow = tmp;
		if (tmp->data == v)  vnow = tmp;
		tmp = tmp->next;
	}
	if (cnt < 2)  return false;    //�����u v����ͼ�У��ſ��Լӱߣ�����ӱ�ʧ�� 

	Edge* cur = unow->first;    
	while (cur) {
		if (cur->v == v)  break;
		if(cur->u == unow->data)  cur = cur->unext;
		else  cur = cur->vnext;
	}
	if (cur && cur->v == v)  return false;    //����Ѿ����������ߣ���ӱ�ʧ�� 

	cur = new Edge;    //����һ���� 
	cur->u = u;
	cur->v = v;
	cur->unext = unow->first;
	unow->first = cur;
	cur->vnext = vnow->first;
	vnow->first = cur;
	return true;
}

bool DeleteArc(Graph& G, char u, char v) {    //ɾ���� 
	if(u > v)  swap(u, v);
	Node* tmp = G.head;    //��Ҫά�����������ҳ�����u����ͷ�ͺ���v����ͷ 
	Node* unow = NULL;
	Node* vnow = NULL;
	int cnt = 0;
	while (tmp) {
		if (tmp->data == u || tmp->data == v)  cnt++;
		if (tmp->data == u)  unow = tmp;
		if (tmp->data == v)  vnow = tmp;
		tmp = tmp->next;
	}
	if (cnt < 2)  return false;    //�����u v����ͼ�У��ſ���ɾ�ߣ�����ʧ�� 
	
	Edge* cur = unow->first;    //ά������u���� 
	Edge* pre = unow->first;
	int preflag = 0;
	while(cur) {
		if(cur->u == v || cur->v == v)  break;
		pre = cur;
		if(cur->u == unow->data){
			cur = cur->unext;
			preflag = 0;
		}else{
			cur = cur->vnext;
			preflag = 1;
		}
	}
	if(!cur || (cur->v != v && cur->u !=v))  return false;    //���û�������ߣ���ɾ��ʧ�� 
	if(pre == cur)     //ɾ����ǰ�ߣ�����������׽��������ԣ���Ҫ�����ж� 
		unow->first = cur->u == unow->data ? cur->unext : cur->vnext;
	else {
		if(!preflag)  pre->unext = cur->u == unow->data ? cur->unext : cur->vnext;
		else  pre->vnext = cur->u == unow->data ? cur->unext : cur->vnext;
	}
	
	cur = vnow->first;    //ά������v���� 
	pre = vnow->first;
	preflag = 0;
	while(cur) {
		if(cur->u == u || cur->v == u)  break;
		pre = cur;
		if(cur->u == vnow->data){
			cur = cur->unext;
			preflag = 0;
		}else{
			cur = cur->vnext;
			preflag = 1;
		}
	}
	if(!cur || (cur->v != u && cur->u !=u))  return false;    //���û�������ߣ���ɾ��ʧ�� 
	if(pre == cur)     //ɾ����ǰ�ߣ�����������׽��������ԣ���Ҫ�����ж� 
		vnow->first = cur->u == vnow->data ? cur->unext : cur->vnext;
	else {
		if(!preflag)  pre->unext = cur->u == vnow->data ? cur->unext : cur->vnext;
		else  pre->vnext = cur->u == vnow->data ? cur->unext : cur->vnext;
	}

	delete cur;       //�ͷ��ڴ� 
	return true;
}

bool DeleteVex(Graph& G, char v) {    //ɾ����� 
	Node* now = G.head;
	Node* pre = G.head;
	while(now) {
		if(now->data == v)  break;
		pre = now;
		now = now->next;
	}
	if(!now || now->data != v)  return false;
	
	Edge* cur = now->first;
	while(cur) {    //ɾ���������ıߣ�������ڵ� 
		Edge* tmp = cur;
		if(cur->u == now->data)  cur = cur->unext;
		else  cur = cur->vnext;
		DeleteArc(G, tmp->u, tmp->v);
	}
	if(pre == now)
		G.head = now->next;
	else
	 	pre->next = now->next;
	delete now;
	
	return true;
}

void GraphShow(Graph& G) {    //���ͼ 
	Node* now = G.head;
	while(now) {
		Edge* cur = now->first;
		cout << now->data << ":\t";
		while(cur) {
			cout << "(" << cur->u << "," << cur->v << ")\t";
			if(cur->u == now->data)  cur = cur->unext;
			else  cur = cur->vnext;
		}
		cout << "\n";
		now = now->next;
	}
}

bool CreatGraph(Graph& G, int n, int m) {
	for(int i = 1; i <= n; i++) {
		char x;
		cin >> x;
		if(!InsertVex(G,x))  return false;
	}
	for(int i = 1; i <= m; i++) {
		char u, v;
		cin >> u >> v;
		if(!InsertArc(G, u, v))  return false;
	}
	return true;
}

bool GraphDestory(Graph& G) {
	Node* now = G.head;
	while(now) {
		Node* tmp = now;
		now = now->next;
		DeleteVex(G, tmp->data);
	}
	return true;
}
//Sample.in 
//5 8
//A B C D E	
//A B
//A C
//A D
//C B
//B E
//E A
//B D
//E C
//A
//B D
