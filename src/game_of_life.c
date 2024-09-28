#include <stdio.h>
#include <stdlib.h>
#include <conio.h>  // Для _getch()
#include <windows.h>  // Для Sleep()

#define WIDTH 80
#define HEIGHT 25

void menu(int field[HEIGHT][WIDTH]);
void set_console_utf8();
void game_menu(int field[HEIGHT][WIDTH], char input);
void init_field(int field[HEIGHT][WIDTH]);
void load_field_from_file(int field[HEIGHT][WIDTH], const char *filename);
void load_field_from_stdin(int field[HEIGHT][WIDTH]);

int get_neighbour_count(int field[HEIGHT][WIDTH], int row, int col);
void update_field(int current[HEIGHT][WIDTH], int next[HEIGHT][WIDTH]);
void display_field(int field[HEIGHT][WIDTH]);
void game_loop(int field[HEIGHT][WIDTH]);
void clear_screen();
void pause_execution();

int main() {
    set_console_utf8();
    int field[HEIGHT][WIDTH];
    init_field(field);
    menu(field);
    game_loop(field);
    return 0;
}

void set_console_utf8() {
    SetConsoleOutputCP(CP_UTF8);
}

// ui

void menu(int field[HEIGHT][WIDTH]) {
    printf("1. Загрузить поле из файла\n");
    printf("2. Ввести поле с клавиатуры\n");
    printf("3. Выход\n");
    printf("Q или q - для выхода\n");

    char choice;
    scanf(" %c", &choice);  // Пробел перед %c для игнорирования пробельных символов
    switch (choice) {
        case '1':
            game_menu(field, choice);
            break;
        case '2':
            load_field_from_stdin(field);
            break;
        case 'q':
        case 'Q':
            exit(0);
            break;
        default:
            printf("Ошибка: Неверный выбор. Пожалуйста, попробуйте снова.\n");
            menu(field);  // Повторный вызов меню в случае ошибки
            break;
    }
}

// Game menu

void game_menu(int field[HEIGHT][WIDTH], char choice) {
    clear_screen();
    printf("1. Загрузить шаблон Beacon \n");
    printf("2. Загрузить шаблон Blinker\n");
    printf("3. Загрузить шаблон Block\n");
    printf("4. Загрузить шаблон Glider\n");
    printf("5. Загрузить шаблон Pulsar\n");
    printf("Q или q - для выхода\n");
    scanf("%c", &choice);

    switch (choice) {
        case '1':
            load_field_from_file(field, "data/init_beacon.txt");
            break;
        case '2':
            load_field_from_file(field, "data/init_blinker.txt");
            break;
        case '3':
            load_field_from_file(field, "data/init_block.txt");
            break;
        case '4':
            load_field_from_file(field, "data/init_glider.txt");
            break;
        case '5':
            load_field_from_file(field, "data/init_pulsar.txt");
            break;
        case 'q':
        case 'Q':
            exit(0);
            break;
        default:
            printf("Ошибка: Неверный выбор. Пожалуйста, попробуйте снова.\n");
            game_menu(field, choice);  // Повторный вызов меню в случае ошибки
            break;
    }
}

// Инициализация поля

void init_field(int field[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            field[i][j] = 0;  // Все клетки мертвы
        }
    }
}

// Загрузка поля из файла

void load_field_from_file(int field[HEIGHT][WIDTH], const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        return;
    }

    char line[WIDTH + 2];  // +2 для учёта символа новой строки и завершающего '\0'
    for (int i = 0; i < HEIGHT && fgets(line, sizeof(line), file); i++) {
        for (int j = 0; j < WIDTH; j++) {
            field[i][j] = (line[j] == '*') ? 1 : 0;
        }
    }

    fclose(file);

    // Вывод массива для проверки
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%d", field[i][j]);
        }
        printf("\n");
    }
}

// Загрузка поля с клавиатуры

void load_field_from_stdin(int field[HEIGHT][WIDTH]) {
    char line[WIDTH + 2];

    printf("Введите поле (каждая строка должна содержать %d символов):\n", WIDTH);
    for (int i = 0; i < HEIGHT; i++) {
        if (fgets(line, sizeof(line), stdin) == NULL) {
            fprintf(stderr, "Ошибка ввода данных.\n");
            exit(1);
        }
        for (int j = 0; j < WIDTH; j++) {
            field[i][j] = (line[j] == '*') ? 1 : 0;
        }
    }
}

// Подсчет количества живых соседей

int get_neighbour_count(int field[HEIGHT][WIDTH], int row, int col) {
    int count = 0;

    // Проверка всех восьми соседей
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;  // Пропускаем саму клетку

            int neighbour_row = (row + i + HEIGHT) % HEIGHT;  // Обертка по вертикали
            int neighbour_col = (col + j + WIDTH) % WIDTH;    // Обертка по горизонтали

            count += field[neighbour_row][neighbour_col];
        }
    }

    return count;
}

// Обновление поля

void update_field(int current[HEIGHT][WIDTH], int next[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int alive_neighbours = get_neighbour_count(current, i, j);

            // Правила игры "Жизнь"
            if (current[i][j] == 1) {
                // Клетка остается живой, если у нее 2 или 3 живых соседа
                next[i][j] = (alive_neighbours == 2 || alive_neighbours == 3) ? 1 : 0;
            } else {
                // Мертвая клетка становится живой, если у нее ровно 3 живых соседа
                next[i][j] = (alive_neighbours == 3) ? 1 : 0;
            }
        }
    }
}

// Отображение поля

void display_field(int field[HEIGHT][WIDTH]) {
    clear_screen();  // Перемещаем курсор в верхний левый угол // Добавить отдельную функцию

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", field[i][j] ? '*' : ' ');  // Живая клетка - '*', мертвая - ' '
        }
        printf("\n");
    }
}

// Главный цикл игры

void game_loop(int current[HEIGHT][WIDTH]) {
    int next[HEIGHT][WIDTH];
    int notnull = 1;

    while (notnull) {
        display_field(current);
        update_field(current, next);
        notnull = 0;
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (next[i][j] == 1) {
                    notnull = 1;
                }
                current[i][j] = next[i][j];
            }
        }
        if (notnull == 0) {
            display_field(current);
        }
        pause_execution();
    }
}

// Очистка экрана

void clear_screen() {
    system("cls");  // Очистка экрана для Windows
}

void pause_execution() {
    Sleep(1000);  // Пауза на 1 секунду
}
