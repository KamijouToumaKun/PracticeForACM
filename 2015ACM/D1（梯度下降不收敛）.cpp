/*P和r未知
P(ABC)和r(abc)已知
dis(P, PA) = r-ra
dis(P, PB) = r-rb
dis(P, PC) = r-rc

就是解方程：
(x-xa)^2+(y-ya)^2 = (r-ra)^2
(x-xb)^2+(y-yb)^2 = (r-rb)^2
(x-xc)^2+(y-yc)^2 = (r-rc)^2

误差函数：((x-xa)^2+(y-ya)^2-(r-ra)^2)^2
+ ((x-xb)^2+(y-yb)^2-(r-rb)^2)^2
+ ((x-xc)^2+(y-yc)^2-(r-rc)^2)^2

梯度下降
x -= 2((x-xa)^2+(y-ya)^2-(r-ra)^2) 2(x-xa)
	+ 2((x-xb)^2+(y-yb)^2-(r-rb)^2) 2(x-xb)
	+ 2((x-xc)^2+(y-yc)^2-(r-rc)^2) 2(x-xc)
y -= 2((x-xa)^2+(y-ya)^2-(r-ra)^2) 2(y-ya)
	+ 2((x-xb)^2+(y-yb)^2-(r-rb)^2) 2(y-yb)
	+ 2((x-xc)^2+(y-yc)^2-(r-rc)^2) 2(y-yc)
r -= 2((x-xa)^2+(y-ya)^2-(r-ra)^2) (-2)(r-ra)
	+ 2((x-xb)^2+(y-yb)^2-(r-rb)^2) (-2)(r-rb)
	+ 2((x-xc)^2+(y-yc)^2-(r-rc)^2) (-2)(r-rc)
*/
/*
1
1000 200 10
100 20 1
100 10 9
=> 754.41434646 -857.56163040 1095.70203800
*/
#include <math.h>
#include <stdio.h>
double max(double x, double y) {
	return x>y?x:y;
}
int main(int argc, char const *argv[]) {
	int T;
	scanf("%d", &T);
	while (T--) {
		int xa, ya, ra;
		int xb, yb, rb;
		int xc, yc, rc;
		scanf("%d %d %d", &xa, &ya, &ra);
		scanf("%d %d %d", &xb, &yb, &rb);
		scanf("%d %d %d", &xc, &yc, &rc);
		double x = (xa+xb+xc)/3, y = (ya+yb+yc)/3, r;
		r += sqrt((x-xa)*(x-xa)+(y-ya)*(y-ya))+ra;
		r += sqrt((x-xb)*(x-xb)+(y-yb)*(y-yb))+rb;
		r += sqrt((x-xc)*(x-xc)+(y-yc)*(y-yc))+rc;
		r /= 3;
		//设置合适的初值，降低迭代次数
		double lastx = -10000, lasty = -10000, lastr = -10000;
		double x_a, y_a, r_a;
		double x_b, y_b, r_b;
		double x_c, y_c, r_c;
		double rate = 1e-7;//最多是1e-7，不然会溢出；long double都不行
		const double epsilon = 1e-7;//精度是1e-6
		const int maxEpoch = 100000;//设置迭代上限，否则无解
		//这个样例就会陷入鞍点无法收敛。给它加扰动都不行。放弃。
		int i;
		for (i=0;i<maxEpoch;++i) {
			x_a = x-xa;y_a = y-ya;r_a = r-ra;
			x_b = x-xb;y_b = y-yb;r_b = r-rb;
			x_c = x-xc;y_c = y-yc;r_c = r-rc;

			x -= rate* 4* ((x_a*x_a+y_a*y_a-r_a*r_a) * x_a
				+ (x_b*x_b+y_b*y_b-r_b*r_b) * x_b
				+ (x_c*x_c+y_c*y_c-r_c*r_c) * x_c);
			y -= rate* 4* ((x_a*x_a+y_a*y_a-r_a*r_a) * y_a
				+ (x_b*x_b+y_b*y_b-r_b*r_b) * y_b
				+ (x_c*x_c+y_c*y_c-r_c*r_c) * y_c);
			r += rate* 4* ((x_a*x_a+y_a*y_a-r_a*r_a) * r_a
				+ (x_b*x_b+y_b*y_b-r_b*r_b) * r_b
				+ (x_c*x_c+y_c*y_c-r_c*r_c) * r_c);
			if (abs(lastx-x)<=epsilon && abs(lasty-y)<=epsilon
				&& abs(lastr-r)<=epsilon) {//收敛
				break;
			} else {
				lastx = x;
				lasty = y;
				lastr = r;
			}
		}
		// if (i == maxEpoch) {
		// 	printf("no solution\n");
		// } else {
			printf("%.8lf %.8lf %.8lf\n", x, y, r);
			printf("%.8lf %.8lf %.8lf\n", 
				x_a*x_a+y_a*y_a-r_a*r_a,
				x_b*x_b+y_b*y_b-r_b*r_b,
				x_c*x_c+y_c*y_c-r_c*r_c);
		// }
	}
	return 0;
}