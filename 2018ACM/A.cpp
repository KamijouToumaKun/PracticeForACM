/*
每天的陪伴时间是非负整数
约束：每连续7天，陪伴时间之和不小于7
最小化总代价：∑每天的陪伴时间 * 陪伴代价
测试组数1<=T<=100, 1<=N<=10000

第i天的陪伴小时数只被前六天约束，自然想到动规。
设dp[i][a][b]...[g]表示：最近七天的陪伴时间为a～g的情况下，第1～i天的最小总代价
1<=i<=N<=10000, 0<=a~g<=7
状态转移方程：dp[i][a][b]...[g] 
1、= min{dp[i-1][z][a]...[f]+price[i]*g for z+a+...+f >= 7}
   = min{dp[i-1][z][a]...[f] for z+a+...+f >= 7} +price[i]*g (if a+...+g >= 7)
2、= inf (others)
时间复杂度：T*N*(8^8)（7维 & 内层循环）

可以省去当天这一维（？）
dp_new[i][a][b]...[f] 
= min{dp_new[i-1][z][a]...[e]+price[i]*f for z+a+...+e+f >= 7}
时间复杂度：T*N*(8^7)（6维 & 内层循环）

还可以使用滚动数组省去天数这一维，节省内存开销。但是时间复杂度没有降低、太高了。

如何优化？
1、可以认为每连续7天，陪伴时间之和都恰好等于7吗？
显然不是。反例：
天数：1 ... 6 7 ... 13 14 ... 19
       inf      0        inf
最优方案是：
     0 ... 0 7 0..0 7  0 ... 0
中间七天就一共陪了14小时。
2、最优化求解？
	这是一个非凸问题。
3、使用整数规划？	
4、考虑到约束和目标函数线性，猜测最小值点的取值也是极端的：
	每天的陪伴时间不是0就是7.
	动规的复杂度下降到2^7。足够了。

如何证明这个假设呢？
有这个结论成立的话，是不是可以直接贪心求解呢？
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define N 10100
#define inf 800000000
int a[2][2][2][2][2][2];//滚动数组
int b[2][2][2][2][2][2];
int x[N];//代价数组
const int res = 7;
int sum,n;
int ans = inf;
int hr[2] = {0,7};//每天的陪伴时间只有0和7两种选择
void update(int x)
{
	for (int a0 = 0; a0 <= 1; ++ a0)
	for (int a1 = 0; a1 <= 1; ++ a1)
	for (int a2 = 0; a2 <= 1; ++ a2)
	for (int a3 = 0; a3 <= 1; ++ a3)
	for (int a4 = 0; a4 <= 1; ++ a4)
	for (int a5 = 0; a5 <= 1; ++ a5)
	{
		b[a0][a1][a2][a3][a4][a5] = inf;
		sum = hr[a0] + hr[a1] + hr[a2] + hr[a3] + hr[a4] + hr[a5];
		for (int i = 0; i <= 1; ++i) 
			if (sum + hr[i] >= 7)
				b[a0][a1][a2][a3][a4][a5] = min(b[a0][a1][a2][a3][a4][a5],
					a[i][a0][a1][a2][a3][a4] + x * hr[a5]);
	}
}

void copy()
{
	for (int a0 = 0; a0 <= 1; ++ a0)
	for (int a1 = 0; a1 <= 1; ++ a1)
	for (int a2 = 0; a2 <= 1; ++ a2)
	for (int a3 = 0; a3 <= 1; ++ a3)
	for (int a4 = 0; a4 <= 1; ++ a4)
	for (int a5 = 0; a5 <= 1; ++ a5)
		a[a0][a1][a2][a3][a4][a5] = b[a0][a1][a2][a3][a4][a5];
}

int main()
{
	int T;
	cin >> T;
	for (int k = 0; k < T; ++k)
	{
		cin >> n;
		ans = inf;
		for (int i = 0; i < n; ++i) cin >> x[i];
		for (int a0 = 0; a0 <= 1; ++ a0)
		for (int a1 = 0; a1 <= 1; ++ a1)
		for (int a2 = 0; a2 <= 1; ++ a2)
		for (int a3 = 0; a3 <= 1; ++ a3)
		for (int a4 = 0; a4 <= 1; ++ a4)
		for (int a5 = 0; a5 <= 1; ++ a5)
		{
			a[a0][a1][a2][a3][a4][a5] = b[a0][a1][a2][a3][a4][a5] = inf;
		}
		for (int a0 = 0; a0 <= 1; ++ a0)
		for (int a1 = 0; a1 <= 1; ++ a1)
		for (int a2 = 0; a2 <= 1; ++ a2)
		for (int a3 = 0; a3 <= 1; ++ a3)
		for (int a4 = 0; a4 <= 1; ++ a4)
		for (int a5 = 0; a5 <= 1; ++ a5)
		{//第6天的状态
			a[a0][a1][a2][a3][a4][a5] = hr[a0] * x[0] + hr[a1] * x[1] + hr[a2] * x[2] + hr[a3] * x[3] + hr[a4] * x[4] + hr[a5] * x[5];
		}
		for (int i = 6; i < n; ++i)
		{
			update(x[i]);//第7天到第n天，进行dp
			copy();//滚动数组
		}
		for (int a0 = 0; a0 <= 1; ++ a0)
		for (int a1 = 0; a1 <= 1; ++ a1)
		for (int a2 = 0; a2 <= 1; ++ a2)
		for (int a3 = 0; a3 <= 1; ++ a3)
		for (int a4 = 0; a4 <= 1; ++ a4)
		for (int a5 = 0; a5 <= 1; ++ a5)
			ans = min(ans,a[a0][a1][a2][a3][a4][a5]);
		cout << ans << endl;
	}
	return 0;
}