#include "matrix.h"

Matrix::Matrix(int width, int height) {
    this->width = width;
    this->height = height;
    initalizeMatrix(width, height);
}

Matrix::~Matrix() {
    for (int i = 0; i < width; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void Matrix::initalizeMatrix(int width, int height) {
    matrix = new int*[width];
    for(int i = 0; i < width; ++i) {
        matrix[i] = new int[height];
    }
}