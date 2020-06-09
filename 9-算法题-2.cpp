#include <iostream>

using namespace std;

struct Node{
	char index;
	Node *leftchild, *rightsibling;    //左儿子右兄弟法表示森林 
};

bool CreatTree(Node* &subTree, char *s, bool flag = true) {    //创建树，最后一个参数用来判断是否为其他函数调用 
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

bool DestoryTree(Node* &root) {    //销毁树 
	if(root) {
		DestoryTree(root->leftchild);
		DestoryTree(root->rightsibling);
		delete root;
		root = NULL;
	}
	return true;
}

void PrintEdge(Node *root) {    //算法第二题，递归打印所有边 
	if(!root)  return; 
	Node *p = root, *q = root->leftchild;
	
	while(q) {    //输出以root为父节点的边 
		cout << '(' << p->index << ',' << q->index << ')' << endl;
		q = q->rightsibling;
	}
	PrintEdge(root->leftchild);    //输出root的孩子去掉root构成的森林 
	PrintEdge(root->rightsibling);    //输出root所有右兄弟 
	return;
}

int main() {
	Node* root;
	char str[] = "ABD#H##EI###CF#J##G##";    //测试数据 
	CreatTree(root, str);
	PrintEdge(root);
	DestoryTree(root);
	return 0;
}
