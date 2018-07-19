/*
我们把这两只青蛙分别叫做青蛙A和青蛙B，各自朝西跳
并且规定纬度线上东经0度处为原点，由东往西为正方向，
单位长度1米，这样我们就得到了一条首尾相接的数轴。
设青蛙A的出发点坐标是a，青蛙B的出发点坐标是b。青蛙A一次能跳m米，
青蛙B一次能跳n米，两只青蛙跳一次所花费的时间相同。纬度线总长L米。
现在要你求出它们跳了几次以后才会碰面

a+xm === b+xn mod L
x(m-n) + yL = b-a
x(b-a)/GCD + tL/GCD
y(b-a)/GCD - t(m-n)/GCD
*/
#include <stdio.h>
long long gcd(long long a,long long b,long long &x,long long &y){
    if (b==0){
        x=1,y=0;
        return a;
    }
    long long q=gcd(b,a%b,y,x);
    y-=a/b*x;
    return q;
}
void calc(long long a, long long b, long long m, long long n, long long L)
{
	long long x, y;
	long long GCD = gcd(m-n, L, x, y);
	if ((b-a) % GCD != 0)
	{
		printf("Impossible\n");
		return;
	}
	long long q = (b-a)/GCD;
	if (q == 0)
	{
		printf("0\n");
		return;
	}
	x *= q;
	x %= (L/GCD);
	if (x < 0)
	{
		if (GCD > 0)
			x += L/GCD;
		else
			x -= L/GCD;
	}
	printf("%lld\n", x);
	return;
}
int main(int argc, char const *argv[])
{
	long long a, b, m, n, L;
	scanf("%lld%lld%lld%lld%lld", &a, &b, &m, &n, &L);
	calc(a,b,m,n,L);
	return 0;
}