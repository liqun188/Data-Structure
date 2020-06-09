//��Ⱥ 2019212340 
#include <iostream>

using namespace std;

struct Node {    //��Ŀ�����Ľ��洢��ʽ 
	int order, mark;
	Node *lc, *rc, *p;
};

Node *getTree(int n);    //��������n�У�ÿ������������������n���������ı�ţ������������Ҷ��� 

void lastRoot(Node *root);    //ʹ�ú���������м���֤�㷨��ȷ�� 

void change(Node *root);    //�������㷨���ݹ�ʵ�����������Ե� 

int main() {
	int n;
	Node *root;
	cin >> n;    //���ĸ��� 
	root = getTree(n);    //����n�������� 
	lastRoot(root);    //������� 
	change(root);    //���������Ե� 
	lastRoot(root);    //������� 
	return 0;
}

Node *getTree(int n) {
	Node **map;
	map = new Node* [n+1];    //ӳ������ڴ洢n�����Ĵ洢��ַ 
	for(int i = 0; i <= n; i++)
		map[i] = NULL;
	for(int i = 1; i <= n; i++) {    //����n�еĹ�ϵ 
		int p, l, r;
		cin >> p >> l >> r;
		if(!map[p]) {
			map[p] = new Node;
			map[p]->p = NULL;
		}
		map[p]->order = p;
		map[p]->mark = 0;
		if(l && !map[l]) {
			map[l] = new Node;
			map[l]->p = map[p];
		}
		if(r && !map[r]) {
			map[r] = new Node;
			map[r]->p = map[p];
		}
		map[p]->lc = map[l];
		map[p]->rc = map[r];
	}
	Node *root;
	for(int i = 1; i <= n; i++) {    //����Ѱ�Ҹ��ڵ㣨û�и��ڵ�Ľ�㣩 
		if(map[i]->p == NULL) {
			root = map[i];
			break;
		}
	}
	delete[] map;    //ɾ��ӳ��� 
	return root;
}

void lastRoot(Node *root) {    //������� 
	Node *cur = root;
	while(cur) {    //�����ʵ����ڵ�֮���ڷ����丸�ڵ㣨�գ���ֹͣѭ�� 
		int tmp = cur->mark;    //��mark��0����ζ�Ŵ�δ���ʹ��ýڵ㣬��Ҫ��������������1ʱ��������������2��˵����������������ɣ������ǰ�ڵ� 
		if(tmp == 2) {
			cout << cur->order << ' ';
			cur->mark = 0;    //���ã������´α��� 
			cur = cur->p;    //�Ըýڵ�Ϊ��������������� 
		}else if(tmp == 0) {
			cur->mark++;
			if(cur->lc)  cur = cur->lc;    //���������� 
		}else {
			cur->mark++;
			if(cur->rc)  cur = cur->rc;    //���������� 
		}
	}
	cout << endl;
	return;
}

void change(Node *root) {    //�������㷨 
	if(root == NULL)  return;    //��ΪҶ�ӽ�㣬���� 
	change(root->lc);    //�Ե������� 
	change(root->rc);    //�Ե������� 
	swap(root->lc, root->rc);    //�Ե���ǰ�ڵ�������ӽڵ� 
	return;
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
