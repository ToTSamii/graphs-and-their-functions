#define UNICODE
#include "../headers/main_app_header.hpp"

//main

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hInst2, LPSTR param, int cmdMode) {
    WNDCLASS wc = { 0 };
    MSG msg = { 0 };
    HWND hwnd;
    hinst = hInst;

    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance = hInst;
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = L"MyClass";
    wc.lpszMenuName = NULL;
    wc.style = 0;

    if (!RegisterClass(&wc)) {
        MessageBox(0, L"Ошибка регистрации класса!", L"Ошибка!", MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindow(L"MyClass", L"y = x", WS_VISIBLE | WS_OVERLAPPEDWINDOW&~(WS_MAXIMIZEBOX) ^ WS_THICKFRAME, 50, 50, WIDTH, HEIGHT, 0, 0, 0, 0);

    if (!hwnd) {
        MessageBox(0, L"Ошибка создания окна!", L"Ошибка!", MB_ICONERROR);
        return 0;
    }

    ShowWindow(hwnd, cmdMode);

    while (GetMessage(&msg, 0, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {

    switch (msg) {
    case WM_COMMAND:

        switch(wp) {

        case button_graph_1:
            start = true;
            GetDlgItemTextA(hwnd, id_edit_1, argv_edit_1, sizeof(argv_edit_1));
            GetDlgItemTextA(hwnd, id_edit_2, argv_edit_2, sizeof(argv_edit_2));
            GetDlgItemTextA(hwnd, id_edit_3, argv_edit_3, sizeof(argv_edit_3));
            GetDlgItemTextA(hwnd, id_edit_4, argv_edit_4, sizeof(argv_edit_4));
            GetDlgItemTextA(hwnd, id_edit_min, argv_edit_min, sizeof(argv_edit_min));
            GetDlgItemTextA(hwnd, id_edit_max, argv_edit_max, sizeof(argv_edit_max));
            RedrawWindow(hwnd, 0, 0, RDW_INVALIDATE);
            break;
        case button_graph_2:
            start = false;
            InvalidateRect(hwnd, NULL, TRUE);
            UpdateWindow(hwnd);
            SetDlgItemTextA(hwnd, id_edit_1, "");
            SetDlgItemTextA(hwnd, id_edit_2, "");
            SetDlgItemTextA(hwnd, id_edit_3, "");
            SetDlgItemTextA(hwnd, id_edit_4, "");
            SetDlgItemTextA(hwnd, id_edit_min, "");
            SetDlgItemTextA(hwnd, id_edit_max, "");
            RedrawWindow(hwnd, 0, 0, RDW_INVALIDATE);
            break; 
        case menu_c_1:
            CaseGraph(hwnd, 3, dc);
            break;
        case menu_c_2:
            CaseGraph(hwnd, 4, dc);
            break;
        case menu_c_3:
            CaseGraph(hwnd, 5, dc);
            break;
        case menu_c_4:
            CaseGraph(hwnd, 6, dc);
            break;
        case menu_c_5:
            CaseGraph(hwnd, 7, dc);
            break;
        }

        break;

    case WM_CREATE:
        graph = 3;
        hpen1 = CreatePen(PS_SOLID, 2, RGB(0, 0, 10));
        hpen2 = CreatePen(PS_SOLID, 1, RGB(0, 0, 200));
        hpen3 = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
        hpen4 = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
        hpen5 = CreatePen(PS_SOLID, 2, RGB(240, 200, 108));
        hpen6 = CreatePen(PS_SOLID, 2, RGB(240, 24, 211));
        hpen7 = CreatePen(PS_SOLID, 2, RGB(133, 80, 240));
        font = CreateFont(10, 5, 0, 0, 15, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));
        CreateMyMenu(hwnd);
        break;

    case WM_PAINT: 
        dc = BeginPaint(hwnd, &ps);
        CreateWidgets(hwnd, dc);

        if (start) {
            Paint_Graphik(dc, hwnd);
            SetDlgItemTextA(hwnd, id_edit_1, argv_edit_1);
            SetDlgItemTextA(hwnd, id_edit_2, argv_edit_2);
            SetDlgItemTextA(hwnd, id_edit_3, argv_edit_3);
            SetDlgItemTextA(hwnd, id_edit_4, argv_edit_4);
            SetDlgItemTextA(hwnd, id_edit_min, argv_edit_min);
            SetDlgItemTextA(hwnd, id_edit_max, argv_edit_max);
            RedrawWindow(hwnd, 0, 0, RDW_INVALIDATE);
            start = false;
        } else {
            Paint_Cletka(dc);
            Paint_Start(dc);
        }

        EndPaint(hwnd, &ps);
        break;

    case WM_DESTROY:
        DeleteObject(hpen1);
        DeleteObject(hpen2);
        DeleteObject(hpen3);
        DeleteObject(hpen4);
        DeleteObject(hpen5);
        DeleteObject(hpen6);
        DeleteObject(hpen7);
        DeleteObject(font);
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hwnd, msg, wp, lp);
}

//------------------------------------------------------------------------------------------------


//interface

void CreateWidgets(HWND hwnd, HDC dc) {
    CreateInterfaceMain(hwnd);
    switch (graph) {
    case 3:
        CreateInterfaceLine(hwnd, dc);
        break;
    case 4:
        CreateInterfaceParabola(hwnd, dc);
        break;
    case 5:
        CreateInterfaceGiperbola(hwnd, dc);
        break;
    case 6:
        CreateInterfaceSin(hwnd, dc);
        break;
    case 7:
        CreateInterfaceCos(hwnd, dc);
        break;
    }
}


void CreateMyMenu(HWND hwnd) {
    menu_1 = CreateMenu();
    menu_popup_1 = CreatePopupMenu();
    AppendMenu(menu_1, MF_STRING | MF_POPUP, (UINT_PTR)menu_popup_1, L"Графики");
    AppendMenu(menu_popup_1, MF_STRING, menu_c_1, L"Прямая");
    AppendMenu(menu_popup_1, MF_STRING, menu_c_2, L"Парабола");
    AppendMenu(menu_popup_1, MF_STRING, menu_c_3, L"Гипербола");
    AppendMenu(menu_popup_1, MF_STRING, menu_c_4, L"Sin");
    AppendMenu(menu_popup_1, MF_STRING, menu_c_5, L"Cos");
    SetMenu(hwnd, menu_1);
    SetMenu(hwnd, menu_popup_1);
}


void DestroyInterface() {
    DestroyWindow(text_line_main_1);
    DestroyWindow(text_line_main_2);
    DestroyWindow(edit_line_min);
    DestroyWindow(edit_line_max);
    DestroyWindow(text_line_1);
    DestroyWindow(text_line_2);
    DestroyWindow(text_line_3);
    DestroyWindow(text_line_4);
    DestroyWindow(edit_line_1);
    DestroyWindow(edit_line_2);
    DestroyWindow(edit_line_3);
    DestroyWindow(edit_line_4);
    DestroyWindow(text_line_min);
    DestroyWindow(text_line_max);
}


void CreateInterfaceMain(HWND hwnd) {
    CreateWindow(L"button", L"Построить", WS_CHILDWINDOW | WS_VISIBLE | ES_CENTER, 710, 480, 80, 40, hwnd, (HMENU)button_graph_1, 0, 0);
    CreateWindow(L"button", L"Очистить", WS_CHILDWINDOW | WS_VISIBLE | ES_CENTER, 800, 480, 80, 40, hwnd, (HMENU)button_graph_2, 0, 0);
}


void CreateInterfaceLine(HWND hwnd, HDC dc) {
    SetBkColor(dc, RGB(240, 240, 240));
    DestroyInterface();
    edit_line_1 = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 710, 300, 70, 30, hwnd, (HMENU)id_edit_1, 0, 0);
    edit_line_2 = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 820, 300, 70, 30, hwnd, (HMENU)id_edit_2, 0, 0);
    edit_line_3 = CreateWindow(L"edit", L"", 0, 880, 400, 50, 30, hwnd, (HMENU)id_edit_3, 0, 0);
    text_line_1 = CreateWindow(L"edit", L"k:", WS_VISIBLE | WS_CHILD | ES_READONLY, 690, 300, 15, 30, hwnd, (HMENU)id_edit_text_1, 0, 0);
    text_line_2 = CreateWindow(L"edit", L"b:", WS_VISIBLE | WS_CHILD | ES_READONLY, 800, 300, 15, 30, hwnd, (HMENU)id_edit_text_2, 0, 0);
    text_line_3 = CreateWindow(L"edit", L"", 0, 870, 400, 15, 30, hwnd, (HMENU)id_edit_text_3, 0, 0);
    text_line_min = CreateWindow(L"edit", L"От X:", WS_VISIBLE | WS_CHILD | ES_READONLY, 674, 200, 35, 30, hwnd, (HMENU)id_edit_text_min, 0, 0);
    text_line_max = CreateWindow(L"edit", L"До X:", WS_VISIBLE | WS_CHILD | ES_READONLY, 782, 200, 36, 30, hwnd, (HMENU)id_edit_text_max, 0, 0);
    text_line_main_1 = CreateWindow(L"edit", L"График: Прямая", WS_VISIBLE | WS_CHILD | ES_READONLY, 750, 60, 200, 30, hwnd, (HMENU)id_edit_text_main, 0, 0);
    text_line_main_2 = CreateWindow(L"edit", L"Вид: y=kx+b", WS_VISIBLE | WS_CHILD | ES_READONLY, 760, 90, 200, 30, hwnd, (HMENU)id_edit_text_main, 0, 0);
    edit_line_min = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 710, 200, 70, 30, hwnd, (HMENU)id_edit_min, 0, 0);
    edit_line_max = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 820, 200, 70, 30, hwnd, (HMENU)id_edit_max, 0, 0);
}


void CreateInterfaceParabola(HWND hwnd, HDC dc) {
    SetBkColor(dc, RGB(240, 240, 240));
    DestroyInterface();
    edit_line_1 = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 680, 300, 50, 30, hwnd, (HMENU)id_edit_1, 0, 0);
    edit_line_2 = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 780, 300, 50, 30, hwnd, (HMENU)id_edit_2, 0, 0);
    edit_line_3 = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 880, 300, 50, 30, hwnd, (HMENU)id_edit_3, 0, 0);
    text_line_1 = CreateWindow(L"edit", L"a:", WS_VISIBLE | WS_CHILD | ES_READONLY, 660, 300, 15, 30, hwnd, (HMENU)id_edit_text_1, 0, 0);
    text_line_2 = CreateWindow(L"edit", L"b:", WS_VISIBLE | WS_CHILD | ES_READONLY, 760, 300, 15, 30, hwnd, (HMENU)id_edit_text_2, 0, 0);
    text_line_3 = CreateWindow(L"edit", L"c:", WS_VISIBLE | WS_CHILD | ES_READONLY, 860, 300, 15, 30, hwnd, (HMENU)id_edit_text_3, 0, 0);
    text_line_min = CreateWindow(L"edit", L"От X:", WS_VISIBLE | WS_CHILD | ES_READONLY, 674, 200, 35, 30, hwnd, (HMENU)id_edit_text_min, 0, 0);
    text_line_max = CreateWindow(L"edit", L"До X:", WS_VISIBLE | WS_CHILD | ES_READONLY, 782, 200, 36, 30, hwnd, (HMENU)id_edit_text_max, 0, 0);
    text_line_main_1 = CreateWindow(L"edit", L"График: Парабола", WS_VISIBLE | WS_CHILD | ES_READONLY, 740, 60, 200, 30, hwnd, (HMENU)id_edit_text_main, 0, 0);
    text_line_main_2 = CreateWindow(L"edit", L"Вид: y=ax^2+bx+c", WS_VISIBLE | WS_CHILD | ES_READONLY, 740, 90, 200, 30, hwnd, (HMENU)id_edit_text_main, 0, 0);
    edit_line_min = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 710, 200, 70, 30, hwnd, (HMENU)id_edit_min, 0, 0);
    edit_line_max = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 820, 200, 70, 30, hwnd, (HMENU)id_edit_max, 0, 0);
}


void CreateInterfaceGiperbola(HWND hwnd, HDC dc) {
    SetBkColor(dc, RGB(240, 240, 240));
    DestroyInterface();
    edit_line_1 = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 735, 295, 50, 30, hwnd, (HMENU)id_edit_1, 0, 0);
    edit_line_2 = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 815, 295, 50, 30, hwnd, (HMENU)id_edit_2, 0, 0);
    edit_line_3 = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 735, 365, 50, 30, hwnd, (HMENU)id_edit_3, 0, 0);
    edit_line_4 = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 815, 365, 50, 30, hwnd, (HMENU)id_edit_4, 0, 0);
    text_line_1 = CreateWindow(L"edit", L"k:", WS_VISIBLE | WS_CHILD | ES_READONLY, 715, 295, 15, 30, hwnd, (HMENU)id_edit_text_1, 0, 0);
    text_line_2 = CreateWindow(L"edit", L"a:", WS_VISIBLE | WS_CHILD | ES_READONLY, 795, 295, 15, 30, hwnd, (HMENU)id_edit_text_2, 0, 0);
    text_line_3 = CreateWindow(L"edit", L"b:", WS_VISIBLE | WS_CHILD | ES_READONLY, 715, 365, 15, 30, hwnd, (HMENU)id_edit_text_3, 0, 0);
    text_line_4 = CreateWindow(L"edit", L"c:", WS_VISIBLE | WS_CHILD | ES_READONLY, 795, 365, 15, 30, hwnd, (HMENU)id_edit_text_4, 0, 0);
    text_line_min = CreateWindow(L"edit", L"От X:", WS_VISIBLE | WS_CHILD | ES_READONLY, 674, 200, 35, 30, hwnd, (HMENU)id_edit_text_min, 0, 0);
    text_line_max = CreateWindow(L"edit", L"До X:", WS_VISIBLE | WS_CHILD | ES_READONLY, 782, 200, 36, 30, hwnd, (HMENU)id_edit_text_max, 0, 0);
    text_line_main_1 = CreateWindow(L"edit", L"График: Гипербола", WS_VISIBLE | WS_CHILD | ES_READONLY, 738, 60, 200, 30, hwnd, (HMENU)id_edit_text_main, 0, 0);
    text_line_main_2 = CreateWindow(L"edit", L"Вид: y=k/(ax+b)+c", WS_VISIBLE | WS_CHILD | ES_READONLY, 740, 90, 200, 30, hwnd, (HMENU)id_edit_text_main, 0, 0);
    edit_line_min = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 710, 200, 70, 30, hwnd, (HMENU)id_edit_min, 0, 0);
    edit_line_max = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 820, 200, 70, 30, hwnd, (HMENU)id_edit_max, 0, 0);
}


void CreateInterfaceSin(HWND hwnd, HDC dc) {
    SetBkColor(dc, RGB(240, 240, 240));
    DestroyInterface();
    edit_line_1 = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 735, 295, 50, 30, hwnd, (HMENU)id_edit_1, 0, 0);
    edit_line_2 = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 815, 295, 50, 30, hwnd, (HMENU)id_edit_2, 0, 0);
    edit_line_3 = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 735, 365, 50, 30, hwnd, (HMENU)id_edit_3, 0, 0);
    edit_line_4 = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 815, 365, 50, 30, hwnd, (HMENU)id_edit_4, 0, 0);
    text_line_1 = CreateWindow(L"edit", L"a:", WS_VISIBLE | WS_CHILD | ES_READONLY, 715, 295, 15, 30, hwnd, (HMENU)id_edit_text_1, 0, 0);
    text_line_2 = CreateWindow(L"edit", L"k:", WS_VISIBLE | WS_CHILD | ES_READONLY, 795, 295, 15, 30, hwnd, (HMENU)id_edit_text_2, 0, 0);
    text_line_3 = CreateWindow(L"edit", L"l:", WS_VISIBLE | WS_CHILD | ES_READONLY, 715, 365, 15, 30, hwnd, (HMENU)id_edit_text_3, 0, 0);
    text_line_4 = CreateWindow(L"edit", L"b:", WS_VISIBLE | WS_CHILD | ES_READONLY, 795, 365, 15, 30, hwnd, (HMENU)id_edit_text_4, 0, 0);
    text_line_min = CreateWindow(L"edit", L"От X:", WS_VISIBLE | WS_CHILD | ES_READONLY, 674, 200, 35, 30, hwnd, (HMENU)id_edit_text_min, 0, 0);
    text_line_max = CreateWindow(L"edit", L"До X:", WS_VISIBLE | WS_CHILD | ES_READONLY, 782, 200, 36, 30, hwnd, (HMENU)id_edit_text_max, 0, 0);
    text_line_main_1 = CreateWindow(L"edit", L"График: Sin", WS_VISIBLE | WS_CHILD | ES_READONLY, 758, 60, 200, 30, hwnd, (HMENU)id_edit_text_main, 0, 0);
    text_line_main_2 = CreateWindow(L"edit", L"Вид: y=a*Sin(kx+l)+b", WS_VISIBLE | WS_CHILD | ES_READONLY, 738, 90, 200, 30, hwnd, (HMENU)id_edit_text_main, 0, 0);
    edit_line_min = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 710, 200, 70, 30, hwnd, (HMENU)id_edit_min, 0, 0);
    edit_line_max = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 820, 200, 70, 30, hwnd, (HMENU)id_edit_max, 0, 0);
}


void CreateInterfaceCos(HWND hwnd, HDC dc) {
    SetBkColor(dc, RGB(240, 240, 240));
    DestroyInterface();
    edit_line_1 = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 735, 295, 50, 30, hwnd, (HMENU)id_edit_1, 0, 0);
    edit_line_2 = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 815, 295, 50, 30, hwnd, (HMENU)id_edit_2, 0, 0);
    edit_line_3 = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 735, 365, 50, 30, hwnd, (HMENU)id_edit_3, 0, 0);
    edit_line_4 = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 815, 365, 50, 30, hwnd, (HMENU)id_edit_4, 0, 0);
    text_line_1 = CreateWindow(L"edit", L"a:", WS_VISIBLE | WS_CHILD | ES_READONLY, 715, 295, 15, 30, hwnd, (HMENU)id_edit_text_1, 0, 0);
    text_line_2 = CreateWindow(L"edit", L"k:", WS_VISIBLE | WS_CHILD | ES_READONLY, 795, 295, 15, 30, hwnd, (HMENU)id_edit_text_2, 0, 0);
    text_line_3 = CreateWindow(L"edit", L"l:", WS_VISIBLE | WS_CHILD | ES_READONLY, 715, 365, 15, 30, hwnd, (HMENU)id_edit_text_3, 0, 0);
    text_line_4 = CreateWindow(L"edit", L"b:", WS_VISIBLE | WS_CHILD | ES_READONLY, 795, 365, 15, 30, hwnd, (HMENU)id_edit_text_4, 0, 0);
    text_line_min = CreateWindow(L"edit", L"От X:", WS_VISIBLE | WS_CHILD | ES_READONLY, 674, 200, 35, 30, hwnd, (HMENU)id_edit_text_min, 0, 0);
    text_line_max = CreateWindow(L"edit", L"До X:", WS_VISIBLE | WS_CHILD | ES_READONLY, 782, 200, 36, 30, hwnd, (HMENU)id_edit_text_max, 0, 0);
    text_line_main_1 = CreateWindow(L"edit", L"График: Cos", WS_VISIBLE | WS_CHILD | ES_READONLY, 758, 60, 200, 30, hwnd, (HMENU)id_edit_text_main, 0, 0);
    text_line_main_2 = CreateWindow(L"edit", L"Вид: y=a*Cos(kx+l)+b", WS_VISIBLE | WS_CHILD | ES_READONLY, 738, 90, 200, 30, hwnd, (HMENU)id_edit_text_main, 0, 0);
    edit_line_min = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 710, 200, 70, 30, hwnd, (HMENU)id_edit_min, 0, 0);
    edit_line_max = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 820, 200, 70, 30, hwnd, (HMENU)id_edit_max, 0, 0);
}


//------------------------------------------------------------------------------------------------


//graphic

void Paint_Start(HDC dc) {
    SelectObject(dc, hpen1);
    MoveToEx(dc, X_CENTER, Y_CENTER, nullptr);
    LineTo(dc, X_CENTER - X_CENTER + 10, Y_CENTER);
    LineTo(dc, X_CENTER + X_CENTER - 10, Y_CENTER);
    MoveToEx(dc, X_CENTER, Y_CENTER, nullptr);
    LineTo(dc, X_CENTER, Y_CENTER - Y_CENTER + 10);
    LineTo(dc, X_CENTER, Y_CENTER + Y_CENTER - 10);
    MoveToEx(dc, X_CENTER, Y_CENTER, nullptr);
}


void Paint_Cletka(HDC dc) {
    SelectObject(dc, hpen2);
    MoveToEx(dc, X_CENTER, Y_CENTER, nullptr);

    for (int i = -15; i <= 15; i++) {
        Paint_CletkaAddX(i);
        Paint_CletkaAddY(i);
    }

    MoveToEx(dc, X_CENTER, Y_CENTER, nullptr);
}


void Paint_CletkaAddX(int amount) {
    MoveToEx(dc, X_CENTER + amount * X_CLETKA, Y_CENTER, nullptr);
    SelectObject(dc, font);
    TextOut(dc, X_CENTER + amount * X_CLETKA, Y_CENTER, to_wstring(amount).c_str(), 3);
    if (amount == 14)
        TextOut(dc, X_CENTER + amount * X_CLETKA + 10, Y_CENTER - 10, L"X", 1);
    LineTo(dc, X_CENTER + amount * X_CLETKA, Y_CENTER - Y_CENTER + 10);
    LineTo(dc, X_CENTER + amount * X_CLETKA, Y_CENTER + Y_CENTER - 10);
}


void Paint_CletkaAddY(int amount) {
    MoveToEx(dc, X_CENTER, Y_CENTER + amount * Y_CLETKA, nullptr);
    SelectObject(dc, font);
    TextOut(dc, X_CENTER, Y_CENTER + amount * Y_CLETKA, to_wstring(-1 * amount).c_str(), 3);
    if (amount == -14)
        TextOut(dc, X_CENTER - 10, Y_CENTER + amount * X_CLETKA - 15, L"Y", 1);
    LineTo(dc, X_CENTER + X_CENTER - 10, Y_CENTER + amount * Y_CLETKA);
    LineTo(dc, X_CENTER - X_CENTER + 10, Y_CENTER + amount * Y_CLETKA);
}


void Paint_Graphik(HDC dc, HWND hwnd) {
    hpen = RandomHpen();
    SelectObject(dc, hpen);

    switch (graph) {
    case 3: 
        k = atof(argv_edit_1);
        b = atof(argv_edit_2);
        min_g = atof(argv_edit_min);
        max_g = atof(argv_edit_max);
        LineGraphik(dc, k, b, min_g, max_g);
        break;
    case 4:
        k = atof(argv_edit_1);
        b = atof(argv_edit_2);
        c = atof(argv_edit_3);
        min_g = atof(argv_edit_min);
        max_g = atof(argv_edit_max);
        ParabolaGraphik(dc, k, b, c, min_g, max_g);
        break;
    case 5:
        k = atof(argv_edit_1);
        b = atof(argv_edit_2);
        c = atof(argv_edit_3);
        l = atof(argv_edit_4);
        min_g = atof(argv_edit_min);
        max_g = atof(argv_edit_max);
        GiperbolaGraphik(dc, k, b, c, l, min_g, max_g);
        break;
    case 6:
        k = atof(argv_edit_1);
        b = atof(argv_edit_2);
        c = atof(argv_edit_3);
        l = atof(argv_edit_4);
        min_g = atof(argv_edit_min);
        max_g = atof(argv_edit_max);
        SinGraphik(dc, k, b, c, l, min_g, max_g);
        break;
    case 7:
        k = atof(argv_edit_1);
        b = atof(argv_edit_2);
        c = atof(argv_edit_3);
        l = atof(argv_edit_4);
        min_g = atof(argv_edit_min);
        max_g = atof(argv_edit_max);
        CosGraphik(dc, k, b, c, l, min_g, max_g);
        break;
    }   
}


HPEN RandomHpen() {
    int a = abs(rand()%(5 - 1)) + 1;
    if (a == 1) {
        return hpen3;
    } else if (a == 2) {
        return hpen4;
    } else if (a == 3) {
        return hpen5;
    } else if (a == 4) {
        return hpen6;
    } else if (a == 5) {
        return hpen7;
    } else {
        return hpen3;
    }
}


void CaseGraph(HWND hwnd, int v, HDC dc) {
    graph = v;
    CreateWidgets(hwnd, dc);
    UpdateWindow(hwnd);
}


void LineGraphik(HDC dc, float k, float b, float min_g, float max_g) {
    float x, y;

    for (float i = min_g; i <= max_g; i += 0.1) {
        x = X_CENTER + i * X_CLETKA;
        y = Y_CENTER - (k * i + b) * Y_CLETKA;
        if (i - min_g < 0.000001) 
            MoveToEx(dc, x, y, nullptr);
        else {
            LineTo(dc, x, y);
            MoveToEx(dc, x, y, nullptr);
        }
    }
}


void ParabolaGraphik(HDC dc, float a, float b, float c, float min_g, float max_g) {
    float x, y, v;
    v = -1 * b / 2 * a;

    for (float i = v + min_g; i <= v + max_g; i += 0.1) {
        x = X_CENTER + i * X_CLETKA;
        y = Y_CENTER - (a * i * i + b * i + c) * Y_CLETKA;

        if (i == v + min_g || i == v + max_g) 
            MoveToEx(dc, x, y, nullptr);
        else {
            LineTo(dc, x, y);
            MoveToEx(dc, x, y, nullptr);
        } 
    }
}


void GiperbolaGraphik(HDC dc, float a, float b, float c, float l, float min_g, float max_g) {
    float x, y;

    for (float i = min_g; i < -c/b; i += 0.1) {
        x = X_CENTER + i * X_CLETKA;
        y = Y_CENTER - ((a / (b * i + c)) + l) * Y_CLETKA;
        if (i - min_g < 0.000001) {
            MoveToEx(dc, x, y, nullptr);
        } else {
            LineTo(dc, x, y);
            MoveToEx(dc, x, y, nullptr); 
        }
    }

    for (float i = max_g; i > -c/b; i -= 0.1) {
        x = X_CENTER + i * X_CLETKA;
        y = Y_CENTER - ((a / (b * i + c)) + l) * Y_CLETKA;
        if (max_g - i < 0.000001) {
            MoveToEx(dc, x, y, nullptr);
        } else {
            LineTo(dc, x, y);
            MoveToEx(dc, x, y, nullptr); 
        }
    }
}


void SinGraphik(HDC dc, float a, float b, float c, float l, float min_g, float max_g){
    int x, y;

     for (float i = min_g; i <= max_g; i += 0.1) {
        x = X_CENTER + i * X_CLETKA;
        y = Y_CENTER - (a * sin(b * i + c) + l) * Y_CLETKA;
        if (i - min_g < 0.000001) {
            MoveToEx(dc, x, y, nullptr);
        } else {
            LineTo(dc, x, y);
            MoveToEx(dc, x, y, nullptr);
        }
    }
}


void CosGraphik(HDC dc, float a, float b, float c, float l, float min_g, float max_g){
    int x, y;

     for (float i = min_g; i <= max_g; i += 0.1) {
        x = X_CENTER + i * X_CLETKA;
        y = Y_CENTER - (a * cos(b * i + c) + l) * Y_CLETKA;
        if (i - min_g < 0.000001) {
            MoveToEx(dc, x, y, nullptr);
        } else {
            LineTo(dc, x, y);
            MoveToEx(dc, x, y, nullptr);
        }
    }
}


//------------------------------------------------------------------------------------------------

