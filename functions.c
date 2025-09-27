// "Copyright 2024 Cretu Cristina" [legal/copyright]
#include "functions.h"

int AlocateMatrix(int ***a, int N, int M) {
    *a = malloc(N * sizeof(int *));
    if (*a == NULL)
        return -1;
    for (int i = 0; i < N; i++) {
        (*a)[i] = calloc(M, sizeof(int));
        if ((*a)[i] == NULL)
            return -1;
    }
}

int AlocateArray(int **v, int y) {
    *v = calloc(y, sizeof(int));
    if (*v == NULL)
        return -1;
}

void ReadMatrix(int **a, int N, int M) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            scanf("%d", &a[i][j]);
}

void DisplayMatrix(int **a, int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
}

void CopyMatrix(int ***m1, int **m2, int N, int M) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            (*m1)[i][j] = m2[i][j];
}

void SpinThePixels(int **a, int N, int c, int r) {
    for (int i = 1; i <= r; i++) {
        int x = a[N - 1][c];
        for (int j = N - 1; j > 0; j--)
            a[j][c] = a[j - 1][c];
        a[0][c] = x;
    }
}

void ScoreLines(int **a, int *v, int N, int M, int *valid_lines, int *score_lines, int *scor_s) {
    for (int i = 0; i < 3; i++) {
        int length_max = 0, b1 = a[i][0], b2, length_streak = 1, x = -1;
        if (v[a[i][0]] == 0)
            v[a[i][0]]++;
        for (int j = 1; j < M; j++) {
            if (v[a[i][j]] == 0)
                v[a[i][j]]++;
            b2 = a[i][j];
            if (b2 == b1) {
                length_streak++;
            } else {
                if (length_streak >= 3 && length_streak > length_max) {
                    length_max = length_streak;
                    x = b1;
                }
                length_streak = 1;
            }
            b1 = b2;
        }
        if (length_streak >= 3 && length_streak > length_max) {
            length_max = length_streak;
            x = b1;
        }
        if (length_max) {
            (*valid_lines)++;
            if (x == 7)
                *score_lines += 2 * length_max;
            else
                *score_lines += length_max;
        }
    }
    int nr_s = 0;   // nr of distinct symbols
    for (int i = 0; i <= 9; i++)
        if (v[i])
            nr_s++;
    if (nr_s <= 2)
        (*scor_s) += 100;
    else if (nr_s <= 4)
        (*scor_s) += 15;
}

void ScoreDiagonals(int **a, int N, int M, int *valid_diagonals, int *score_diagonals) {
    for (int j = 1; j < M - 1; j++) {
        int centre = a[1][j];
        if (centre == a[0][j - 1] && centre == a[2][j + 1]) {
            if (centre == a[0][j + 1] && centre == a[2][j - 1]) {
                (*valid_diagonals)++;
                (*score_diagonals) += 21;
                if (centre == 7)   // bonus
                    (*score_diagonals) += 21;
            } else {
                (*valid_diagonals)++;
                (*score_diagonals) += 7;
                if (centre == 7)   // bonus
                    (*score_diagonals) += 7;
            }
        } else if (centre == a[0][j + 1] && centre == a[2][j - 1]) {
            (*valid_diagonals)++;
            (*score_diagonals) += 7;
            if (centre == 7)   // bonus
                (*score_diagonals) += 7;
        }
    }
}

void FreeMatrix(int ***a, int N) {
    for (int i = 0; i < N; i++)
        free((*a)[i]);
    free(*a);
    *a = NULL;
}

void FreeArray(int **v, int y) {
    free(*v);
    *v = NULL;
}