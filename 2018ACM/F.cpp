/*找到所有的映射链，它们两两不交。
例如，N=3,F(1)=2,F(2)=4,F(3)=4
则链为1->2；3

只需要单独考虑每一条链。
设一条链的长度为k，不妨设它就是1->2->...->k
设有a1个顾客的首选是1，a2个的首选是2，……，ak个的首选是k
为了使这条链上不发生冲突，要去求a1～ak的每一组解，它满足：
ak <= 1
a[k-1]+ak <= 2
a[k-2]+a[k-1]+ak <= 3
...
a1+a2+...+ak <= k
且a1+a2+...+ak = k（要取等，不然人数超过链长也会发生冲突）
对每一组这样的解，a1个1、a2个2……ak个k的任意一个排列，都是一个可行的序列
这样的排列有k!/a1!a2!...ak!个
将它们求和：k! * ∑(1/a1!a2!...ak! for a1~ak是一组解)。这就是答案。

k! * ∑(1/a1!a2!...ak! for a1~ak是一组解) = ？
对k=1、2、3、4手工验证，得到答案为(k+1)^(k-1)（我也不知道怎么证明……）
设一共有t条链，长度分别为k1～kt，且k1+...+kt=n
每条链的元素可以交叉地在序列中出现。
先从长为n的序列中挑k1个位置用来放链1对应的序列
再挑k2个位置用来放链2对应的序列
……
得到n!/(k1!k2!...kn!)，再乘以每条链的可行序列数(ki+1)^(ki-1)，就是最后答案。

如何计算n!/(k1!k2!...kn!) mod 10^9+7？
10^9+7是素数，除以a等于乘以a的数论倒数。
数论倒数可以用扩展欧几里得算法求。
(ki+1)^(ki-1)就直接求幂，因为ki<=n<=200000，比较小，连快速幂都不用写。
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
#define M 1000000007
#define N 200001
#define LL long long
int ny[N];

int exgcd(int a,int b, int &x, int &y)
{
	if (!b) { x = 1; y = 0; return a;}
	int sav = exgcd(b,a % b, x, y);
	int tmp = y;
	y = x - (a/b) * y;
	x = tmp;
	return sav;
}

LL getans(int n,int *k,int kn)
{
	//cout << n << endl;
	//for (int i = 0; i < kn; ++i)
	//	cout << k[i] << ' ';
	//cout << endl;
	//cout << kn << endl;

	LL res = 1;
	for (LL i = 1; i <= n; ++i)
		res = (res * i) % M;
	//cout << res << endl;
	for (int i = 0; i < kn; ++i)
	{
		for (int j = 0; j < k[i] - 1; ++j)
		{
			res *= (LL)(k[i] + 1);
			res %= M;
		}
		for (int j = 1; j <= k[i]; ++j)
		{
			res *= (LL)(ny[j]);
			res %= M;
		}
		//cout << "res = " << res << endl;
	}
	return res;
}

int a[2000002];
bool flag[200002];
int chain[200002];
int main()
{
	int tmp;
	for (int i = 1; i < N; ++i)
	{
		exgcd(i,M,ny[i],tmp);
		if (ny[i] < 0)
			ny[i] += M;
	}
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		for (int i=1;i<=n;++i) {
			scanf("%d", &a[i]);
			flag[i] = false;
		}
		flag[n+1] = true;
		int num = 0;
		for (int i=1;i<=n;++i) {
			if (flag[i]) continue;//已经存在于另一条链上了
			int j = i;
			int count = 0;
			while (flag[j] == false){//找到一条新链的开头，计算它的长度
				flag[j] = true;
				j = a[j];
				count++;
			}
			chain[num++] = count;
		}
		//cout << (getans(n, chain, num) * ny[2]) % M << endl;
		cout << getans(n,chain,num) << endl;
	}
	//for (int i = 1; i < 10; ++i)
	//	cout << ny[i] << endl;
	return 0;
}