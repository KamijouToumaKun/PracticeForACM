#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
	char s[501];
	cin.getline(s, 500, '\n');

	int beg = 0, len = strlen(s);
	for (int i=0;i<=len;++i) {
		if (i == len || s[i] == ' ') {
			for (int j=i-1;j>=beg;--j)
				printf("%c", s[j]);
			while (s[i] == ' ') {
				printf("%c", s[i]);
				++i;
			}
			beg = i;
		}
	}

	return 0;
}