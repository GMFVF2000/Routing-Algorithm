//
// Created by manrif on 04/11/19.
//

#ifndef ROUTINGALOGRITHM_MATRIX_H
#define ROUTINGALOGRITHM_MATRIX_H


#include <vector>
#include <string>

class Matrix {

public:

    struct PrintTransformation {
        int value;
        std::string replace;
    };

    Matrix();

    explicit Matrix(ulong size);

    Matrix(ulong height,ulong width, int defaultValue = 0);

    explicit Matrix(std::vector<std::vector<int>> values);

    static Matrix fromFile(std::string filePath);

    const Matrix clone() const;

    const Matrix swap() const;

    const ulong ySize() const;

    const ulong xSize() const;

    const int get(int y, int x, int defaultValue = -1) const;

    const bool set(int y, int x, int v);

    const bool exists(int y, int x) const;

    const bool isSquare() const;

    void applyPrintTransformation(Matrix::PrintTransformation const &transformations);

    friend std::ostream& operator<<(std::ostream &out, const Matrix &matrix);

private:

    std::vector<std::vector<int>> values;
    std::vector<Matrix::PrintTransformation> printTransformations;

    void printWithHeader(std::ostream &out) const;

    void print(std::ostream &out) const;

    const std::string transform(int i) const;

};


#endif //ROUTINGALOGRITHM_MATRIX_H
