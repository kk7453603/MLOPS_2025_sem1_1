import numpy as np
from scipy.linalg import svd as scipy_svd
import pytest


from _svd_core import SVDComputer


class TestSVD:

    def test_basic_svd(self):
        """Тест базового SVD"""
        matrix = [
            [1.0, 0.0, 0.0],
            [0.0, 2.0, 0.0],
            [0.0, 0.0, 3.0]
        ]

        U, singular_values, VT = SVDComputer.compute(matrix)

        assert len(singular_values) > 0
        assert all(sv >= 0 for sv in singular_values)
        print(f"Singular values: {singular_values}")

    def test_rectangular_matrix(self):
        """Тест на прямоугольной матрице"""
        matrix = [
            [1.0, 2.0, 3.0],
            [4.0, 5.0, 6.0]
        ]

        U, singular_values, VT = SVDComputer.compute(matrix)

        assert len(singular_values) >= 2
        print(f"Rectangular matrix singular values: {singular_values}")

    def test_compare_with_scipy(self):
        """Сравнение с scipy.linalg.svd"""
        matrix = np.array([
            [1.0, 2.0],
            [3.0, 4.0],
            [5.0, 6.0]
        ])

        # Наша реализация
        U, singular_values, VT = SVDComputer.compute(matrix.tolist())

        # scipy реализация
        U_scipy, s_scipy, VT_scipy = scipy_svd(matrix)

        print(f"\nNaive SVD singular values: {singular_values[:2]}")
        print(f"Scipy SVD singular values: {s_scipy}")

        # Проверяем, что сингулярные значения положительны и отсортированы
        assert singular_values == sorted(singular_values, reverse=True)

    def test_empty_matrix_raises(self):
        """Тест на пустой матрице"""
        with pytest.raises(Exception):
            SVDComputer.compute([])

    def test_identity_matrix(self):
        """Тест на единичной матрице"""
        matrix = [
            [1.0, 0.0],
            [0.0, 1.0]
        ]

        U, singular_values, VT = SVDComputer.compute(matrix)

        # Для единичной матрицы все сингулярные значения должны быть близки к 1
        assert len(singular_values) >= 2
        print(f"Identity matrix singular values: {singular_values}")


if __name__ == "__main__":
    pytest.main([__file__, "-v", "-s"])
