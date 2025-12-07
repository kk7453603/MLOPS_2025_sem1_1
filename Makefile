.PHONY: build install clean test docker-build docker-test

build:
	touch README.md
	python3 -m pip install --upgrade pip setuptools wheel build
	python3 -m pip install scikit-build-core[pyproject] cmake ninja pybind11
	python3 -m build

install: build
	python3 -m pip install dist/*.whl --force-reinstall

clean:
	rm -rf build/ dist/ *.egg-info __pycache__ .pytest_cache _svd_core*.so
	find . -type d -name __pycache__ -exec rm -rf {} + 2>/dev/null || true

test:
	python3 -m pip install numpy scipy pytest
	python3 -m pytest tests/ -v -s

docker-build:
	docker build -t svd-bindings:latest .

docker-test: docker-build
	docker run --rm svd-bindings:latest
