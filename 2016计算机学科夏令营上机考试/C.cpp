#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
	char array[200][20];
	int col;
	char s[201];
	scanf("%d", &col);
	scanf("%s", s); //no space

	int row = strlen(s) / col;
	int k=0;
	for (int i=0;i<row;++i)
		for (int j=0;j<col;++j) {
			if (i%2 == 0) {
				array[i][j] = s[k++];
			} else {
				array[i][col-1-j] = s[k++];
			}
		}
	for (int j=0;j<col;++j)
		for (int i=0;i<row;++i) {
			printf("%c", array[i][j]);
		}

	return 0;
}