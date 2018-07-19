#include <stdio.h>
// using namespace std;
int main(int argc, char const *argv[])
{
	int k, num, count[3] = {0};
	scanf("%d", &k);
	for (int i=0;i<k;++i)
	{
		scanf("%d", &num);
		if (num == 1)
			count[0] ++;
		else if (num == 5)
			count[1] ++;
		else if (num == 10)
			count[2] ++;
	}
	printf("%d\n%d\n%d", count[0], count[1], count[2]);
	return 0;
}