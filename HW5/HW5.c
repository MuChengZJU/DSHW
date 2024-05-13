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

#include "CrossList.h"
#include "GList.h"


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
                // ����Ԫ����ʽ�����ʮ�������ʾ��ϡ������з���Ԫ�ؼ����±���㷨
                // ERROR: INDEX STARTS FROM 0!!!
                {
                    CrossList Matrix;
                    createCrossList(&Matrix);
                    printCrossList(&Matrix);
                    // destroyCrossList(&Matrix); //TODO: Memory Leak
                }
                break;
            case 2:
                // 5.33
                // �ݹ��㷨����������������ԭ��������ڵĲ��
                {
                    char *str = "(a,(b,c))";
                    GList L = NULL;
                    createGList(L, str);
                    printGList(L, 0);
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
