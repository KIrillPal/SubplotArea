#include "FloatMap.h"
#include <iostream>

double f1(double x)
{
    return 3 / ((x - 1) * (x - 1) + 1);
}

double f2(double x)
{
    return sqrt(x + 0.5);
}

double f3(double x)
{
    return exp(-x);
}
// 4.9212279617-0.39638-2.81625
//

double d11(double x)
{
    return 6 * (1 - x) / (((x - 1) * (x - 1) + 1) * ((x - 1) * (x - 1) + 1));
}

double d12(double x)
{
    return 1 / (2 * sqrt(x + 0.5));
}

double d13(double x)
{
    return -exp(-x);
}

double d21(double x)
{
    double t = x*x - 2 * x + 2;
    return (18 * (x - 1) * (x - 1) - 6) / (t*t*t);
}

double d22(double x)
{
    double t = x + 0.5;
    return -1 / (4 * sqrt(t*t*t));
}

double d23(double x)
{
    return exp(-x);
}
d_list localize(FP &fp, double left, double right, double rate)
{
    d_list res;
    double last_val = fp.subt(left);
    for (double x = left + rate; x < right; x += rate)
    {
        double val = fp.subt(x);
        if (last_val * val <= 0 && last_val != 0)
            res.push_back({ x - rate, x });
        last_val = val;
    }
    return res;
}

double find_root(FP &fp, double left, double right, double eps)
{
    while (right - left >= eps)
    {
        double fl = fp.subt(left), fr = fp.subt(right);
        if (fl * fp.sub_d2(left) < 0)
            left += (right - left) / (fl - fr)*fl;
        else
            left -= fl / fp.sub_d1(left);
        if (fr * fp.sub_d2(right) < 0)
            right += (left - right) / (fr - fl)*fr;
        else
            right -= fr / fp.sub_d1(right);
    }
    return (left + right) / 2;
}

std::list<double> real_roots(FP &fp, double eps)
{
    std::list<double> roots;
    for (auto lr : fp.localized)
    {
        if (fp.subt(lr.first) == 0) roots.push_back(lr.first);
        else if (fp.subt(lr.second) == 0) roots.push_back(lr.second);
        else roots.push_back(find_root(fp, lr.first, lr.second, eps));
    }
    return roots;
}

double area_between(double left, double right, double size)
{
    double mid = (left + right) / 2;
    double(*f)(double x) = f2;
    if (f(mid) < f3(mid)) f = f3;
    double area = (f1(left) - f1(right)) / 2, rate = (right - left) / size;
    for (double x = left + rate; x <= right; x += rate)
        area += f1(x);
    area += (f(right) - f(left)) / 2;
    rate = (right - left) / size;
    for (double x = left + rate; x <= right; x += rate)
        area -= f(x);
    return area * rate;
}

double make_area(std::list<double> roots, double eps)
{
    double area = 0;
    double left = *roots.begin();
    for (auto pr = next(roots.begin()); pr != roots.end(); ++pr)
    {
        double right = *pr, size = 64, last_s, s = 0;
        do
        {
            last_s = s;
            s = area_between(left, right, size), size *= 2;
        } while (abs(s - last_s) * 1 / 3 >= eps);
        area += s;
        left = right;
    }
    return area;
}

double getArea(double eps)
{
    Function af(f1, d11, d21), bf(f2, d12, d22), cf(f3, d13, d23);
    FP ab(af, bf);
    FP ac(af, cf);
    FP bc(bf, cf);
    ab.localized = localize(ab, SCREEN_L, SCREEN_R, 0.1);
    ac.localized = localize(ac, SCREEN_L, SCREEN_R, 0.1);
    bc.localized = localize(bc, SCREEN_L, SCREEN_R, 0.1);
    ab.roots = real_roots(ab, eps);
    ac.roots = real_roots(ac, eps);
    bc.roots = real_roots(bc, eps);
    printf("Roots found:\n");
    printf("A-B: ");
    for (auto l : ab.roots)
        std::cout << l << ' ';
    printf("\nA-C: ");
    for (auto l : ac.roots)
        std::cout << l << ' ';
    printf("\nB-C: ");
    for (auto l : bc.roots)
        std::cout << l << ' ';
    printf("\n");
    std::list<double> roots = ab.roots;
    roots.merge(ac.roots);
    roots.merge(bc.roots);
    roots.sort();
    return make_area(roots, eps / 20);
}

bool isInArea(float x, float y)
{
   // if (x < -0.5) return false;
    double y1 = f1(x);
    double y2 = f2(x);
    double y3 = f3(x);
    return (y < y1 && y > std::max(y2, y3) && y >= 0);
}