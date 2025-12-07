#include "svd.hpp"
#include <cmath>
#include <algorithm>
#include <stdexcept>

// Базовая реализация SVD через власные значения A^T * A
SVDResult SVDComputer::compute(const Matrix& A) {
    if (A.empty() || A.empty()) {
        throw std::invalid_argument("Matrix cannot be empty");
    }

    int m = A.size();
    int n = A.size();

    // Вычисляем A^T * A
    Matrix AT = transpose(A);
    Matrix ATA = matmul(AT, A);

    // Вычисляем собственные значения и векторы (упрощённо)
    std::vector<double> singular_values = eigenvalues(ATA);

    // Преобразуем в сингулярные значения
    for (auto& sv : singular_values) {
        if (sv > 0) sv = std::sqrt(sv);
    }

    // Сортируем по убыванию
    std::sort(singular_values.begin(), singular_values.end(),
              [](double a, double b) { return a > b; });

    // Для демонстрации: V — матрица из A^T
    // U — матрица из A
    Matrix U = A;
    Matrix V = AT;

    return std::make_tuple(U, singular_values, V);
}

Matrix SVDComputer::transpose(const Matrix& A) {
    if (A.empty()) return {};

    int m = A.size();
    int n = A.size();

    Matrix result(n, std::vector<double>(m, 0.0));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            result[j][i] = A[i][j];
        }
    }
    return result;
}

Matrix SVDComputer::matmul(const Matrix& A, const Matrix& B) {
    if (A.empty() || B.empty() || A.size() != B.size()) {
        throw std::invalid_argument("Invalid matrix dimensions for multiplication");
    }

    int m = A.size();
    int n = B.size();
    int k = B.size();

    Matrix result(m, std::vector<double>(n, 0.0));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int p = 0; p < k; ++p) {
                result[i][j] += A[i][p] * B[p][j];
            }
        }
    }
    return result;
}

std::vector<double> SVDComputer::eigenvalues(const Matrix& A) {
    if (A.empty()) return {};

    int n = A.size();
    std::vector<double> evals(n, 0.0);

    // Упрощённая версия: берём диагональные элементы + некоторый шум
    for (int i = 0; i < n; ++i) {
        evals[i] = std::abs(A[i][i]) + 1e-6;
    }

    return evals;
}
