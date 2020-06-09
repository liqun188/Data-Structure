#include <iostream>

using namespace std;

struct Node{
	char index;
	Node *leftchild, *rightsibling;    //��������ֵܷ���ʾɭ�� 
};

bool CreatTree(Node* &subTree, char *s, bool flag = true) {    //�����������һ�����������ж��Ƿ�Ϊ������������ 
	static int sptr = 0;
	if(flag)  sptr = 0;
	else  sptr++;
	
	if(s[sptr] == '\0')  return true;
	if(s[sptr] == '#')  subTree = NULL;
	else {
		subTree = new Node;
		subTree->index = s[sptr];
		CreatTree(subTree->leftchild, s, false);
		CreatTree(subTree->rightsibling, s, false);
	}
	return true;
}

bool DestoryTree(Node* &root) {    //������ 
	if(root) {
		DestoryTree(root->leftchild);
		DestoryTree(root->rightsibling);
		delete root;
		root = NULL;
	}
	return true;
}

void PrintEdge(Node *root) {    //�㷨�ڶ��⣬�ݹ��ӡ���б� 
	if(!root)  return; 
	Node *p = root, *q = root->leftchild;
	
	while(q) {    //�����rootΪ���ڵ�ı� 
		cout << '(' << p->index << ',' << q->index << ')' << endl;
		q = q->rightsibling;
	}
	PrintEdge(root->leftchild);    //���root�ĺ���ȥ��root���ɵ�ɭ�� 
	PrintEdge(root->rightsibling);    //���root�������ֵ� 
	return;
}

int main() {
	Node* root;
	char str[] = "ABD#H##EI###CF#J##G##";    //�������� 
	CreatTree(root, str);
	PrintEdge(root);
	DestoryTree(root);
	return 0;
}
