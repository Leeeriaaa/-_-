#include<stdio.h>
#include <locale.h>
#include <conio.h>
#include <stdlib.h>
#define ROWS 11
#define COLS 11

int FileMass(const char* filename, char h[11][11]);
void Menu();
void Mass(char arr[11][11], int a);
void Step(int i, int j, int step, char arr[11][11], int start, int b);
void progress(char arr[11][11], int b);
void pravila();
int proverka(char pole[11][11], char itog[11][11]);
char itog[11][11];   
char b[11][11];
char a[11][11] = { {'-', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'},
                   {'1', '2', '-', '-', '4', '-', '-', '-', '2', '6', '-'},
                   {'2', '-', '1', '-', '-', '-', '7', '-', '-', '5', '-'},
                   {'3', '-', '5', '-', '-', '-', '-', '-', '-', '-', '-'},
                   {'4', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
                   {'5', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
                   {'6', '-', '-', '-', '-', '3', '-', '-', '-', '-', '-'},
                   {'7', '-', '-', '-', '4', '7', '-', '-', '-', '-', '-'},
                   {'8', '-', '-', '-', '-', '-', '-', '3', '-', '-', '-'},
                   {'9', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
                   {'0', '-', '-', '-', '1', '-', '-', '-', '-', '-', '6'} };
int main() {
    setlocale(LC_ALL, "Rus");
    int option, row = 0, col = 0, start_value = 0, direction = -1, n = 10, result;
    FileMass("play.txt", itog);
    do {
        Menu();
        scanf("%d", &option);
        switch (option) {
        case 1:
            printf("\nИсходное поле\n");
            Mass(a, n);
            printf("Игра началась!!\n");
            Step(row, col, direction, a, start_value, n);
            printf("промежуточный результат игры:\n");//вывод промежуточного поля
            printf("_________________________________\n");
            Mass(a, n);
            progress(a, n);
            break;
        case 2:
            FileMass("progress.txt", b);
            Mass(b, n);
            Step(row, col, direction, b, start_value, n);
            printf("промежуточный результат игры:\n");//вывод промежуточного поля
            printf("_________________________________\n");
            Mass(b, n);
            progress(b, n);
            break;
        case 3:
            pravila();
            break;
        case 4:
            result = proverka(a, itog);
            if (result == 1) {
                printf("Вы победили!!!\n");
            }
            else {
                printf("\nВы проиграли ): Попробуйте снова\n");
            }
            break;
        case 5:
            printf("\nДо свидания!");
            break;
        default:
            printf("неверно выбрана опция \n");
        }
    } while (option != 5);

}

//считывание данных из файла и запись их в массив 
int FileMass(const char* filename, char h[11][11]) {
    FILE* itoog = fopen(filename, "r");
    if (itoog == 0) {
        printf("Ошибка при открытии файла\n");
        return 1;
    }
    for (int i = 0; i <= 10; i++) {
        for (int j = 0; j <= 10; j++) {
            fscanf(itoog, "%c ", &h[i][j]);
        }
    }
    return 0;
    fclose(itoog);
}
//меню игры
void Menu() {
    printf("\n~~~~~~~~~ Соедини числа ~~~~~~~~~\n");
    printf("1) Игра\n");
    printf("2) Продолжить игру\n");
    printf("3) Правила игры\n");
    printf("4) Проверить игру\n");
    printf("5) Выход\n");


    printf("Выберите номер опции: ");
}
//Вывод массива
void Mass(char arr[11][11], int a) {

    printf("_________________________________\n");
    for (int i = 0; i <= a; i++) {
        for (int j = 0; j <= a; j++) {
            printf("|_%c", arr[i][j]);
        }
        printf("|\n");
    }
    printf("\n");
}
//выполнение игры
void Step(int i, int j, int step, char arr[11][11], int start, int b) {
    //выбор координат, с которых начнем игру
    printf("Введите номер строки (от 1 до 10): ");
    scanf("%d", &i);
    printf("Введите номер столбца (от 1 до 10): ");
    scanf("%d", &j);
    start = arr[i][j];
    printf("Соеденив число нажмите 0\n");//условие завершения соеденения чисел
    printf("Выберите направление (1 - вправо, 2 - влево, 3 - вниз, 4 - вверх)\n");//передвижение по полю
    do {
        printf("Шаг: ");
        scanf("%d", &step);
        switch (step) {
        case 1: // вправо
            if (j < COLS - 1) {
                j++;
                arr[i][j] = start;
            }
            break;
        case 2: // влево
            if (j > 0) {
                j--;
                arr[i][j] = start;
            }
            break;
        case 3: // вниз
            if (i < ROWS - 1) {
                i++;
                arr[i][j] = start;
            }
            break;
        case 4: // вверх
            if (i > 0) {
                i--;
                arr[i][j] = start;
            }
            break;
        }
    } while (step != 0);
}
//функция сохранения прогресса игры
void progress(char arr[11][11], int b) {
    FILE* file = fopen("progress.txt", "w");
    if (file == 0) {
        printf("Ошибка открытия файла.\n");
        return;
    }
    for (int i = 0; i <= b; i++) {
        for (int j = 0; j <= b; j++) {
            fprintf(file, "%c ", arr[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    printf("Прогресс успешно сохранен\n");
}
//Функция правила
void pravila() {
    printf("правила игры:\n");
    printf("- линии, которые соединяют числа не должны пересекаться с другими линиями и сами с собой\n");
    printf("- линии, должны соединять только одинаковые числа\n");
}
//функция для проверки игры
int proverka(char pole[11][11], char itog[11][11]) {
    int n = 10;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (pole[i][j] != itog[i][j]) {
                return 0; // проигрыш
            }
        }
    }
    return 1; // победа
}