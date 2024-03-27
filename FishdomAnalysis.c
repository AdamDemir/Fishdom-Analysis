#include <stdio.h>
#include <stdlib.h>
#include "avltree.h"


AVLTree insertFish(struct FishData data, AVLTree *t);
AVLTree insertFishAALength(struct FishData data, AVLTree *t);

//read data read the file and create an AVL tree
AVLTree readData(char *FileName);

// print the information of the heaviest Fish
void heaviestFish(AVLTree t);

// Print the full index of the fishdom
void displayIndex(AVLTree *t);

//  return the information of the longest fish
void findMaxLength(AVLTree t);


int main() {
    char name[] = "fishes.txt";
    printf("Hello, World!\n");
    int option = 0;
    AVLTree t =readData(name);
    do {
        printf("*******************************************\n"
               "Menu\n"
               "1. Display the full index of fishdom\n"
               "2. Display the heaviest fishes\n"
               "3. Display the longest fishes\n"
               "4. Exit\n"
               "*******************************************\n");
        printf("Enter your option:");
        scanf("%d", &option);


        switch (option) {
            case 1:
                displayIndex(&t);
                break;
            case 2: {
                heaviestFish(t);
            }
                break;
            case 3:
                findMaxLength(t);
                break;
            case 4:
                printf("Bye");
                break;


            default:
                printf("Enter a valid value please!");
        }
    } while (option != 4);
    return 0;
}


AVLTree readData(char FileName[]) {
    FILE *infile;
    AVLTree t,t1;
    infile = fopen(FileName, "r");
    if (infile == NULL) {
        printf("Error while opening the file");
        printf("%s", FileName);
        exit(1);
    }
    struct FishData data;


    t = CreateTree();
    t1 = CreateTree();
    while (fscanf(infile, "%79[^,],%d,%lf,%d/%d/%d,%s\n", data.name, &data.weight,
                  &data.length, &data.date.day, &data.date.month, &data.date.year, data.city) != EOF) {
        insertFish(data, &t);
        insertFishAALength(data,&t1);
    }


    return t;
}


AVLTree insertFish(struct FishData data, AVLTree *t) {


    if ((*t) == NULL) {
        /*Create and return a one-node tree */
        (*t) = (AVLTree) malloc(sizeof(struct Node));
        if (*t == NULL)
            printf("Out of memory space!!!\n");
        else {
            (*t)->data = data;
            (*t)->height = 0;
            (*t)->left = (*t)->right = (*t)->next = NULL;


        }
    } else if (data.weight < (*t)->data.weight) {
        (*t)->left = insertFish(data, &((*t)->left));




        if (AVLTreeHeight((*t)->left) - AVLTreeHeight((*t)->right) == 2)
            if (data.weight < (*t)->left->data.weight) {
                *t = SingleRotateWithRight((*t));
            } else {
                (*t)->left = DoubleRotateWithRight((*t)->left);
                (*t) = SingleRotateWithRight((*t));
            }
    } else if (data.weight > (*t)->data.weight) {
        (*t)->right = insertFish(data, &(*t)->right);
        if (AVLTreeHeight((*t)->right) - AVLTreeHeight((*t)->left) == 2)
            if (data.weight > (*t)->right->data.weight)
                (*t) = SingleRotateWithLeft((*t));
            else {
                (*t)->right = DoubleRotateWithLeft((*t)->right);
                (*t) = SingleRotateWithLeft((*t));
            }
            // handle the case when the weight of the fishes are the same
    } else if (data.weight == (*t)->data.weight) {
        AVLTree tmp = (*t);
        if (tmp->next == NULL) {
            tmp->next = (struct Node *) malloc(sizeof(struct Node));
            if (tmp->next == NULL) {
                printf("Out of memory space!!!\n");
            } else {
                tmp->next->data = data;
                tmp->next->next = NULL;
            }
        } else {
            while (tmp != NULL) {
                tmp = tmp->next;
            }


            tmp->next = (struct Node *) malloc(sizeof(struct Node));
            if (tmp->next == NULL) {
                printf("Out of memory space!!!\n");
            } else {
                tmp->next->data = data;
                tmp->next->next = NULL;
            }
        }
    }


    (*t)->height = Max(AVLTreeHeight((*t)->left), AVLTreeHeight((*t)->right)) + 1;
    return *t;


}
AVLTree insertFishAALength(struct FishData data, AVLTree *t) {


    if ((*t) == NULL) {
        /*Create and return a one-node tree */
        (*t) = (AVLTree) malloc(sizeof(struct Node));
        if (*t == NULL)
            printf("Out of memory space!!!\n");
        else {
            (*t)->data = data;
            (*t)->height = 0;
            (*t)->left = (*t)->right = (*t)->next = NULL;


        }
    } else if (data.length < (*t)->data.length) {
        (*t)->left = insertFish(data, &((*t)->left));




        if (AVLTreeHeight((*t)->left) - AVLTreeHeight((*t)->right) == 2)
            if (data.length < (*t)->left->data.length) {
                *t = SingleRotateWithRight((*t));
            } else {
                (*t)->left = DoubleRotateWithRight((*t)->left);
                (*t) = SingleRotateWithRight((*t));
            }
    } else if (data.length > (*t)->data.length) {
        (*t)->right = insertFish(data, &(*t)->right);
        if (AVLTreeHeight((*t)->right) - AVLTreeHeight((*t)->left) == 2)
            if (data.length > (*t)->right->data.length)
                (*t) = SingleRotateWithLeft((*t));
            else {
                (*t)->right = DoubleRotateWithLeft((*t)->right);
                (*t) = SingleRotateWithLeft((*t));
            }
    } else if (data.length == (*t)->data.length) {
        AVLTree tmp = (*t);
        if (tmp->next == NULL) {
            tmp->next = (struct Node *) malloc(sizeof(struct Node));
            if (tmp->next == NULL) {
                printf("Out of memory space!!!\n");
            } else {
                tmp->next->data = data;
                tmp->next->next = NULL;
            }
        } else {
            while (tmp != NULL) {
                tmp = tmp->next;
            }


            tmp->next = (struct Node *) malloc(sizeof(struct Node));
            if (tmp->next == NULL) {
                printf("Out of memory space!!!\n");
            } else {
                tmp->next->data = data;
                tmp->next->next = NULL;
            }
        }
    }


    (*t)->height = Max(AVLTreeHeight((*t)->left), AVLTreeHeight((*t)->right)) + 1;
    return *t;


}
void displayIndex(AVLTree *t) {
    AVLTree tmpTree = (*t);
    struct Node *tmp;
    if (tmpTree != NULL) {
        displayIndex(&(tmpTree)->left);
        printf("%-20s%-10d%-10.2lf%02d/%02d/%-10d%-10s\n\n", tmpTree->data.name, tmpTree->data.weight,
               tmpTree->data.length,
               tmpTree->data.date.day, tmpTree->data.date.month, tmpTree->data.date.year, tmpTree->data.city);
        tmp = tmpTree->next;
        while (tmp != NULL) {
            printf("%-20s%-10d%-10.2lf%02d/%02d/%-10d%-10s\n\n", tmp->data.name, tmp->data.weight, tmp->data.length,
                   tmp->data.date.day, tmp->data.date.month, tmp->data.date.year, tmp->data.city);
            tmp = tmp->next;
        }
        displayIndex(&(tmpTree)->right);
    } else {
        //printf("Tree is null\n");
    }


}


void heaviestFish(AVLTree t) {
    if (t == NULL) {
        printf("The tree is empty.\n");
        exit(1);
    }
    AVLTree tmp = t;
    while (tmp->right != NULL) {
        tmp = tmp->right;


    }
    printf("%-20s%-10d%-10.2lf%02d/%02d/%-10d%-10s\n", tmp->data.name, tmp->data.weight,
           tmp->data.length,
           tmp->data.date.day, tmp->data.date.month, tmp->data.date.year, tmp->data.city);
}
// the complexity is O(n) I don't think there can be a better search algorthim

void findMaxLength(AVLTree t) {
    if (t == NULL) {
        printf("The tree is empty.\n");
        exit(1);
    }
    AVLTree tmp = t;
    while (tmp->right != NULL) {
        tmp = tmp->right;


    }
    printf("%-20s%-10d%-10.2lf%02d/%02d/%-10d%-10s\n", tmp->data.name, tmp->data.weight,
           tmp->data.length,
           tmp->data.date.day, tmp->data.date.month, tmp->data.date.year, tmp->data.city);
}
// the complexity is O(n) I don't think there can be a better search algorithm
// though I sacrificed a lot of space for performance here initializing a whole new tree
// I could've done an in-order Traversal with time complexity O(log n)
