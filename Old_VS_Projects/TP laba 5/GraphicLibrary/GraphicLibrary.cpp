#include "pch.h"
#include <utility>
#include <limits.h>
#include "GraphicLibrary.h"
#include <tchar.h>
#include <sstream>
#include <windowsx.h>
using namespace std;

float massive[12] = { 0 };
int unity = 0;
HFONT hf = NULL;
HMODULE hLib = NULL;

LRESULT CALLBACK ChildProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
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

        int (*pFunction)(float*, float&, float&, float&);                            // <----------------------------------------------
        (FARPROC&)pFunction = GetProcAddress(hLib, "NumofVar");
        unity = pFunction(massive, x1, x2, x3);
        FreeLibrary(hLib);

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
        break;
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
            20, 200,                                                // x, y position          
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
            hLib = LoadLibrary(L"MathLibrary");                            // <-------------------------
            if (NULL == hLib) {
                MessageBox(hWnd, L"Библиотека MathLibrary не найдена\nпопробуйте переустановить программу", L"Ошибка", MB_OK | MB_ICONEXCLAMATION);

            }
            else {
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
            }
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