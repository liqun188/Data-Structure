//��Ⱥ 2019212340
//kmp�㷨�������ʵ��Ĭ���ַ�������λ���Ϊ0 
#include <cstdio>
#include <cstring>

using namespace std;

void get_fail(char *P, int *fail) {    //�㷨4.9 ���ʧ���Ĭ���ַ�����0��ʼ�� 
	int len = strlen(P);
	fail[0] = fail[1] = 0;
	for(int i = 1; i < len; i++) {
		int j = fail[i];
		while(j && P[i] != P[j]) j = fail[j];
		fail[i + 1] = P[i]==P[j] ? j + 1 : 0;
	}
	return;
}

int kmp(char *P, int *fail, char *T) {    //�㷨4.8 �����ַ���ƥ�� 
	int lenP = strlen(P), lenT = strlen(T);
	int j = 0;
	for(int i = 0; i < lenT; i++) {
		while(j && T[i] != P[j])  j = fail[j];
		if(T[i] == P[j])  j++;
		if(j == lenP)  printf("%d ", i - j + 1);
	}
	return 0;
}

int main() {
	char T[1001], P[105];
	int fail[105];
	scanf("%s",T);
	scanf("%s",P);
	get_fail(P,fail);
	kmp(P,fail,T);
	return 0;
}
