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
	
void Dijkstra(Graph G, int* dis, int s);

int main() {    //主函数入口
	Graph G;
	int n, m;
	cin >> n >> m;
	CreatGraph(G, n ,m);
	int* dis = new int[n + 1];
	Dijkstra(G, dis, 1);
	cout << "到点1的最短距离为：" ; 
	for(int i = 1; i <= n; i++)
		cout << dis[i] << ' ';
	GraphDestory(G);
	return 0;
}

bool CreatGraph(Graph& G, int n, int m) {     //有向图 
	G.n = n;
	G.m = m;
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

void Dijkstra(Graph G, int* dis, int s) {    //邻接表实现Dijkstra 
	int* vis = new int[G.n + 1];    //标记表 
	for(int i = 0; i <= G.n; i++) {
		vis[i] = 0;
		dis[i] = INF;
	}
	dis[s] = 0;    //源点到自己的距离为0 
	for(int i = 1; i <= G.n; i++) {
		int m = 0;
		for(int j = 1; j <= G.n; j++)
			if(!vis[j] && dis[j] < dis[m])  m = j;    //寻找到原点的最短距离 
		vis[m] = 1;    //加入到状态确定的点中 
		Edge* cur = G.node[m];
		while(cur) {    //对第m个点的所有出边松弛 
			dis[cur->v] = min(dis[cur->v], dis[m] + cur->w);
			cur = cur->next;
		}
	}
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
