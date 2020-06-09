//李群 2019212340 
//使用数组实现顺序表的基本功能:
//创建、销毁、插入、删除、查找、获取长度、遍历顺序表 
#include <cstdio>
#include <cstdlib>

struct node {
	int data;
	node *next;
};

bool init(node *(&head)) {    //创建链表，头指针置为空 
	head = NULL;
	return true;
}

bool destory(node *(&head)) {    //销毁链表，释放所有内存 
	if(head == NULL) return true;
	destory(head->next);
	free(head);
	head = NULL;
	return true;
}

bool insert(node *(&head), int pos, int x) {         //插入元素，将x插入到第pos个元素后面 
	node *current = head;
	for(int i = 1; i < pos; i++) {
		 if(current == NULL) return false;
		 current = current->next; 
	}
	node *tmp;
	tmp = (node*) malloc(sizeof(node));
	tmp->data = x;
	if(pos == 0){									 //需要对第一个结点特殊处理 
		tmp->next = head;
		head = tmp;
	}else{
		tmp->next = current->next; 
		current->next = tmp;
	}
	return true;
}

int query(node *head, int pos) {                      //返回第pos个元素的值,非法查询将返回-1 
	for(int i = 1; i < pos; i++){
		if(head == NULL) return -1;
		head = head->next;
	} 
	return head->data;
}

bool del(node *(&head), int pos) {                    //删除第pos个元素 
	if(pos == 1){                                     //这里需要对第一个结点特殊处理 
		if(head == NULL)  return false;
		node *tmp = head;
		head = head->next;
		free(tmp);
		return true;
	}
	node *current = head;
	for(int i = 1; i < pos - 1; i++) {
		if(current == NULL)  return false;
		current = current->next;
	}
	node *tmp = current->next;
	current->next = current->next->next;
	free(tmp);
	return true;
}

void print(node *head) {                           //遍历并打印整个顺序表 
	while(head != NULL){
		printf("%d ", head->data);
		head = head->next;
	}
	printf("\n");
}

int length(node *head) {                             //获取顺序表的长度 
	int len = 0;
	while(head != NULL) { 
		head = head->next;
		len++; 
	}
	return len;
}

int main() {
	node *head;
	init(head);
	int op;
	while(true){
		printf("请输入操作符：\n"); 
		scanf("%d", &op);
		int pos, x;
		switch(op) {
			case 1:
				scanf("%d%d", &pos, &x);
				insert(head, pos, x);
				break;
			case 2:
				scanf("%d", &pos);
				del(head, pos);
				break;
			case 3:
				scanf("%d", &pos);
				printf("%d\n", query(head, pos));
				break;
			case 4:
				print(head);
				break;
			case 5:
				printf("%d\n", length(head));
				break;
			case 6:
				destory(head); 
		}
		printf("--------------------------\n");
	} 
	return 0;
}
