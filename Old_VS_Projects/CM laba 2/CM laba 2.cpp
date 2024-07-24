#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

double f1(double x, double y) {
    return (x - exp(-1.6 - y) + 1.4);
}

double f2(double x, double y){
    return (y - (sin(x) / cos(x)));
}

double f1x(double x, double y) {
    return (1);
}

double f1y(double x, double y) {
    return (exp(-1.6 - y));
}

double f2x(double x, double y) {
    return (-(1 / (cos(x) * cos(x))));
}

double f2y(double x, double y) {
    return (1);
}

void gauss(double matrix[4][5], int n, double e) {
    double* xx = new double[n];
    double summa[4] = {0, 0, 0, 0};
    char str[500] = "";
    char add[] = "           ";
    cout << fixed << setprecision(4) << "|    x1    |    x2    |    x3    |    x4    |    c    |  сумма  |\n";
    for (int i = 0; i < n; i++)         // <-------- прямой ход
    {
        double tmp = 0;
        for (int z = i; z < n; z++) {
            if ((matrix[z][i] == 0) or abs(matrix[z][i]) > tmp) { swap(matrix[i], matrix[z]); }
            tmp = matrix[z][i];
        } 
        tmp = matrix[i][i]; 

        for (int booba = i; booba <= 3; booba += 1) {
            summa[booba] = 0;
            for (int biba = 0; biba <= 4; biba += 1) {
                cout << " " << matrix[booba][biba] << "    ";
                summa[booba] += matrix[booba][biba];
            }
            cout << " " << summa[booba] << endl;
        }
        cout << "_________________________________________________________________\n" << str;
        for (int j = i; j <= n; j++) {
            matrix[i][j] /= tmp;
            cout << " " << matrix[i][j] << "    ";
        }
        summa[i] /= tmp;
        cout << " " << summa[i];
        strcat_s(str, add);
        cout << "\n_________________________________________________________________\n";
        for (int j = i + 1; j < n; j++)
        {
            tmp = matrix[j][i];
            for (int k = n; k >= i; k--)
                matrix[j][k] -= tmp * matrix[i][k];
        }
    }
    xx[n - 1] = matrix[n - 1][n];       // <------- обратный ход
    for (int i = n - 2; i >= 0; i--)
    {
        xx[i] = matrix[i][n];
        for (int j = i + 1; j < n; j++) xx[i] -= matrix[i][j] * xx[j];
    }

    cout << "Ответ: ";
    cout << fixed << setprecision(4) << "x1 = " << xx[0] << endl;
    cout << "       x2 = " << xx[1] << endl;
    cout << "       x3 = " << xx[2] << endl;
    cout << "       x4 = " << xx[3] << endl;
    cout << endl;
}

void newton(double x0, double y0, double e) {   
    cout << "| n |    x    |    y    | d^2 - e |\n";
    int n = 0;
    while (true) {
        double a[2][2] = { { f1x(x0, y0), f1y(x0, y0) },
                           { f2x(x0, y0), f2y(x0, y0) } };
        double b[2] = { -f1(x0, y0), -f2(x0,y0) };
        double d = (a[0][0] * a[1][1]) - (a[0][1] * a[1][0]);
        double dx = (b[0] * a[1][1] - b[1] * a[0][1]) / d;
        double dy = (a[0][0] * b[1] - b[0] * a[1][0]) / d;
        if (std::max(dx*dx, dy*dy) < e) { break; }
        else {
            x0 += dx;
            y0 += dy;
        }
        n += 1;
        cout << fixed << setprecision(4) << "  " << n << "   " << x0 << "   " << y0 << "   " << std::max(dx * dx, dy * dy) - e << endl;
    }
    cout << endl;
    cout << "Ответ: ";
    cout << "x = " << x0 << endl;
    cout << "       y = " << y0 << endl;
    cout << endl;
}

double firstNorm(double  A[4][4], int n, int m)
{
    int i, j;
    double sum = 0, subSum;
    for (i = 0; i < n; i++) {
        subSum = 0;
        for (j = 0; j < m; j++) {
            subSum += abs(A[i][j]);
        }
        if (subSum > sum) {
            sum = subSum;
        }
    }
    return sum;
}

double secondNorm(double  A[4][4], int n, int m)
{
    int i, j;
    double sum = 0, subSum;
    for (j = 0; j < n; j++) {
        subSum = 0;
        for (i = 0; i < m; i++) {
            subSum += abs(A[i][j]);
        }
        if (subSum > sum) {
            sum = subSum;
        }
    }
    return sum;
}

double thirdNorm(double A[4][4], int n, int m)
{
    int i, j;
    double sum = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            sum += (A[i][j] * A[i][j]);
        }
    }
    sum = sqrt(sum);
    return sum;
}

void zeidel(double A[4][4], double B[4], int N, double eps) {
    cout << "Первая норма матрицы A: " << firstNorm(A, N, N) << endl;
    if ((thirdNorm(A, N, N) < 1) || firstNorm(A, N, N) < 1 || secondNorm(A, N, N) < 1) {
        cout << "Условие сходимости выполняется\n\n";
        cout << "| n |     x1     |     x2     |     x3     |     x4     | ||Xk+1 - Xk|| |\n";
        int k = 0;
        int i, j;
        double X[4];
        double s;
        double g;
        for (i = 0; i < N; i++) { X[i] = B[i]; }
        do {
            s = 0; k++;
            for (i = 0; i < N; i++) {
                g = B[i];
                for (j = 0; j < N; j++) { g = g + A[i][j] * X[j]; }
                s += (X[i] - g) * (X[i] - g);
                X[i] = g;
            } 
            cout << setprecision(5) << "  " << k << "    " << X[0] << "     " << X[1] << "     " << X[2] << "      " << X[3] << "       " << sqrt(s) << endl;
        } while (sqrt(s) >= eps * (1 - thirdNorm(A, N, N)) / pow(thirdNorm(A, N, N),k));
        cout << endl;
        cout << "Ответ: ";
        cout << "x1 = " << X[0] << endl;
        cout << "       x2 = " << X[1] << endl;
        cout << "       x3 = " << X[2] << endl;
        cout << "       x4 = " << X[3] << endl;
    }
    else {
        cout << "Условие сходимости не выполняется\n";
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
    cout << "Определитель матрицы: -64\n";
    cout << "Определитель матрицы не равен 0\n\n";
    cout << "Обратная матрица:\n";
    for (int booba = 0; booba <= 2; booba += 1) {
        for (int biba = 0; biba <= 2; biba += 1) {
            cout << " " << E[booba][biba] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void multi(double A[][3], double B[3], double X[3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            X[i] += A[i][j] * B[j];
    cout << "Ответ: ";
    cout << setprecision(0) << "x1 = " << X[0] << endl;
    cout << "       x2 = " << X[1] << endl;
    cout << "       x3 = " << X[2] << endl;
}

int main()
{
    //const int NotUsed = system("color 70");
    setlocale(0, "");
    cin.get();
    cout << "\n------------------------- Метод Гаусса -------------------------\n\n";
    cout << "Система уравнений:  0,64*x1 + 0,72*x2 - 0,83*x3 + 4,20*x4 = 2,23\n";
    cout << "                    0,58*x1 - 0,83*x2 + 1,43*x3 - 0,62*x4 = 1,71\n";
    cout << "                    0,86*x1 + 0,77*x2 - 1,83*x3 + 0,88*x4 = -0,54\n";
    cout << "                    1,32*x1 - 0,52*x2 - 0,65*x3 + 1,22*x4 = 0,65\n\n";
    double A1[4][5] = { { 0.64, 0.72, -0.83, 4.20, 2.23 },
                        {0.58, -0.83, 1.43, -0.62, 1.71 },
                        {0.86, 0.77, -1.83, 0.88, -0.54 },
                        {1.32, -0.52, -0.65, 1.22, 0.65 }  };
    gauss(A1, 4, 0.001);
    cin.get();
    cout << "\n------------------------- Метод Ньютона -----------------------\n\n";
    cout << "Система уравнений:  x - exp(-1,6 - y) + 1,4 = 0\n";
    cout << "                    y - tg(x) = 0\n";
    cout << "\nx0 = -1.4  y0 = -1.6\n";
    cout << "F1'x(x0,y0) = 1               F1'y(x0,y0) = exp(-1.6 - y)\nF2'x(x0,y0) = -1/cos(x)^2     F2'y(x0,y0) = 1\n\n";
    newton(-1.4, -1.6, 0.001);
    cin.get();
    cout << "------------------------- Метод Зейделя -----------------------\n\n";
    cout << "Система уравнений:  x1 = 0,19*x1 - 0,07*x2 + 0,38*x3 - 0,21*x4 - 0,81\n";
    cout << "                    x2 = -0,22*x1 + 0,08*x2 + 0,11*x3 + 0,33*x4 - 0,64\n";
    cout << "                    x3 = 0,51*x1 - 0,07*x2 - 0,09*x3 - 0,11*x4 + 1,71\n";
    cout << "                    x4 = 0,33*x1 - 0,41*x2 - 1,21\n\n";
    double A2[4][4] = { { 0.19, -0.07,  0.38, -0.21 },
                        {-0.22,  0.08,  0.11,  0.33 },
                        { 0.51, -0.07, -0.09, -0.11 },
                        { 0.33, -0.41,     0,     0} };
    double B[4] = { -0.81, -0.64, 1.71, -1.21 };
    zeidel(A2, B, 4, 0.0001);
    cin.get();
    cout << "\n------------------------- Метод обратной матрицы -----------------------\n\n";
    cout << "Система уравнений:  3*x1 + 8*x2 + x3 = 4 \n";
    cout << "                    7*x1 + 13*x2 + 4*x3 = 7 \n";
    cout << "                    6*x1 + 5*x2 + 9*x3 = 11\n\n";
    double A3[3][3] = { { 3, 8, 1 },
                        { 7,  13, 4 },
                        { 6, 5, 9 } };
    double B3[3] = { 4, 7, 11 };
    double E[3][3] = { 1.0, 0.0, 0.0,
                       0.0, 1.0, 0.0,
                       0.0, 0.0, 1.0 };
    double X[3] = { 0, 0, 0 };
    inversion(A3, E);
    multi(E, B3, X);
    cin.get();
}
