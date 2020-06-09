//李群 2019212340 
//多项式的加法，链表实现
//多项式的输入：输入每一项的系数和指数，以0 0终止
//输入两个多项式，输出他们的和 
//（由于主要目标是实现多项式加法，所以假定数据输入是按次数升高来排列的，并且没有不合法输入） 
#include <cstdio>
#include <cstdlib>

struct polyn {    //多项式的存储方式 
	int a, p;
	polyn *next;
};

void initPolyn(polyn *(&Q)) {    //初始化多项式 
	Q = (polyn *)malloc(sizeof(polyn));
	Q->next = NULL;
	return;
}

void getPolyn(polyn *Q) {    //读入一个多项式，以0 0结束 
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

void printPolyn(polyn *Q) {    //打印一个多项式 
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

void mergePolyn(polyn *Q, polyn *R) {    //实现多项式相加，即：Q += R 的操作 
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
//sample：
//input：
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
//output： 
//    (8x^1)+(5x^2)+(7x^5)+(7x^10)+(3x^2222)+(9x^7777)+(15x^9999) 
