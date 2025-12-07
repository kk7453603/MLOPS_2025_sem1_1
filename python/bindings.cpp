#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../src/svd.hpp"

namespace py = pybind11;

PYBIND11_MODULE(_svd_core, m) {
    m.doc() = "SVD (Singular Value Decomposition) C++ bindings";

    py::class_<SVDComputer>(m, "SVDComputer")
        .def_static("compute", &SVDComputer::compute,
                    py::arg("matrix"),
                    "Compute SVD of a matrix. Returns (U, singular_values, V^T)");
}
