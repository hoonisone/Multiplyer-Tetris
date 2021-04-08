#pragma once
#define NODE_SIZE 100

typedef void* Data;

typedef struct Node {
    Data data;
    struct Node* prev;
    struct Node* next;
} Node;

Node* nodeCreateNode(Data data);
void nodeDeleteNode(Node* node);

Node* nodeGetNextNode(Node* node);
void nodeSetNextNode(Node* node, Node* next);

Node* nodeGetPrevNode(Node* node);
void nodeSetPrevNode(Node* node, Node* prev);

Data nodeGetData(Node* node);
void nodeSetData(Node* node, Data data);
