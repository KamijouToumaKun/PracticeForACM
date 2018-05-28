#include <stdio.h>
int main(int argc, char const *argv[]) {
	int T;
	int date;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &date);
		if (date <= 20170521) {
			printf("unsafe\n");
		} else {
			printf("safe\n");
		}
	}
	return 0;
}