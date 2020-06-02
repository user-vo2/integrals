
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define l -5.0
#define r -0.1
#define BUF_SIZE 9

int cnt = 0;  // переменная для подсчета итераций в функции root

extern double f1(double x);
extern double f2(double x);
extern double f3(double x);
extern double f1p(double x);
extern double f2p(double x);
extern double f3p(double x);
extern double f1pp(double x);
extern double f2pp(double x);
extern double f3pp(double x);

double (*f_1)(double);
double (*f_2)(double);
double (*f_1p)(double);
double (*f_2p)(double);
double (*f_1pp)(double);
double (*f_2pp)(double);

//нахождение абсцисс пересечения v 2.0
double root(double (*f)(double), double (*g)(double), double (*fp)(double), double (*gp)(double), double (*fpp)(double), double (*gpp)(double), double a, double b, double eps1)
{
    cnt++;
    double a1 = a, b1 = b, fa, fb, fbp, fap;
    fa = f(a) - g(a);
    fb = f(b) - g(b);
    fbp = fp(b) - gp(b);
    fap = fp(a) - gp(a);
    if (fap * (fpp(a) - gpp(a)) > 0)
    {
        a1 = a - fa * (b - a) / (fb - fa);
        b1 = b - fb / fbp;
    }
    else if (fbp * (fpp(b) - gpp(b)) > 0)
    {
        a1 = a - fa / fap;
        b1 = b - fb * (b - a) / (fb - fa);
    }
    if (a > a1 || b < b1 || (f(a1) - g(a1)) * (f(b1) - g(b1)) > 0)
    {
        a1 = (a + b) / 2;
        b1 = b;
    }
    if (fabs(b1 - a1) > eps1)
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
    n = (floor ((b-a)/eps2) + 1) / 2;
    h = (b - a) / (2 * n);
    sum_int = f(a) + f(b);
    for(int i = 1; i < n; i++)
    {
        sum_int += 2 * f(a + 2 * i * h);
    }
    for(int i = 1; i <= n; i++)
    {
        sum_int += 4 * f(a + (2 * i - 1) * h);
    }
    sum_int *= h;
    sum_int /= 3;
    return sum_int;
}



int main(int argc, char **argv)
{
    
    char name[BUF_SIZE];
    int test_mode = 0;
    char *help = "-help", *test = "-test", *integr = "integral", *rt = "root", *qt = "quit", *command_integr = "-integral";
    char *abs[3];
    char *cnt_eq[3];
    abs[0] = "-abs12";
    abs[1] = "-abs13";
    abs[2] = "-abs23";
    cnt_eq[0] = "-eq12";
    cnt_eq[1] = "-eq13";
    cnt_eq[2] = "-eq23";
    double a, b, c, ans = 0;
    double eps1 = 0.01, eps2 = 0.001;
    a = root (f1, f3, f1p, f3p, f1pp, f3pp, l, r, eps1);
    printf("%lf %lf\n",a, f1(a));
    b = root (f2, f3, f2p, f3p, f2pp, f3pp, l, r, eps1);
    printf("%lf %lf\n",b, f2(b));
    c = root (f1, f2, f1p, f2p, f1pp, f2pp, l, r, eps1);
    printf("%lf %lf\n",c, f1(c));
    ans = integral(f1, a, c, eps2) - integral(f2, b, c, eps2) - integral(f3, a, b, eps2);
    printf("%lf\n", ans);
    for (int i = 1; i < argc; i++)
    {
        if (strncmp(argv[i], "-help" , 5) == 0)
        {
            printf("write '-absxy' to find abscissa of intersection between fx and fy. (x > y)\n");
            printf("write '-eqxy' to find number of iterations needed to find intersection between fx and fy. (x > y)\n");
            printf("write '-test' to enter testing mode\n");
            printf("write '-integral' to find integral with given values\n");
        }
        if (strncmp(argv[i], "-test", 5) == 0)
        {
            test_mode = 1;
        }
        if (strncmp(argv[i], abs[0], 6) == 0)
        {
            printf("%lf\n", c);
        }
        if (strncmp(argv[i], abs[1], 6) == 0)
        {
            printf("%lf\n", a);
        }
        if (strncmp(argv[i], abs[2], 6) == 0)
        {
            printf("%lf\n", b);
        }
        if (strncmp(argv[i], cnt_eq[0], 5) == 0)
        {
            cnt = 0;
            root (f1, f2, f1p, f2p, f1pp, f2pp, l, r, eps1);
            printf("%d\n", cnt);
        }
        if (strncmp(argv[i], cnt_eq[1], 5) == 0)
        {
            cnt = 0;
            root (f1, f3, f1p, f3p, f1pp, f3pp, l, r, eps1);
            printf("%d\n", cnt);
        }
        if (strncmp(argv[i], cnt_eq[2], 5) == 0)
        {
            cnt = 0;
            root (f2, f3, f2p, f3p, f2pp, f3pp, l, r, eps1);
            printf("%d\n", cnt);
        }
        if (strncmp(argv[i], command_integr, 9) == 0)
        {
            a = root (f1, f3, f1p, f3p, f1pp, f3pp, l, r, eps1);
            b = root (f2, f3, f2p, f3p, f2pp, f3pp, l, r, eps1);
            c = root (f1, f2, f1p, f2p, f1pp, f2pp, l, r, eps1);
            ans = integral(f1, a, c, eps2) - integral(f2, b, c, eps2) - integral(f3, a, b, eps2);
            printf("area between functions:   %lf\n", ans);
        }
    }
    while (test_mode)
    {
        printf("enter 'quit' to exit testing\n");
        printf("enter name of testing function or 'quit':  ");
        scanf("%8s", name);
        if(strncmp (name, rt, 4) == 0)
        {
            int num1, num2;
            double left, right;
            printf("enter numbers of tested functions, bounds and eps1 (num1 > num2)\n");
            scanf("%d%d%lf%lf%lf", &num1, &num2, &left, &right, &eps1);
            switch (num1)
            {
                case 1:
                    f_1 = &f1;
                    f_1p = &f1p;
                    f_1pp = &f1pp;
                    break;
                case 2:
                    f_1 = &f2;
                    f_1p = &f2p;
                    f_1pp = &f2pp;
                    break;
                default:
                    break;
            }
            switch (num2)
            {
                case 2:
                    f_2 = &f2;
                    f_2p = &f2p;
                    f_2pp = &f2pp;
                    break;
                case 3:
                    f_2 = &f3;
                    f_2p = &f3p;
                    f_2pp = &f3pp;
                    break;
                default:
                    break;
            }
            printf("%lf\n", root(f_1, f_2, f_1p, f_2p, f_1pp, f_2pp, left, right, eps1));
        }
        if(strncmp (name, integr, 8) == 0)
        {
            int num;
            double left, right;
            printf("enter number of tested function, bounds and eps2\n");
            scanf("%d%lf%lf%lf", &num, &left, &right, &eps2);
            switch (num)
            {
                case 1:
                    f_1 = &f1;
                    f_1p = &f1p;
                    f_1pp = &f1pp;
                    break;
                case 2:
                    f_1 = &f2;
                    f_1p = &f2p;
                    f_1pp = &f2pp;
                    break;
                case 3:
                    f_1 = &f3;
                    f_1p = &f3p;
                    f_1pp = &f3pp;
                    break;
                default:
                    break;
            }
            printf("%lf\n", integral(f_1, left, right, eps2));
        }
        if(strncmp (name, qt, 4) == 0)
        {
            break;
        }
    }
    return 0;
}