#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

double function(double x) {
    return (2 * x - log(x) - 7);
}

double derivation1(double x) {
    return (2 - (1 / x));
}

double derivation2(double x) {
    return (1 / (x * x));
}

double canonical(double x) {
    return (0.5 * log(x) + 3.5);
}

double canderv1(double x) {
    return (1 / (2 * x));
}

void clarification(double acc, double &left, double &right)
{
    while ((function(right) * function(left + acc) < 0) && (derivation1(left) * derivation1(right) > 0)) left += acc;
    while ((function(right - acc) * function(left) < 0) && (derivation1(left) * derivation1(right) > 0)) right -= acc;
}

bool CheckInterval(double left, double right) {
    double M = max(derivation2(left), derivation2(right));
    double m = min(derivation2(left), derivation2(right));
    return M <= 2 * m;
}

void combined(double a, double b, double e) {
    double xn, xi, h, t4 , t5;
    int n = 0;
    if (function(a) * derivation2(a) > 0) {
        cout << "Выбрана первая формула, неподвижна точка a\n\n";
        cout << "| n |    xk    |   f(xk)   |     h     |  xn - h  |\n";
        do {
            n += 1;
            xn = b;
            a = a - (function(a) / derivation1(a));
            t4 = (function(b) - function(a));
            t5 = (function(b) * (b - a));
            h = t5 / t4;
            b = b - h;
            xi = b;
            cout << "  " << n << "   " << xn << "   " << function(xn) << "     " << t4 << "     " << t5 << "     " << h << "   " << xi << endl;
        } while (abs(xi - xn) > e);
    }
    else if (function(b) * derivation2(b) > 0) {
        cout << "Выбрана вторая формула, неподвижна точка b\n\n";
        cout << "| n |    xk    |   f(xk)   |f(xk) - f(xn)|f(xk)(xk - xn)|     h     |  xn - h  |\n";
        do {
            n += 1;
            xn = a;
            t4 = (function(a) - function(b));
            t5 = (function(a) * (a - b));
            h = t5 / t4;   
            a = a - h;
            b = b - (function(b) / derivation1(b));
            xi = a;
            cout << "  " << n << "   " << xn << "   " << function(xn) << "     " << t4 << "     " << t5 << "     " << h << "   " << xi << endl;
        } while (abs(xi - xn) > e);
    }
}

void iterations(double a, double b, double e) {
    int n = 0;
    double xi, xn, q;
    xi = (a + b) / 2;
    if (canderv1(xi) < 0) {
        cout << "Сходимость двусторонняя, критерий останова: |Xn+1 − Xn| <= e\n\n";
        cout << "| n |    Xn    |   Xn+1   |   |Xn+1 − Xn|   |\n";
        do {
            n += 1;
            xn = xi;
            xi = canonical(xi);
            cout << "  " << n << "   " << xn << "   " << xi << "   " << (xi - xn) << endl;
        } while (abs(xi - xn) > e);
    }
    else if (canderv1(xi) > 0) {
        cout << "Сходимость односторонняя, критерий останова: |Xn+1 − Xn| <= (1 - q)e\n\n";
        q = max(canderv1(a), canderv1(b));
        cout << "| n |    Xn    |   Xn+1   | |Xn+1 - Xn| |\n";
        do {
            n += 1;
            xn = xi;
            xi = canonical(xi);
            cout << "  " << n << "   " << xn << "   " << xi << "   " << (xi - xn) << endl;
        } while (abs(xi - xn) > (1 - q) * e);
    }
}

int main()
{
    double a = 4.0;
    double b = 5.8;
    setlocale(0, "");
    cout << "\n------------ Комбинированный метод --------------\n";
    cout << "Уравнение: 2x - ln(x) - 7 = 0\n" << "Интервал изоляции: [" << a << "; " << b << "]\n" << "Первая производная: f'(x) = 2 - 1 / x\n" << R"(Вторая производная: f"(x) = 1 / x^2)";
    clarification(0.1, a, b);
    cout << "\nУточнение интервала изоляции: [" << a << "; " << b << "]\n";
    cout << "f(a) = " << function(a) << "   " << "f(b) = " << function(b) << "\n";
    cout << "f'(a) = " << derivation1(a) << "      " << "f'(b) = " << derivation1(b) << "\n";
    cout << R"(f"(a) = )" << derivation2(a) << "   " << R"(f"(b) = )" << derivation2(b) << "\n";
    cout << "Проверка условия M <= 2m: ";
    if (CheckInterval) cout << "Верно\n" << "критерий останова : |Xn+1 - Xn| <= e\n";
    else cout << "Неверно\n";
    cout << fixed << setprecision(6);
    combined(a, b, 0.00001);      //   a = a - ((b - a) / (function(b) - function(a)));
    cin.get();
    a = 4.0;
    b = 5.0;
    cout << "\n------------ Метод простых итераций -------------\n";
    cout << "Уравнение: 2x - ln(x) - 7 = 0\n" << "Интервал изоляции: [" << setprecision(0) << a << "; " << setprecision(1) << b << "]\n" << "Каноническое уравнение: x = 0.5 * ln(x) + 3.5\n" << R"(Производная канонической функции: phi'(x) = 1 / 2x)";
    cout << endl << setprecision(3) << R"(phi'(a) = )" << canderv1(a) << "   " << setprecision(1) << R"(phi'(b) = )" << canderv1(b) << setprecision(6) << endl;
    iterations(a, b, 0.00001);
    cin.get();
}
