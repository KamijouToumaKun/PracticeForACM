#define N 16
#include <string.h>
#include <stdio.h>
char name[N][2][1000];
int arr[N] = {14,1,2,3,0,4,5,6,7,8,9,10,11,12,13};
int n = 15;

// int arr[N] = {7,6,1,2,3,0,4,5};
// int n = 8;
// int arr[N] = {1,2,0,4,3};
// int n = 5;

int recordTop = 0; //记录当前一步操作
int recordStatus[N];
int recordTurns[N];
int bestRecordTop = 0; //当前最佳的一步操作
int bestRecordStatus[N];
int bestArr[N];

int pathTop; //当前最佳路径
int path[N][3];
void mypush(int status) {
	recordStatus[recordTop] = status;
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
int maxcount;
int count() {
	int c = 0;
	for (int i=0;i<n;++i)
		c += (arr[i]==i);
	return c;
}
void search(int status, bool leaf) {
	int tmp;
	if (leaf) {//叶节点
		int nowcount = count();//当前匹配的元素个数
		if (nowcount > maxcount) {
			maxcount = nowcount;
			bestRecordTop = recordTop;//把当前操作复制一份
			for (int t=0;t<recordTop;++t) {
				bestRecordStatus[t] = recordStatus[t];
			}
			for (int t=0;t<n;++t) {//把当前数组也复制一份
				bestArr[t] = arr[t];
			}
		}
	} else {
		if (status != 0) {//不记录根节点
			mypush(status); //当前操作入栈
		}
		for (int i=0;i<n;++i)
			for (int j=i+1;j<n;++j) {
				if ((arr[j]==i || arr[i]==j) && //每一次并行的交换至少要多让一个元素归位
					(((1<<i)|(1<<j)) & status) == 0) {
					tmp = arr[i];
					arr[i] = arr[j];
					arr[j] = tmp;
					search(status|(1<<i)|(1<<j), false);//没有冲突、可以并行，于是可以继续搜索
					tmp = arr[i];
					arr[i] = arr[j];
					arr[j] = tmp;
				}
			}
		search(status, true);//当前节点也可以就是叶节点
		if (status != 0) {
			mypop(); //出栈
		}
	}
}
int main(int argc, char const *argv[]) {
	scanf("%d", &n);
	for (int i=0;i<n;++i) {
		scanf("%s %s", name[i][0], name[i][1]);
	}
	for (int i=0;i<n;++i) {
		for (int j=0;j<n;++j) {
			if (strcmp(name[i][1], name[j][0]) == 0) {
				arr[i] = j;
				break;
			}
		}
	}//input

	recordTop = 1; //栈清空，保留一个根节点
	for (int i=1;i<=n;++i) {
		maxcount = 0;
		search(0, false); //遍历每一轮的所有并行交换方法，得到最优解：一步之后匹配的元素最多

		recordTop = bestRecordTop;//恢复record
		for (int t=0;t<recordTop;++t) {
			recordStatus[t] = bestRecordStatus[t];
			if (recordTurns[t] == 0)
				recordTurns[t] = i;
		}
		// printf("---\n");
		// for (int t=0;t<recordTop;++t) {
		// 	printf("%x ", recordStatus[t]);
		// }
		// printf("\n");
		for (int t=0;t<n;++t) {//恢复最佳的arr状态，继续
			arr[t] = bestArr[t];
			// printf("%d ", arr[t]);
		}
		// printf("\n---\n");
		if (maxcount == n) {//搜索到了终点，结束
			break;
		}
	}
	myrecord();
	printf("%d\n", path[pathTop-1][2]);
	int lastTurns = 0, turns;
	for (int i=0;i<pathTop;++i) {
		turns = path[i][2];
		if (turns == lastTurns+1) {//新的turns开始了
			printf("%d\n", turns);
		}
		lastTurns = turns;
		printf("%s %s\n", name[path[i][0]][0], name[path[i][1]][0]);
	}
	return 0;
}