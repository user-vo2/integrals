#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define dbl double
#define l -5.0
#define r 0

extern double f1(double x);
extern double f2(double x);
extern double f3(double x);
extern double f1p(double x);
extern double f2p(double x);
extern double f3p(double x);
extern double f1pp(double x);
extern double f2pp(double x);
extern double f3pp(double x);
extern double f2p4(double x);

double max(double a, double b)
{
    return (a > b) ? a : b;
}

double root(double (*f)(double), double (*g)(double), double (*fp)(double), double (*gp)(double), double (*fpp)(double), double (*gpp)(double), double a, double b, double eps1)
{
    double a1, b1, fa, fb, fbp, fap;
    fa = f(a) - g(a);
    fb = f(b) - g(b);
    fbp = fp(b) - gp(b);
    fap = fp(a) - gp(a);
    if (fap * (fpp(a) - gpp(a)))
    {
        a1 = a - fa * (b - a) / (fb - fa);
        b1 = b - fb / fbp;
    }
    else
    {
        a1 = a - fa / fap;
        b1 = b - fb * (b - a) / (fb - fa);
    }
    if ((b1 - a1) > eps1)
    {
        return root(f, g, fp, gp, fpp, gpp, a, b, eps1);
    }
    return a1;
}

int infelicity(double (*fp4)(double), double a, double b, double eps2)
{
    double n_real;
    int n;
    n_real = max(fabs(fp4(a)), fabs(fp4(b)));
    int k = 5;
    while (k > 0)
    {
        n_real *= (b - a);
        k--;
    }
    n_real /= 2880;
    n_real *= eps2;
    n = floor(sqrt(sqrt(n_real)));
    n = (n + 1) / 2 * 2; //n = 2k
    return n;
}

double integral(double (*f)(double), double (*fp4)(double), double a, double b, double eps2)
{
    int n;
    double h, sum_int = 0;
    n = infelicity(fp4, a, b, eps2);
    h = (b - a) / n;
    sum_int = f(a) + f(b);
    int i = 1;
    while (i < n)
    {
        sum_int += 2 * f(a + 2 * i * h) + 4 * f(a + 2 * i * h - 1);
        i++;
    }
    sum_int *= h / 3;
    return sum_int;
}



int main(void)
{
    double a, b, c, ans;
    double eps1 = 0.001, eps2 = 0.001;
    a = root (f1, f3, f1p, f3p, f1pp, f3pp, l, r, eps1);
    b = root (f2, f3, f2p, f3p, f2pp, f3pp, l, r, eps1);
    c = root (f1, f2, f1p, f2p, f1pp, f2pp, l, r, eps1);
    ans = integral(f1, f1p, a, c, eps2) - integral(f2, f2p4, b, c, eps2) - integral(f3, f3pp, a, b, eps2);
    printf("%lf", ans);
    return 0;
}
