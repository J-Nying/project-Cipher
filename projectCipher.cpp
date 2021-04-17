#ifndef UNICODE
#define UNICODE
#endif 
#include <cstdio>
#include <iostream>
#include <windows.h>
#include "ciphers.h"
using namespace std;


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int createMyWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow){

    // Register the window class.
    const wchar_t CLASS_NAME[]  = L"Sample Window Class";

    WNDCLASS wc = { };
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    // Create the window.
    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"project Cipher by github.com/J-Nying Copyright (c) 2021 | 17-04-2021",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

HWND button1;
HWND button2;
HWND button3;
HWND button4;
HWND TextBox;
HWND key1;
HWND key2;
HWND key3;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    wchar_t msg[32];
    switch (uMsg)
    {
    case WM_CREATE:
        button1=CreateWindow(TEXT("BUTTON"), TEXT("Caesar cipher"), WS_VISIBLE | WS_CHILD, 70, 70, 200, 50, hwnd, (HMENU) 1, NULL, NULL);
        button2=CreateWindow(TEXT("BUTTON"), TEXT("Rail-Fence cipher"), WS_VISIBLE | WS_CHILD, 70, 170, 200, 50, hwnd, (HMENU) 2, NULL, NULL);
        button3=CreateWindow(TEXT("BUTTON"), TEXT("Simple Substitution cipher"), WS_VISIBLE | WS_CHILD, 70, 270, 200, 50, hwnd, (HMENU) 3, NULL, NULL);
        button4=CreateWindow(TEXT("BUTTON"), TEXT("Atbash cipher"), WS_VISIBLE | WS_CHILD, 70, 370, 200, 50, hwnd, (HMENU) 4, NULL, NULL);
        TextBox=CreateWindow(TEXT("EDIT"), TEXT("Enter plaintext to cipher here."), WS_BORDER | WS_CHILD | WS_VISIBLE, 500, 70, 500, 200, hwnd, NULL, NULL, NULL);
        key1=CreateWindow(TEXT("EDIT"), TEXT(""), WS_BORDER | WS_CHILD | WS_VISIBLE, 280, 70, 50, 50, hwnd, NULL, NULL, NULL);
        key2=CreateWindow(TEXT("EDIT"), TEXT(""), WS_BORDER | WS_CHILD | WS_VISIBLE, 280, 170, 50, 50, hwnd, NULL, NULL, NULL);
        key3=CreateWindow(TEXT("EDIT"), TEXT(""), WS_BORDER | WS_CHILD | WS_VISIBLE, 280, 285, 200, 20, hwnd, NULL, NULL, NULL);
        break;

    case WM_COMMAND:{
        int getWindowText = 0;
        char s[]={};
        int len = GetWindowTextLength(hwnd)+1;
        getWindowText = GetWindowTextA(TextBox, s, 2*len);
        string p;
        char ko[2];
        char substitutionKey[26];
        int k;
        switch (LOWORD(wParam))
        {
            case 1:{
                getWindowText = GetWindowTextA(key1, ko, 2);
                for(int i=0; i<2; i++){
                    p+=ko[i];
                }
                k = stoi(p);
                p=caesarCipher(s,k);
                CreateWindowA("STATIC", p.c_str(), WS_VISIBLE | WS_CHILD, 500, 300, 500, 170, hwnd, NULL, NULL, NULL);
                break;
            }
            case 2:
                getWindowText = GetWindowTextA(key2, ko, 2);
                for(int j=0; j<2; j++){
                    p+=ko[j];
                }
                k = stoi(p);
                p=railFenceCipher(s,k);
                CreateWindowA("STATIC", p.c_str(), WS_VISIBLE | WS_CHILD, 500, 300, 500, 170, hwnd, NULL, NULL, NULL);
                break;

            case 3:
                getWindowText = GetWindowTextA(key3, substitutionKey, 26);
                p=simpleSubstitutionCipher(s,substitutionKey);
                CreateWindowA("STATIC", p.c_str(), WS_VISIBLE | WS_CHILD, 500, 300, 500, 170, hwnd, NULL, NULL, NULL);
                break;
            case 4:
                getWindowText = GetWindowTextA(TextBox, s, 2*len);
                p=atbashCipher(s);
                CreateWindowA("STATIC", p.c_str(), WS_VISIBLE | WS_CHILD, 500, 300, 500, 170, hwnd, NULL, NULL, NULL);
                break;
        }
        break;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
            EndPaint(hwnd, &ps);
        }
        return 0;

    case WM_SYSKEYDOWN:
        swprintf_s(msg, L"WM_SYSKEYDOWN: 0x%x\n", wParam);
        OutputDebugString(msg);
        break;

    case WM_SYSCHAR:
        swprintf_s(msg, L"WM_SYSCHAR: %c\n", (wchar_t)wParam);
        OutputDebugString(msg);
        break;

    case WM_SYSKEYUP:
        swprintf_s(msg, L"WM_SYSKEYUP: 0x%x\n", wParam);
        OutputDebugString(msg);
        break;

    case WM_KEYDOWN:
        swprintf_s(msg, L"WM_KEYDOWN: 0x%x\n", wParam);
        OutputDebugString(msg);
        break;

    case WM_KEYUP:
        swprintf_s(msg, L"WM_KEYUP: 0x%x\n", wParam);
        OutputDebugString(msg);
        break;

    case WM_CHAR:
        swprintf_s(msg, L"WM_CHAR: %c\n", (wchar_t)wParam);
        OutputDebugString(msg);
        break;
    }
    
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}





int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    int returnThis = createMyWindow(hInstance, hPrevInstance, pCmdLine, nCmdShow);
    return returnThis;
}