# s21_containers

📦 **s21_containers** — это учебный проект, реализующий основные контейнеры стандартной библиотеки C++ STL. Цель проекта — глубокое понимание внутренних механизмов работы STL и практика написания шаблонного кода, итераторов, аллокаторов и структуры контейнеров.

## 📚 Реализованные контейнеры

Проект охватывает следующие STL-контейнеры:

| Контейнер | Расположение | Протестировано |
|-----------|--------------|----------------|
| `array`   | `array/include/s21_array.h` | ✅ |
| `vector`  | `vector/include/s21_vector.h` | ✅ |
| `list`    | `list/include/s21_list.h` | ✅ |
| `stack`   | `stack/include/s21_stack.h` | ✅ |
| `queue`   | `queue/include/s21_queue.h` | ✅ |
| `map`     | `map/include/s21_map.h` | ✅ |
| `set`     | `set/include/s21_set.h` | ✅ |
| `tree`    | `tree/include/s21_tree.h` (вспомогательная структура) | ✅ |

Все контейнеры поддерживают основные методы, соответствующие оригинальным STL-реализациям, и используют собственные итераторы, шаблонные классы и типы узлов.

---

## 📂 Структура проекта

```bash
src
   ├── array/            # Реализация и тесты для std::array
   ├── vector/           # Реализация и тесты для std::vector
   ├── list/             # Реализация и тесты для std::list
   ├── stack/            # Реализация и тесты для std::stack
   ├── queue/            # Реализация и тесты для std::queue
   ├── map/              # Реализация и тесты для std::map
   ├── set/              # Реализация и тесты для std::set
   ├── tree/             # Общая структура красно-черного дерева, используемая в map и set
   ├── include/          # Общий хедер s21_containers.h
   ├── tests/            # Общий runner для контейнеров
   ├── Makefile          # Сборка проекта и тестов
   ├── Dockerfile        # Docker-среда для сборки/тестов
   ├── Doxyfile          # Конфигурация для генерации документации Doxygen
```

## ⚙️ Зависимости
Перед сборкой убедитесь, что в вашей системе установлены следующие зависимости:

| Зависимость |	Назначение |
|-----------|--------------|
| g++ (C++20) |	Компилятор |
| make |	Сборка проекта |
| cmake (опц.) |	Альтернатива сборке (необязательно) |
| Google Test (libgtest-dev) |	Фреймворк для модульного тестирования |
| lcov |	Генерация покрытия кода |
| clang-format	| Проверка и автоформатирование кода |
| doxygen |	Генерация документации |
| docker	| Изолированная сборка и тестирование |

## Для установки всех зависимостей на Ubuntu:

``` bash
sudo apt update
sudo apt install build-essential lcov clang-format doxygen libgtest-dev cmake
```

## 🎯 Цели Makefile

```makefile
make                # Сборка и запуск тестов (по умолчанию)
make test           # Сборка и запуск тестов
make build_cov      # Сборка с флагами покрытия кода (--coverage)
make gcov_report    # Генерация HTML-отчета покрытия (использует lcov и genhtml)
make docs           # Генерация документации с помощью Doxygen
make clang-format-check    # Проверка форматирования кода (clang-format -n)
make clang-format-improve  # Автоматическое форматирование кода (clang-format -i)
make rebuild         # Очистка и пересборка проекта
make clean           # Удаление временных файлов, объектов, отчетов и документации
make docker_run      # Сборка и запуск проекта внутри Docker-контейнера
make ultimate_check  # Выполнение форматирования, покрытия и генерации документации
```


## 🧪 Тестирование
Для каждого контейнера написаны модульные тесты с использованием Google Test. Чтобы запустить все тесты:

``` bash
make test
```

## 🐳 Сборка с Docker

Сборка проекта и запуск тестов в изолированной среде Docker:

```bash
docker build -t s21_containers .
docker run --rm s21_containers
```

## 📖 Документация

Генерация документации через Doxygen:

```bash
doxygen Doxyfile
```

