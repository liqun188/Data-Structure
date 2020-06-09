//李群 2019212340 
#include <iostream>

using namespace std;

struct Node {    //题目描述的结点存储方式 
	int order, mark;
	Node *lc, *rc, *p;
};

Node *getTree(int n);    //读入树，n行，每行三个数（均不超过n，代表树的标号），结点和其左右儿子 

void lastRoot(Node *root);    //使用后序遍历进行简单验证算法正确性 

void change(Node *root);    //第三题算法，递归实现左右子树对调 

int main() {
	int n;
	Node *root;
	cin >> n;    //结点的个数 
	root = getTree(n);    //读入n个结点的树 
	lastRoot(root);    //后序遍历 
	change(root);    //左右子树对调 
	lastRoot(root);    //后序遍历 
	return 0;
}

Node *getTree(int n) {
	Node **map;
	map = new Node* [n+1];    //映射表，用于存储n个结点的存储地址 
	for(int i = 0; i <= n; i++)
		map[i] = NULL;
	for(int i = 1; i <= n; i++) {    //读入n行的关系 
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
	for(int i = 1; i <= n; i++) {    //用于寻找根节点（没有父节点的结点） 
		if(map[i]->p == NULL) {
			root = map[i];
			break;
		}
	}
	delete[] map;    //删除映射表 
	return root;
}

void lastRoot(Node *root) {    //后序遍历 
	Node *cur = root;
	while(cur) {    //当访问到根节点之后在访问其父节点（空），停止循环 
		int tmp = cur->mark;    //当mark是0是意味着从未访问过该节点，需要遍历左子树，是1时遍历右子树，是2是说明左右子树遍历完成，输出当前节点 
		if(tmp == 2) {
			cout << cur->order << ' ';
			cur->mark = 0;    //重置，便于下次遍历 
			cur = cur->p;    //以该节点为根的子树遍历完成 
		}else if(tmp == 0) {
			cur->mark++;
			if(cur->lc)  cur = cur->lc;    //遍历左子树 
		}else {
			cur->mark++;
			if(cur->rc)  cur = cur->rc;    //遍历右子树 
		}
	}
	cout << endl;
	return;
}

void change(Node *root) {    //第三题算法 
	if(root == NULL)  return;    //当为叶子结点，返回 
	change(root->lc);    //对调左子树 
	change(root->rc);    //对调右子树 
	swap(root->lc, root->rc);    //对调当前节点的两个子节点 
	return;
}
//Sample：
//12          （十二个结点） 
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
