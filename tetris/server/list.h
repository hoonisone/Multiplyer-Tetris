#pragma once
#include "node.h"

typedef struct List {
    int num;
    Node* core;
    int (*equal)(Data data1, Data data2);
    int (*compare)(Data data1, Data data2);
    void (*print)(Data data);
} List;

// Basic Calculator
List* listCreateList(   int (*equal)(Data data1, Data data2),
                        int (*compare)(Data data1, Data data2),
                        void (*print)(Data data));
int listGetSize(List* list);
int listIsEmpty(List* list);
static int listIsAccessableByIdx(List* list, int idx);
static Node* listGetCore(List* list);
static Node* listGetNode(List* list, int idx);
static Node* listGetFirstNode(List* list);
static Node* listGetLastNode(List* list);
static void listPushNode(List* list, int idx, Node* node);
static void listPushBackNode(List* list, Node* node);
static void listPopNode(List* list, int idx);

List* listCopyEmptyList(List* list);

// Element Calculator
void listEmptyOut(List* list);
Data listGetElement(List* list, int idx);
void listSetElement(List* list, int idx, Data data);
void listPushElement(List* list, int idx, Data data);
void listPushBackElement(List* list, Data data);
void listPopElement(List* list, int idx);

// List Calculator
void listPushList(List* subject, int idx, List* object);
void listPushBackList(List* subject, List* object);
void listDeleteList(List* list);
List* listCopyPartialList(List* list, int from, int to);

void listSort(List* list);
void listEnrollEqual(List* list, int (*equal)(Data data1, Data data2));
void listEnrollCompare(List* list, int (*compare)(Data data1, Data data2));
void listEnrollPrint(List* list, void (*print)(Data data));

static int listDefaultEqual(Data data1, Data data2);
static int listDefaultCompare(Data data1, Data data2);
static int listDefaultPrint(Data data);

int listFindFirstElement(List* list, Data target);
int listCountElement(List* list, Data target);
void listPrintAllElement(List* list);

//void listReverse(List* list); // ±¸Çö ¾ÈµÊ

int ListTestEqual(Data data1, Data data2);
int ListTestCompare(Data data1, Data data2);
void ListTestPrint(Data data);

void ListTestAll();
int ListTestListCountElement();
int ListTestListFindFirstElement();
int ListTestListSort();
int ListTestListPushList();

int listCharEqual(Data data1, Data data2);
int listCharCompare(Data data1, Data data2);
void listCharPrint(Data data);

int listIntEqual(Data data1, Data data2);
int listIntCompare(Data data1, Data data2);
void listIntPrint(Data data);

int listFloatEqual(Data data1, Data data2);
int listFloatCompare(Data data1, Data data2);
void listFloatPrint(Data data);

int listDoubleEqual(Data data1, Data data2);
int listDoubleCompare(Data data1, Data data2);
void listDoublePrint(Data data);

int listStringEqual(Data data1, Data data2);
int listStringCompare(Data data1, Data data2);
void listStringPrint(Data data);