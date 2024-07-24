#include <windows.h>
#include <tchar.h>
#include <windowsx.h>
#include <iostream>
#include <sstream>
#include <Wingdi.h>
using namespace std;

float massive[12] = { 0 };
int unity = 0;
HFONT hf = NULL;

bool Kramer(float a[12], float &x1, float& x2, float& x3) {
    float det = a[0] * a[4] * a[8] + a[1] * a[5] * a[6] + a[2] * a[3] * a[7] - a[2] * a[4] * a[6] - a[3] * a[1] * a[8] - a[0] * a[7] * a[5];
    if (det == 0) { 
        return false;
    }
    float det1 = a[9] * a[4] * a[8] + a[1] * a[5] * a[11] + a[10] * a[7] * a[2] - a[2] * a[4] * a[11] - a[10] * a[1] * a[8] - a[7] * a[5] * a[9];
    float det2 = a[0] * a[10] * a[8] + a[9] * a[5] * a[6] + a[3] * a[11] * a[2] - a[2] * a[10] * a[6] - a[3] * a[9] * a[8] - a[11] * a[5] * a[0];
    float det3 = a[0] * a[4] * a[11] + a[1] * a[10] * a[6] + a[3] * a[7] * a[9] - a[9] * a[4] * a[6] - a[3] * a[1] * a[11] - a[0] * a[7] * a[10];
    x1 = det1 / det;
    x2 = det2 / det;
    x3 = det3 / det;
    return true;
}

extern "C" bool Kramer(float* a, float& x1, float& x2);

bool Kramer(float a[2], float& x1) {
    if (a[0] == 0) {
        return false;
    }
    x1 = a[1] / a[0];
    return true;
}

int NumofVar(float matrix[12], float& xx1, float& xx2, float& xx3, HWND hWnd) {
    if (Kramer(matrix, xx1, xx2, xx3)) {
        return 300;
    }
    else {
        float arr[6];
        float ar[2];
        if (matrix[0] + matrix[3] + matrix[6] == 0) {

            if (matrix[1] + matrix[4] + matrix[7] == 0) {
                ar[0] = matrix[2]; ar[1] = matrix[9];
                if (Kramer(ar, xx3)) {
                    return 13;
                }
                else {
                    ar[0] = matrix[5]; ar[1] = matrix[10];
                    if (Kramer(ar, xx3)) {
                        return 13;
                    }
                    else {
                        ar[0] = matrix[8]; ar[1] = matrix[11];
                        if (Kramer(ar, xx3)) {
                            return 13;
                        }
                    }
                }
            }

            if (matrix[2] + matrix[5] + matrix[8] == 0) {
                ar[0] = matrix[1]; ar[1] = matrix[9];
                if (Kramer(ar, xx2)) {
                    return 12;
                }
                else {
                    ar[0] = matrix[4]; ar[1] = matrix[10];
                    if (Kramer(ar, xx2)) {
                        return 12;
                    }
                    else {
                        ar[0] = matrix[7]; ar[1] = matrix[11];
                        if (Kramer(ar, xx2)) {
                            return 12;
                        }
                    }
                }
            }

            arr[0] = matrix[1]; arr[1] = matrix[2]; arr[2] = matrix[9];
            arr[3] = matrix[4]; arr[4] = matrix[5]; arr[5] = matrix[10];

            if (Kramer(arr, xx2, xx3)) {
                return 223;
            }
            else {
                arr[3] = matrix[7]; arr[4] = matrix[8]; arr[5] = matrix[11];
                if (Kramer(arr, xx2, xx3)) {
                    return 223;
                }
                else {
                    arr[0] = matrix[4]; arr[1] = matrix[5]; arr[2] = matrix[10];
                    if (Kramer(arr, xx2, xx3)) {
                        return 223;
                    }
                }
            }
        }
        if (matrix[1] + matrix[4] + matrix[7] == 0) {

            if (matrix[0] + matrix[3] + matrix[6] == 0) {
                ar[0] = matrix[2]; ar[1] = matrix[9];
                if (Kramer(ar, xx3)) {
                    return 13;
                }
                else {
                    ar[0] = matrix[5]; ar[1] = matrix[10];
                    if (Kramer(ar, xx3)) {
                        return 13;
                    }
                    else {
                        ar[0] = matrix[8]; ar[1] = matrix[11];
                        if (Kramer(ar, xx3)) {
                            return 13;
                        }
                    }
                }
            }

            if (matrix[2] + matrix[5] + matrix[8] == 0) {
                ar[0] = matrix[0]; ar[1] = matrix[9];
                if (Kramer(ar, xx1)) {
                    return 11;
                }
                else {
                    ar[0] = matrix[3]; ar[1] = matrix[10];
                    if (Kramer(ar, xx1)) {
                        return 11;
                    }
                    else {
                        ar[0] = matrix[6]; ar[1] = matrix[11];
                        if (Kramer(ar, xx1)) {
                            return 11;
                        }
                    }
                }
            }

            arr[0] = matrix[0]; arr[1] = matrix[2]; arr[2] = matrix[9];
            arr[3] = matrix[3]; arr[4] = matrix[5]; arr[5] = matrix[10];
            if (Kramer(arr, xx1, xx3)) {
                return 213;
            }
            else {
                arr[3] = matrix[6]; arr[4] = matrix[8]; arr[5] = matrix[11];
                if (Kramer(arr, xx1, xx3)) {
                    return 213;
                }
                else {
                    arr[0] = matrix[3]; arr[1] = matrix[5]; arr[2] = matrix[10];
                    if (Kramer(arr, xx1, xx3)) {
                        return 213;
                    }
                }
            }
        }
        if (matrix[2] + matrix[5] + matrix[8] == 0) {
            if (matrix[1] + matrix[4] + matrix[7] == 0) {
                ar[0] = matrix[0]; ar[1] = matrix[9];
                if (Kramer(ar, xx1)) {
                    return 11;
                }
                else {
                    ar[0] = matrix[3]; ar[1] = matrix[10];
                    if (Kramer(ar, xx1)) {
                        return 11;
                    }
                    else {
                        ar[0] = matrix[6]; ar[1] = matrix[11];
                        if (Kramer(ar, xx1)) {
                            return 11;
                        }
                    }
                }
            }

            if (matrix[0] + matrix[3] + matrix[6] == 0) {
                ar[0] = matrix[1]; ar[1] = matrix[9];
                if (Kramer(ar, xx2)) {
                    return 12;
                }
                else {
                    ar[0] = matrix[4]; ar[1] = matrix[10];
                    if (Kramer(ar, xx2)) {
                        return 12;
                    }
                    else {
                        ar[0] = matrix[7]; ar[1] = matrix[11];
                        if (Kramer(ar, xx2)) {
                            return 12;
                        }
                    }
                }
            }

            arr[0] = matrix[0]; arr[1] = matrix[1]; arr[2] = matrix[9];
            arr[3] = matrix[3]; arr[4] = matrix[4]; arr[5] = matrix[10];
            if (Kramer(arr, xx1, xx2)) {
                return 212;
            }
            else {
                arr[3] = matrix[6]; arr[4] = matrix[7]; arr[5] = matrix[11];
                if (Kramer(arr, xx1, xx2)) {
                    return 212;
                }
                else {
                    arr[0] = matrix[3]; arr[1] = matrix[4]; arr[2] = matrix[10];
                    if (Kramer(arr, xx1, xx2)) {
                        return 212;
                    }
                }
            }
        }
    }
    return 0;
}

LRESULT CALLBACK ChildProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HWND Button2 = NULL, Edit1 = NULL, Edit2 = NULL, Edit3 = NULL;
    HDC hdc;
    wostringstream wcharStream1, wcharStream2, wcharStream3;
    switch (message)
    {
    case WM_CREATE: {
        Button2 = CreateWindow(
            L"BUTTON",                                              // Predefined class; Unicode assumed 
            L"OK",                                                  // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            125, 200,                                               // x, y position          
            100, 35,                                                // Button width, height
            hWnd,                                                   // Parent window
            reinterpret_cast<HMENU>(2),
            NULL,
            NULL);
        Edit1 = CreateWindowW(L"EDIT", L"0", WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_READONLY, 135, 47, 70, 13, hWnd, reinterpret_cast<HMENU>(100), NULL, NULL);
        Edit2 = CreateWindowW(L"EDIT", L"0", WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_READONLY, 135, 100, 70, 13, hWnd, reinterpret_cast<HMENU>(101), NULL, NULL);
        Edit3 = CreateWindowW(L"EDIT", L"0", WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_READONLY, 135, 150, 70, 13, hWnd, reinterpret_cast<HMENU>(102), NULL, NULL);

        float x1 = 0, x2 = 0, x3 = 0;
        unity = NumofVar(massive, x1, x2, x3, hWnd);
        if ((massive[0] * x1 + massive[1] * x2 + massive[2] * x3 != massive[9]) ||
            (massive[3] * x1 + massive[4] * x2 + massive[5] * x3 != massive[10]) ||
            (massive[6] * x1 + massive[7] * x2 + massive[8] * x3 != massive[11])) {
            unity = 0;
        } 

        x1 = round(x1 * 100000) / 100000;
        x2 = round(x2 * 100000) / 100000;
        x3 = round(x3 * 100000) / 100000;
        if (abs(x1) < 0.000001) { x1 = 0; }
        if (abs(x2) < 0.000001) { x2 = 0; }
        if (abs(x3) < 0.000001) { x3 = 0; }

        wcharStream1 << x1;  // MessageBox(hWnd, wcharStream2.str().c_str(), wcharStream2.str().c_str(), MB_OKCANCEL | MB_ICONEXCLAMATION);    
        wcharStream2 << x2;
        wcharStream3 << x3;
        if (unity == 0) {
            Edit_SetText(GetDlgItem(hWnd, 100), L"");
            Edit_SetText(GetDlgItem(hWnd, 101), L"");
            Edit_SetText(GetDlgItem(hWnd, 102), L"");
            SendMessageW(hWnd, WM_PAINT, 0, 0);
        }
        if (unity == 11) {   
            Edit_SetText(GetDlgItem(hWnd, 100), wcharStream1.str().c_str());
            Edit_SetText(GetDlgItem(hWnd, 101), L"");
            Edit_SetText(GetDlgItem(hWnd, 102), L"");
        }
        if (unity == 12) {
            Edit_SetText(GetDlgItem(hWnd, 100), L"");
            Edit_SetText(GetDlgItem(hWnd, 101), wcharStream2.str().c_str());
            Edit_SetText(GetDlgItem(hWnd, 102), L"");
        }
        if (unity == 13) {
            Edit_SetText(GetDlgItem(hWnd, 100), L"");
            Edit_SetText(GetDlgItem(hWnd, 101), L"");
            Edit_SetText(GetDlgItem(hWnd, 102), wcharStream3.str().c_str());
        }
        if (unity == 212) {
            Edit_SetText(GetDlgItem(hWnd, 100), wcharStream1.str().c_str());
            Edit_SetText(GetDlgItem(hWnd, 101), wcharStream2.str().c_str());
            Edit_SetText(GetDlgItem(hWnd, 102), L"");
        }
        if (unity == 213) {
            Edit_SetText(GetDlgItem(hWnd, 100), wcharStream1.str().c_str());
            Edit_SetText(GetDlgItem(hWnd, 101), L"");
            Edit_SetText(GetDlgItem(hWnd, 102), wcharStream3.str().c_str());
        }
        if (unity == 223) {
            Edit_SetText(GetDlgItem(hWnd, 100), L"");
            Edit_SetText(GetDlgItem(hWnd, 101), wcharStream2.str().c_str());
            Edit_SetText(GetDlgItem(hWnd, 102), wcharStream3.str().c_str());
        }
        if (unity == 300) {
            Edit_SetText(GetDlgItem(hWnd, 100), wcharStream1.str().c_str());
            Edit_SetText(GetDlgItem(hWnd, 101), wcharStream2.str().c_str());
            Edit_SetText(GetDlgItem(hWnd, 102), wcharStream3.str().c_str());
        }
    }
    case WM_COMMAND: {
        switch (LOWORD(wParam))
        {
        case 2: {
            DestroyWindow(hWnd);
        }
              break;
        }
        break;
    }
    case WM_PAINT: {   // Paint the main window
        hdc = BeginPaint(hWnd, &ps);
        SelectObject(hdc, hf);
        if (unity == 0) { TextOut(hdc, 15, 15, L"Система несовместна", _tcslen(L"Система несовместна")); }
        else { TextOut(hdc, 15, 15, L"Система совместна", _tcslen(L"Система совместна")); }
        TextOut(hdc, 115, 47, L"x1", _tcslen(L"a1"));
        TextOut(hdc, 115, 100, L"x2", _tcslen(L"a1"));
        TextOut(hdc, 115, 150, L"x3", _tcslen(L"a1"));
        SetBkMode(hdc, TRANSPARENT);
        if (massive[0] + massive[1] + massive[2] != 0) {
            TextOut(hdc, 15, 47, L"D = R,E = R", _tcslen(L"D = R,E = R"));
        }
        else {
            TextOut(hdc, 15, 47, L"D = { },E = { }", _tcslen(L"D = { },E = { }"));
        }
        if (massive[3] + massive[4] + massive[5] != 0) {
            TextOut(hdc, 15, 100, L"D = R,E = R", _tcslen(L"D = R,E = R"));
        }
        else {
            TextOut(hdc, 15, 100, L"D = { },E = { }", _tcslen(L"D = { },E = { }"));
        }
        if (massive[6] + massive[7] + massive[8] != 0) {
            TextOut(hdc, 15, 150, L"D = R,E = R", _tcslen(L"D = R,E = R"));
        }
        else {
            TextOut(hdc, 15, 150, L"D = { },E = { }", _tcslen(L"D = { },E = { }"));
        }
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DESTROY: {  // post a quit message and return
        PostQuitMessage(EXIT_SUCCESS);
        break;
    }
    default: {
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    }
    return 0;
};

HWND CreateChild(const wchar_t clas[], const wchar_t title[], HWND parent) {
    WNDCLASSEX wchild;
    wchild.cbSize = sizeof(WNDCLASSEX);
    wchild.cbClsExtra = 0;
    wchild.cbWndExtra = 0;
    wchild.hbrBackground = (HBRUSH)(COLOR_WINDOW - 1);
    wchild.style = CS_HREDRAW | CS_VREDRAW;
    wchild.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wchild.hCursor = LoadCursor(NULL, IDC_ARROW);
    wchild.lpszMenuName = NULL;
    wchild.lpszClassName = clas;
    wchild.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wchild.lpfnWndProc = ChildProc;

    if (!RegisterClassEx(&wchild))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);
        return (NULL);
    }

    HWND child = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,        
        clas,                          
        title,                    
        WS_CAPTION | WS_SYSMENU,      
        455, 50,  
        255, 300,                      
        parent,                         
        NULL,                       
        NULL,                 
        NULL); 

    if (!child) {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);
        return (NULL);
    }
    else {
        ShowWindow(child, SW_SHOWDEFAULT); 
        UpdateWindow(child);

        MSG ms;
        while (GetMessage(&ms, NULL, 0, 0)) {
            TranslateMessage(&ms);
            DispatchMessage(&ms);
        }
        if (!UnregisterClassW(wchild.lpszClassName, NULL))
        {
            MessageBox(NULL,
                _T("Call to RegisterClassEx failed!"),
                _T("Windows Desktop Guided Tour"),
                NULL);
            return (NULL);
        }
        return (child);
    }

}

void EditCompletion(int editID, HWND ParentWindow) {
    int len = GetWindowTextLength(GetDlgItem(ParentWindow, editID)) + 1;
    TCHAR* buff = new TCHAR[len];
    len = GetWindowTextW(GetDlgItem(ParentWindow, editID), buff, len);
    buff[len] = 0;
    TCHAR c[2] = { buff[wcsspn(buff, L"0123456789.")],'\0' };
    if (c[0])                                                  // Если найдёт неверный сивол вернёт его
    {
        int l = wcscspn(buff, c);                              // Вернёт номер неверного символа в строке
        buff[l] = L'\0';                                       // удалить из строки всё что после этого символа
        Edit_SetText(GetDlgItem(ParentWindow, editID), buff);  // Вставить обратно в окно исправленый текст
        Edit_SetSel(GetDlgItem(ParentWindow, editID), l, l);   // Установить курсор в конец строки
        MessageBeep(0xFFFFFFFF);                               // Воспроизвести сигнал неверного ввода
    }
    if (buff[len - 1] == L'.') {
        for (int workj = len - 2; workj >= 0; --workj) {
            if (buff[workj] == L'.') {
                buff[len - 1] = L'\0';
                Edit_SetText(GetDlgItem(ParentWindow, editID), buff);
                Edit_SetSel(GetDlgItem(ParentWindow, editID), len - 1, len - 1);
                MessageBeep(0xFFFFFFFF);
                break;
            }
        }
    }
    if (((buff[0] == L'0') && (buff[1] != L'.') && (len > 1)) || (buff[0] == L'.')) {
        for (int workj = 0; workj <= len - 1; ++workj) {
            buff[workj] = buff[workj + 1];
        }
        Edit_SetText(GetDlgItem(ParentWindow, editID), buff);
        Edit_SetSel(GetDlgItem(ParentWindow, editID), 1, 1);
        MessageBeep(0xFFFFFFFF);
    }
    delete[] buff;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)  // Processes messages for the main window. MessageBox(hWnd, buff, TEXT("text"), MB_OKCANCEL | MB_ICONEXCLAMATION);
{
    HWND Button1 = NULL, Button2, ch1 = NULL, Edit[12]{ NULL };
    PAINTSTRUCT ps;
    HDC hdc;
    switch (message)
    {
    case WM_CREATE: {
            Button1 = CreateWindow(
            L"BUTTON",                                              // Predefined class; Unicode assumed 
            L"Результат",                                           // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            295, 200,                                               // x, y position          
            100, 35,                                                // Button width, height
            hWnd,                                                   // Parent window
            reinterpret_cast<HMENU>(1),     
            NULL,
            NULL);
            Button2 = CreateWindow(
                L"BUTTON",                                              // Predefined class; Unicode assumed 
                L"Выход",                                               // Button text 
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
                20, 200,                                               // x, y position          
                100, 35,                                                // Button width, height
                hWnd,                                                   // Parent window
                reinterpret_cast<HMENU>(2),
                NULL,
                NULL);
            Edit[0] = CreateWindowW(L"EDIT", L"0", WS_CHILD | WS_TABSTOP | WS_VISIBLE, 20, 50, 70, 13, hWnd, reinterpret_cast<HMENU>(100), NULL, NULL);
            Edit[1] = CreateWindowW(L"EDIT", L"0", WS_CHILD | WS_TABSTOP | WS_VISIBLE, 120, 50, 70, 13, hWnd, reinterpret_cast<HMENU>(101), NULL, NULL);
            Edit[2] = CreateWindowW(L"EDIT", L"0", WS_CHILD | WS_TABSTOP | WS_VISIBLE, 220, 50, 70, 13, hWnd, reinterpret_cast<HMENU>(102), NULL, NULL);
            Edit[3] = CreateWindowW(L"EDIT", L"0", WS_CHILD | WS_TABSTOP | WS_VISIBLE, 20, 100, 70, 13, hWnd, reinterpret_cast<HMENU>(103), NULL, NULL);
            Edit[4] = CreateWindowW(L"EDIT", L"0", WS_CHILD | WS_TABSTOP | WS_VISIBLE, 120, 100, 70, 13, hWnd, reinterpret_cast<HMENU>(104), NULL, NULL);
            Edit[5] = CreateWindowW(L"EDIT", L"0", WS_CHILD | WS_TABSTOP | WS_VISIBLE, 220, 100, 70, 13, hWnd, reinterpret_cast<HMENU>(105), NULL, NULL);
            Edit[6] = CreateWindowW(L"EDIT", L"0", WS_CHILD | WS_TABSTOP | WS_VISIBLE, 20, 150, 70, 13, hWnd, reinterpret_cast<HMENU>(106), NULL, NULL);
            Edit[7] = CreateWindowW(L"EDIT", L"0", WS_CHILD | WS_TABSTOP | WS_VISIBLE, 120, 150, 70, 13, hWnd, reinterpret_cast<HMENU>(107), NULL, NULL);
            Edit[8] = CreateWindowW(L"EDIT", L"0", WS_CHILD | WS_TABSTOP | WS_VISIBLE, 220, 150, 70, 13, hWnd, reinterpret_cast<HMENU>(108), NULL, NULL);
            Edit[9] = CreateWindowW(L"EDIT", L"0", WS_CHILD | WS_TABSTOP | WS_VISIBLE, 320, 50, 70, 13, hWnd, reinterpret_cast<HMENU>(109), NULL, NULL);
            Edit[10] = CreateWindowW(L"EDIT", L"0", WS_CHILD | WS_TABSTOP | WS_VISIBLE, 320, 100, 70, 13, hWnd, reinterpret_cast<HMENU>(110), NULL, NULL); 
            Edit[11] = CreateWindowW(L"EDIT", L"0", WS_CHILD | WS_TABSTOP | WS_VISIBLE, 320, 150, 70, 13, hWnd, reinterpret_cast<HMENU>(111), NULL, NULL);
            hf = CreateFont(17, 7, 0, 0, 700, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Hob-Arial"));
    }
    case WM_PAINT: {   // Paint the main window
        hdc = BeginPaint(hWnd, &ps);
        SetBkMode(hdc, TRANSPARENT);
        SelectObject(hdc, hf);
        TextOutW(hdc, 45, 30, L"a11", _tcslen(L"a13"));
        TextOutW(hdc, 145, 30, L"a12", _tcslen(L"a23"));
        TextOutW(hdc, 245, 30, L"a13", _tcslen(L"a33"));
        TextOutW(hdc, 45, 80, L"a21", _tcslen(L"a43"));
        TextOutW(hdc, 145, 80, L"a22", _tcslen(L"a53"));
        TextOutW(hdc, 245, 80, L"a23", _tcslen(L"a63"));
        TextOutW(hdc, 45, 130, L"a31", _tcslen(L"a73"));
        TextOutW(hdc, 145, 130, L"a32", _tcslen(L"a83"));
        TextOutW(hdc, 245, 130, L"a33", _tcslen(L"a93"));
        TextOutW(hdc, 345, 30, L"b1", _tcslen(L"b1"));
        TextOutW(hdc, 345, 80, L"b2", _tcslen(L"b2"));
        TextOutW(hdc, 345, 130, L"b3", _tcslen(L"b3"));
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_COMMAND: {  
        switch (LOWORD(wParam))
        {
            case 1: {
                EnableWindow(GetDlgItem(hWnd, 1), false);
                for (int worki = 0; worki < 12; ++worki) {
                     int len = GetWindowTextLength(GetDlgItem(hWnd, 100 + worki)) + 1;
                     TCHAR* buff = new TCHAR[len];
                     len = GetWindowTextW(GetDlgItem(hWnd, 100 + worki), buff, len);
                     buff[len] = 0;
                     massive[worki] = wcstof(buff, NULL);
                     delete[] buff;
                     EnableWindow(GetDlgItem(hWnd, 100 + worki), false);
                }
                ch1 = CreateChild(L"chld1", L"Результат", hWnd);
                if (ch1 == NULL) { return 0; }
                EnableWindow(GetDlgItem(hWnd, 1), true);
                for (int worki = 0; worki < 12; ++worki) { EnableWindow(GetDlgItem(hWnd, 100 + worki), true); }
                break;
            }
            case 2: {
                DestroyWindow(hWnd);
                break;
            }
        }
        if (HIWORD(wParam) == EN_CHANGE) {
            switch (LOWORD(wParam))
            {
                case 100: {
                    EditCompletion(100, hWnd);
                    break;
                }
                case 101: {
                    EditCompletion(101, hWnd);
                    break;
                }
                case 102: {
                    EditCompletion(102, hWnd);
                    break;
                }
                case 103: {
                    EditCompletion(103, hWnd);
                    break;
                }
                case 104: {
                    EditCompletion(104, hWnd);
                    break;
                }
                case 105: {
                    EditCompletion(105, hWnd);
                    break;
                }
                case 106: {
                    EditCompletion(106, hWnd);
                    break;
                }
                case 107: {
                    EditCompletion(107, hWnd);
                    break;
                }
                case 108: {
                    EditCompletion(108, hWnd);
                    break;
                }
                case 109: {
                    EditCompletion(109, hWnd);
                    break;
                }
                case 110: {
                    EditCompletion(110, hWnd);
                    break;
                }
                case 111: {
                    EditCompletion(111, hWnd);
                    break;
                }
            }
        }
        break;
    }
    case WM_DESTROY: {  // post a quit message and return
        PostQuitMessage(EXIT_SUCCESS);
        break;
    }
    default: {
        return DefWindowProc(hWnd, message, wParam, lParam);
        break; 
    }
    }
    return 0;
}

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow)
{
    WNDCLASSEX wmain;
    wmain.cbSize = sizeof(WNDCLASSEX);
    wmain.style = CS_HREDRAW | CS_VREDRAW;
    wmain.lpfnWndProc = WndProc;
    wmain.cbClsExtra = 0;
    wmain.cbWndExtra = 0;
    wmain.hInstance = hInstance;
    wmain.hIcon = LoadIcon(wmain.hInstance, IDI_APPLICATION);
    wmain.hCursor = LoadCursor(NULL, IDC_ARROW);
    wmain.hbrBackground = (HBRUSH)(COLOR_WINDOW - 1);
    wmain.lpszMenuName = NULL;
    wmain.lpszClassName = L"window1";
    wmain.hIconSm = LoadIcon(wmain.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wmain))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);
        return 1;
    }

    //hInst = hInstance; Store instance handle in our global variable

    HWND win1 = CreateWindowEx(          
        WS_EX_OVERLAPPEDWINDOW,                   // WS_EX_OVERLAPPEDWINDOW : An optional extended window style.
        L"window1",                               // the name of the application
        L"Окно 1",                                // the text that appears in the title bar
        WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, // WS_OVERLAPPEDWINDOW: the type of window to create WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX
        50, 50,                                   // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
        425, 300,                                 // initial size (length, width)
        NULL,                                     // NULL: the parent of this window
        NULL,                                     // NULL: this application does not have a menu bar
        hInstance,                                // hInstance: the first parameter from WinMain
        NULL);                                    // NULL: not used in this application
    
    if (!win1) {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);
        return 1;
    }

    ShowWindow(win1, nCmdShow);  // win1: the value returned from CreateWindow, nCmdShow: the fourth parameter from WinMain
    UpdateWindow(win1);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}