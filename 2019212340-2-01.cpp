//��Ⱥ 2019212340 
//��һ��:����Ԫ�ص�������� 
#include <cstdio>
#define MAXN 2005    //�����󳤶�ΪMAXN 

bool insert(int *va, int &valen, int x) {    //��x���뵽���½��ı�va�У���Ϊvalen���ɹ����뽫����true 
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
	int list[MAXN] = {1, 3, 3, 4, 5, 5, 5, 8, 10};    //����Ϊ�������� 
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
