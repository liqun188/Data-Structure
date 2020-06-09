//��Ⱥ 2019212340
//��׺���ʽ��ֵ��ʹ��ջʵ�� 
#include <iostream>
#include <string>
using namespace std;

template <class T>
class stack {    //ջ��ʵ�� 
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
	
	bool push(T x) {    //ѹջ 
		node *tmp = new node;
		if(tmp == NULL)  return false;
		tmp->data = x;
		tmp->pre = top;
		top = tmp;
		return true;
	}
	
	bool pop(T &x) {    //����Ԫ�� 
		if(top == NULL)  return false;
		x = top->data;
		node *tmp = top;
		top = top->pre;
		delete tmp;
		return true;
	}
	
	bool query(T &x) {    //��ѯջ�� 
		if(top == NULL)  return false;
		x= top->data;
		return true;
	}
	
	bool isEmpty() {    //�ж��Ƿ�Ϊ�� 
		return top == NULL;
	}
	
	~stack() {
		T tmp;
		while(pop(tmp)){
		}
	}
	
};

int op2num(char ch) {    //����������ȼ� 
	if(ch == '+')  return -100;
	if(ch == '-')  return -101;
	if(ch == '*')  return -200;
	if(ch == '/')  return -201;
	if(ch == '(')  return -1;
	if(ch == ')')  return -300;
	return 0;
}

string convert(string s) {    //����׺���ʽתΪ��׺���ʽ 
	string suf;
	int len = s.length();
	
	int i = 0;
	stack<char> op_s;
	while(i < len) {
		if(s[i] == '(') {
			op_s.push(s[i]);
			i++;
			continue;
		}
		if(s[i] == ')') {
			char opt;
			do{
				op_s.pop(opt);
				suf.push_back(opt);
			}while(opt != '(');
			suf[suf.length()-1] = ' ';
			i++;
			continue;
		}
		if(s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
			if(op_s.isEmpty()){
				op_s.push(s[i]);
				i++;
				continue;
			}else{
				while(!op_s.isEmpty()) {
					char tmp;
					op_s.query(tmp);
					if(op2num(tmp) - op2num(s[i]) > 10) break;
					op_s.pop(tmp);
					suf.push_back(tmp);
					suf.push_back(' ');
				}
				op_s.push(s[i]);
				i++;
				continue;
			}
			continue;
		}
		suf.push_back(s[i]); 
		if(i+1 == len - 1 || s[i+1] < '0' || s[i+1] > '9') {
			suf.push_back(' ');
		}
		i++;
	}
	while(!op_s.isEmpty()) {
		char tmp;
		op_s.pop(tmp);
		suf.push_back(tmp);
		suf.push_back(' ');
	}
	return suf;
}

double calc(string suf) {    //�����׺���ʽ 
	int len = suf.length();
	double ans = 0;
	stack<double> num_s;
	int num = 0;
	for(int i = 0; i < len; i++) {
		if(suf[i] >= '0' && suf[i] <= '9'){
			num = num * 10 + suf[i] - '0';
			continue;
		}
		if(suf[i] == ' ') {
			if(num){
				num_s.push(num);
				num = 0;
			}
			continue;
		}
		double x, y;
		num_s.pop(x);
		num_s.pop(y);
		switch(suf[i]) {
			case '+':
				num_s.push(y + x);
				break;
			case '-':
				num_s.push(y - x);
				break;
			case '*':
				num_s.push(y * x);
				break;
			case '/':
				num_s.push(y / x);
				break;
		}
	}
		num_s.pop(ans);
		num_s.~stack();
		return ans;
}
		

int main() {
	using namespace std;
	string s;
	cin >> s;
	cout << convert(s);
	return 0;
}
//sample: 
//1+(2-3)*4+4/2 = -1
//20+30*4/2*8-(30-10)/2*2 = 48
//20+30*4/2*8-(30-10)/2*2 = 480 
