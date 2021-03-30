#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "error.h"

Node* nodeCreateNode(Data data) {
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = newNode->prev = NULL;
    return newNode;
}
void nodeDeleteNode(Node* node) {
    if (node == NULL) {
        errorPrint("The parameter \"node\" is NULL");
    }
    else {
        free(node);
    }
}
Node* nodeGetNextNode(Node* node) {
    return node->next;
}
void nodeSetNextNode(Node* node, Node* next) {
    if (node == NULL) {
        errorPrint("The parameter \"node\" is NULL");
    }
    else {
        node->next = next;
    }
}
Node* nodeGetPrevNode(Node* node) {
    return node->prev;
}
void nodeSetPrevNode(Node* node, Node* prev) {
    if (node == NULL) {
        errorPrint("The parameter \"node\" is NULL");
    }
    else {
        node->prev = prev;
    }
}
Data nodeGetData(Node* node) {
    if (node == NULL) {
        errorPrint("The parameter \"node\" is NULL");
    }
    else {
        return node->data;
    }
}
void nodeSetData(Node* node, Data data) {
    if (node == NULL) {
        errorPrint("The parameter \"node\" is NULL");
    }
    else {
        node->data = data;
    }
}