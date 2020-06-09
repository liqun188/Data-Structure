//李群 2019212340
//括号匹配，使用栈实现 
#include <iostream>
#include <string>

using namespace std;

template <class T>
class stack {
private:
	struct node {
		T data;
		node *pre;
	};
	node *top = NULL;
public:
	stack() {
		top = NULL;
	}
	
	bool push(T x) {
		node *tmp = new node;
		if(tmp == NULL)  return false;
		tmp->data = x;
		tmp->pre = top;
		top = tmp;
		return true;
	}
	
	bool pop(T &x) {
		if(top == NULL)  return false;
		x = top->data;
		node *tmp = top;
		top = top->pre;
		delete tmp;
		return true;
	}
	
	bool query(T &x) {
		if(top == NULL)  return false;
		x= top->data;
		return true;
	}
	
	bool isEmpty() {
		return top == NULL;
	}
	
	~stack() {
		T tmp;
		while(pop(tmp)){
		}
	}
	
};

int main(int argh,char *argv[]) {
	if(argh != 2) {    //只允许使用一个参数 
		cout << "参数错误！";
		return 0;
	}
	freopen(argv[1],"r",stdin);
	stack<char> s;
	string st;
	int line = 0;
	while((getline(cin,st))){
		line++;
		int len = st.length();
		for(int i = 0; i < len; i++) {
			if(st[i] == '(' || st[i] == '[' || st[i] == '{')
				s.push(st[i]);
			if(st[i] == ')' || st[i] == ']' || st[i] == '}'){
				if(s.isEmpty()) { 
					cout << "第" << line << "行中" << st[i] << "符号无法匹配";	
					return 0;    //当出现不匹配时，停止查找 
				}
				char ch;
				s.pop(ch);
				if( (st[i] == ')' && ch == '(') || (st[i] == ']' && ch == '[') || (st[i] == '}' && ch == '{') )
					continue;
				else{
					cout << "第" << line << "行中" << st[i] << "符号无法匹配";	
					return 0;
				}
			}
		}
	}
	if(!s.isEmpty()){
		char ch;
		s.pop(ch);
		cout << "第" << line << "行中" << ch << "符号无法匹配";	
		return 0;
	}
	cout << "正确" ; 
	return 0;
}
//使用栈实现简易的括号匹配

//这里对注释和字符串也进行了检测 
//可以加入flag标记每次出现的注释符号、字符（串）符号判断是否位于忽略检测范围内

//这里如果最后没有与之匹配的符号，会显示最后一行没有匹配，如果需要显示左括号出现的位置
//则栈的数据需要以结构体方式存储，记录每一个括号出现的位置才行。
 
