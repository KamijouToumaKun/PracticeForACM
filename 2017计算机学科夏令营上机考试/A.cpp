#include <stdio.h>
int is_prime(int num) //1~100000不会超时的
{
	if (num == 1)
		return 0;
	for (int i=2;i*i<=num;++i)
		if (num % i == 0)
			return 0;
	return 1;
}
int main(int argc, char const *argv[])
{
	int x, y;
	scanf("%d %d", &x, &y);
	if (x > y)
	{
		int tmp;
		tmp = x;
		x = y;
		y = tmp;
	}
	int sum = 0;
	for (int i=x;i<=y;++i)
		sum += is_prime(i);
	printf("%d", sum);
	return 0;
}