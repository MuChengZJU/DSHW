/**
 * @file HW5.c
 * @author MuChengZJU (MuChengZJU@qq.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-12
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Node of the sparse matrix
 * 
 */
typedef struct OLNode {
    int i, j;
    double e;
    struct OLNode *right, *down;
} OLNode, *OLink;

/**
 * @brief The sparse matrix in cross list
 * 
 */
typedef struct {
    OLink *rhead, *chead;
    int mu, nu, tu;
} CrossList;

typedef char AtomType; // 原子类型定义为cahr*

// 广义表的头尾链表存储表示
typedef enum {ATOM, LIST} ElemTag;
// ATOM==0：原子，LIST==1：子表

typedef struct GLNode {
    ElemTag tag;
    // 公共部分，用于区分原子结点和表结点
    union {
        // 原子结点和表结点的联合部分
        AtomType atom;
        // atom是原子结点的值域，AtomType由typedef char 定义
        struct {
            struct GLNode *hp, *tp;
        } ptr;
        // ptr是表结点的指针域，prt.hp和ptr.tp分别指向表头和表尾
    };
} *GList, GLNode; // 广义表类型

int createCrossList(CrossList *Matrix);

int printCrossList(CrossList *Matrix);

int destroyCrossList(CrossList *Matrix);

int createGList(GList L, char *Str);
int main() {
    int choice = 0;
    do {
        // Menu
        printf("Please choose the function you want to test:\n");
        printf("1. 5.26\n");
        printf("2. 5.33\n");
        printf("0. Exit\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                // 5.26 
                // 以三元组形式输出用十字链表表示的稀疏矩阵中非零元素及其下标的算法
                // ERROR: INDEX STARTS FROM 0!!!
                {
                    CrossList Matrix;
                    createCrossList(&Matrix);
                    printCrossList(&Matrix);
                    destroyCrossList(&Matrix);
                }
                break;
            case 2:
                // 5.33
                // 递归算法，输出广义表中所有原子项及其所在的层次
                {
                    char *str = "(a,(b,c),d,(e,(f),g))";
                    GList L;
                    createGList(L, str);
                    printf("The atoms and their levels are:\n");
                }   
                break;
            case 0:
                printf("Exit!\n");
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } while (choice != 0);


    return 0;
}

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

int createGList(GList L, char *str) {
    if (str[2] == '\0') { // Empty String "()"
        L = NULL;
        return 1;
    } else {
        L = (GList)malloc(sizeof(GLNode));
        L->tag = LIST;
        GList p = L;
        // Remove brackets of Str to sub
        char *sub = (char *)malloc(strlen(str-2) * sizeof(char));
        strncpy(sub, str+1, strlen(str-2));

        do {
            // Take out hsub before ',' from sub
            char *hsub = strtok(sub, ",");
            // Create GList p->ptr.hp from hsub
            if (strlen(hsub) == 1) {
                p->ptr.hp = (GList)malloc(sizeof(GLNode));
                p->ptr.hp->tag = ATOM;
                p->ptr.hp->atom = *hsub;
            } else {
                createGList(p->ptr.hp, hsub); // Recursive call
            }

            if (strlen(sub)) {
                p->ptr.tp = (GList)malloc(sizeof(GLNode));
                p=p->ptr.tp;
            }

        } while (strlen(sub));
        p->ptr.tp = NULL; // Tail node is NULL
    } 
}