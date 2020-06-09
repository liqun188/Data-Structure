//��Ⱥ 2019212340 
#include <iostream>
#define N 1005    //�������Ŀ 

using namespace std;

int L[N+1], R[N+1];    

bool isChild(const int cur, const int x) {    //��1���㷨ʵ�ֺ��� 
	return cur == 0 ? false : (L[cur] == x || R[cur] == x || isChild(L[cur],x) || isChild(R[cur],x));
}    //ʹ�õݹ�ʵ��������� 

int main() {
	int n;
	cin >> n;      //��������Ŀn 
	for(int i = 1; i <= n; i++) {    //�����������뷽ʽ��n�У�ÿ��p,lc,rc,��ÿ���������������ӽڵ� 
		int p,lc,rc;
		cin >> p >> lc >> rc;
		L[p] = lc;
		R[p] = rc;
	}
	int m;
	cin >> m;    //����ѯ�ʴ��� 
	for(int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		cout << isChild(x,y) << endl;
	}
	return 0;
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
//         
//5          ��5��ѯ�ʣ� 
//1 12     
//2 9     
//3 6     
//4 5     
//12 1    
