#include <stdio.h>
int prime[10001];
int top = 0;
int isprime(int num)
{
	for (int i=2;i*i<=num;++i)
		if (num % i == 0)
			return false;
	return true;
}
int main(int argc, char const *argv[])
{
	int n;
	scanf("%d", &n);
	for (int num=2;num<10000000;++num)
	{
		if (isprime(num))
		{
			prime[top++] = num;
			if (top == n)
			{
				printf("%d", num);
				break;
			}
		}
	}
	return 0;
}