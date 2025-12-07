FROM python:3.10-slim

WORKDIR /app

# Установка системных зависимостей
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    && rm -rf /var/lib/apt/lists/*

# Копирование исходного кода
COPY . .

# Шаг 1: Установка инструментов сборки (отдельный слой)
RUN python3 -m pip install --upgrade pip setuptools wheel build && \
    python3 -m pip install scikit-build-core[pyproject] cmake ninja pybind11

# Шаг 2: Сборка wheel (теперь модуль build точно доступен)
RUN python3 -m build

# Шаг 3: Установка собранного wheel и зависимостей для тестов
RUN pip install dist/*.whl && \
    pip install pytest numpy scipy

# Запуск тестов
CMD ["python3", "-m", "pytest", "tests/", "-v", "-s"]
