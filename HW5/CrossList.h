/**
 * @file CrossList.h
 * @author MuChengZJU (MuChengZJU@qq.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-13
 * 
 * 
 */

#ifndef CROSSLIST_H
#define CROSSLIST_H

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


int createCrossList(CrossList *Matrix);

int printCrossList(CrossList *Matrix);

int destroyCrossList(CrossList *Matrix);

#endif // CROSSLIST_H