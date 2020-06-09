#include <iostream>

using namespace std;

struct Node{
	char index;
	Node *lc, *rc, *p;
};

bool CreatTree(Node* &subTree, Node* P, char *s, bool flag = true) {    //�����������һ�����������ж��Ƿ�Ϊ������������ 
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

bool DestoryTree(Node* &root) {    //������ 
	if(root) {
		DestoryTree(root->lc);
		DestoryTree(root->rc);
		delete root;
		root = NULL;
	}
	return true;
}

bool TraversalPreOrder(Node *root, bool (*vis) (Node *)) {    //������� 
	if(root) {
		if(!vis(root))  return false;
		if(!TraversalPreOrder(root->lc, vis))  return false;
		if(!TraversalPreOrder(root->rc, vis))  return false;
	}
	return true;
}

bool print(Node *x) {    //��ӡ��ǰ��� 
	cout << (x->index) << ' ';
	return true;
}

void PublicRoute(Node *root, Node *p, Node *q) {    //��һ���㷨ʵ�֣�Ѱ�ҹ���·�� 
	char proute[50], qroute[50];    //����������������50��ʵ�ֵ�ʱ����Ը���ʵ��������� 
	Node *cur;
	int pptr = 0, qptr = 0;
	
	cur = p;
	while(cur != root) {    //Ѱ��p��root ��·�� 
		proute[pptr] = cur->index;
		pptr++;
		cur = cur->p;
	} 
	proute[pptr] = cur->index;
	pptr++;
	
	cur = q;
	while(cur != root) {    //Ѱ��q��root��·�� 
		qroute[qptr] = cur->index;
		qptr++;
		cur = cur->p;
	}
	qroute[qptr] = cur->index;
	qptr++;
	
	int l = min(pptr, qptr), r = 0;
	while(l > r) {    //ͨ�����ַ��ķ�ʽ�ҵ�����Ĺ������ȣ���Ϊ����һ���ֵ�·������ͬ�ģ� 
		int mid = (l + r + 1) >> 1;
		if(proute[pptr - mid] == qroute[qptr - mid])  r = mid;
		else l = mid - 1;
	}
	for(int i = 1; i <= r; i++)    //�����������������ȵ�root��·�� 
		cout << proute[pptr - i] << ' ';
}
		

int main() {
	Node* root;
	char str[] = "ABD#H##EI###CF#J##G##";    //�������� 
	CreatTree(root, NULL, str);
	cout << "Pre-Order-Traversal: ";
	TraversalPreOrder(root,print);
	
	cout << endl << "Public Route: ";    //���в������� 
	Node* p = root->lc->lc->rc;
	Node* q = root->lc->rc;
	PublicRoute(root, p, q);
	
	DestoryTree(root);
	return 0;
}
