/*
calculate the integral part of (7+4√3)^N

回想一下斐波那契数列，
a[n+2] = a[n+1] + a[n]
特征方程x^2-x-1 = 0
特征根(1+-√5)/2
a[n] = k1((1+√5)/2)^n + k2((1-√5)/2)^n

这里要凑一个特征方程：
不妨令a = 1
-b+-√b^2-4c / 2 = 7+-4√3
于是b=-14，c=1
x^2-14x+1=0, a[n+2] = 14a[n+1]-a[n]

a[n] = k1(7+4√3)^n + k2(7-4√3)^n
a[0] = k1+k2, a[1] = k1(7+4√3)+k2(7-4√3)
要找这样的一组a[0]、a[1]
1、它们都是整数，这样才能递推
	于是需要k1=k2=k，则a0=2k，a1=14k
	（令k=1即可）
2、则a[n] = k((7+4√3)^n + (7-4√3)^n)
a[n]/k = (7+4√3)^n + (7-4√3)^n
其中0<(7-4√3)^n<1（当n>=1）
于是[(7+4√3)^n] = 1（当n=0）；a[n]/k-1（当n>=1）
代码：
			long long an_2 = 2, an_1 = 14, an;
			for (int i=0;i<=n-2;++i) { 
				an = an_1 - an_2;
				while (an < 0) an += M;
				while (an >= M) an -= M;
				for (int t=0;t<13;++t) {
					an += an_1;
					while (an < 0) an += M;
					while (an >= M) an -= M;
				}
				an_2 = an_1;
				an_1 = an;
			}
			printf("%lld\n", an-1);

但是，注意到，n可以是1,000,000,000。还是会超时。
当n=10000000，得到答案325745954，已经就超时了。
还要使用矩阵快速幂。
[an+1	=	[14 -1	^n	[14
an]			1 0]		2]
*/
#define M 1000000007ll
#include <stdio.h>
long long tmp[2][2];
void multi(long long a[2][2], long long b[2][2]) {//a *= b
	for (int i=0;i<2;++i)
		for (int j=0;j<2;++j)
			tmp[i][j] = 0;
	for (int i=0;i<2;++i)
		for (int j=0;j<2;++j)  
			for (int k=0;k<2;++k) {
				tmp[i][j] = (tmp[i][j]+a[i][k]*b[k][j]) % M; //负数也可以求模，求出来是负数
			}
	for(int i=0;i<2;++i)  
		for(int j=0;j<2;++j)  
			a[i][j] = tmp[i][j];  
}
int main(int argc, char const *argv[]) {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n; //1,000,000,000
		scanf("%d", &n);
		if (n == 0) {
			printf("%d\n", 1);
		} else if (n == 1) {
			printf("%d\n", 13);
		} else {
			long long res[2][2] = {0};
			for (int i=0;i<2;++i)
				res[i][i] = 1;
			long long mi[2][2] = {14,-1,1,0};
			while (n) {//快速幂
				if (n & 1)  
					multi(res,mi);//res=res*mi;
				multi(mi,mi);//mi=mi*mi
				n>>=1;  
			}
			long long start[2][2] = {14,0,2,0};
			multi(res,start);
			long long ans = res[1][0]-1;
			if (ans < 0) ans += M;//最后的结果不能是负数
			printf("%lld\n", ans);
		}
	}
	return 0;
}