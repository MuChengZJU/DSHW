/**
 * @file CrossList.c
 * @author MuChengZJU (MuChengZJU@qq.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-13
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CrossList.h"
int createCrossList(CrossList *Matrix) {
    int m, n, t;
    printf("Please input the row, column and the number of the elements of the matrix: ");
    scanf("%d %d %d", &m, &n, &t);
    Matrix->mu = m;
    Matrix->nu = n;
    Matrix->tu = t;
    Matrix->rhead = (OLink *)malloc((m + 1) * sizeof(OLink));
    Matrix->chead = (OLink *)malloc((n + 1) * sizeof(OLink));
    
    // Init the head node
    for (int i = 0; i < m; i++) {
        Matrix->rhead[i] = NULL;
    }
    for (int i = 0; i < n; i++) {
        Matrix->chead[i] = NULL;
    }
    
    // Create the matrix
    for (int i = 0; i < t; i++) {
        int x, y;
        double e;
        printf("Please input the row, column and the element of the %dth element: ", i + 1);
        scanf("%d %d %lf", &x, &y, &e);
        OLink p = (OLink)malloc(sizeof(OLNode));
        p->i = x;
        p->j = y;
        p->e = e;
        p->right = NULL;
        p->down = NULL;

        // If this is the first element in the row, then set the head node
        if (Matrix->rhead[x] == NULL || Matrix->rhead[x]->j > y) {
            p->right = Matrix->rhead[x];
            Matrix->rhead[x] = p;
        } else {
            OLink q = Matrix->rhead[x];
            while (q->right != NULL && q->right->j < y) {
                q = q->right;
            }
            p->right = q->right;
            q->right = p;
        }

        // If this is the first element in the column, then set the head node
        if (Matrix->chead[y] == NULL || Matrix->chead[y]->i > x) {
            p->down = Matrix->chead[y];
            Matrix->chead[y] = p;
        } else {
            OLink q = Matrix->chead[y];
            while (q->down != NULL && q->down->i < x) {
                q = q->down;
            }
            p->down = q->down;
            q->down = p;
        }
    }
}

int printCrossList(CrossList *Matrix) {
    for (int i = 0; i < Matrix->mu; i++) {
        OLink p = Matrix->rhead[i];
        for (int j = 0; j < Matrix->nu; j++) {
            if (p != NULL && p->j == j) {
                if (p->e != 0) {
                    printf("%d, %d, %lf\n", p->i, p->j, p->e);
                }
                p = p->right;
            }
        }
    }
}

int destroyCrossList(CrossList *Matrix) {
    for (int i = 0; i < Matrix->mu; i++) {
        OLink p = Matrix->rhead[i];
        while (p != NULL) {
            OLink q = p;
            p = p->right;
            free(q);
        }
    }
    for (int i = 0; i < Matrix->nu; i++) {
        OLink p = Matrix->chead[i];
        while (p != NULL) {
            OLink q = p;
            p = p->down;
            free(q);
        }
    }
    free(Matrix->rhead);
    free(Matrix->chead);
}
