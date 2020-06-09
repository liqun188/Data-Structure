//��Ⱥ 2019212340
//����ƥ�䣬ʹ��ջʵ�� 
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
	if(argh != 2) {    //ֻ����ʹ��һ������ 
		cout << "��������";
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
					cout << "��" << line << "����" << st[i] << "�����޷�ƥ��";	
					return 0;    //�����ֲ�ƥ��ʱ��ֹͣ���� 
				}
				char ch;
				s.pop(ch);
				if( (st[i] == ')' && ch == '(') || (st[i] == ']' && ch == '[') || (st[i] == '}' && ch == '{') )
					continue;
				else{
					cout << "��" << line << "����" << st[i] << "�����޷�ƥ��";	
					return 0;
				}
			}
		}
	}
	if(!s.isEmpty()){
		char ch;
		s.pop(ch);
		cout << "��" << line << "����" << ch << "�����޷�ƥ��";	
		return 0;
	}
	cout << "��ȷ" ; 
	return 0;
}
//ʹ��ջʵ�ּ��׵�����ƥ��

//�����ע�ͺ��ַ���Ҳ�����˼�� 
//���Լ���flag���ÿ�γ��ֵ�ע�ͷ��š��ַ������������ж��Ƿ�λ�ں��Լ�ⷶΧ��

//����������û����֮ƥ��ķ��ţ�����ʾ���һ��û��ƥ�䣬�����Ҫ��ʾ�����ų��ֵ�λ��
//��ջ��������Ҫ�Խṹ�巽ʽ�洢����¼ÿһ�����ų��ֵ�λ�ò��С�
 
