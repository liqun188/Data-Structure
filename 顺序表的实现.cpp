//数据结构小组： 
//李群  _2019212340 
//苗科基_2019212344
//蒋竞宽_2019212330 
//李顺杉_2019212332 
//
//使用数组实现顺序表的基本功能:
//创建、销毁、插入、删除、查找、获取长度、遍历顺序表等 
#include <cstdio>
#include <cstdlib>

struct list {
	int *data;
	int size;
	int maxsize;
};

bool init(list &l, int max) {    //初始化顺序表，参数：被初始化的顺序表和最大存储位数，成功将返回true
	l.data = (int*) malloc(sizeof(int) * max);
	l.size = 0;
	l.maxsize =  max;
	return true;
}

bool destory(list &l) {    //销毁顺序表，参数：被销毁的顺序表，成功将返回true
	free(l.data);
	l.maxsize = l.size = 0;
	return true;
}

bool insert(list &l, int pos, int x) {    //将x插入到顺序表的第pos个元素后面，成功将返回true 
	if(l.size >= l.maxsize || pos > l.size) return false;
	for(int i = l.size; i > pos; i--)
		l.data[i] = l.data[i -1]; 
	l.data[pos] = x;
	l.size++;
	return true;
}

bool del(list &l, int pos) {    //删除第pos个元素，成功将返回true 
	if(pos > l.size) return false;
	for(int i = pos; i < l.size; i++)
		l.data[i - 1] = l.data[i];
	l.size--;
	return true;
}

int query(list l, int pos) {    //返回第pos个元素的值，失败将放回-1 
	if(pos > l.size) return -1;
	return l.data[pos - 1];
}

int locate(list l, int x) {    //返回第一个值为x的位置，失败将返回-1 
	for(int i = 0; i < l.size; i++) 
		if(l.data[i] == x)  return i+1;
	return -1;
}

int length(list l) {    //返回顺序表的长度 
	return l.size;
}

void print(list l) {    //遍历并打印顺序表 
	for(int i = 0; i < l.size; i++)
		printf("%d ",l.data[i]);
	printf("\n");
}

bool isEmpty(list l) {    //判断顺序表是否为空 
	return l.size == 0;
}

int pre(list l, int pos) {    //返回第pos个数的前驱 
	return pos == 0 ? -1 : l.data[pos - 2];
}

int suc(list l,int pos) {    //返回第pos个数的后继 
	return pos == l.size - 1 ? -1 : l.data[pos];
}

int main() {
	list l;
	printf("1.初始化    2.销毁    3.插入    4.删除\n5.查询第x个元素\
     6.查询x第一次出现的位置\n7.长度  8.是否为空    9.前驱    10.后继    11.打印    12.退出\n");
	while(true) {
		int op, pos, x;
		scanf("%d", &op);
		switch(op) {
			case 1:
				printf("将初始化顺序表，请输入顺序表的最大值："); 
				scanf("%d", &x);
				printf(init(l, x) ? "初始化成功！\n" : "初始化失败！\n");
				break;
			case 2:
				printf(destory(l) ? "销毁顺序表成功！\n" : "销毁顺序表失败!\n");
				break;
			case 3:
				printf("插入元素，请分别输入要插入的位置和元素：");
				scanf("%d%d", &pos, &x);
				printf(insert(l, pos, x) ? "插入成功！\n" : "插入失败!\n" );
				break;
			case 4:
				printf("删除元素，请输入要删除的元素位置：");
				scanf("%d", &pos);
				printf(del(l, pos) ? "删除成功！\n" : "删除失败！\n");
				break;
			case 5:
				printf("请输入要查询的位置：");
				scanf("%d", &pos);
				printf("第%d个元素的值为%d\n", pos, query(l ,pos));
				break;
			case 6:
				printf("请输入要查询的值：");
				scanf("%d", &x);
				printf("%d第一次出现在%d\n", x, locate(l, x));
				break;
			case 7:
				printf("顺序表的长度是：%d\n", length(l));
				break;
			case 8:
				printf(isEmpty(l) ? "顺序表为空\n" : "顺序表不为空\n");
				break;
			case 9:
				printf("请输入要查询的位置：");
				scanf("%d", &pos);
				printf("第%d个元素的前驱值为%d\n", pos, pre(l,pos));
				break;
			case 10:
				printf("请输入要查询的位置：");
				scanf("%d", &pos);
				printf("第%d个元素的后继值为%d\n", pos, suc(l,pos));
				break;
			case 11:
				print(l);
				break;
			case 12:
				return 0; 
		}
		printf("---------------------------------\n");
	}
	return 0;
}
