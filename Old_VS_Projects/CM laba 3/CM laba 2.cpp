#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

struct table
{
    double x;
    double y;
};

void lagrange(table tab[6], double x)
{
    double tmp[6][6];
    double D[6] = { 0, 0, 0, 0, 0, 0 };
    double Dy = 0, Sx = 0;
    for (int i = 0; i <= 5; i++)
        for (int j = 0; j <= 5; j++) {
           if (i != j) {
                tmp[i][j] = tab[i].x - tab[j].x;
           }
           if (i == j) {
                tmp[i][j] = x - tab[i].x;
           } 
        }
    cout << showpos << "                                                     |      D      |        y/D        |\n";
    Sx = tmp[1][1];
    for (int i = 0; i <= 5; i++) {
        D[i] = tmp[i][1];
        for (int j = 0; j <= 5; j++) {
            cout << " " << setprecision(3) << tmp[i][j] << " |";
            if ((i == j) && (i != 1)) {
                Sx = Sx * tmp[i][j];
            }
            if (j != 1) {
                D[i] = D[i] * tmp[i][j];
            }
        }
        Dy = Dy + tab[i].y / D[i];
        if ((i == 1) || (i == 2)) { cout << " " << setprecision(8) << D[i] << " |" << " " << tab[i].y / D[i] << " |\n"; }
        else { cout << " " << setprecision(8) << D[i] << " |" << " " << tab[i].y / D[i] << "  |\n"; }
    }
    cout << endl;
    cout << noshowpos << " y(" << setprecision(3) << x << ") = " << setprecision(6) << Sx * 1000000 << " * " << "10^-6" << " * " << Dy << " = " << Dy * Sx << "\n";
}

void newton(table tab[11], double x[4])
{
    cout << "| n |  x  |   y    |   dy    |   d^2y  |   d^3y  |   d^4y  |   d^5y  |   d^6y  |   d^7y  |   d^8y  |   d^9y  |   d^10y  |\n";
    double dy[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    double d2y[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    double d3y[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    double d4y[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    double d5y[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    double d6y[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    double d7y[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    double d8y[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    double d9y[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    double d10y[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    for (int i = 0; i <= 9; i++) { dy[i] = tab[i + 1].y - tab[i].y; }
    for (int i = 0; i <= 8; i++) { d2y[i] = dy[i + 1] - dy[i]; }
    for (int i = 0; i <= 7; i++) { d3y[i] = d2y[i + 1] - d2y[i]; }
    for (int i = 0; i <= 6; i++) { d4y[i] = d3y[i + 1] - d3y[i]; }
    for (int i = 0; i <= 5; i++) { d5y[i] = d4y[i + 1] - d4y[i]; }
    for (int i = 0; i <= 4; i++) { d6y[i] = d5y[i + 1] - d5y[i]; }
    for (int i = 0; i <= 3; i++) { d7y[i] = d6y[i + 1] - d6y[i]; }
    for (int i = 0; i <= 2; i++) { d8y[i] = d7y[i + 1] - d7y[i]; }
    for (int i = 0; i <= 1; i++) { d9y[i] = d8y[i + 1] - d8y[i]; }
    d10y[0] = d9y[1] - d9y[0];
    for (int i = 0; i <= 10; i++) {
        if (i != 10) { cout << noshowpos << "  " << setprecision(0) << i << "  " << setprecision(3) << tab[i].x << " " << setprecision(6) << tab[i].y << " " << setprecision(6) << showpos << dy[i] << " " << d2y[i] << " " << d3y[i] << " " << d4y[i] << " " << d5y[i] << " " << d6y[i] << " " << d7y[i] << " " << d8y[i] << " " << d9y[i] << " " << d10y[i] << " \n"; }
        else { cout << noshowpos << " " << setprecision(0) << i << "  " << setprecision(3) << tab[i].x << " " << setprecision(6) << tab[i].y << " " << setprecision(6) << showpos << dy[i] << " " << d2y[i] << " " << d3y[i] << " " << d4y[i] << " " << d5y[i] << " " << d6y[i] << " " << d7y[i] << " " << d8y[i] << " " << d9y[i] << " " << d10y[i] << " \n"; }
    }
    cout << endl;
    double res;
    for (int i = 0; i <= 3; i++) {
        if (x[i] < tab[5].x) {
            double q = (x[i] - tab[0].x) / (tab[1].x - tab[0].x);
            res = tab[0].y + q * dy[0] + ((q * (q - 1)) / 2) * d2y[0] + ((q * (q - 1) * (q - 2)) / 6) * d3y[0] + ((q * (q - 1) * (q - 2) * (q - 3)) / 24) * d4y[0] + ((q * (q - 1) * (q - 2) * (q - 3) * (q - 4)) / 120) * d5y[0] + ((q * (q - 1) * (q - 2) * (q - 3) * (q - 4) * (q - 5)) / 720) * d6y[0] + ((q * (q - 1) * (q - 2) * (q - 3) * (q - 4) * (q - 5) * (q - 6)) / 5040) * d7y[0]
                + ((q * (q - 1) * (q - 2) * (q - 3) * (q - 4) * (q - 5) * (q - 6) * (q - 7)) / 40320) * d8y[0] + ((q * (q - 1) * (q - 2) * (q - 3) * (q - 4) * (q - 5) * (q - 6) * (q - 7) * (q - 8)) / 362880) * d9y[0] + ((q * (q - 1) * (q - 2) * (q - 3) * (q - 4) * (q - 5) * (q - 6) * (q - 7) * (q - 8) * (q - 9)) / 3628800) * d10y[0];
            cout << noshowpos << " y(" << setprecision(3) << x[i] << ") = " << setprecision(6) << res <<"\n";
        }
        else {
            double q = (x[i] - tab[10].x) / (tab[1].x - tab[0].x);
            res = tab[10].y + q * dy[9] + ((q * (q - 1)) / 2) * d2y[8] + ((q * (q - 1) * (q - 2)) / 6) * d3y[7] + ((q * (q - 1) * (q - 2) * (q - 3)) / 24) * d4y[6] + ((q * (q - 1) * (q - 2) * (q - 3) * (q - 4)) / 120) * d5y[5] + ((q * (q - 1) * (q - 2) * (q - 3) * (q - 4) * (q - 5)) / 720) * d6y[4] + ((q * (q - 1) * (q - 2) * (q - 3) * (q - 4) * (q - 5) * (q - 6)) / 5040) * d7y[3]
                + ((q * (q - 1) * (q - 2) * (q - 3) * (q - 4) * (q - 5) * (q - 6) * (q - 7)) / 40320) * d8y[2] + ((q * (q - 1) * (q - 2) * (q - 3) * (q - 4) * (q - 5) * (q - 6) * (q - 7) * (q - 8)) / 362880) * d9y[1] + ((q * (q - 1) * (q - 2) * (q - 3) * (q - 4) * (q - 5) * (q - 6) * (q - 7) * (q - 8) * (q - 9)) / 3628800) * d10y[0];
            cout << noshowpos << " y(" << setprecision(3) << x[i] << ") = " << setprecision(6) << res << "\n";
        }
    }
}

void inversion(double A[][3], double E[][3])
{
    double temp;
    for (int k = 0; k < 3; k++) {
        temp = A[k][k];
        for (int j = 0; j < 3; j++) {
            A[k][j] /= temp;
            E[k][j] /= temp;
        }
        for (int i = k + 1; i < 3; i++) {
            temp = A[i][k];
            for (int j = 0; j < 3; j++) {
                A[i][j] -= A[k][j] * temp;
                E[i][j] -= E[k][j] * temp;
            }
        }
    }
    cout << endl;
    for (int k = 3 - 1; k > 0; k--) {
        for (int i = k - 1; i >= 0; i--) {
            temp = A[i][k];
            for (int j = 0; j < 3; j++) {
                A[i][j] -= A[k][j] * temp;
                E[i][j] -= E[k][j] * temp;
            }
        }
    }
    cout << endl;
}

void multi(double A[][3], double B[3], double X[3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            X[i] += A[i][j] * B[j];
    cout << "Полученная зависимость: " << setprecision(6) << X[0] << " * x^2 + " << X[1] << " * x + (" << X[2] << ")";
}

void kvadrat(table tab[10])
{
    cout << "Эмпирическая зависимость: y = ax^2 + bx + c\n";
    double x = 0, x2 = 0, x3 = 0, x4 = 0, n = 10, y = 0, xy = 0, x2y = 0;
    for (int i = 0; i <= 9; i++) {
        x = x + tab[i].x;
        x2 = x2 + tab[i].x * tab[i].x;
        x3 = x3 + tab[i].x * tab[i].x * tab[i].x;
        x4 = x4 + tab[i].x * tab[i].x * tab[i].x * tab[i].x;
        y = y + tab[i].y;
        xy = xy + tab[i].x * tab[i].y;
        x2y = x2y + tab[i].x * tab[i].y * tab[i].x;
    }
    cout << endl;
    cout << "Система уравнений: a * 54.7333 + b * 34.075 + c * 21.85 = 465.36\n" << "                   a * 34.075 + b * 21.85 + c * 14.5 = 282.6\n" << "                   a * 21.85 + b * 14.5 + c * 10 = 175\n";
    double A3[3][3] = { { 54.7333, 34.075, 21.85 },
                        { 34.075,  21.85, 14.5 },
                        { 21.85, 14.5, 10 } };
    double B3[3] = { 465.36, 282.6, 175 };
    double E[3][3] = { 1.0, 0.0, 0.0,
                       0.0, 1.0, 0.0,
                       0.0, 0.0, 1.0 };
    double X[3] = { 0, 0, 0 };
    inversion(A3, E);
    multi(E, B3, X);
}

int main()
{
    //const int NotUsed = system("color 70");
    setlocale(0, "");
    cout << "\n------------------------- Формула Лагранжа -------------------------\n\n";
    table lag[6];
    lag[0].x = 0.43;  lag[0].y = 1.63597;
    lag[1].x = 0.48;  lag[1].y = 1.73234;
    lag[2].x = 0.55;  lag[2].y = 1.87686;
    lag[3].x = 0.62;  lag[3].y = 2.03345;
    lag[4].x = 0.70;  lag[4].y = 2.22846;
    lag[5].x = 0.75;  lag[5].y = 2.83973;
    cout << "|     x     |     y     |\n";
    for (int i = 0; i <= 5; i++)
        cout << fixed << "    " << setprecision(2) << lag[i].x << "       " << setprecision(5) << lag[i].y << endl;
    lagrange(lag, 0.512);
    cin.get();
    cout << "\n------------------------- Формулы Ньютона -------------------------\n\n";
    table newt[11];
    newt[0].x = 1.415;  newt[0].y = 0.888551;
    newt[1].x = 1.420;  newt[1].y = 0.889599;
    newt[2].x = 1.425;  newt[2].y = 0.890637;
    newt[3].x = 1.430;  newt[3].y = 0.891667;
    newt[4].x = 1.435;  newt[4].y = 0.892687;
    newt[5].x = 1.440;  newt[5].y = 0.893698;
    newt[6].x = 1.445;  newt[6].y = 0.894700;
    newt[7].x = 1.450;  newt[7].y = 0.895693;
    newt[8].x = 1.455;  newt[8].y = 0.896677;
    newt[9].x = 1.460;  newt[9].y = 0.897653;
    newt[10].x = 1.465;  newt[10].y = 0.898619;
    cout << "|     x     |      y      |\n";
    for (int i = 0; i <= 10; i++)
        cout << fixed << "    " << setprecision(3) << newt[i].x << "       " << setprecision(6) << newt[i].y << endl;
    cout << endl;
    double XX[4] = { 1.4161, 1.4625, 1.4135, 1.4700 };
    newton(newt, XX);
    cin.get();
    cout << "\n------------------------- Метод наименьших квадратов -------------------------\n\n";
    table kvad[10];
    kvad[0].x = 1.0;  kvad[0].y = 0;
    kvad[1].x = 1.1;  kvad[1].y = 5;
    kvad[2].x = 1.2;  kvad[2].y = 9;
    kvad[3].x = 1.3;  kvad[3].y = 13;
    kvad[4].x = 1.4;  kvad[4].y = 17;
    kvad[5].x = 1.5;  kvad[5].y = 20;
    kvad[6].x = 1.6;  kvad[6].y = 24;
    kvad[7].x = 1.7;  kvad[7].y = 26;
    kvad[8].x = 1.8;  kvad[8].y = 29;
    kvad[9].x = 1.9;  kvad[9].y = 32;
    cout << "|    x    |   y    |\n";
    for (int i = 0; i <= 9; i++)
        cout << fixed << "    " << setprecision(1) << kvad[i].x << "       " << setprecision(0) << kvad[i].y << endl;
    cout << endl;
    kvadrat(kvad);
    cin.get();
}
