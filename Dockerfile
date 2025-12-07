FROM python:3.10-slim

WORKDIR /app

# Установить зависимости для компиляции
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    && rm -rf /var/lib/apt/lists/*

# Скопировать исходный код
COPY . .

# Собрать пакет
RUN python3 -m pip install --upgrade pip setuptools wheel && \
    python3 -m pip install scikit-build-core[pyproject] cmake ninja pybind11 && \
    python3 -m build

# Установить собранный пакет
RUN pip install dist/*.whl && \
    pip install pytest numpy scipy

# По умолчанию запустить тесты
CMD ["python3", "-m", "pytest", "tests/", "-v"]
