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


typedef char AtomType; // ԭ�����Ͷ���Ϊcahr*

// ������ͷβ����洢��ʾ
typedef enum {ATOM, LIST} ElemTag;
// ATOM==0��ԭ�ӣ�LIST==1���ӱ�

typedef struct GLNode {
    ElemTag tag;
    // �������֣���������ԭ�ӽ��ͱ���
    union {
        // ԭ�ӽ��ͱ�������ϲ���
        AtomType atom;
        // atom��ԭ�ӽ���ֵ��AtomType��typedef char ����
        struct {
            struct GLNode *hp, *tp;
        } ptr;
        // ptr�Ǳ����ָ����prt.hp��ptr.tp�ֱ�ָ���ͷ�ͱ�β
    };
} *GList, GLNode; // ���������


int createGList(GList L, char *Str);

void splitGList(char** sub, char** hsub);

void printGList(GList L, int d);

#endif // GLIST_H