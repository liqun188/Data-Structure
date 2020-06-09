#include <iostream>

using namespace std;

struct Node{
	char index;
	Node *lc, *rc, *p;
};

bool CreatTree(Node* &subTree, Node* P, char *s, bool flag = true) {    //创建树，最后一个参数用来判断是否为其他函数调用 
	static int sptr = 0;
	if(flag)  sptr = 0;
	else  sptr++;
	
	if(s[sptr] == '\0')  return true;
	if(s[sptr] == '#')  subTree = NULL;
	else {
		subTree = new Node;
		subTree->index = s[sptr];
		subTree->p = P;
		CreatTree(subTree->lc, subTree, s, false);
		CreatTree(subTree->rc, subTree, s, false);
	}
	return true;
}

bool DestoryTree(Node* &root) {    //销毁树 
	if(root) {
		DestoryTree(root->lc);
		DestoryTree(root->rc);
		delete root;
		root = NULL;
	}
	return true;
}

bool TraversalPreOrder(Node *root, bool (*vis) (Node *)) {    //先序遍历 
	if(root) {
		if(!vis(root))  return false;
		if(!TraversalPreOrder(root->lc, vis))  return false;
		if(!TraversalPreOrder(root->rc, vis))  return false;
	}
	return true;
}

bool print(Node *x) {    //打印当前结点 
	cout << (x->index) << ' ';
	return true;
}

void PublicRoute(Node *root, Node *p, Node *q) {    //第一题算法实现，寻找公共路径 
	char proute[50], qroute[50];    //假设树的最大深度是50，实现的时候可以根据实际情况调整 
	Node *cur;
	int pptr = 0, qptr = 0;
	
	cur = p;
	while(cur != root) {    //寻找p到root 的路径 
		proute[pptr] = cur->index;
		pptr++;
		cur = cur->p;
	} 
	proute[pptr] = cur->index;
	pptr++;
	
	cur = q;
	while(cur != root) {    //寻找q到root的路径 
		qroute[qptr] = cur->index;
		qptr++;
		cur = cur->p;
	}
	qroute[qptr] = cur->index;
	qptr++;
	
	int l = min(pptr, qptr), r = 0;
	while(l > r) {    //通过二分法的方式找到最近的公共祖先（因为后面一部分的路径是相同的） 
		int mid = (l + r + 1) >> 1;
		if(proute[pptr - mid] == qroute[qptr - mid])  r = mid;
		else l = mid - 1;
	}
	for(int i = 1; i <= r; i++)    //输出从最近公共的祖先到root的路径 
		cout << proute[pptr - i] << ' ';
}
		

int main() {
	Node* root;
	char str[] = "ABD#H##EI###CF#J##G##";    //测试数据 
	CreatTree(root, NULL, str);
	cout << "Pre-Order-Traversal: ";
	TraversalPreOrder(root,print);
	
	cout << endl << "Public Route: ";    //题中测试数据 
	Node* p = root->lc->lc->rc;
	Node* q = root->lc->rc;
	PublicRoute(root, p, q);
	
	DestoryTree(root);
	return 0;
}
