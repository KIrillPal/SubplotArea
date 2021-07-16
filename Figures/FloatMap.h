#include <SFML\Graphics.hpp>
#include <list>

typedef std::list<std::pair<double, double> > d_list;

const double SCREEN_L = -10, SCREEN_R = 10;

struct Function
{
    Function(double(*f)(double x), double(*d1)(double x), double(*d2)(double x)) : f(f), d1(d1), d2(d2) {}
    double(*f)(double x);
    double(*d1)(double x);
    double(*d2)(double x);
};

struct FP
{
    Function a, b;
    FP(Function a, Function b) : a(a), b(b) {}
    d_list localized;
    std::list<double> roots;
    double subt(double x)
    {
        return a.f(x) - b.f(x);
    }
    double sub_d1(double x)
    {
        return a.d1(x) - b.d1(x);
    }
    double sub_d2(double x)
    {
        return a.d2(x) - b.d2(x);
    }
};

bool isInArea(float x, float y);
double f1(double x);
double f2(double x);
double f3(double x);
double d11(double x);
double d12(double x);
double d13(double x);
double d21(double x);
double d22(double x);
double d23(double x);
double getArea(double eps);