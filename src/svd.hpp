#pragma once
#include <vector>
#include <tuple>

using Matrix = std::vector<std::vector<double>>;
using SVDResult = std::tuple<Matrix, std::vector<double>, Matrix>;

class SVDComputer {
public:
    static SVDResult compute(const Matrix& A);

private:
    static Matrix transpose(const Matrix& A);
    static Matrix matmul(const Matrix& A, const Matrix& B);
    static std::vector<double> eigenvalues(const Matrix& A);
};
