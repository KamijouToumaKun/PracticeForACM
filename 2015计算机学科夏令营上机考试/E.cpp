#include <string.h>
#include <stdio.h>
char a[256];
char b[256];
int min(int x, int y)
{
	if (x < y)
		return x;
	else
		return y;
}
int main(int argc, char const *argv[])
{
	char *s1 = a, *s2 = b, *tmp;
	int n, len1, len2, sum = 0, lenpre;
	scanf("%d", &n);
	scanf("%s", s1);
	len1 = strlen(s1);
	sum += len1;
	for (int i=1;i<n;++i)
	{
		scanf("%s", s2);
		len2 = strlen(s2);
		lenpre = 0;
		for (int j=0;j<min(len1,len2);++j)
		{
			if (s1[j] != s2[j])
				break;
			lenpre++;
		}
		sum += 1+len2-lenpre;
		tmp = s1;
		s1 = s2;
		s2 = tmp;
		len1 = len2;
	}
	printf("%d", sum);
	return 0;
}