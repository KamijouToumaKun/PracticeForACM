#define N 16
#include <stdio.h>
// int arr[N] = {14,1,2,3,0,4,5,6,7,8,9,10,11,12,13};
// int n = 15;
// int arr[N] = {7,6,1,2,3,0,4,5};
// int n = 8;
int arr[N] = {4,2,3,0,1};
int n = 5;
int maxdepth;

int recordTop = 0; //当前最佳路径栈
int recordStatus[N];
int recordTurns[N];
int pathTop; //当前最佳路径
int path[N][3];
void mypush(int status, int turns) {
	recordStatus[recordTop] = status;
	recordTurns[recordTop] = turns;
	++recordTop;
}
void mypop() {
	--recordTop;
}
void recordxy(int deltaStatus, int turns) {
	int t = 0;
	for (int i=0;i<n;++i)
		if ((1<<i) & deltaStatus) {
			path[pathTop][t] = i;
			++t;
		}
	path[pathTop][2] = turns;
	++pathTop;
}
void myrecord() {//把栈中的当前最佳路径记录在path里面
	pathTop = 0;
	int lastTurns = recordTurns[0];
	int lastStatus = recordStatus[0];
	int turns, status;
	for (int i=1;i<recordTop;++i) {
		turns = recordTurns[i];
		status = recordStatus[i];
		if (turns == lastTurns+1) {//如果跟上次的turns不一样
			recordxy(status, turns);
		} else {//记录下两次status的差，就是这一次交换的两个数
			recordxy(status&(~lastStatus), turns);
		}
		lastTurns = turns;
		lastStatus = status;
	}

	/*for (int i=0;i<pathTop;++i) {
		printf("%d %d %d;", path[i][0], path[i][1], path[i][2]);
	}
	printf("\n");*/
}
void search(int status, int depth, int turns) {
	if (depth > maxdepth) return;

	mypush(status, turns); //当前操作入栈
	int i, tmp;
	for (i=0;i<n;++i)
		if (arr[i] != i)
			break;
	if (i == n) { //到达终点
		maxdepth = turns; //更新最小值
		myrecord(); //反向记录路径方案
	} else {
		for (int i=0;i<n;++i)
			for (int j=i+1;j<n;++j) {
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
				if ((((1<<i)|(1<<j)) & status) == 0) {
					search(status|(1<<i)|(1<<j), depth+1, turns);//没有冲突，可以和上次并行
				} else {
					search((1<<i)|(1<<j), depth+1, turns+1);//不能和上次并行，重开一轮
				}
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
	}
	mypop(); //出栈
}
int main(int argc, char const *argv[]) {
	//TODO: input
	maxdepth = n;//已知一个解：每次交换至少让一个数复位。于是至多需要n次交换。
	search(0, 0, 1);
	
	printf("%d\n", pathTop);
	int lastTurns = 0, turns;
	for (int i=0;i<pathTop;++i) {
		turns = path[i][2];
		if (turns == lastTurns+1) {//新的turns开始了
			printf("%d\n", turns);
		}
		lastTurns = turns;
		printf("%d %d\n", path[i][0], path[i][1]);
	}

	return 0;
}