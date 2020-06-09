//李群 2019212340 
#include <iostream>
#define N 1005    //最大结点数目 

using namespace std;

int L[N+1], R[N+1];    

bool isChild(const int cur, const int x) {    //第1题算法实现函数 
	return cur == 0 ? false : (L[cur] == x || R[cur] == x || isChild(L[cur],x) || isChild(R[cur],x));
}    //使用递归实现这个函数 

int main() {
	int n;
	cin >> n;      //读入结点数目n 
	for(int i = 1; i <= n; i++) {    //读入树，读入方式：n行，每行p,lc,rc,即每个结点和他的两个子节点 
		int p,lc,rc;
		cin >> p >> lc >> rc;
		L[p] = lc;
		R[p] = rc;
	}
	int m;
	cin >> m;    //读入询问次数 
	for(int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		cout << isChild(x,y) << endl;
	}
	return 0;
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
//         
//5          （5次询问） 
//1 12     
//2 9     
//3 6     
//4 5     
//12 1    
