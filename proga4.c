#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *f = fopen("matrix.txt", "r");
    if (!f) {
        printf("Ошибка: не удалось открыть файл!\n");
        return 1;
    }

    int n, m;
    if (fscanf(f, "%d %d", &n, &m) != 2  n <= 0  m <= 0) {
        printf("Ошибка: неверный формат размеров матрицы!\n");
        fclose(f);
        return 1;
    }
    int **a = (int**)malloc(n * sizeof(int*));
    if (!a) {
        printf("Ошибка: память не выделена!\n");
        fclose(f);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        a[i] = (int*)malloc(m * sizeof(int));
        if (!a[i]) {
            printf("Ошибка: память не выделена!\n");
            for (int k = 0; k < i; k++)
                free(a[k]);
            free(a);
            fclose(f);
            return 1;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (fscanf(f, "%d", &a[i][j]) != 1) {
                printf("Ошибка: некорректные данные в файле!\n");
                for (int k = 0; k < n; k++)
                    free(a[k]);
                free(a);
                fclose(f);
                return 1;
            }
        }
    }

    fclose(f);

    int sum_neg = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (i + j > n - 1 && a[i][j] < 0)
                sum_neg += a[i][j];
    int min_pos = 1000000, min_index = -1;
    for (int i = 0; i < n; i++) {
        if (a[i][1] > 0 && a[i][1] < min_pos) {
            min_pos = a[i][1];
            min_index = i;
        }
    }
    if (min_index != -1 && m >= 4 && n >= 2) { // проверка выхода за границы
        int temp = a[min_index][1];
        a[min_index][1] = a[1][3];
        a[1][3] = temp;
    }

    printf("\nСумма отрицательных элементов под побочной диагональю: %d\n", sum_neg);
    if (min_index != -1)
        printf("Минимальный положительный элемент 2 столбца: %d\n\n", min_pos);
    else
        printf("Положительных элементов во 2 столбце нет\n\n");

    printf("Матрица после обмена:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            printf("%5d", a[i][j]);
        printf("\n");
    }

    for (int i = 0; i < n; i++)
        free(a[i]);
    free(a);

    return 0;
}
