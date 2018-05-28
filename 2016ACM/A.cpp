#include <stdio.h>
int main(int argc, char const *argv[]) {
	int T;
	scanf("%d", &T);
	while (T--) {
		int N, P;
		scanf("%d %d", &N, &P);
		int l;
		float r;
		float maxr = 0;
		int index = 0;
		for (int i=1;i<=N;++i) {
			scanf("%d %f", &l, &r);
			if (r > maxr && P >= l) {
				maxr = r;
				index = i;
			}
		}
		printf("%d\n", index);
	}
	return 0;
}