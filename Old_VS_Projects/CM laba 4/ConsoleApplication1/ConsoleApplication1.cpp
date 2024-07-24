#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

struct table
{
    double x;
    double y;
};

struct xA
{
    double x;
    double A;
};

void Error(double I, double R)
{
    cout << "|     I      |     d      |      s      |\n";
    double d = abs(I - R);
    double s = (d / R) * 100;
    cout << setprecision(8) << "  " << I << "   " << d << "   " << s << "%" << endl;
}

double SimpF(double x)
{
    return 1 / sqrt((x * x) - 1);
}

double TrapF(double x)
{
    return sin(x) / (x + 1);
}

double GaF(double x)
{
    return (x * x) / sqrt((x * x) + 4);
}

double Simpson()
{
    int n = 20;
    double h = 1.5 / n, k = 0, S = 0, I = 0;
    cout << "Возьмем сетку с шагом " << h << endl;
    table* tab = new table[n + 1];
    double* kf = new double[n + 1];
    cout << "\n| n |    x    |    y    | k |  kf(x)  |\n";
    for (int i = 0; i <= n; i++) {
        tab[i].x = 2 + (h * i);
        tab[i].y = SimpF(tab[i].x);
        if ((i == 0) || (i == n)) { k = 1; }
        else if ((i % 2) == 0) { k = 2; }
        else { k = 4; }
        kf[i] = tab[i].y * k;
        S += kf[i];
        cout << fixed << setprecision(0) << "  " << i << "   " << setprecision(5) << tab[i].x << "   " << tab[i].y << "   " << setprecision(0) << k << "   " << setprecision(5) << kf[i] << endl;
    }
    cout << "                               " << S << endl;
    I = (h / 3) * S;
    cout << "I = " << I << endl << endl;
    delete[] tab, kf;
    return I;
}

double Trapec(double h, bool o)
{
    double S = 0, I = 0;
    int n = 0;
    n = (int)round((double)(abs(0.18 - 0.98) / h));
    cout << "Возьмем сетку с шагом " << setprecision(5) << h << endl;
    table* tab = new table[n + 1];
    cout << "\n| n |    x1    |   f1(x)  |\n";
    for (int i = 0; i <= n; i++) {
        tab[i].x = 0.18 + (h * i);
        tab[i].y = TrapF(tab[i].x);
        cout << fixed << setprecision(0) << "  " << i << "   " << setprecision(5) << tab[i].x << "   " << tab[i].y << endl;
        if ((i == 0) || (i == n)) { S += tab[i].y / 2; }
        else S += tab[i].y;
    }
    cout << "                  " << S << endl;
    I = h * S;
    if (o == false) cout << "I1 = " << I << endl << endl;
    else cout << "I2 = " << I << endl << endl;
    delete[] tab;
    cin.get();
    return I;
}

double Runge()
{
    double I1 = 0, I2 = 0, I = 0, h = 0.01, d = 1;
    while (d >= 0.0001) {
        I1 = Trapec(h, false);
        I2 = Trapec(h / 2, true);
        d = abs(I1 - I2);
        if (d >= 0.0001) cout << "d >= e -> Повторяем расчет с шагом h/4\n";
        else cout << "d < e -> Конец вычислений I = I2\n";
        h = h / 4;
    }
    I = I2;
    cout << "I = " << I << endl << endl;
    return I;
}

double Gaus(int n, xA G[]) {
    double I = 0, S = 0, X = 0, a = -0.8, b = 1.4;
    table* tab = new table[n];
    cout << endl << setprecision(0) << n << " узлов:\n\n";
    cout << "| n |     x     |     A      |      X      |   Af(X)   |\n";
    for (int i = 0; i <= n - 1; i++) {
        X = a + (b - a) * G[i].x;
        I = G[i].A * GaF(X);
        S += I;
        cout << fixed << setprecision(0) << "  " << i << "   " << setprecision(8) << G[i].x << "  " << G[i].A << "   " << X  << "  " << I << endl;
    }
    I = (b - a) * S;
    cout << "                                            " << S << endl;
    return I;
}

double Gauss(xA G5[5], xA G8[8])
{
    double I1 = 0, I2 = 0;
    I1 = Gaus(5, G5);
    I2 = Gaus(8, G8);
    cout << "\nI5 = " << I1 << endl << endl;
    cout << "I8 = " << I2 << endl << endl;
    cout << "|I8 - I5| = " << abs(I1 - I2) << endl << endl;
    return I2;
}

double DifF(double x, double y)
{
    return x * y + y * y;
}

double Different(double h)
{
    double y = 0.6, dy = 0, x = 0, yh = 0, f1 = 0, xt = 0, f2 = 0;
    int n = (int)round((double)(abs(0 - 1) / h));
    cout << "Шаг равен: " << setprecision(2) << h << endl;
    cout << "| n |  x  |    y     |  x + h/2  |  f(x, y)  | y + h/2 * f(x, y)| f(x + h/2, y + h/2 * f(x,y))|    dy    |\n";
    for (int i = 0; i <= n; i++) {
        y += dy;
        x = h * i;
        yh = x + h / 2;
        f1 = DifF(x, y);
        xt = y + h / 2 * f1;
        f2 = DifF(yh, xt);
        dy = h * f2;
        if (i < 10) cout << fixed << setprecision(0) << "  " << i << "   " << setprecision(2) << x << setprecision(8) << "  " << y << "  " << yh << "  " << f1 << "     " << xt << "             " << f2 << "            " << dy << endl;
        else cout << fixed << setprecision(0) << " " << i << "   " << setprecision(2) << x << setprecision(8) << "  " << y << "  " << yh << "  " << f1 << "    " << xt << "             " << f2 << "           " << dy << endl;
    }
    return y;
}

void Differror()
{
    double d1, d2;
    d1 = Different(0.1);
    cout << endl;
    d2 = Different(0.1 / 2);
    cout << "\nПогрешность: " << setprecision(8) << abs(d1 - d2) / 3 << endl;
}

int main()
{
    const int NotUsed = system("color 70");
    setlocale(0, "");
    cout << "\n------------------------- Формула Симпсона -------------------------\n\n";
    cout << "Вычислить определённый интеграл от функции : 1 / sqrt(x^2 - 1) с точностью 0.0001\nПределы интегрирования: [2.0; 3.5]\n\n";
    Error(Simpson(), 0.607889);
    cin.get();
    cout << "\n------------------ Формула трапеций, правило Рунге -----------------\n\n";
    cout << "Вычислить определённый интеграл от функции : sin(x) / (x + 1) с точностью 0.0001\nПределы интегрирования: [0.18; 0.98]\n\n";
    Error(Runge(), 0.2613775);
    cin.get();
    cout << "\n-------------------- Квадратурная формула Гаусса -------------------\n\n";
    cout << "Вычислить определённый интеграл от функции : x^2 / sqrt(x^2 + 4)\nПределы интегрирования: [-0.8; 1.4]\n\n";
    xA G5[5];
 /* G5[0].x = -0.90618;   G5[0].A = 0.23698;
    G5[1].x = -0.538469;  G5[1].A = 0.47863;
    G5[2].x = 0;          G5[2].A = 0.56889;
    G5[3].x = -0.538469;  G5[3].A = 0.47863;
    G5[4].x = -0.90618;   G5[4].A = 0.23698;  */

    G5[0].x = 0.04691008;   G5[0].A = 0.11846344;
    G5[1].x = 0.23076534;   G5[1].A = 0.23931433;
    G5[2].x = 0.5;          G5[2].A = 0.28444444;
    G5[3].x = 0.76923466;   G5[3].A = 0.23931433;
    G5[4].x = 0.95308992;   G5[4].A = 0.11846344;

    xA G8[8];
    G8[0].x = 0.01985507;  G8[0].A = 0.05061427;
    G8[1].x = 0.10166676;  G8[1].A = 0.11119052;
    G8[2].x = 0.23723379;  G8[2].A = 0.15685332;
    G8[3].x = 0.40828268;  G8[3].A = 0.18134189;
    G8[4].x = 0.59171732;  G8[4].A = 0.18134189;
    G8[5].x = 0.76276621;  G8[5].A = 0.15685332;
    G8[6].x = 0.89833324;  G8[6].A = 0.11119052;
    G8[7].x = 0.98014493;  G8[7].A = 0.05061427;

 /* G8[0].x = -0.96028986;  G8[0].A = 0.10122854;
    G8[1].x = -0.79666648;  G8[1].A = 0.22238103;
    G8[2].x = -0.52553242;  G8[2].A = 0.31370664;
    G8[3].x = -0.18343464;  G8[3].A = 0.36268378;
    G8[4].x = -0.18343464;  G8[4].A = 0.36268378;
    G8[5].x = -0.52553242;  G8[5].A = 0.31370664;
    G8[6].x = -0.79666648;  G8[6].A = 0.22238103;
    G8[7].x = -0.96028986;  G8[7].A = 0.10122854;  */

    double I;
    Error(Gauss(G5, G8), 0.4851403);
    cin.get();
    cout << "\n-------------------- Усовершенствованный метод Эйлера 2-го порядка-------------------\n\n";
    cout << "Решить дифференциальное уравнение: y' = x * y + y^2\ny(0)=0.6; h=0.1; 0 <= x <= 1\n\n";
    Differror();
    cin.get();
}
