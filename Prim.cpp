//为方便检索，图的结点从1到n编号，否则将需要map进行映射
//读入边为 u,v,w 
#include <iostream>

using namespace std;

const int INF = 1e9;

struct Edge {    //边的定义
	int u, v;    //u->v 
	int w;    
	int mark;
	Edge* next;    //下一条边 
};

struct Graph{    //图的定义
	Edge** node;
	int n, m;
};

bool CreatGraph(Graph& G, int n, int m);  //创建n个点，m条边的图 

void GraphShow(Graph& G); //输出图 

bool GraphDestory(Graph& G);  //销毁图 
	
int Prim(Graph& G);

int main() {    //主函数入口
	Graph G;
	int n, m;
	cin >> n >> m;
	CreatGraph(G, n ,m);
	cout << "最小权值和为：" << Prim(G);
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

int Prim(Graph& G) {    //邻接表实现Prim算法 
	int ans = 0;
	int* vis = new int[G.n + 1];    //标记当前节点是否已经在MST中 
	Edge* dis = new Edge[G.n + 1];    //标记当前结点到MST集合中的点的最短距离 
	for(int i = 0; i <= G.n; i++) {    //默认所有的结点都不在MST中 
		vis[i] = 0;
		dis[i].w = INF;
	}
	dis[1].w = 0;    //从1开始寻找 
	for(int i = 0; i < G.n; i++) {    //寻找n次 
		int m = 0;
		for(int j = 1; j <= G.n; j++)
			if(!vis[j] && dis[j].w < dis[m].w)  m = j;
		vis[m] = 1;
		if(m != 1)    //第一次添加1进入MST，此时还没有边 
			cout << "第" << i << "条边：" << dis[m].u << ' ' << dis[m].v << ' ' << dis[m].w <<endl;
		ans += dis[m].w;
		Edge* cur = G.node[m];
		while(cur) {    //松弛对应的边 
			if(cur->w < dis[cur->v].w)  dis[cur->v] = *cur;
			cur = cur->next;
		}
	}
	int flag = 0;
	for(int i = 1; i <= G.n; i++) //如果有未标记的点，说明图不连通，返回-1，否则返回边权和 
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
