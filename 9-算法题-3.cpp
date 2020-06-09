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

Node* CreatTree(char *prebegin, char *preend, char *postbegin, char *postend) {    //利用前序和后序遍历的序列创建树 
	Node* T; 
	T = new Node;
	T->index = *prebegin;
	T->child = new Pointer;
	Pointer *ptr = T->child;    //便于创建孩子链表，让T->child指向空表头 
	ptr->next = NULL;
	if(prebegin == preend) {    //只有一个结点时返回树的根 
		return T;
	}else {
		prebegin++;
		postend--;
		while(preend-prebegin >= 0) {    //按照先序遍历和后序遍历的过程切割子树 
			char *tmp = postbegin;
			while(*tmp != *prebegin)  tmp++;
			ptr->next = new Pointer;
			ptr = ptr->next;
			ptr->node = CreatTree(prebegin, prebegin + (tmp - postbegin), postbegin, tmp);    //得到一棵子树，递归调用建树 
			ptr->next = NULL;
			prebegin = prebegin + (tmp - postbegin) + 1;    //继续寻找余下的子树 
			postbegin = tmp + 1;
		}
		return T;
	}
}

bool DestoryTree(Node* &root) {    //销毁树 
	if(root) {
		Pointer *ptr = root->child->next;
		while(ptr) {    //销毁每一棵子树，并销毁孩子链表 
			DestoryTree(ptr->node);
			Pointer *tmp = ptr;
			ptr = ptr->next;
			delete tmp;
		}
		delete root->child;    //销毁表头结点 
		delete root;
		root = NULL;
	}
	return true;
}

int Depth(Node* root) {    //第三题算法，递归求树的深度 
	int deep = 1;
	Pointer *ptr = root->child->next;
	while(ptr) {    //为所有子树的深度最大值加一 
		deep = max(deep, Depth(ptr->node) + 1);
		ptr = ptr->next;
	}
	return deep;
}

int main() {
	Node* root;
	char preorder[] = "ABEHIJCDFGK";    //先序遍历序列
	char postorder[] = "HIJEBCFKGDA";    //后序遍历序列 
	root = CreatTree(preorder,preorder+strlen(preorder)-1,postorder,postorder+strlen(postorder)-1);
	cout << Depth(root);
	DestoryTree(root);
	return 0;
}
