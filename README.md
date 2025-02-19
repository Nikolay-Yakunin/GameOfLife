# Игра "Жизнь" на C

## Описание

Этот проект реализует игру "Жизнь" на языке программирования C. Игра "Жизнь" — это клеточный автомат, изобретенный математиком Джоном Конвеем. В данной реализации используется MinGW для компиляции и запуска программы на Windows.

## Требования

- Windows 10
- MinGW (GCC и G++ компиляторы)
- CMake (для генерации make-файлов)
- Make (для сборки проекта)

## Установка MinGW и необходимых инструментов

### 1. Установка Chocolatey

Chocolatey — это менеджер пакетов для Windows. Установите его, следуя [официальным инструкциям](https://chocolatey.org/install).

### 2. Установка MinGW

Используйте Chocolatey для установки MinGW:

```sh
choco install mingw
```

### 3. Установка CMake и Make

Используйте Chocolatey для установки CMake и Make:

```sh
choco install cmake
choco install make
```

### 4. Настройка переменных окружения

Добавьте путь к `cmake` в переменные окружения:

1. Откройте "Переменные среды" в Windows.
2. Нажмите "Переменные среды".
3. В верхнем окне (переменные пользователя) нажмите "Создать".
4. Имя переменной: `cmake`
5. Значение переменной: `C:\Program Files\CMake\bin` (проверьте путь на вашем компьютере)
6. Нажмите "ОК" и "ОК" для завершения.

## Сборка проекта

### 1. Клонирование репозитория

Склонируйте репозиторий проекта:

```sh
git clone https://github.com/Nikolay-Yakunin/GameOfLife.git
cd game_of_life
```

### 2. Генерация make-файлов

Используйте CMake для генерации make-файлов:

```sh
cmake -G "MinGW Makefiles" .
```

### 3. Сборка проекта

Соберите проект с помощью Make:

```sh
make
```

### 4. Запуск программы

После успешной сборки выполните скомпилированный файл:

```sh
./game_of_life.exe
```

## Использование

### Меню

При запуске программы вы увидите меню с опциями:

1. Загрузить поле из файла
2. Ввести поле с клавиатуры
3. Выход
4. Q или q - для выхода

### Управление

- Выберите опцию, введя соответствующую цифру или букву.
- Следуйте инструкциям на экране для загрузки или ввода поля.

## Лицензия

Этот проект лицензирован под лицензией MIT. Подробности см. в файле [LICENSE](LICENSE).

## Ссылки

- [MinGW на GitHub](https://github.com/DennisPing/Windows-10-Cpp-MinGW64)
- [Документация по CMake](https://cmake.org/documentation/)
- [Chocolatey](https://chocolatey.org/)