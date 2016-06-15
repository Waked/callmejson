/**
 *  Created by Kamil Dzierzanowski and
 *  published under GNU GPL v.3.0 license.
 *
 *  Claiming authorship to this project
 *  is forbidden for the duration of
 *  the course it is made for.
 **/

#include <windows.h>
#include "include/Engine.hpp"

using namespace std;

char classname[] = "Nazwa klasy";
static HWND shLabel_First, shLabel_Second, shLabel_Third, shLabel_Fourth;
HWND hText_InputPath;
HWND hCombo_Type;
HWND hText_OutputPath;
HWND hButton_Convert;

HFONT hNormalFont = (HFONT) GetStockObject(DEFAULT_GUI_FONT);

LRESULT CALLBACK WndProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam){
    switch (Msg){
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_COMMAND:
        if ((HWND)lParam == hButton_Convert){
            Engine silnik;
            char inpath[256], outpath[256];
            GetWindowText(hText_InputPath, inpath, 256);
            GetWindowText(hText_OutputPath, outpath, 256);
            int index = SendMessage((HWND) lParam, WM_SETTEXT, (WPARAM) 0, (LPARAM) 0);
            silnik.getconvtype(index);
            silnik.readfile(string(inpath));
            silnik.writefile(string(outpath));
        }
        break;
    default:
        return DefWindowProc(hwnd, Msg, wParam, lParam);
    }
    return 0;
}

bool RegisterWndClass(HINSTANCE hinstance){
    WNDCLASSEX wcx;
    wcx.cbSize          = sizeof(WNDCLASSEX);
    wcx.style           = CS_HREDRAW | CS_VREDRAW;
    wcx.lpfnWndProc     = WndProc;
    wcx.cbClsExtra      = 0;
    wcx.cbWndExtra      = 0;
    wcx.hInstance       = hinstance;
    wcx.hIcon           = LoadIcon(NULL, IDI_APPLICATION);
    wcx.hCursor         = LoadCursor(NULL, IDC_ARROW);
    wcx.hbrBackground   = (HBRUSH)GetSysColorBrush(COLOR_MENU);
    wcx.lpszMenuName    = "Glowne Menu";
    wcx.lpszClassName   = classname;
    wcx.hIconSm         = LoadIcon( NULL, IDI_APPLICATION );

    return RegisterClassEx(&wcx);
}

bool CreateAndShowMainWindow(HINSTANCE hInstance, int nCmdShow){
    HWND hwnd;
    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, classname, "callmejson - Konwerter JSON/XML", WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME, CW_USEDEFAULT, CW_USEDEFAULT, 360, 310, NULL, NULL, hInstance, NULL);

    shLabel_First = CreateWindowEx(WS_EX_STATICEDGE, "static", "SHLABEL_FIRST", WS_CHILD | WS_VISIBLE | SS_LEFT, 10, 10, 90, 20, hwnd, NULL, hInstance, NULL);
    SetWindowText(shLabel_First, "Œcie¿ka wejœcia");
    SendMessage( shLabel_First, WM_SETFONT,( WPARAM ) hNormalFont, 0 );

    hText_InputPath = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 40, 320, 22, hwnd, NULL, hInstance, NULL );
    SendMessage( hText_InputPath, WM_SETFONT,( WPARAM ) hNormalFont, 0 );

    shLabel_Second = CreateWindowEx(WS_EX_STATICEDGE, "static", "SHLABEL_SECOND", WS_CHILD | WS_VISIBLE | SS_LEFT, 10, 70, 90, 20, hwnd, NULL, hInstance, NULL);
    SetWindowText(shLabel_Second, "Format docelowy");
    SendMessage( shLabel_Second, WM_SETFONT,( WPARAM ) hNormalFont, 0 );

    hCombo_Type = CreateWindowEx( WS_EX_CLIENTEDGE, "COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |  CBS_DROPDOWNLIST, 10, 100, 150, 200, hwnd, NULL, hInstance, NULL );
    SendMessage( hCombo_Type, WM_SETFONT,( WPARAM ) hNormalFont, 0 );
    SendMessage(hCombo_Type,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) "JSON");
    SendMessage(hCombo_Type,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) "XML");
    SendMessage(hCombo_Type, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);

    shLabel_Third = CreateWindowEx(WS_EX_STATICEDGE, "static", "SHLABEL_THIRD", WS_CHILD | WS_VISIBLE | SS_LEFT, 10, 130, 90, 20, hwnd, NULL, hInstance, NULL);
    SetWindowText(shLabel_Third, "Œcie¿ka wyjœcia");
    SendMessage( shLabel_Third, WM_SETFONT,( WPARAM ) hNormalFont, 0 );

    hText_OutputPath = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 160, 320, 22, hwnd, NULL, hInstance, NULL );
    SendMessage( hText_OutputPath, WM_SETFONT,( WPARAM ) hNormalFont, 0 );

    shLabel_Fourth = CreateWindowEx(WS_EX_STATICEDGE, "static", "SHLABEL_FOURTH", WS_CHILD | WS_VISIBLE | SS_CENTER, 10, 190, 340, 20, hwnd, NULL, hInstance, NULL);
    SetWindowText(shLabel_First, "");
    SendMessage( shLabel_Fourth, WM_SETFONT,( WPARAM ) hNormalFont, 0 );

    hButton_Convert = CreateWindowEx( 0, "BUTTON", "Generuj", WS_CHILD | WS_VISIBLE, 100, 220, 150, 30, hwnd, NULL, hInstance, NULL );
    SendMessage( hButton_Convert, WM_SETFONT,( WPARAM ) hNormalFont, 0 );

    if (hwnd == NULL)
        return false;
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    return true;
}

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    MSG msg;
    if (!RegisterWndClass(hInstance))
        return 1337;

    if (!CreateAndShowMainWindow(hInstance, nCmdShow))
        return 2137;

    while (GetMessage(&msg, (HWND)NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
