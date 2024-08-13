#include <windows.h>
#include <iostream>
#include <random>
#include "utils/drawing.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    FreeConsole();

    Drawing d;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> widthGen(0, d.WIDTH);
    std::uniform_int_distribution<> heightGen(0, d.HEIGHT);

    int pixelX = widthGen(gen);
    int pixelY = heightGen(gen);

    d.RandomPixel(pixelX, pixelY, 25, false);

    return 0;
}