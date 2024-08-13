#ifndef MATRIX_H
#define MATRIX_H

#pragma once
#include <iostream>
#include <vector>
#include <windows.h>

class Matrix {

    public:
        Matrix(int width, int height);
        ~Matrix();

        int getWidth();
        int getHeight();

        int ** getMatrix() const {return matrix;}
        void initalizeMatrix(int witdh, int height);

    private:
        int width;
        int height;
        int ** matrix;
};

#endif // MATRIX_H