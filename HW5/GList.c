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


int createGList(GList L, char *str) {
    if (str[2] == '\0') { // Empty String "()"
        L = NULL;
        return 1;
    } else {
        L = (GList)malloc(sizeof(GLNode));
        L->tag = LIST;
        GList p = L;
        // Remove brackets of Str to sub
        char *sub = (char *)malloc(strlen(str-1) * sizeof(char));
        strncpy(sub, str+1, strlen(str)-2);
        sub[strlen(str)-2] = '\0';
        printf("sub: %s\n", sub);

        do {
            // Take out hsub before ',' from sub
            char subCopy[strlen(sub)];
            strcpy(subCopy, sub);
            char *hsub = strtok(subCopy, ",");
            printf("hsub: %s\n", hsub);
            // Create GList p->ptr.hp from hsub
            if (strlen(hsub) == 1) {
                p->ptr.hp = (GList)malloc(sizeof(GLNode));
                p->ptr.hp->tag = ATOM;
                p->ptr.hp->atom = hsub[0];
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

