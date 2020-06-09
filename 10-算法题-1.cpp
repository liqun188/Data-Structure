#include <iostream>

using namespace std;

struct Edge {    //边的定义
	char u, v;    //u->v 
	struct Edge* next;    //下一条边 
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

bool InsertArc(Graph& G, char u, char v); //向图G中增加边<u,v> 

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

bool InsertArc(Graph& G, char u, char v) {    //向图G中增加边<u,v> 
	Node* tmp = G.head;
	Node* now = NULL;
	int cnt = 0;
	while (tmp) {
		if (tmp->data == u || tmp->data == v)  cnt++;
		if (tmp->data == u)  now = tmp;
		tmp = tmp->next;
	}
	if (cnt < 2)  return false;    //如果点u v都在图中，才可以加边，否则加边失败 

	Edge* cur = now->first;    
	while (cur) {
		if (cur->v == v)  break;
		cur = cur->next;
	}
	if (cur && cur->v == v)  return false;    //如果已经存在这条边，则加边失败 

	cur = new Edge;    //加入一条边 
	cur->u = u;
	cur->v = v;
	cur->next = now->first;
	now->first = cur;
	return true;
}

bool DeleteArc(Graph& G, char u, char v) {    //删除边 
	Node* now = G.head;
	while(now) {
		if(now->data == u) break;    //寻找起点为u的链表 
		now = now->next;
	}
	if(!now || now->data != u)  return false;    //如果没有起点，则删除边失败 
	
	Edge* cur = now->first;
	Edge* pre = now->first;
	while(cur) {
		if(cur->v == v)  break;
		pre = cur;
		cur = cur->next;
	}
	if(!cur || cur->v != v)  return false;    //如果没有这条边，则删除失败 
	
	if(pre == cur)     //删除当前边，由于链表的首结点的特殊性，需要特殊判断 
		now->first = cur->next;
	else 
		pre->next = cur->next;
	delete cur;     
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
	
	while(now->first) {    //删除以这个点为起点的边，及这个节点 
		Edge* tmp;
		tmp = now->first;
		now->first = now->first->next;
		delete tmp;
	}
	if(pre == now)
		G.head = now->next;
	else
	 	pre->next = now->next;
	delete now;
	
	now = G.head;
	while(now) {    //删除以这个点为终点的边 
		Edge* cur = now->first;
		while(cur) {
			if(cur->v == v) {
				DeleteArc(G, now->data, v);
				break;
			}
			cur = cur->next;
		}
		now = now->next;
	}
	
	return true;
}

void GraphShow(Graph& G) {    //输出图 
	Node* now = G.head;
	while(now) {
		Edge* cur = now->first;
		cout << now->data << ":\t";
		while(cur) {
			cout << "<" << cur->u << "," << cur->v << ">\t";
			cur = cur->next;
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
//5 10
//A B C	D E	
//A B
//A C
//A D
//D A
//C B
//B E
//E A
//B D
//B C
//E C
//A
//B D
