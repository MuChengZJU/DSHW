/**
 * @file GLIst.h
 * @author MuChengZJU (MuChengZJU@qq.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-13
 * 
 * 
 */

#ifndef GLIST_H
#define GLIST_H


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


void createGList(GList *L, char *Str);

void splitGList(char** sub, char** hsub);

void printGList(GList L, int d);

#endif // GLIST_H