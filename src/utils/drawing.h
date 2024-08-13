#ifndef DRAWING_H
#define DRAWING_H

#pragma once
#include <iostream>
#include <windows.h>
#include <vector>
#include "matrix.h"
#include <mfapi.h>
#include <cmath>

class Drawing {
    public:
        Drawing();
        ~Drawing();

        const int WIDTH = GetSystemMetrics(SM_CXSCREEN);
        const int HEIGHT = GetSystemMetrics(SM_CYSCREEN);

        Matrix screen;

        void RandomPixel(int x, int y, int radius, bool checkPos);
        void DrawPixel(int x, int y, COLORREF color);
        void DeletePixel(int x, int y);

    private:
        HWND hwnd;
        HDC hdc;
};

#endif // DRAWING_H