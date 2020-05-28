#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define l -5.0
#define r -0.1
#define eps 1e-6

int cnt = 0;


extern double f1(double x);
extern double f2(double x);
extern double f3(double x);
extern double f1p(double x);
extern double f2p(double x);
extern double f3p(double x);
extern double f1pp(double x);
extern double f2pp(double x);
extern double f3pp(double x);

/*
double f1(double x)
{
    return exp(x) + 2;
}


double f2(double x)
{
    return -1/x;
}

double f3(double x)
{
    return -2.0 * (x + 1) / 3.0;
}

double f1p(double x)
{
    return exp(x);
}

double f2p(double x)
{
    return 1/x/x;
}

double f3p(double x)
{
    return -2/3;
}

double f1pp(double x)
{
    return f1p(x);
}

double f2pp(double x)
{
    return -2/x/x/x;
}

double f3pp(double x)
{
    return 0;
}


double f2p4(double x)
{
    return -24 /x/x/x/x/x;
}
*/


//функция сравнения строк
int cmp_str(char* s1, char* s2)
{
    int i = 0;
    while (s1[i] != 0 && s2[i] != 0)
    {
        if (s1[i] != s2[i])
        {
            return -1;
        }
        i++;
    }
    return 0;
}


//нахождение абсцисс пересечения 
double root(double (*f)(double), double (*g)(double), double (*fp)(double), double (*gp)(double), double (*fpp)(double), double (*gpp)(double), double a, double b, double eps1)
{
    cnt++;
    double a1, b1, fa, fb, fbp, fap;
    fa = f(a) - g(a);
    fb = f(b) - g(b);
    fbp = fp(b) - gp(b);
    fap = fp(a) - gp(a);
    if (fap * (fpp(a) - gpp(a)) > 0)
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
        return root(f, g, fp, gp, fpp, gpp, a1, b1, eps1);
    }
    return a1;
}


//подсчет интеграла
double integral(double (*f)(double), double a, double b, double eps2)
{
    int n;
    double h, sum_int = 0;
    n = (floor ((b-a)/eps2) + 1) / 2 * 2;
    h = (b - a) / n;
    sum_int = f(a) + f(b);
    int i = 1;
    while (i < n/2)
    {
        sum_int += 2 * f(a + 2 * i * h) + 4 * f(a + (2 * i - 1) * h);
        i++;
    }
    sum_int *= h / 3;
    return sum_int;
}



int main(int argc, char **argv)
{
    int test_mode = 0;
    char *help = "-help", **abs, **cnt_eq, *test = "-test";
    abs[0] = "-abs12";
    abs[1] = "-abs13";
    abs[2] = "-abs23";
    cnt_eq[0] = "-eq12";
    cnt_eq[1] = "-eq13";
    cnt_eq[2] = "-eq23";
    double a, b, c, ans = 0;
    double eps1 = 0.001, eps2 = 0.001;
    //printf ("deb");
    a = root (f1, f3, f1p, f3p, f1pp, f3pp, l, r, eps1);
    //printf ("Iterations needed to find intersection between f(x) = exp(x) + 2 and g(x) = -2 * (x + 1) / 3 :     %d.\n", cnt);
    cnt = 0;
    b = root (f2, f3, f2p, f3p, f2pp, f3pp, l, r, eps1);
    //printf ("Iterations needed to find intersection between f(x) = -1 / x and g(x) = -2 * (x + 1) / 3     :     %d.\n", cnt);
    cnt = 0;
    c = root (f1, f2, f1p, f2p, f1pp, f2pp, l, r, eps1);
    //printf ("Iterations needed to find intersection between f(x) = exp(x) + 2 and g(x) = -1 / x           :     %d.\n", cnt);
    ans = integral(f1, a, c, eps2) - integral(f2, b, c, eps2) - integral(f3, a, b, eps2);
    //printf("%lf", ans);
    for (int i = 1; i <= argc; i++)
    {
        if (cmp_str(argv[i], help) == 0)
        {
            printf("write '-absxy' to find abscissa of intersection between fx and fy. (x > y)\n");
            printf("write '-eqxy' to find number of iterations needed to find intersection between fx and fy. (x > y)\n");
            printf("write '-test' to enter testing mode\n");
        }
        if (cmp_str(argv[i], test) == 0)
        {
            test_mode = 1;
        }
       /* for (int j = 0; j < 3; j++)
        {
            if (cmp_str(argv[i], abs[j]) == 0)
            {
            }
        }*/
    }
    
    return 0;
}