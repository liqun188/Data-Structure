//���ݽṹС�飺 
//��Ⱥ  _2019212340 
//��ƻ�_2019212344
//������_2019212330 
//��˳ɼ_2019212332 
//
//ʹ������ʵ��˳���Ļ�������:
//���������١����롢ɾ�������ҡ���ȡ���ȡ�����˳���� 
#include <cstdio>
#include <cstdlib>

struct list {
	int *data;
	int size;
	int maxsize;
};

bool init(list &l, int max) {    //��ʼ��˳�������������ʼ����˳�������洢λ�����ɹ�������true
	l.data = (int*) malloc(sizeof(int) * max);
	l.size = 0;
	l.maxsize =  max;
	return true;
}

bool destory(list &l) {    //����˳��������������ٵ�˳����ɹ�������true
	free(l.data);
	l.maxsize = l.size = 0;
	return true;
}

bool insert(list &l, int pos, int x) {    //��x���뵽˳���ĵ�pos��Ԫ�غ��棬�ɹ�������true 
	if(l.size >= l.maxsize || pos > l.size) return false;
	for(int i = l.size; i > pos; i--)
		l.data[i] = l.data[i -1]; 
	l.data[pos] = x;
	l.size++;
	return true;
}

bool del(list &l, int pos) {    //ɾ����pos��Ԫ�أ��ɹ�������true 
	if(pos > l.size) return false;
	for(int i = pos; i < l.size; i++)
		l.data[i - 1] = l.data[i];
	l.size--;
	return true;
}

int query(list l, int pos) {    //���ص�pos��Ԫ�ص�ֵ��ʧ�ܽ��Ż�-1 
	if(pos > l.size) return -1;
	return l.data[pos - 1];
}

int locate(list l, int x) {    //���ص�һ��ֵΪx��λ�ã�ʧ�ܽ�����-1 
	for(int i = 0; i < l.size; i++) 
		if(l.data[i] == x)  return i+1;
	return -1;
}

int length(list l) {    //����˳���ĳ��� 
	return l.size;
}

void print(list l) {    //��������ӡ˳��� 
	for(int i = 0; i < l.size; i++)
		printf("%d ",l.data[i]);
	printf("\n");
}

bool isEmpty(list l) {    //�ж�˳����Ƿ�Ϊ�� 
	return l.size == 0;
}

int pre(list l, int pos) {    //���ص�pos������ǰ�� 
	return pos == 0 ? -1 : l.data[pos - 2];
}

int suc(list l,int pos) {    //���ص�pos�����ĺ�� 
	return pos == l.size - 1 ? -1 : l.data[pos];
}

int main() {
	list l;
	printf("1.��ʼ��    2.����    3.����    4.ɾ��\n5.��ѯ��x��Ԫ��\
     6.��ѯx��һ�γ��ֵ�λ��\n7.����  8.�Ƿ�Ϊ��    9.ǰ��    10.���    11.��ӡ    12.�˳�\n");
	while(true) {
		int op, pos, x;
		scanf("%d", &op);
		switch(op) {
			case 1:
				printf("����ʼ��˳���������˳�������ֵ��"); 
				scanf("%d", &x);
				printf(init(l, x) ? "��ʼ���ɹ���\n" : "��ʼ��ʧ�ܣ�\n");
				break;
			case 2:
				printf(destory(l) ? "����˳���ɹ���\n" : "����˳���ʧ��!\n");
				break;
			case 3:
				printf("����Ԫ�أ���ֱ�����Ҫ�����λ�ú�Ԫ�أ�");
				scanf("%d%d", &pos, &x);
				printf(insert(l, pos, x) ? "����ɹ���\n" : "����ʧ��!\n" );
				break;
			case 4:
				printf("ɾ��Ԫ�أ�������Ҫɾ����Ԫ��λ�ã�");
				scanf("%d", &pos);
				printf(del(l, pos) ? "ɾ���ɹ���\n" : "ɾ��ʧ�ܣ�\n");
				break;
			case 5:
				printf("������Ҫ��ѯ��λ�ã�");
				scanf("%d", &pos);
				printf("��%d��Ԫ�ص�ֵΪ%d\n", pos, query(l ,pos));
				break;
			case 6:
				printf("������Ҫ��ѯ��ֵ��");
				scanf("%d", &x);
				printf("%d��һ�γ�����%d\n", x, locate(l, x));
				break;
			case 7:
				printf("˳���ĳ����ǣ�%d\n", length(l));
				break;
			case 8:
				printf(isEmpty(l) ? "˳���Ϊ��\n" : "˳���Ϊ��\n");
				break;
			case 9:
				printf("������Ҫ��ѯ��λ�ã�");
				scanf("%d", &pos);
				printf("��%d��Ԫ�ص�ǰ��ֵΪ%d\n", pos, pre(l,pos));
				break;
			case 10:
				printf("������Ҫ��ѯ��λ�ã�");
				scanf("%d", &pos);
				printf("��%d��Ԫ�صĺ��ֵΪ%d\n", pos, suc(l,pos));
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
