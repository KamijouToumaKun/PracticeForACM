/*对于x，求floor(2^31-1/x的最大素因子)
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
#define N 1000
#define LL long long
LL n;
int main()
{
	cin >> n;
	//LL x = ~(1 << 31);
	//cout << x << endl;
	while (n != 0)
	{
		LL ans = -1;
		LL tmp;
		for (LL i = 2;;++i)
		{
			tmp = i * i;
			if (tmp > n)
				break;
			if (n % i == 0)
			{
				ans = i;
				while (n % i == 0)
					n /= i;
			}
		}
		if (ans == -1 || n != 1)
			ans = n;
		LL x = 2147483647;
		cout << x / ans << endl;
		cin >> n;
	}
	return 0;
}