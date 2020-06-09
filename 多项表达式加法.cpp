//��Ⱥ 2019212340 
//����ʽ�ļӷ�������ʵ��
//����ʽ�����룺����ÿһ���ϵ����ָ������0 0��ֹ
//������������ʽ��������ǵĺ� 
//��������ҪĿ����ʵ�ֶ���ʽ�ӷ������Լٶ����������ǰ��������������еģ�����û�в��Ϸ����룩 
#include <cstdio>
#include <cstdlib>

struct polyn {    //����ʽ�Ĵ洢��ʽ 
	int a, p;
	polyn *next;
};

void initPolyn(polyn *(&Q)) {    //��ʼ������ʽ 
	Q = (polyn *)malloc(sizeof(polyn));
	Q->next = NULL;
	return;
}

void getPolyn(polyn *Q) {    //����һ������ʽ����0 0���� 
	int a = 1, p = 1;
	polyn *ptr=Q;
	while(!(a == 0 && p == 0)) {
		scanf("%d%d", &a, &p);
		if(a == 0)  continue;
		ptr->next = (polyn *)malloc(sizeof(polyn));
		ptr = ptr->next;
		ptr->a = a;
		ptr->p = p;
		ptr->next = NULL;
	}
	return;
}

void printPolyn(polyn *Q) {    //��ӡһ������ʽ 
	int flag = 1;
	while(Q->next) {
		Q = Q->next;
		if(flag) {
			printf("(%dx^%d)",Q->a, Q->p);
			flag = 0;
		}else{
			printf("+(%dx^%d)",Q->a, Q->p);
		}
	}
	return;
}

void mergePolyn(polyn *Q, polyn *R) {    //ʵ�ֶ���ʽ��ӣ�����Q += R �Ĳ��� 
	R = R->next;
	while(R){
		while(Q->next && Q->next->p < R->p)
			Q = Q->next;
		if(!Q->next) {
			Q->next = R;
			break;
		}else if(Q->next->p == R->p) {
			Q->next->a += R->a;
			Q = Q->next;
			R = R->next;
		}else {
			polyn *tmp = R;
			R = R->next;
			tmp->next = Q->next;
			Q->next = tmp;
			Q = Q->next;
		}
	}
	return;
}

int main() {
	polyn *A, *B;
	initPolyn(A);
	initPolyn(B);
	
	getPolyn(A);
	getPolyn(B);
	
	mergePolyn(A, B);
	
	printPolyn(A);
	return 0;
}
//sample��
//input��
//    3 1
//    5 2
//    7 10
//    1 2222
//    0 0
//    5 1
//    7 5
//    2 2222
//    9 7777
//    15 9999
//    0 0
//output�� 
//    (8x^1)+(5x^2)+(7x^5)+(7x^10)+(3x^2222)+(9x^7777)+(15x^9999) 
