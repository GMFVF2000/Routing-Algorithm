#include <utility>

//
// Created by manrif on 04/11/19.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Matrix.h"

Matrix::Matrix(): Matrix(0) {

}

Matrix::Matrix(ulong size) : Matrix(size, size, 0) {

}

Matrix::Matrix(ulong height, ulong width, int defaultValue) {
    std::vector<std::vector<int>> values = std::vector<std::vector<int>>(static_cast<unsigned long>(height));
    std::vector<int> line;
    for (int i = 0; i < height; ++i) {
        line = std::vector<int>(static_cast<unsigned long>(width));
        for (int j = 0; j < width; ++j) {
            line[j] = defaultValue;
        }
        values[i] = line;
    }
    this->values = std::move(values);
    this->printTransformations = std::vector<PrintTransformation>();
}

Matrix::Matrix(std::vector<std::vector<int>> values) {
    this->values = std::move(values);
    this->printTransformations = std::vector<PrintTransformation>();
}

Matrix Matrix::fromFile(std::string filePath) {
    std::ifstream inFile;

    inFile.open(filePath);
    if (!inFile) {
        std::cout << "Unable to open file" << std::endl;
        exit(1);
    }

    std::string line;
    std::vector<std::vector<int>> values  = std::vector<std::vector<int>>();
    std::vector<int> lineValues;

    while (getline(inFile, line)) {
        lineValues = std::vector<int>();
        for (char number : line) {
            if (isdigit(number)) {
                lineValues.push_back(number - '0');
            }
        }
        values.push_back(lineValues);
    }

    inFile.close();

    return Matrix(values);
}

const Matrix Matrix::clone() const {
    return Matrix(std::vector<std::vector<int>>(values));
}

const Matrix Matrix::swap() const {
    Matrix matrix = clone();

    auto size = static_cast<unsigned long>(matrix.ySize());
    bool swapped[size][size];
    int value;
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            if ((value = matrix.get(y, x)) != 0 && !swapped[y][x] && !swapped[x][y]) {
                matrix.set(y, x, matrix.get(x, y));
                matrix.set(x, y, value);
                swapped[y][x] = true;
                swapped[x][y] = true;
            }
        }
    }

    return matrix;
}

const ulong Matrix::ySize() const {
    return values.size();
}

const ulong Matrix::xSize() const {
    return ySize() > 0 ? values[0].size() : 0;
}

const int Matrix::get(const int y, const int x, const int defaultValue) const {
    return exists(y, x) ? values[y][x] : defaultValue;
}

const bool Matrix::set(const int y, const int x, const int v) {
    if (!exists(y, x)) {
        return false;
    }
    values[y][x] = v;
    return true;
}

const bool Matrix::exists(const int y, const int x) const {
    return y <= ySize() && x <= xSize();
}

std::ostream &operator<<(std::ostream &out, const Matrix &matrix) {
    if (std::max(matrix.xSize(), matrix.ySize()) > 9) {
        matrix.print(out);
    } else {
        matrix.printWithHeader(out);
    }
    return out;
}

const bool Matrix::isSquare() const {
    return ySize() == xSize();
}

void Matrix::applyPrintTransformation(Matrix::PrintTransformation const &transformation) {
    printTransformations.push_back(transformation);
}

void Matrix::printWithHeader(std::ostream &out) const {
    out << "\t  ";
    for (int i = 0; i < xSize(); ++i) {
        out <<std::to_string(i + 1) + "  ";
    }
    out << std::endl;
    print(out);
}

void Matrix::print(std::ostream &out) const {
    int x = 1;
    for (std::vector<int> const &line : values) {
        out << std::to_string(x) + (x > 9 ? " " : "  ") + "[";
        for (int i : line) {
            out << "  " + transform(i);
        }
        out << "  ]" << std::endl;
        x++;
    }
}

const std::string Matrix::transform(const int i) const {
    for (Matrix::PrintTransformation const &transformation: printTransformations) {
        if (i == transformation.value) {
            return transformation.replace;
        }
    }
    return std::to_string(i);
}
