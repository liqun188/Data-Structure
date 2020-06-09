//Ϊ���������ͼ�Ľ���1��n��ţ�������Ҫmap����ӳ��
//�����Ϊ u,v,w 
#include <iostream>

using namespace std;

const int INF = 1e9;

struct Edge {    //�ߵĶ���
	int u, v;    //u->v 
	int w;    
	int mark;
	Edge* next;    //��һ���� 
};

struct Graph{    //ͼ�Ķ���
	Edge** node;
	int n, m;
};

bool CreatGraph(Graph& G, int n, int m);  //����n���㣬m���ߵ�ͼ 

void GraphShow(Graph& G); //���ͼ 

bool GraphDestory(Graph& G);  //����ͼ 
	
int Prim(Graph& G);

int main() {    //���������
	Graph G;
	int n, m;
	cin >> n >> m;
	CreatGraph(G, n ,m);
	cout << "��СȨֵ��Ϊ��" << Prim(G);
	GraphDestory(G);
	return 0;
}

bool CreatGraph(Graph& G, int n, int m) {     
	G.n = n;
	G.m = m * 2;
	G.node = new Edge*[n + 1];
	for(int i = 1; i <= n; i++)
		G.node[i] = NULL;
	for(int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		Edge* cur = new Edge;
		cur->mark = 0;
		cur->next = G.node[u];
		cur->u = u;
		cur->v = v;
		cur->w = w;
		G.node[u] = cur;
		
		cur = new Edge;
		cur->mark = 0;
		cur->next = G.node[v];
		cur->u = v;
		cur->v = u;
		cur->w = w;
		G.node[v] =cur;
	}
	return true;
}

void GraphShow(Graph& G) {
	for(int i = 1; i <= G.n; i++) {
		Edge* cur = G.node[i];
		while(cur) {
			cout << cur->u << ' ' << cur->v << ' ' << cur->w << endl;
			cur = cur->next;
		}
	}
}

bool GraphDestory(Graph& G) {
	for(int i = 1; i <= G.n; i++) {
		Edge* cur = G.node[i];
		while(cur) {
			Edge* tmp = cur;
			cur = cur->next;
			delete tmp;
		}
	}
	delete[] G.node;
	G.node = NULL;
	G.n = 0;
	G.m = 0;
	return true;
}

int Prim(Graph& G) {    //�ڽӱ�ʵ��Prim�㷨 
	int ans = 0;
	int* vis = new int[G.n + 1];    //��ǵ�ǰ�ڵ��Ƿ��Ѿ���MST�� 
	Edge* dis = new Edge[G.n + 1];    //��ǵ�ǰ��㵽MST�����еĵ����̾��� 
	for(int i = 0; i <= G.n; i++) {    //Ĭ�����еĽ�㶼����MST�� 
		vis[i] = 0;
		dis[i].w = INF;
	}
	dis[1].w = 0;    //��1��ʼѰ�� 
	for(int i = 0; i < G.n; i++) {    //Ѱ��n�� 
		int m = 0;
		for(int j = 1; j <= G.n; j++)
			if(!vis[j] && dis[j].w < dis[m].w)  m = j;
		vis[m] = 1;
		if(m != 1)    //��һ�����1����MST����ʱ��û�б� 
			cout << "��" << i << "���ߣ�" << dis[m].u << ' ' << dis[m].v << ' ' << dis[m].w <<endl;
		ans += dis[m].w;
		Edge* cur = G.node[m];
		while(cur) {    //�ɳڶ�Ӧ�ı� 
			if(cur->w < dis[cur->v].w)  dis[cur->v] = *cur;
			cur = cur->next;
		}
	}
	int flag = 0;
	for(int i = 1; i <= G.n; i++) //�����δ��ǵĵ㣬˵��ͼ����ͨ������-1�����򷵻ر�Ȩ�� 
		if(!vis[i])  flag = 1;
	return flag == 1 ? -1 : ans; 
}
//Sample.in
//5 7
//1 2 10
//1 3 30
//1 5 100
//2 3 50
//3 4 20
//3 5 10
//4 5 60
