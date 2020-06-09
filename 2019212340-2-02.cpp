//李群 2019212340 
//第二题：求有序表的交集 
#include <cstdio>

bool getIntersection(int *a, int &aLength, int *b, int bLength) {    //对不递减的表a和表b求交集，并存入表a中 
	int i = 0, j = 0;
	int aLen = 0;
	while(i < aLength && j < bLength) {
		while(i < aLength && a[i] < b[j]) i++;
		while(j < bLength && b[j] < a[i]) j++;
		if(a[i] == b[j]) {
			a[aLen++] = a[i];
			i++;
			j++;
			while(a[i - 1] == a[i]) i++;
			while(b[j - 1] == b[j]) j++;
		}
	}
	aLength = aLen; 
	return true;
}

int main() {
	int a[105] = {1, 3, 5, 5, 5, 6, 10, 10, 10, 10, 12};    //testData 
	int b[105] = {1, 2, 6, 10, 10, 10, 11, 11, 11, 100};    //testData 
	int aLen = 11, bLen = 10;
	getIntersection(a, aLen, b, bLen);
	for(int i = 0; i < aLen; i++)
		printf("%d ", a[i]);
	return 0;
}
