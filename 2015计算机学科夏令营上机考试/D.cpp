#include <iostream>
#include <stdio.h>
using namespace std;
int main(int argc, char const *argv[])
{
	int n;
	scanf("%d", &n);
	char s[10];
	float h;
	float m[40], f[40];
	int topm = 0, topf = 0;
	for (int i=0;i<n;++i)
	{
		scanf("%s %f", s, &h);
		if (s[0] == 'm')
			m[topm++] = h;
		else
			f[topf++] = h;
	}
	sort(m, m+topm);
	sort(f, f+topf);
	for (int i=0;i<topm;++i)
		printf("%.2f ", m[i]);
	for (int i=topf-1;i>=1;--i)
		printf("%.2f ", f[i]);
	printf("%.2f", f[0]);
	return 0;
}