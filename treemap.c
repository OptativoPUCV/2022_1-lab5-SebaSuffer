#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap * new = (TreeMap *) malloc (sizeof(TreeMap));
    new->root = NULL;
    new->current = NULL;
    new->lower_than = lower_than;
    return new;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
    TreeNode * nodo = tree->root;
    TreeNode * newNode = createTreeNode(key,value);
    
    while (nodo != NULL){
        tree->current = nodo;
        if (is_equal(tree, nodo->pair->key, key) == 1){
            return;
        }
        else if (tree->lower_than(key, nodo->pair->key) == 1){
            nodo = nodo->left;
        }
        else if (tree->lower_than(nodo->pair->key, key) == 1)
            nodo = nodo->right;
    }
    
    if (tree->lower_than(tree->current->pair->key, key)== 1){
        tree->current->right = newNode;
        tree->current = newNode->parent;
        tree->current = newNode;
    }
    else if (tree->lower_than(key, tree->current->pair->key)== 1){
        tree->current->left = newNode;
        newNode->parent = tree->current;
        tree->current = newNode;
    }
}

TreeNode * minimum(TreeNode * x){
    if (x->left == NULL)
        return x;
    while (x->left != NULL){
        x = x->left;
    }
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    TreeNode * nodo = tree->root;
    while (nodo != NULL){
        if (tree->lower_than(key, nodo->pair->key) == 1){
            nodo = nodo->left;
        }
        else if (tree->lower_than(nodo->pair->key, key) == 1){
            nodo = nodo->right;
        }else{
            tree->current = nodo;
            return nodo->pair;
        }      
    }
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    tree->current = minimum(tree->root);
    return tree->current->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
    //if (tree->current->right != NULL)
        //tree->current = minimum(tree->current->right);
    //else if (tree->current->parent != NULL)
        //tree->current = minimun(tree->current->parent);
    //return tree->current->pair;
    return NULL;
}
