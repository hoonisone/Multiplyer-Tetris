#pragma once
#include "node.h"
#include "intList.h"
#include "charList.h"
#include "floatList.h"
#include "doubleList.h"
#include "stringList.h"

typedef struct List {
    int num;
    Node* core;

    // external method
    int (*equal)(Data data1, Data data2);
    int (*compare)(Data data1, Data data2);
    void (*print)(Data data);
    void (*del)(Data data);


    // internal method
    int (*getSize)(List* list);
    int (*isEmpty)(List* list);
    // List Calculator
    List* (*copyEmptyList)(List* list);
    List* (*copyPartialList)(List* list, int from, int to);
    //void listReverse(List* list); // ±¸Çö ¾ÈµÊ
    void (*pushList)(List* subject, int idx, List* object);
    void (*pushBackList)(List* subject, List* object);
    void (*emptyOut)(List* list);
    void (*deleteList)(List* list);
    void (*sort)(List* list);

    // Element Calculator
    Data(*getElement)(List* list, int idx);
    void(*setElement)(List* list, int idx, Data data);
    void (*pushElement)(List* list, int idx, Data data);
    void (*pushBackElement)(List* list, Data data);
    void (*popElement)(List* list, int idx);
    int (*findFirstElement)(List* list, Data target);
    int (*countElement)(List* list, Data target);
    void (*printAllElement)(List* list);

    //Function Enroll
    void (*enrollEqual)(List* list, int (*equal)(Data data1, Data data2));
    void (*enrollCompare)(List* list, int (*compare)(Data data1, Data data2));
    void (*enrollPrint)(List* list, void (*print)(Data data));
    void (*enrollDelete)(List* list, void (*del)(Data data));
} List;

// Basic Calculator
List* listCreateList(   int (*equal)(Data data1, Data data2),
                        int (*compare)(Data data1, Data data2),
                        void (*print)(Data data),
                        void (*del)(Data data));