#include "drawing.h"

Drawing::Drawing() : screen(WIDTH, HEIGHT) {
    std::cout << "Drawing Initialized\n";
}

Drawing::~Drawing() {
    // Destructor
}

void Drawing::DrawPixel(int x, int y, COLORREF color) {
    SetPixel(hdc, x, y, color);
}

void Drawing::DeletePixel(int x, int y) {
    SetPixel(hdc, x, y, RGB(0,0,0));
}

void Drawing::RandomPixel(int x, int y, int radius, bool checkPos) {
    const char class_name[] = "randomPixel";

    WNDCLASS wc = {};
    wc.lpfnWndProc = DefWindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = class_name;

    RegisterClass(&wc);

    hwnd = CreateWindowEx(
        WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
        class_name,
        "Random Pixel",
        WS_POPUP,
        0, 0, WIDTH, HEIGHT,
        NULL, NULL, GetModuleHandle(NULL), NULL
    );

    if (hwnd == NULL) {
        std::cerr << "[randomPixel] [!] Failed to create window.\n";
        return;
    }

    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
    ShowWindow(hwnd, SW_SHOWNORMAL);

    hdc = GetDC(hwnd);
    
    DrawPixel(x, y, RGB(255, 0, 0));

    // Force an update of the window
    InvalidateRect(hwnd, NULL, FALSE);
    UpdateWindow(hwnd);

    MSG msg;
    POINT mousepos;
    bool shouldExit = false;

    while (!shouldExit) {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT) {
                shouldExit = true;
                break;
            }
        }

        GetCursorPos(&mousepos);
        std::cout << "Mouse X: " << mousepos.x << " Mouse Y: " << mousepos.y << "\n";

        int dx = mousepos.x - x;
        int dy = mousepos.y - y;
        if (sqrt(dx * dx + dy * dy) <= radius) {
            shouldExit = true;
        }

        Sleep(10);  // Add a small delay to reduce CPU usage
    }

    ReleaseDC(hwnd, hdc);
    DestroyWindow(hwnd);
}