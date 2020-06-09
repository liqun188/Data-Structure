//李群 2019212340 
//第一题:插入元素到有序表中 
#include <cstdio>
#define MAXN 2005    //表的最大长度为MAXN 

bool insert(int *va, int &valen, int x) {    //将x插入到不下降的表va中，表长为valen，成功插入将返回true 
	if(valen >= MAXN) return false;
	int i = valen;
	while(va[i - 1] > x && i > 0) {
		va[i]=va[i - 1];
		i--;
	}
	va[i]=x;
	valen++;
	return true;
}
		
int main() {
	int list[MAXN] = {1, 3, 3, 4, 5, 5, 5, 8, 10};    //这里为测试数据 
	int len=9;
	while(true) {
		int x;
		scanf("%d",&x);
		insert(list,len,x);
		for(int i = 0; i < len; i++) 
			printf("%d ",list[i]);
		printf("\n");
	}
	return 0;
}
