#include <iostream>
#include <cstring>

using namespace std;

struct Node;
struct Pointer;

struct Pointer{
	Node *node;
	Pointer *next;
};

struct Node{
	char index;
	Pointer *child;
};

Node* CreatTree(char *prebegin, char *preend, char *postbegin, char *postend) {    //����ǰ��ͺ�����������д����� 
	Node* T; 
	T = new Node;
	T->index = *prebegin;
	T->child = new Pointer;
	Pointer *ptr = T->child;    //���ڴ�������������T->childָ��ձ�ͷ 
	ptr->next = NULL;
	if(prebegin == preend) {    //ֻ��һ�����ʱ�������ĸ� 
		return T;
	}else {
		prebegin++;
		postend--;
		while(preend-prebegin >= 0) {    //������������ͺ�������Ĺ����и����� 
			char *tmp = postbegin;
			while(*tmp != *prebegin)  tmp++;
			ptr->next = new Pointer;
			ptr = ptr->next;
			ptr->node = CreatTree(prebegin, prebegin + (tmp - postbegin), postbegin, tmp);    //�õ�һ���������ݹ���ý��� 
			ptr->next = NULL;
			prebegin = prebegin + (tmp - postbegin) + 1;    //����Ѱ�����µ����� 
			postbegin = tmp + 1;
		}
		return T;
	}
}

bool DestoryTree(Node* &root) {    //������ 
	if(root) {
		Pointer *ptr = root->child->next;
		while(ptr) {    //����ÿһ�������������ٺ������� 
			DestoryTree(ptr->node);
			Pointer *tmp = ptr;
			ptr = ptr->next;
			delete tmp;
		}
		delete root->child;    //���ٱ�ͷ��� 
		delete root;
		root = NULL;
	}
	return true;
}

int Depth(Node* root) {    //�������㷨���ݹ���������� 
	int deep = 1;
	Pointer *ptr = root->child->next;
	while(ptr) {    //Ϊ����������������ֵ��һ 
		deep = max(deep, Depth(ptr->node) + 1);
		ptr = ptr->next;
	}
	return deep;
}

int main() {
	Node* root;
	char preorder[] = "ABEHIJCDFGK";    //�����������
	char postorder[] = "HIJEBCFKGDA";    //����������� 
	root = CreatTree(preorder,preorder+strlen(preorder)-1,postorder,postorder+strlen(postorder)-1);
	cout << Depth(root);
	DestoryTree(root);
	return 0;
}
