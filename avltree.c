#include <stdio.h>
#include <stdlib.h>
#include "avltree.h"




AVLTree CreateTree(void) {
    return NULL;
}




AVLTree MakeEmptyTree(AVLTree t) {
    if (t != NULL) {
        MakeEmptyTree(t->left);
        MakeEmptyTree(t->right);
        free(t);
    }
    return NULL;
}








void DisplayTreeStructure(AVLTree t, int depth) {
    int i;




    if (t != NULL) {
        DisplayTreeStructure(t->right, depth + 1);




        for (i = 0; i < depth; i++)
            printf("     ");
        printf("%-10s,%-5d,%-5f,%d/%d/%d,%-10s\n", t->data.name, t->data.weight, t->data.length,
               t->data.date.day, t->data.date.month, t->data.date.year, t->data.city);




        DisplayTreeStructure(t->left, depth + 1);
    }
}




int AVLTreeHeight(AVLTree t) {
    if (t == NULL)
        return -1;
    else
        return t->height;
}




AVLTree SingleRotateWithLeft(AVLTree k2) {
    struct Node *x = k2->right;
    struct Node *T2 = x->left;




    x->left = k2;
    k2->right = T2;




    k2->height = Max(AVLTreeHeight(k2->left), AVLTreeHeight(k2->right)) + 1;
    x->height = Max(AVLTreeHeight(x->left), AVLTreeHeight(x->right)) + 1;




    return x;
}




AVLTree SingleRotateWithRight(AVLTree k1) {
    AVLTree y = k1->left;
    AVLTree T2 = y->right;




    // Perform rotation
    y->right = k1;
    k1->left = T2;




    // Update heights
    k1->height = Max(AVLTreeHeight(k1->left), AVLTreeHeight(k1->right)) + 1;
    y->height = Max(AVLTreeHeight(y->left), AVLTreeHeight(y->right)) + 1;




    return y;
}




AVLTree DoubleRotateWithLeft(AVLTree k3) {
    k3->left = SingleRotateWithLeft(k3->left);
    return SingleRotateWithRight(k3);
}




AVLTree DoubleRotateWithRight(AVLTree k3) {
    k3->right = SingleRotateWithRight(k3->right);
    return SingleRotateWithLeft(k3);
}




int Max(int x, int y) {
    if (x >= y)
        return x;
    else
        return y;
}


