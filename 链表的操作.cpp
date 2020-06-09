//��Ⱥ 2019212340 
//ʹ������ʵ��˳���Ļ�������:
//���������١����롢ɾ�������ҡ���ȡ���ȡ�����˳��� 
#include <cstdio>
#include <cstdlib>

struct node {
	int data;
	node *next;
};

bool init(node *(&head)) {    //��������ͷָ����Ϊ�� 
	head = NULL;
	return true;
}

bool destory(node *(&head)) {    //���������ͷ������ڴ� 
	if(head == NULL) return true;
	destory(head->next);
	free(head);
	head = NULL;
	return true;
}

bool insert(node *(&head), int pos, int x) {         //����Ԫ�أ���x���뵽��pos��Ԫ�غ��� 
	node *current = head;
	for(int i = 1; i < pos; i++) {
		 if(current == NULL) return false;
		 current = current->next; 
	}
	node *tmp;
	tmp = (node*) malloc(sizeof(node));
	tmp->data = x;
	if(pos == 0){									 //��Ҫ�Ե�һ��������⴦�� 
		tmp->next = head;
		head = tmp;
	}else{
		tmp->next = current->next; 
		current->next = tmp;
	}
	return true;
}

int query(node *head, int pos) {                      //���ص�pos��Ԫ�ص�ֵ,�Ƿ���ѯ������-1 
	for(int i = 1; i < pos; i++){
		if(head == NULL) return -1;
		head = head->next;
	} 
	return head->data;
}

bool del(node *(&head), int pos) {                    //ɾ����pos��Ԫ�� 
	if(pos == 1){                                     //������Ҫ�Ե�һ��������⴦�� 
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

void print(node *head) {                           //��������ӡ����˳��� 
	while(head != NULL){
		printf("%d ", head->data);
		head = head->next;
	}
	printf("\n");
}

int length(node *head) {                             //��ȡ˳���ĳ��� 
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
		printf("�������������\n"); 
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
