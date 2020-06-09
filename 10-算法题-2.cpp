#include <iostream>

using namespace std;

struct Edge {    //边的定义
	char u, v;    //u->v 
	struct Edge* unext, * vnext;    //下一条边 
};

struct Node {    //点的定义，由于需要动态增删点，需要是用来链表
	char data;    //结点 
	Edge* first;    //第一条边 
	Node* next;    //下一个点 
};

struct Graph{    //图的定义
	Node* head;
};

bool InsertVex(Graph& G, char v);  //向图G中增加点v

bool InsertArc(Graph& G, char u, char v); //向图G中增加边(u,v) 

bool DeleteArc(Graph& G, char u, char v) ;    //删除边 

bool DeleteVex(Graph& G, char v);  //删除结点

bool CreatGraph(Graph& G, int n, int m);  //创建n个点，m条边的图 

void GraphShow(Graph& G); //输出图 

bool GraphDestory(Graph& G);  //销毁图 
	

int main() {    //主函数入口
	Graph G = {NULL};
	int n, m;
	cin >> n >> m;
	CreatGraph(G, n, m);    //创建新图 
	cout << "===========================\n";
	GraphShow(G);    //输出新图 
	cout << "===========================\n";	

	char u, v;  
	cin >> u;    //读入一个结点u，删除它 
	DeleteVex(G, u);
	cout << "===========================\n";
	GraphShow(G);
	cout << "===========================\n";
	
	cin >> u >> v;    //读入一条边（u，v），删除它 
	DeleteArc(G, u, v);
	cout << "===========================\n";
	GraphShow(G);
	cout << "===========================\n";
	
	GraphDestory(G);    //销毁图 
	GraphShow(G);
	return 0;
}

bool InsertVex(Graph& G, char v) {  //向图G中增加点v
	Node* now = G.head;
	while (now) {
		if (now->data == v)  return false;    //如果点V存在，则加点失败 
		now = now->next;
	}
	now = new Node;    //新增点 
	now->data = v;
	now->first = NULL;     
	now->next = G.head;
	G.head = now;
	return true;
}

bool InsertArc(Graph& G, char u, char v) {    //向图G中增加边(u,v) 
	if(u > v)  swap(u, v);    //让u<v，方便操作 
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
	if (cnt < 2)  return false;    //如果点u v都在图中，才可以加边，否则加边失败 

	Edge* cur = unow->first;    
	while (cur) {
		if (cur->v == v)  break;
		if(cur->u == unow->data)  cur = cur->unext;
		else  cur = cur->vnext;
	}
	if (cur && cur->v == v)  return false;    //如果已经存在这条边，则加边失败 

	cur = new Edge;    //加入一条边 
	cur->u = u;
	cur->v = v;
	cur->unext = unow->first;
	unow->first = cur;
	cur->vnext = vnow->first;
	vnow->first = cur;
	return true;
}

bool DeleteArc(Graph& G, char u, char v) {    //删除边 
	if(u > v)  swap(u, v);
	Node* tmp = G.head;    //需要维护两条链，找出含有u的链头和含有v的链头 
	Node* unow = NULL;
	Node* vnow = NULL;
	int cnt = 0;
	while (tmp) {
		if (tmp->data == u || tmp->data == v)  cnt++;
		if (tmp->data == u)  unow = tmp;
		if (tmp->data == v)  vnow = tmp;
		tmp = tmp->next;
	}
	if (cnt < 2)  return false;    //如果点u v都在图中，才可以删边，否则失败 
	
	Edge* cur = unow->first;    //维护含有u的链 
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
	if(!cur || (cur->v != v && cur->u !=v))  return false;    //如果没有这条边，则删除失败 
	if(pre == cur)     //删除当前边，由于链表的首结点的特殊性，需要特殊判断 
		unow->first = cur->u == unow->data ? cur->unext : cur->vnext;
	else {
		if(!preflag)  pre->unext = cur->u == unow->data ? cur->unext : cur->vnext;
		else  pre->vnext = cur->u == unow->data ? cur->unext : cur->vnext;
	}
	
	cur = vnow->first;    //维护含有v的链 
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
	if(!cur || (cur->v != u && cur->u !=u))  return false;    //如果没有这条边，则删除失败 
	if(pre == cur)     //删除当前边，由于链表的首结点的特殊性，需要特殊判断 
		vnow->first = cur->u == vnow->data ? cur->unext : cur->vnext;
	else {
		if(!preflag)  pre->unext = cur->u == vnow->data ? cur->unext : cur->vnext;
		else  pre->vnext = cur->u == vnow->data ? cur->unext : cur->vnext;
	}

	delete cur;       //释放内存 
	return true;
}

bool DeleteVex(Graph& G, char v) {    //删除结点 
	Node* now = G.head;
	Node* pre = G.head;
	while(now) {
		if(now->data == v)  break;
		pre = now;
		now = now->next;
	}
	if(!now || now->data != v)  return false;
	
	Edge* cur = now->first;
	while(cur) {    //删除有这个点的边，及这个节点 
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

void GraphShow(Graph& G) {    //输出图 
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
