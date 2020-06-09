//李群 2019212340 
#include <iostream>

using namespace std;

const int MAXSIZE = 1200;    //默认最大非零元素 

struct triple{    //三元组 
		int x, y;    //行列坐标 
		int e;    //数据元素 
};

struct matrix{    //矩阵结构体 
	triple data[MAXSIZE + 1];
	int m,n;     //矩阵为m*n 
	int size;    //非零元素个数 
};

bool initmatrix(matrix &mat, int l, int c) {    //初始化矩阵 
	mat.m = l, mat.n = c;
	mat.size = 0;
	return true;
}
	
bool getmatrix(matrix &mat) {    //读入矩阵 
	for(int i = 0; i < mat.m; i++)    //读入每一行 
		for(int j = 0; j < mat.n; j++) {
			int tmp;
			cin >> tmp;
			if(tmp != 0) {
				mat.size++;
				if(mat.size > MAXSIZE) {    //边界条件判断 
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
		
void print(const matrix &mat) {    //打印矩阵 
	int num = 0;
	for(int i = 0; i < mat.m; i++){  //打印每一行 
		for(int j = 0; j < mat.n; j++)
			if(i == mat.data[num].x && j == mat.data[num].y){    //判断是否为0 
				cout << mat.data[num].e << '\t';
				num++;
			}else{
				cout << "0\t";
			}
		cout << '\n';
	}
}

void add(matrix &ans, const matrix &ma, const matrix &mb) {    //矩阵加法 将结果存到ans里面 
	initmatrix(ans, ma.m, ma.n);
	int i = 0, j = 0;    //设置两个标志指向两个矩阵的第一个非零元素 
	while(i < ma.size && j < mb.size) {    
		const triple &ta = ma.data[i], &tb = mb.data[j];
		if(ta.x < tb.x || (ta.x == tb.x && ta.y < tb.y)){    //保证两个标志“均衡”的移动 
			ans.data[ans.size++] = ta;
			i++;
		}else if(ta.x == tb.x && ta.y == tb.y){    //如果有相等的坐标，则相加 
			ans.data[ans.size] = ta;
			ans.data[ans.size++].e += tb.e;
			i++;
			j++;
		}else {    //否则复制 
			ans.data[ans.size++] = tb;
			j++;
		}
	}
	while(i < ma.size) {    //将剩余元素复制过来 
		ans.data[ans.size++] = ma.data[i];
		i++;
	}
	while(j < mb.size) {    //将剩余元素复制过来 
		ans.data[ans.size++] = mb.data[j];
		j++;
	}
}
		
int main() {
	matrix A, B;    
	matrix C;
	
	int m, n;    //矩阵是m*n 
	cin >> m >> n;
	
	initmatrix(A, m, n);    //初始化三个矩阵 
	initmatrix(B, m, n);
	initmatrix(C, m, n);
	
	getmatrix(A);    //读入A,B矩阵 
	getmatrix(B);
	
	add(C, A, B);  //相加 
	print(C);  //输出 
	return 0;
}
