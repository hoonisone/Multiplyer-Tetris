#pragma once
#include "node.h"

typedef struct List {
    Node* core;
    int num;
    void (*printFunc)(Data data);
    void (*deleteFunc)(Data data);
    Data* (*copyFunc)(Data data);
} List;

List* listCreate();
int listGetSize(List* list);
static int listIsAccessableByIdx(List* list, int idx);
static Node* listGetCore(List* list);
static Node* listGetNode(List* list, int idx);
static Node* listGetFirstNode(List* list);
static Node* listGetLastNode(List* list);
static void listPushNode(List* list, int idx, Node* node);
static void listPushBackNode(List* list, Node* node);
static void listPopNode(List* list, int idx);
Data listGetElement(List* list, int idx);
void listSetElement(List* list, int idx, Data data);
void listPushElement(List* list, int idx, Data data);
void listPushBackElement(List* list, Data data);
void listPushList(List* subject, int idx, List* object);
void listPushBackList(List* subject, List* object);
void listPopElement(List* list, int idx);
void listDelete(List* list);
void listEmptyOut(List* list);
List* listCopyPartialList(List* list, int from, int to);
void listSort(List* list, int(*compare)(Data a, Data b));
