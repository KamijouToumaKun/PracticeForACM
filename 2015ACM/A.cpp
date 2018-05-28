#include <string.h>
#include <stdio.h>
int translate(char s[]) {
	if (strcmp(s, "water") == 0) return 0;
	else if (strcmp(s, "wood") == 0) return 1;
	else if (strcmp(s, "fire") == 0) return 2;
	else if (strcmp(s, "earth") == 0) return 3;
	else if (strcmp(s, "metal") == 0) return 4;
	else return -1;
}
int main(int argc, char const *argv[]) {
	int wuxing[5][5] = {0}; //default: no relationship
	const int water = 0;
	const int wood = 1;
	const int fire = 2;
	const int earth = 3;
	const int metal = 4;
	wuxing[water][wood] = 1; //generate
	wuxing[wood][fire] = 1;
	wuxing[fire][earth] = 1;
	wuxing[earth][metal] = 1;
	wuxing[metal][water] = 1;
	wuxing[water][fire] = -1; //overcome
	wuxing[fire][metal] = -1;
	wuxing[metal][wood] = -1;
	wuxing[wood][earth] = -1;
	wuxing[earth][water] = -1;
	int T;
	scanf("%d", &T);
	while (T--) {
		char s1[10], s2[10];
		int e1, e2;
		scanf("%s %s", s1, s2);
		e1 = translate(s1);
		e2 = translate(s2);
		if (wuxing[e1][e2] != 0) {
			s1[0] -= 'a'-'A';
			if (wuxing[e1][e2] == 1) {
				printf("%s generates %s.\n", s1, s2);
			} else if (wuxing[e1][e2] == -1) {
				printf("%s overcomes %s.\n", s1, s2);
			}
		} else if (wuxing[e2][e1] != 0) {
			s2[0] -= 'a'-'A';
			if (wuxing[e2][e1] == 1) {
				printf("%s generates %s.\n", s2, s1);
			} else if (wuxing[e2][e1] == -1) {
				printf("%s overcomes %s.\n", s2, s1);
			}
		} else {
			
		}
	}
	return 0;
}