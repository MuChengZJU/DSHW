/**
 * @file GList.c
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

#include "GList.h"

void createGList(GList *L, char *str)
{
    if (str[2] == '\0')
    { // Empty String "()"
        *L = NULL;
    }
    else
    {
        *L = (GList)malloc(sizeof(GLNode));
        (*L)->tag = LIST;
        GList p = *L;
        // Remove brackets of Str to sub
        char *sub = (char *)malloc((strlen(str) - 1) * sizeof(char));
        strncpy(sub, str + 1, strlen(str) - 2);
        sub[strlen(str) - 2] = '\0';
        // printf("sub: %s\n", sub);

        do
        {
            p->tag = LIST;
            // Split sub to hsub and sub
            char *hsub = NULL;
            splitGList(&sub, &hsub);
            // printf("hsub: %s\n", hsub);
            // printf("sub: %s\n", sub);
            // Create GList p->ptr.hp from hsub
            if (strlen(hsub) == 1)
            {
                p->ptr.hp = (GList)malloc(sizeof(GLNode));
                p->ptr.hp->tag = ATOM;
                p->ptr.hp->atom = hsub[0];
            }
            else
            {
                createGList(&(p->ptr.hp), hsub); // Recursive call
            }

            if (strlen(sub) > 0)
            {
                p->ptr.tp = (GList)malloc(sizeof(GLNode));
                p = p->ptr.tp;
            }

        } while (strlen(sub) > 0);

        p->ptr.tp = NULL; // Tail node is NULL
    }
}

void splitGList(char **sub, char **hsub)
{
    int numBranket = 0;
    int flag = 0;
    for (int i = 0; i < strlen(*sub); i++)
    {
        if ((*sub)[i] == '(')
        {
            numBranket++;
        }
        else if ((*sub)[i] == ')')
        {
            numBranket--;
        }
        if (numBranket == 0 && (*sub)[i] == ',')
        {
            *hsub = (char *)malloc((i + 1) * sizeof(char));
            strncpy(*hsub, *sub, i + 1);
            (*hsub)[i] = '\0';
            *sub = *sub + i + 1;
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        *hsub = (char *)malloc((strlen(*sub) + 1) * sizeof(char));
        strcpy(*hsub, *sub);
        *sub = *sub + strlen(*sub);
    }
}

void printGList(GList L, int d) {
    if (L) {
        if (L->tag == ATOM) {
            printf("%c:Layer%d\n", L->atom, d);
        }
        if (L->tag == LIST) {
            printGList(L->ptr.hp, d + 1);
            printGList(L->ptr.tp, d);
        }
    }
}