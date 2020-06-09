//这样做的优势可以随机访问任意一行的非零元素，而原始算法只能从头开始遍历 
#include <iostream>

using namespace std;

const int MAXN = 1200;    //默认最大非零元素 

struct pr {    //二元组 
	int c, e;
};

struct matrix {    //矩阵的存储结构 
	pr data[MAXN+5];    //二元组数组 
	int m, n;    //矩阵为m*n 
	int size;    //矩阵非零元素个数 
	int rpos[105];    //行标 
};

bool getmatrix(matrix &mat) {    //读入一个矩阵（正常输入） 
	mat.rpos[0] = 0;
	mat.size = 0;
	for(int i = 0; i < mat.m; i++){    //读入每一行 
		mat.rpos[i + 1] = mat.rpos[i];    //初始化下一行行标 
		for(int j = 0; j < mat.n; j++) {    //读入每一个元素 
			int tmp;
			cin >> tmp;
			if(tmp != 0) {    //判断读入元素是否为0 
				mat.size++;
				if(mat.size > MAXN) {    //超出默认读入大小则读入失败 
					mat.size = 0;
					return false;
				}
				mat.data[mat.size - 1].c = j;    //存储列 
				mat.data[mat.size - 1].e = tmp;    //存储数据 
				mat.rpos[i + 1]++;    //修改列标 
			}
		}
	}
	return true;
}

int getelem(const matrix &mat, int i, int j) {    //返回元素（第六题要求的函数） 
	int p = mat.rpos[i], end = mat.rpos[i+1];    //当前行存储的序号为[p,end) 
	while(p < end) {
		if(mat.data[p].c == j) return mat.data[p].e;    //搜索元素是否为0 
		p++;
	}
	return 0;
}

int main() {
	matrix A;
	cin >> A.m >> A.n;    //读入行 列 大小 
	getmatrix(A);    //读入矩阵 
	
	for(int i = 0; i < A.m; i++){    //测试getelem函数，将每一个位置的元素输出 
		for(int j = 0; j < A.n; j++)
			cout << getelem(A,i,j) << '\t';
		cout << endl;
	}
	
	return 0;
}
	
