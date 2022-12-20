/*
 * Создать класс, представляющий матрицу. 
 * Реализовать в нем метод, вычисляющий определитель матрицы. 
 * Для реализации используйте контейнеры из STL.
*/
#include <iostream>
#include <vector>
#include <cstdlib>

class Matrix
{
public:
    Matrix(int dim);
    void fill();
    void test_fill();
    void print() const;
    int det();
private:
    std::vector<std::vector<int>> get_minor(const std::vector<std::vector<int>>& m, int row, int col);
    int det(const std::vector<std::vector<int>>& m);
    std::vector<std::vector<int>> matrix;
};

Matrix::Matrix(int dim)
{
    for (int i = 0; i < dim; ++i) {
        std::vector<int> row(dim);
        matrix.push_back(row);
    }
}

void Matrix::fill()
{
    for (int row = 0; row < matrix.size(); ++row) {
        for (int col = 0; col < matrix[row].size(); ++col) {
            matrix[row][col] = 1 + rand() % 10;
        }
    }
}

void Matrix::test_fill()
{
    std::vector<std::vector<int>> t {
        {2, 4, 3},
        {5, 7, 8},
        {6, 9, 1}
    };
    matrix = t;
}

void Matrix::print() const
{
    for (auto row : matrix) {
        for (auto el : row) {
            std::cout << el << "\t";
        }
        std::cout << std::endl;
    }
}

int Matrix::det()
{
    return det(matrix);
}

std::vector<std::vector<int>> Matrix::get_minor(const std::vector<std::vector<int>>& m, int row, int col)
{
    int dim = m.size() - 1;
    int di, dj;
    std::vector<std::vector<int>> minor(dim, std::vector<int>(dim));
    
    di = 0;
    for (int i = 0; i < dim; ++i) {
        if (i == row) di = 1;
        dj = 0;
        for (int j = 0; j < dim; ++j) {
            if (j == col) dj = 1;
            minor[i][j] = m[i + di][j + dj];
        }
    }

    return minor;
}

int Matrix::det(const std::vector<std::vector<int>>& m)
{
    int d = 0;
    int k = 1;
    
    if (m.size() == 1) {
        return m[0][0];
    }
    if (m.size() == 2) {
        return m[0][0] * m[1][1] - m[0][1] * m[1][0];
    }
    for (int i = 0; i < m.size(); ++i) {
        auto temp = get_minor(m, 0, i);
        d = d + k * m[0][i] * det(temp);
        k = -k;
    }
    return d;
}

int main()
{
    Matrix m(3);
    m.test_fill();
    m.print();

    std::cout << "Determinant: " << m.det() << std::endl;   // 51, вроде, правильно :)

    return 0;
}