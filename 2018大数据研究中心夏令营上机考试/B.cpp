#include <string.h>
#include <stdio.h>
int main(int argc, char const *argv[])
{
	char dst[101], src[101], dst2[101];
	scanf("%s%s%s", dst, src, dst2);
	int src2dst[26], dst2src[26];
	for (int i=0;i<26;++i)
	{
		src2dst[i] = -1;
		dst2src[i] = -1;
	}
	for (int i=0;i<strlen(src);++i)
	{
		if (src2dst[src[i]-'A'] == -1)
			src2dst[src[i]-'A'] = dst[i]-'A';
		else if (src2dst[src[i]-'A'] != dst[i]-'A') //两次映射不同
		{
			printf("Failed");
			return 0;
		}
		if (dst2src[dst[i]-'A'] == -1)
			dst2src[dst[i]-'A'] = src[i]-'A';
		else if (dst2src[dst[i]-'A'] != src[i]-'A') //两次逆映射不同
		{
			printf("Failed");
			return 0;
		}
	}
	for (int i=0;i<26;++i)
		if (dst2src[i] == -1)
		{
			printf("Failed");
			return 0;
		}
	for (int i=0;i<strlen(dst2);++i)
		printf("%c", dst2src[dst2[i]-'A']+'A');
	return 0;
}