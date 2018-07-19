#include <string.h>
#include <stdio.h>
int main(int argc, char const *argv[])
{
	char s[1001];
	scanf("%s", s);
	const int len = strlen(s);
	for (int i=0;i<len;++i)
		if (s[i] <= 'Z')
			s[i] += 'a' - 'A';
	for (int i=0;i<len;)
	{
		char c = s[i];
		int sum = 0;
		while (c == s[i] && i < len)
		{
			sum ++;
			i ++;
		}
		printf("(%c,%d)", c, sum);
	}
	return 0;
}