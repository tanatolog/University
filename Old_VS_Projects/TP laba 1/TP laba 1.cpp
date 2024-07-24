#include <iostream>
#include <string>
#include <iomanip>
//#include <stdarg.h>
using namespace std;

void getvalue(int &a)
{
    while (true) {
        cin >> a;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n'); 
            cout << "Вы ввели некорректное значение, попробуйте еще раз\n";
            continue;
        }
        cin.ignore(32767, '\n');
        if (std::cin.gcount() > 1) {
            cout << "Вы ввели некорректное значение, попробуйте еще раз\n";
            continue; 
        }
        break;
    }
}

void getvalue(float &a)
{
    while (true) {
        cin >> a;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Вы ввели некорректное значение, попробуйте еще раз\n";
            continue;
        }
        cin.ignore(32767, '\n');
        if (std::cin.gcount() > 1) {
            cout << "Вы ввели некорректное значение, попробуйте еще раз\n";
            continue;
        }
        break;
    }
}

template <class U>
void output(U **array, const int row, const int col)  // Вывод элементов матрицы
{
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) { cout << array[i][j] << " "; }
        cout << endl;
    }
}

template <class T>
void input(T **&array, const int row, const int col, string s)
{
    array = new T *[row];
    cout << "Введите элементы " << s << " матрицы" << endl; // Ввод элементов матрицы
    for (int i = 0; i < row; i++) {
        array[i] = new T[col];
        for (int j = 0; j < col; j++) {
            cout << "a[" << i << "][" << j << "]= ";
            getvalue(array[i][j]);
        }
    }
    output(array, row, col);
}

template <class Y>
Y** multiplication(Y **arrA, Y **arrB, const int row, const int co1, const int co2)  // Умножение матриц
{
    Y **arrC = new Y *[row];
    for (int i = 0; i < row; i++)
    {
        arrC[i] = new Y[co2];
        for (int j = 0; j < co2; j++)
        {
            arrC[i][j] = 0;
            for (int k = 0; k < co1; k++) { arrC[i][j] += arrA[i][k] * arrB[k][j]; }
        }
    }
    cout << "Матрица произведения" << endl;
    output(arrC, row, co2);
    return;
}

int main()
{
    setlocale(0, "");
    int row1, row2, col1, col2;
    int **ai = NULL, **bi = NULL, **ci = NULL;
    float **af = NULL, **bf = NULL, **cf = NULL;
    bool type = 1;
    while (true) {
        string TYPE = "";
        row1 = 0; 
        row2 = 0; 
        col1 = 0; 
        col2 = 0;
        cout << "Введите тип элементов матриц или введите exit для выхода\n ";
        while ((TYPE != "int") && (TYPE != "float") && (TYPE != "exit")) {
            cin >> TYPE;
            if (TYPE == "int") { type = true; }
            else if (TYPE == "float") { type = false; }
            else if (TYPE == "exit") { return 0; }
            else { cout << "Вы ввели неверный тип\nВведите тип элементов матриц int или float или exit для выхода\n"; }
        }
        if (type == false) { cout << fixed << setprecision(4); }
        while ((col1 != row2) || ((col1 == 0) || (col2 == 0) || (row1 == 0) || (row2 == 0))) {
            cout << "Введите количество строк первой матрицы: ";
            getvalue(row1);
            cout << "Введите количество столбцов первой матрицы: ";
            getvalue(col1);
            cout << "Введите количество строк второй матрицы: ";
            getvalue(row2);
            cout << "Введите количество столбцов второй матрицы: ";
            getvalue(col2);
            if ((col1 != row2) || ((col1 == 0) || (col2 == 0) || (row1 == 0) || (row2 == 0))) { cout << "Умножение невозможно, введите данные еще раз\n"; }
        }

        if (type) {
            input(ai, row1, col1, "первой");
            input(bi, row2, col2, "второй");
            multiplication(ai, bi, row1, col1, col2);
        }
        else {
            cout << fixed << setprecision(4);
            input(af, row1, col1, "первой");
            input(bf, row2, col2, "второй");
            multiplication(af, bf, row1, col1, col2);
        }
        cout << "\nВычисление завешено\nНажмите любую клавишу\n";
        cin.get();
    }

}