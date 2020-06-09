//��Ⱥ 2019212340 
#include <iostream>

using namespace std;

const int MAXSIZE = 1200;    //Ĭ��������Ԫ�� 

struct triple{    //��Ԫ�� 
		int x, y;    //�������� 
		int e;    //����Ԫ�� 
};

struct matrix{    //����ṹ�� 
	triple data[MAXSIZE + 1];
	int m,n;     //����Ϊm*n 
	int size;    //����Ԫ�ظ��� 
};

bool initmatrix(matrix &mat, int l, int c) {    //��ʼ������ 
	mat.m = l, mat.n = c;
	mat.size = 0;
	return true;
}
	
bool getmatrix(matrix &mat) {    //������� 
	for(int i = 0; i < mat.m; i++)    //����ÿһ�� 
		for(int j = 0; j < mat.n; j++) {
			int tmp;
			cin >> tmp;
			if(tmp != 0) {
				mat.size++;
				if(mat.size > MAXSIZE) {    //�߽������ж� 
					mat.size = 0;
					return false;
				}
				mat.data[mat.size - 1].x = i;
				mat.data[mat.size - 1].y = j;
				mat.data[mat.size - 1].e = tmp;
			}
		}
	return true;
}
		
void print(const matrix &mat) {    //��ӡ���� 
	int num = 0;
	for(int i = 0; i < mat.m; i++){  //��ӡÿһ�� 
		for(int j = 0; j < mat.n; j++)
			if(i == mat.data[num].x && j == mat.data[num].y){    //�ж��Ƿ�Ϊ0 
				cout << mat.data[num].e << '\t';
				num++;
			}else{
				cout << "0\t";
			}
		cout << '\n';
	}
}

void add(matrix &ans, const matrix &ma, const matrix &mb) {    //����ӷ� ������浽ans���� 
	initmatrix(ans, ma.m, ma.n);
	int i = 0, j = 0;    //����������־ָ����������ĵ�һ������Ԫ�� 
	while(i < ma.size && j < mb.size) {    
		const triple &ta = ma.data[i], &tb = mb.data[j];
		if(ta.x < tb.x || (ta.x == tb.x && ta.y < tb.y)){    //��֤������־�����⡱���ƶ� 
			ans.data[ans.size++] = ta;
			i++;
		}else if(ta.x == tb.x && ta.y == tb.y){    //�������ȵ����꣬����� 
			ans.data[ans.size] = ta;
			ans.data[ans.size++].e += tb.e;
			i++;
			j++;
		}else {    //������ 
			ans.data[ans.size++] = tb;
			j++;
		}
	}
	while(i < ma.size) {    //��ʣ��Ԫ�ظ��ƹ��� 
		ans.data[ans.size++] = ma.data[i];
		i++;
	}
	while(j < mb.size) {    //��ʣ��Ԫ�ظ��ƹ��� 
		ans.data[ans.size++] = mb.data[j];
		j++;
	}
}
		
int main() {
	matrix A, B;    
	matrix C;
	
	int m, n;    //������m*n 
	cin >> m >> n;
	
	initmatrix(A, m, n);    //��ʼ���������� 
	initmatrix(B, m, n);
	initmatrix(C, m, n);
	
	getmatrix(A);    //����A,B���� 
	getmatrix(B);
	
	add(C, A, B);  //��� 
	print(C);  //��� 
	return 0;
}
