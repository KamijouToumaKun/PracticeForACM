/*P和r未知
P(ABC)和r(abc)已知
dis(P, PA) = r-ra
dis(P, PB) = r-rb
dis(P, PC) = r-rc

就是解方程：
(x-xa)^2+(y-ya)^2 = (r-ra)^2
(x-xb)^2+(y-yb)^2 = (r-rb)^2
(x-xc)^2+(y-yc)^2 = (r-rc)^2
(1)-(2)和(1)-(3)得到两个xyr的线性方程
表出：x=...r，y=...r，z=...r

x2-2xax+xa2 + y2-2yay+ya2 = r2-2rar+ra2
x2-2xbx+xb2 + y2-2yby+yb2 = r2-2rbr+rb2
相减
-2(xa-xb)x + xa2-xb2 -2(ya-yb)y + ya2-yb2 = -2(ra-rb)r + ra2-rb2
整理
-2(xa-xb)x -2(ya-yb)y = -(xa2-xb2) -(ya2-yb2) +ra2-rb2 -2(ra-rb)r
同理
-2(xa-xc)x -2(ya-yc)y = -(xa2-xc2) -(ya2-yc2) +ra2-rc2 -2(ra-rc)r

[-2(xa-xb) -2(ya-yb)] [x] = [p]
[-2(xa-xc) -2(ya-yc)] [y]   [q]

若左侧的行列式不等于0：有解
|p -2(ya-yb)|				|-2(xa-xb) p|
|q -2(ya-yc)|				|-2(xa-xc) q|
-------------
|-2(xa-xb) -2(ya-yb)|
|-2(xa-xc) -2(ya-yc)|

x的分子=						y的分子=
-2p(ya-yc)+2q(ya-yb)		-(-2p(xa-xc)+2q(xa-xb))
-2 [-(xa2-xb2) -(ya2-yb2) +ra2-rb2 -2(ra-rb)r] (ya-yc)
+2 [-(xa2-xc2) -(ya2-yc2) +ra2-rc2 -2(ra-rc)r] (ya-yb)
= 4(ra-rb)(ya-yc)r -2[-(xa2-xb2) -(ya2-yb2) +ra2-rb2](ya-yc)
-4(ra-rc)(ya-yb)r +2[-(xa2-xc2) -(ya2-yc2) +ra2-rc2](ya-yb)
记为x=s1r+t1
同理，y的表达式等于x的表达式把(ya-yb/c)换成(xa-xb/c)、再加上负号
记为y=s2r+t2

带回到(x-xa)^2+(y-ya)^2 = (r-ra)^2
(s1*r+t1-xa)^2 + (s2*r+t2-ya)^2 = (r-ra)^2
 s1^2 r2 + 2s1(t1-xa) r + (t1-xa)^2
+s2^2 r2 + 2s2(t2-ya) r + (t2-ya)^2
=	  r2 +		-2ra  r + ra^2

记a,b,c = 
s1^2+s2^2-1, 2s1(t1-xa)-2s2(t2-ya)+2ra, (t1-xa)^2+(t2-ya)^2-ra^2
求根公式，取r的较大的根*/
#include <math.h>
#include <stdio.h>
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
		int xa_b=xa-xb, xa_c=xa-xc;
		int ya_b=ya-yb, ya_c=ya-yc;
		int ra_b=ra-rb, ra_c=ra-rc;
		int xab=xa+xb, xac=xa+xc;
		int yab=ya+yb, yac=ya+yc;
		int rab=ra+rb, rac=ra+rc;
		long long fenmu = 4*(xa_b*ya_c-xa_c*ya_b);
		if (fenmu == 0) {
			printf("no solution\n"); //???
			continue;
		}
		double s1 = 4.0*(ra_b*ya_c-ra_c*ya_b)/fenmu;
		double t1 = 2.0*
			((-xa_c*xac -ya_c*yac + ra_c*rac)*ya_b
			-(-xa_b*xab -ya_b*yab + ra_b*rab)*ya_c)/fenmu;
		double s2 = -4.0*(ra_b*xa_c-ra_c*xa_b)/fenmu;
		double t2 = -2.0*
			((-xa_c*xac -ya_c*yac + ra_c*rac)*xa_b
			-(-xa_b*xab -ya_b*yab + ra_b*rab)*xa_c)/fenmu;
		// printf("%lf %lf %lf %lf\n", s1, t1, s2, t2);
		long long s1fenmu = 4.0*(ra_b*ya_c-ra_c*ya_b);
		long long t1fenmu = 2.0*
			((-xa_c*xac -ya_c*yac + ra_c*rac)*ya_b
			-(-xa_b*xab -ya_b*yab + ra_b*rab)*ya_c);
		long long s2fenmu = -4.0*(ra_b*xa_c-ra_c*xa_b);
		long long t2fenmu = -2.0*
			((-xa_c*xac -ya_c*yac + ra_c*rac)*xa_b
			-(-xa_b*xab -ya_b*yab + ra_b*rab)*xa_c);
		// 发现正确的x和r也符合关系：x=mys1*r+myt1
		// 到这里为止是正确的
		double a = s1*s1+s2*s2-1;
		double b = 2*s1*(t1-xa)+2*s2*(t2-ya)+2*ra;
		double c = (t1-xa)*(t1-xa)+(t2-ya)*(t2-ya)-ra*ra;
		long long afenmu2 = s1fenmu*s1fenmu+s2fenmu*s2fenmu-fenmu*fenmu;
		long long bfenmu2 = (2*s1fenmu*(t1fenmu-xa*fenmu)
			+2*s2fenmu*(t2fenmu-ya*fenmu)
			+2*ra*fenmu) * fenmu;
		long long cfenmu2 = (t1fenmu-xa*fenmu)*(t1fenmu-xa*fenmu)
			+(t2fenmu-ya*fenmu)*(t2fenmu-ya*fenmu)
			-ra*ra*fenmu*fenmu;
		//abc同时*=fenmu^2，保证是整数
		if (afenmu2 < 0) {//这样判断其值与0的大小比较准确
			a = -a;
			b = -b;
			c = -c;
		}
		double r;
		// printf("%lf %lf %lf", a,b,c);
		// 求根也是正确的；问题在于，a<0时、-b-sqrt(delta)/2/a才是大根！
		if (afenmu2 == 0) {
			if (bfenmu2 == 0) {
				printf("no solution\n"); //TODO:c=0?c!=0?
				continue;
			}
			r = 1.0*-c/b;
		} else {
			double delta = b*b-4*a*c;
			if (delta < 0) {
				printf("no solution\n");
				continue;
			}
			r = (-b+sqrt(delta))/2/a;
		}
		if (r <= 0) {
			printf("no solution\n");
			continue;
		}
		double x = s1*r+t1;
		double y = s2*r+t2;
		printf("%.8lf %.8lf %.8lf\n", x, y, r);
	}
	return 0;
}