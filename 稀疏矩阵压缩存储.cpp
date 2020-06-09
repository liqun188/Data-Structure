//�����������ƿ��������������һ�еķ���Ԫ�أ���ԭʼ�㷨ֻ�ܴ�ͷ��ʼ���� 
#include <iostream>

using namespace std;

const int MAXN = 1200;    //Ĭ��������Ԫ�� 

struct pr {    //��Ԫ�� 
	int c, e;
};

struct matrix {    //����Ĵ洢�ṹ 
	pr data[MAXN+5];    //��Ԫ������ 
	int m, n;    //����Ϊm*n 
	int size;    //�������Ԫ�ظ��� 
	int rpos[105];    //�б� 
};

bool getmatrix(matrix &mat) {    //����һ�������������룩 
	mat.rpos[0] = 0;
	mat.size = 0;
	for(int i = 0; i < mat.m; i++){    //����ÿһ�� 
		mat.rpos[i + 1] = mat.rpos[i];    //��ʼ����һ���б� 
		for(int j = 0; j < mat.n; j++) {    //����ÿһ��Ԫ�� 
			int tmp;
			cin >> tmp;
			if(tmp != 0) {    //�ж϶���Ԫ���Ƿ�Ϊ0 
				mat.size++;
				if(mat.size > MAXN) {    //����Ĭ�϶����С�����ʧ�� 
					mat.size = 0;
					return false;
				}
				mat.data[mat.size - 1].c = j;    //�洢�� 
				mat.data[mat.size - 1].e = tmp;    //�洢���� 
				mat.rpos[i + 1]++;    //�޸��б� 
			}
		}
	}
	return true;
}

int getelem(const matrix &mat, int i, int j) {    //����Ԫ�أ�������Ҫ��ĺ����� 
	int p = mat.rpos[i], end = mat.rpos[i+1];    //��ǰ�д洢�����Ϊ[p,end) 
	while(p < end) {
		if(mat.data[p].c == j) return mat.data[p].e;    //����Ԫ���Ƿ�Ϊ0 
		p++;
	}
	return 0;
}

int main() {
	matrix A;
	cin >> A.m >> A.n;    //������ �� ��С 
	getmatrix(A);    //������� 
	
	for(int i = 0; i < A.m; i++){    //����getelem��������ÿһ��λ�õ�Ԫ����� 
		for(int j = 0; j < A.n; j++)
			cout << getelem(A,i,j) << '\t';
		cout << endl;
	}
	
	return 0;
}
	
