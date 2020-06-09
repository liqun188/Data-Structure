//李群  2019212340
//递归求斐波那契数列 
#include <cstdio>

using namespace std;

int Fibonacci(int n) {
	if(n == 0) return 0;
	if(n == 1) return 1;
	return Fibonacci(n-1) + Fibonacci(n-2);
}
	
int main() {
	int x;
	scanf("%d", &x);
	printf("Fibonacci(%d) = %d",x,Fibonacci(x));
	return 0;
}
