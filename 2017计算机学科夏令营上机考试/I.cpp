/*A, A+C, A+2C, ... A+aC === B (mod 2^k)
aC + b(2^k) = B-A
m取最小的非负整数解
首先需要(C,2^k)|B-A，否则无解
特解为aC + b(2^k) = (C, 2^k)
解为a + t 2^k/(C,2^k)
b - t C/(C,2^k)
aqC + bq(2^k) = q(C, 2^k) = B-A
解为aq + tq 2^k/(C,2^k) >= 0*/
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

void calc(long long a, long long b, long long c, long long k)
{
	long long x, y;
	long long GCD = gcd(c, 1ll<<k, x, y); //GCD>0
	if ((b-a) % GCD != 0)
	{
		printf("FOREVER\n");
		return;
	}
	long long q = (b-a)/GCD; //如果q<0怎么办？
	if (q == 0) //如果q是0
	{
		printf("0\n");
		return;
	}
	x *= q; //1*-2 = -2
	x %= ((1ll<<k)/GCD); //解为aq + t 2^k/(C,2^k) >= 0，注意后半不加q！
	if (x < 0)
		x += ((1ll<<k)/GCD);
	printf("%lld\n", x);
	return;
}
int main(int argc, char const *argv[])
{
	long long a, b, c, k;
	while (scanf("%lld%lld%lld%lld", &a, &b, &c, &k), a||b||c||k)
		calc(a, b, c, k);
	return 0;
}