#pragma once
#include "node.h"

typedef struct List {
    int num;
    Node* core;
    int (*equal)(Data data1, Data data2);
    int (*compare)(Data data1, Data data2);
    void (*print)(Data data);
    void (*del)(Data data);
} List;

// Basic Calculator
List* listCreateList(   int (*equal)(Data data1, Data data2),
                        int (*compare)(Data data1, Data data2),
                        void (*print)(Data data),
                        void (*del)(Data data));
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



// List Calculator
List* listCopyEmptyList(List* list);
List* listCopyPartialList(List* list, int from, int to);
//void listReverse(List* list); // ±¸Çö ¾ÈµÊ
void listPushList(List* subject, int idx, List* object);
void listPushBackList(List* subject, List* object);
void listEmptyOut(List* list);
void listDeleteList(List* list);
void listSort(List* list);

// Element Calculator
Data listGetElement(List* list, int idx);
void listSetElement(List* list, int idx, Data data);
void listPushElement(List* list, int idx, Data data);
void listPushBackElement(List* list, Data data);
void listPopElement(List* list, int idx);
int listFindFirstElement(List* list, Data target);
int listCountElement(List* list, Data target);
void listPrintAllElement(List* list);

//Function Enroll
void listEnrollEqual(List* list, int (*equal)(Data data1, Data data2));
void listEnrollCompare(List* list, int (*compare)(Data data1, Data data2));
void listEnrollPrint(List* list, void (*print)(Data data));
void listEnrollDelete(List* list, void (*del)(Data data));

// Bacgic Function
int listCharEqual(Data data1, Data data2);
int listCharCompare(Data data1, Data data2);
void listCharPrint(Data data);
void listCharDelete(Data data);

int listIntEqual(Data data1, Data data2);
int listIntCompare(Data data1, Data data2);
void listIntPrint(Data data);
void listIntDelete(Data data);

int listFloatEqual(Data data1, Data data2);
int listFloatCompare(Data data1, Data data2);
void listFloatPrint(Data data);
void listFloatDelete(Data data);

int listDoubleEqual(Data data1, Data data2);
int listDoubleCompare(Data data1, Data data2);
void listDoublePrint(Data data);
void listDoubleDelete(Data data);

int listStringEqual(Data data1, Data data2);
int listStringCompare(Data data1, Data data2);
void listStringPrint(Data data);
void listStringDelete(Data data);

// Test
void ListTestAll();
int ListTestListCountElement();
int ListTestListFindFirstElement();
int ListTestListSort();
int ListTestListPushList();