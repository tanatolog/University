#include <windows.h>
#include <tchar.h>
#include <windowsx.h>
#include <iostream>
#include <sstream>
#include <Wingdi.h>
#include "GraphicLibrary.h"
using namespace std;

float massive[12] = { 0 };
int unity = 0;
HFONT hf = NULL;

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

    HWND win1 = CreateWindowEx(          
        WS_EX_OVERLAPPEDWINDOW,             
        L"window1",                              
        L"Окно 1",                                
        WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 
        50, 50,                                   
        425, 300,                              
        NULL,                                   
        NULL,                                 
        hInstance,                               
        NULL);                                    
    
    if (!win1) {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);
        return 1;
    }

    ShowWindow(win1, nCmdShow); 
    UpdateWindow(win1);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}