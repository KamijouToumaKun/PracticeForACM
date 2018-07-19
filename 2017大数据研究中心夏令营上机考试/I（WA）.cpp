//很复杂啊，要考虑很多种情况，还有不等式的反向
#include <math.h>
#include <stdio.h>
int gcd(int a, int b, int &x, int &y)
{
	if (b==0)//ax + 00 = (a,0) = a
	{
		x=1;y=0;
		return a;
	}
	int GCD = gcd(b, a%b, y, x);
	//by + (a%b)x = (a,b)
	//aka (a-a/b*b)*x + by = (a,b)
	//then ax + b(y-a/b*x) = (a,b)
	y -= a/b*x;
	return GCD;
}
// ax + by = ans
// requirement: (a,b) | ans
// ax + by = (a, b)
// aqx + bqy = ans
// qx+tb/GCD>=0, -(qy-ta/GCD)>=0
// so t >= (-qx)/(b/GCD), t >= qy/(a/GCD)
// 5+3t>=0, t>=-1.67: t>=-1
// get min qx+tb/GCD -(qy-ta/GCD)
// qx-qy + t(a/GCD+b/GCD), t min
const int NEGA_INF = -(1<<28);
int max(int a, int b)
{
	if (a<b)
		return b;
	else
		return a;
}
void test(int a, int b, int ans, int &res1, int &res2, int bflag)
{//bflag=1表示a和b同号，bflag=-1表示异号
	int x, y;
	int GCD = gcd(a, b, x, y);
	if (ans % GCD != 0)
	{
		res1 = res2 = -1;
		return;
	}
	int q = ans/GCD;
	if (bflag == -1)//ax-by=(a,b)
	{
		// qx+tb/GCD>=0, -(qy-ta/GCD)>=0
		// qx-qy+t(b/GCD+a/GCD)最小。t的系数为正，只需要t尽量小
		// t本身不需要>=0 ！
		int t1 = ceil(1.0 * -(q*x) / (b/GCD)); //t>=t1
		int t2 = ceil(1.0 * (q*y) / (a/GCD)); //t>=t2
		int t = max(t1, t2);
		res1 = q*x+t*(b/GCD);
		res2 = -(q*y-t*(a/GCD));
	}
	else//ax+by=(a,b)
	{
		// qx+tb/GCD>=0, qy-ta/GCD>=0
		// qx+qy+t(b/GCD-a/GCD)最小。t的系数可能为负
		int t1 = ceil(1.0 * -(q*x) / (b/GCD));
		int t2 = floor(1.0 * (q*y) / (a/GCD));
		int t;
		if (t2 < t1)
			res1 = res2 = -1;
		else
		{
			if (b > a)
				t = t1;
			else
				t = t2;
			res1 = q*x+t*(b/GCD);
			res2 = (q*y-t*(a/GCD));
		}
	}
	return;
}
int main(int argc, char const *argv[])
{
	int a, b, ans;
	int res[3][2];
	while (scanf("%d%d%d", &a, &b, &ans), a||b||ans)
	{
		// 不要让ab是负数，否则不等式可能要反向变号
		test(a, b, ans, res[0][0], res[0][1], -1);//ax-by = ans
		test(a, b, -ans, res[1][0], res[1][1], -1);//by-ax = ans
		test(a, b, ans, res[2][0], res[2][1], 1);//ax+by = ans
		int minn = -NEGA_INF, index = -1;
		for (int i=0;i<3;++i)
			if (res[i][0]+res[i][1] > 0 && res[i][0]+res[i][1] < minn)
			{
				minn = res[i][0]+res[i][1];
				index = i;
			}
		if (index == -1)
			printf("no solution\n");
		else
			printf("%d %d\n", res[index][0], res[index][1]);
	}
	return 0;
}