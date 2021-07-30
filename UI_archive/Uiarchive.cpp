#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "ContextFile.h"
#include "ContextDiagram.h"
#include "SelectFile.h"
#include "DropFile.h"
#include "DiagramFile.h"
#include "DiagramArchive.h" 

#include <ArchiveFunction.h>

HWND hWnd1, hWnd2, hWnd3, hWnd4, hWnd5, file_butt, dir_butt, add_butt, select_archive, do_archive, select_file, draw_butt,
slct, drop, mode_butt, diagram1, diagram2;
int number, context_flag = 0;
string tmp_path;

static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle[] = _T("Libarchive UI");

unique_ptr<ContextFile> context_file(new ContextFile(new SelectFile));
unique_ptr<ContextDiagram> context_diagram(new ContextDiagram(new DiagramFile));

unique_ptr<ArchiveFactory> f1(new ArchiveFactory);
unique_ptr<IAbstractArchive> archive(f1->CreateProductA());


OPENFILENAME ofn;
HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK SubWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ThrWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK FourWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK FiveWndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_VREDRAW | CS_HREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    WNDCLASSEX subw;
    memset(&subw, 0, sizeof(subw));
    subw.cbSize = sizeof(WNDCLASSEX);
    subw.style = CS_HREDRAW | CS_VREDRAW;
    subw.lpfnWndProc = SubWndProc;
    subw.hInstance = hInstance;
    subw.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    subw.lpszClassName = L"Window2";

    WNDCLASSEX thrw;
    memset(&thrw, 0, sizeof(thrw));
    thrw.cbSize = sizeof(WNDCLASSEX);
    thrw.style = CS_HREDRAW | CS_VREDRAW;
    thrw.lpfnWndProc = ThrWndProc;
    thrw.hInstance = hInstance;
    thrw.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    thrw.lpszClassName = L"Window3";

    WNDCLASSEX four;
    memset(&four, 0, sizeof(four));
    four.cbSize = sizeof(WNDCLASSEX);
    four.style = CS_HREDRAW | CS_VREDRAW;
    four.lpfnWndProc = FourWndProc;
    four.hInstance = hInstance;
    four.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    four.lpszClassName = L"Window4";

    WNDCLASSEX five;
    memset(&five, 0, sizeof(five));
    five.cbSize = sizeof(WNDCLASSEX);
    five.style = CS_HREDRAW | CS_VREDRAW;
    five.lpfnWndProc = FiveWndProc;
    five.hInstance = hInstance;
    five.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    five.lpszClassName = L"Window5";

    if (!RegisterClassEx(&wcex)) {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    hInst = hInstance;

    hWnd1 = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW | WS_EX_ACCEPTFILES,
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        360, 200,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    file_butt = CreateWindow(L"button", L"Single file", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        15, 80, 100, 30, hWnd1, (HMENU)1, hInstance, NULL);
    SendMessage(file_butt, WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), true);

    dir_butt = CreateWindow(L"button", L"Directory", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        120, 80, 100, 30, hWnd1, (HMENU)2, hInstance, NULL);
    SendMessage(dir_butt, WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), true);

    add_butt = CreateWindow(L"button", L"Add file", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        225, 80, 100, 30, hWnd1, (HMENU)3, hInstance, NULL);
    SendMessage(add_butt, WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), true);

    mode_butt = CreateWindow(L"button", L"Mode", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        65, 115, 100, 30, hWnd1, (HMENU)10, hInstance, NULL);
    SendMessage(mode_butt, WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), true); 
    
    draw_butt = CreateWindow(L"button", L"Draw", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        175, 115, 100, 30, hWnd1, (HMENU)7, hInstance, NULL);
    SendMessage(draw_butt, WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), true);

    

    hWnd2 = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        0, 0,
        hWnd1,
        NULL,
        hInstance,
        NULL
    );

    hWnd3 = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        0, 0,
        hWnd1,
        NULL,
        hInstance,
        NULL
    );

    hWnd4 = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        0, 0,
        hWnd1,
        NULL,
        hInstance,
        NULL
    );

    hWnd5 = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        0, 0,
        hWnd1,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd1) {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    ShowWindow(hWnd1,
        nCmdShow);
    UpdateWindow(hWnd1);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR greeting[] = _T("Archive");
    HFONT hFont = CreateFont(15, 7, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, L"Times New Roman");

    RECT r;

    string global_path, global_archive, path, outname;
    wstring str;
    vector<string> argv;


    switch (message) {
    case WM_DROPFILES:
        if (context_flag == 1) context_file->dropLogic(wParam, hWnd, str, path, argv, outname);

        break;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 1:     // Single file
            if (context_flag == 0) context_file->dropLogic(wParam, hWnd, str, path, argv, outname);

            break;

        case 2:     // Directory
            archive->writeArchiveDirectory(str, path, argv, outname);

            break;

        case 3:     // Add file
            SetWindowPos(hWnd2, HWND_NOTOPMOST, 200, 200, 360, 180, NULL);
            EnableWindow(hWnd1, FALSE);
            ShowWindow(hWnd2, SW_SHOWNORMAL);
            UpdateWindow(hWnd2);

            select_file = CreateWindow(L"button", L"Select file", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                15, 80, 100, 30, hWnd2, (HMENU)4, hInst, NULL);
            SendMessage(select_file, WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), true);

            do_archive = CreateWindow(L"button", L"Add", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                120, 80, 100, 30, hWnd2, (HMENU)6, hInst, NULL);
            SendMessage(do_archive, WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), true);

            select_archive = CreateWindow(L"button", L"Select archive", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                225, 80, 100, 30, hWnd2, (HMENU)5, hInst, NULL);
            SendMessage(select_archive, WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), true);

            break;

        case 4:     // Add file::Select file
            archive->selectFile(hWnd, str);

            break;

        case 5:     // Add file::Select archive
            archive->selectArchive(hWnd, str);

            break;

        case 6:     // Add file::Add
            archive->addFileInArchive();

            break;

        case 7:     // Draw
            SetWindowPos(hWnd5, HWND_NOTOPMOST, 200, 200, 360, 180, NULL);
            EnableWindow(hWnd1, FALSE);
            ShowWindow(hWnd5, SW_SHOWNORMAL);
            UpdateWindow(hWnd5);

            diagram1 = CreateWindow(L"button", L"archive size", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                15, 80, 100, 30, hWnd5, (HMENU)11, hInst, NULL);
            SendMessage(diagram1, WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), true);

            diagram2 = CreateWindow(L"button", L"file size", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                225, 80, 100, 30, hWnd5, (HMENU)12, hInst, NULL);
            SendMessage(diagram2, WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), true);

            break;

        case 8:     // Mode::Select
            context_flag = 0;
            context_file->set_strategy(new SelectFile);
            EnableWindow(hWnd1, true);
            ShowWindow(hWnd4, SW_HIDE);

            break;

        case 9:     // Mode::Drop
            context_flag = 1;
            context_file->set_strategy(new DropFile);
            EnableWindow(hWnd1, true);
            ShowWindow(hWnd4, SW_HIDE);
            
            break;

        case 10:
            SetWindowPos(hWnd4, HWND_NOTOPMOST, 200, 200, 360, 180, NULL);
            EnableWindow(hWnd1, FALSE);
            ShowWindow(hWnd4, SW_SHOWNORMAL);
            UpdateWindow(hWnd4);

            slct = CreateWindow(L"button", L"select file", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                15, 80, 100, 30, hWnd4, (HMENU)8, hInst, NULL);
            SendMessage(slct, WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), true);

            drop = CreateWindow(L"button", L"drop file", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                225, 80, 100, 30, hWnd4, (HMENU)9, hInst, NULL);
            SendMessage(drop, WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), true);

            break;

        case 11:
            context_diagram->set_strategy(new DiagramArchive);
            context_diagram->setParameters(hWnd, str, global_archive, number, hWnd3, hWnd1);
            EnableWindow(hWnd1, true);
            ShowWindow(hWnd5, SW_HIDE);
            break;

        case 12:
            context_diagram->set_strategy(new DiagramFile);
            context_diagram->setParameters(hWnd, str, global_archive, number, hWnd3, hWnd1);
            EnableWindow(hWnd1, true);
            ShowWindow(hWnd5, SW_HIDE);
            break;
        }
        case WM_PAINT:
            hdc = BeginPaint(hWnd1, &ps);
            SelectObject(hdc,hFont);
            TextOut(hdc,
                150, 30,
                greeting, _tcslen(greeting));

            EndPaint(hWnd1, &ps);

            hdc = BeginPaint(hWnd2, &ps);
            SelectObject(hdc, hFont);
            TextOut(hdc,
                150, 30,
                greeting, _tcslen(greeting));

            EndPaint(hWnd2, &ps);

            context_diagram->draw(hdc, hWnd3, ps, r, hFont, number);

            hdc = BeginPaint(hWnd4, &ps);
            SelectObject(hdc, hFont);
            TextOut(hdc,
                150, 30,
                greeting, _tcslen(greeting));

            EndPaint(hWnd4, &ps);

            hdc = BeginPaint(hWnd5, &ps);
            SelectObject(hdc, hFont);
            TextOut(hdc,
                150, 30,
                greeting, _tcslen(greeting));

            EndPaint(hWnd5, &ps);

            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
            break;
    }

    return 0;
}

LRESULT CALLBACK SubWndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch (Message)
    {
    case WM_CLOSE:
        archive->close(hWnd2, hWnd1);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default: return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK ThrWndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch (Message)
    {
    case WM_CLOSE:
        archive->close(hWnd3, hWnd1);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default: return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK FourWndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch (Message)
    {
    case WM_CLOSE:
        archive->close(hWnd4, hWnd1);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default: return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK FiveWndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch (Message)
    {
    case WM_CLOSE:
        archive->close(hWnd5, hWnd1);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default: return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}