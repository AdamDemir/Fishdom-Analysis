struct Date{
    int day;
    int month;
    int year;
};
struct FishData{
    char name[80];
    char city[80];
    int weight;
    double length;
    struct Date date;
};
typedef struct Node * AVLTree;
struct Node {
    struct FishData data;
    struct Node * next;
    AVLTree left;
    AVLTree right;
    int height;
};
struct Nodelist{
    int size;
    AVLTree head;
    AVLTree tail;
};
AVLTree CreateTree(void);
AVLTree MakeEmptyTree(AVLTree);
AVLTree InsertElement(struct FishData data, AVLTree  *t);
AVLTree SingleRotateWithLeft(AVLTree);
AVLTree SingleRotateWithRight(AVLTree);
AVLTree DoubleRotateWithLeft(AVLTree);
AVLTree DoubleRotateWithRight(AVLTree);
void DisplayTree(AVLTree  *t);
void DisplayTreeStructure(AVLTree, int);
int AVLTreeHeight(AVLTree);
int Max(int, int);




#ifndef ASSIGNMENT_AVLTREE_H
#define ASSIGNMENT_AVLTREE_H




#endif //ASSIGNMENT_AVLTREE_H