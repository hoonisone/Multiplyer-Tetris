#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "node.h"
#include "error.h"
#include "utill.h"
#include "test.h"

static int listIsAccessableByIdx(List* list, int idx);
static Node* listGetCore(List* list);
static Node* listGetNode(List* list, int idx);
static Node* listGetFirstNode(List* list);
static Node* listGetLastNode(List* list);
static void listPushNode(List* list, int idx, Node* node);
static void listPushBackNode(List* list, Node* node);
static void listPopNode(List* list, int idx);

static int listGetSize(List* list);
static int listIsEmpty(List* list);
// List Calculator
static List* listCopyEmptyList(List* list);
static List* listCopyPartialList(List* list, int from, int to);
//void listReverse(List* list); // 구현 안됨
static void listPushList(List* subject, int idx, List* object);
static void listPushBackList(List* subject, List* object);
static void listEmptyOut(List* list);
static void listDeleteList(List* list);
static void listSort(List* list);

// Element Calculator
static Data listGetElement(List* list, int idx);
static void listSetElement(List* list, int idx, Data data);
static void listPushElement(List* list, int idx, Data data);
static void listPushBackElement(List* list, Data data);
static void listPopElement(List* list, int idx);
static int listFindFirstElement(List* list, Data target);
static int listCountElement(List* list, Data target);
static void listPrintAllElement(List* list);

//Function Enroll
static void listEnrollEqual(List* list, int (*equal)(Data data1, Data data2));
static void listEnrollCompare(List* list, int (*compare)(Data data1, Data data2));
static void listEnrollPrint(List* list, void (*print)(Data data));
static void listEnrollDelete(List* list, void (*del)(Data data));

static void listFillInternalMethod(List* list);

List* createList(	int (*equal)(Data data1, Data data2),
						int (*compare)(Data data1, Data data2),
						void (*print)(Data data),
						void (*del)(Data data))
{
	List* newList = (List*)malloc(sizeof(List));
	newList->core = nodeCreateNode(0);
	newList->core->next = newList->core;
	newList->core->prev = newList->core;
	newList->num = 0;
	newList->equal = equal;
	newList->compare = compare;
	newList->print = print;
	newList->del = del;

	listFillInternalMethod(newList);
	return newList;
}

void listFillInternalMethod(List * list) {	// make function like method
	list->getSize			= listGetSize;
	list->isEmpty			= listIsEmpty;
	list->copyEmptyList		= listCopyEmptyList;
	list->copyPartialList	= listCopyPartialList;
	list->pushList			= listPushList;
	list->pushBackList		= listPushBackList;
	list->emptyOut			= listEmptyOut;
	list->deleteList		= listDeleteList;
	list->sort				= listSort;
	list->getElement		= listGetElement;
	list->setElement		= listSetElement;
	list->pushElement		= listPushElement;
	list->pushBackElement	= listPushBackElement;
	list->popElement		= listPopElement;
	list->findFirstElement	= listFindFirstElement;
	list->countElement		= listCountElement;
	list->printAllElement	= listPrintAllElement;
	list->enrollEqual		= listEnrollEqual;
	list->enrollCompare		= listEnrollCompare;
	list->enrollPrint		= listEnrollPrint;
	list->enrollDelete		= listEnrollDelete;
}

int listGetSize(List * list) {
	if (list == NULL){
		errorPrint("The parameter \"list\" does not exist");
	}
	return list->num;
}
int listIsEmpty(List* list) {
	if (list == NULL) {
		errorPrint("The parameter \"list\" does not exist");
	}
	return listGetSize(list) == 0;
}
static int listIsAccessableByIdx(List* list, int idx) {
	if (list == NULL) {
		errorPrint("The parameter \"list\" does not exist");
	}
	else if (0 <= idx && idx < listGetSize(list)){
		return 1;
	}
	return 0;

}
static Node* listGetCore(List* list) {
	if (list == NULL) {
		errorPrint("The parameter \"list\" does not exist");
	}
	return list->core;
}
static Node* listGetNode(List* list, int idx) {
	if (list == NULL){
		errorPrint("The parameter \"list\" does not exist");
	}
	else if (!listIsAccessableByIdx(list, idx)){
		errorPrint("The parameter \"idx\" is out of range");
	}
	else{
		Node* node = listGetCore(list);
		int lastIdx = listGetSize(list) - 1;
		int left = idx+1;
		int right = lastIdx - idx+1;

		if (left <= right) {				// 왼쪽에서 접근하는 경우
			for (int i = 0; i < left; i++)
				node = nodeGetNextNode(node);
		}
		else {								// 오른쪽에서 접근하는 경우
			for (int i = 0; i < right; i++)
				node = nodeGetPrevNode(node);
		}
		return node;
	}
}
static Node* listGetFirstNode(List* list) {
	if (list == NULL) {
		errorPrint("The parameter \"list\" does not exist");
	}
	return listGetNode(list, 0);

}
static Node* listGetLastNode(List* list) {
	if (list == NULL) {
		errorPrint("The parameter \"list\" does not exist");
	}
	return listGetNode(list, listGetSize(list) - 1);
}
static void listPushNode(List* list, int idx, Node* node) {
	if (list == NULL) {
		errorPrint("The parameter \"list\" does not exist");
	}
	else if (!listIsAccessableByIdx(list, idx)) {
		errorPrint("The parameter \"idx\" is out of range");
	}
	else if (node == NULL) {
		errorPrint("The parameter \"node\" is out of range");
	}
	else {
		Node* targetNode = listGetNode(list, idx);
		Node* prevNode = nodeGetPrevNode(targetNode);
		nodeSetNextNode(prevNode, node);
		nodeSetPrevNode(node, prevNode);
		nodeSetNextNode(node, targetNode);
		nodeSetPrevNode(targetNode, node);
		list->num++;
	}
}
static void listPushBackNode(List* list, Node* node) {
	if (list == NULL) {
		errorPrint("The parameter \"list\" does not exist");
	}
	else if (node == NULL) {
		errorPrint("The parameter \"node\" is out of range");
	}
	else {
		Node* targetNode = listGetCore(list);
		Node* prevNode = nodeGetPrevNode(targetNode);

		nodeSetNextNode(prevNode, node);
		nodeSetPrevNode(node, prevNode);
		nodeSetNextNode(node, targetNode);
		nodeSetPrevNode(targetNode, node);
		list->num++;
	}
}
static void listPopNode(List* list, int idx) {
	if (list == NULL) {
		errorPrint("The parameter \"list\" does not exist");
	}
	else if (!listIsAccessableByIdx(list, idx)) {
		errorPrint("The parameter \"idx\" is out of range");
	}
	else {
		Node* targetNode = listGetNode(list, idx);
		Node* prevNode = nodeGetPrevNode(targetNode);
		Node* nextNode = nodeGetNextNode(targetNode);
		nodeSetNextNode(prevNode, nextNode);
		nodeSetPrevNode(nextNode, prevNode);
		nodeDeleteNode(targetNode);
		list->num--;
	}
}



List* listCopyEmptyList(List* list) {
	return createList(list->equal, list->compare, list->print, list->del);
}
List* listCopyPartialList(List* list, int from, int to) {
	if (!listIsAccessableByIdx(list, from)) {
		errorPrint("The parameter \"from\" is out of range");
	}
	else if (!listIsAccessableByIdx(list, to)) {
		errorPrint("The parameter \"to\" is out of range");
	}
	else if (from > to) {
		errorPrint("The parameter to must less then the parameter to");
	}
	else {
		List* newList = listCopyEmptyList(list);
		for (int idx = from; idx <= to; idx++) {
			Data data = listGetElement(list, idx);
			listPushBackElement(newList, data);
		}
		return newList;
	}
}
void listPushList(List* subject, int idx, List* object) {
	Data data;
	int objectSize = listGetSize(object);
	for (int i = 0 ; i < objectSize; i++) {
		data = listGetElement(object, objectSize-1-i);
		listPushElement(subject, idx, data);
	}
}
void listPushBackList(List* subject, List* object) {
	int size = listGetSize(object);
	for (int i = 0; i < size; i++) {
		Data data = listGetElement(object, i);
		listPushBackElement(subject, data);
	}
}
void listEmptyOut(List* list) {
	while (listGetSize(list)) {
		listPopElement(list, 0);
	}
}
void listDeleteList(List* list) {
	listEmptyOut(list);
	free(list);
}
void listSort(List* list) {
	int(*compare)(Data data1, Data data2) = list->compare;
	if (list == NULL) {
		errorPrint("The parameter \"list\" does not exist");
	}
	else if (compare == NULL) {
		errorPrint("The parameter \"compare\" is NULL");
	}
	int size = listGetSize(list);
	if (size == 1) {
		return;
	}
	else if (size == 2) {
		Data first = listGetElement(list, 0);
		Data last = listGetElement(list, 1);
		if (!compare(first, last)) {
			listPopElement(list, 0);
			listPushBackElement(list, first);
		}
		return;
	}
	else {
		int size = listGetSize(list);
		List* leftList = listCopyPartialList(list, 0, size / 2);
		List* rightList = listCopyPartialList(list, size / 2 + 1, size - 1);
		listSort(leftList);
		listSort(rightList);
		listEmptyOut(list);
		while (!listIsEmpty(leftList) && !listIsEmpty(rightList)) {
			Data leftFirst = listGetElement(leftList, 0);
			Data rightFirst = listGetElement(rightList, 0);
			if (compare(leftFirst, rightFirst)) {
				listPushBackElement(list, leftFirst);
				listPopElement(leftList, 0);
			}
			else {
				listPushBackElement(list, rightFirst);
				listPopElement(rightList, 0);
			}
		}
		if (!listIsEmpty(leftList)) {
			listPushBackList(list, leftList);
		}
		else {
			listPushBackList(list, rightList);
		}
	}
}


Data listGetElement(List* list, int idx) {
	Node* node = listGetNode(list, idx);
	return nodeGetData(node);
}
void listSetElement(List* list, int idx, Data data) {
	Node* node = listGetNode(list, idx);
	nodeSetData(node, data);
}
void listPushElement(List* list, int idx, Data data) {
	Node* newNode = nodeCreateNode(data);
	listPushNode(list, idx, newNode);
}
void listPushBackElement(List* list, Data data) {
	Node* newNode = nodeCreateNode(data);
	listPushBackNode(list, newNode);
}
void listPopElement(List* list, int idx) {
	listPopNode(list, idx);
}
int  listFindFirstElement(List* list, Data target) {
	int (*equal)(Data data1, Data data2) = list->equal;
	if (list == NULL) {
		errorPrint("The parameter \"list\" does not exist");
	}
	else if (equal == NULL) {
		errorPrint("The parameter \"compare\" is NULL");
	}

	int idx = -1;
	for (int i = 0; i < listGetSize(list); i++) {
		Data value = listGetElement(list, i);
		if (equal(value, target)) {
			return i;
		}
	}
	return -1;
}
int  listCountElement(List* list, Data target) {
	int (*equal)(Data data1, Data data2) = list->equal;
	if (list == NULL) {
		errorPrint("The parameter \"list\" does not exist");
	}
	else if (equal == NULL) {
		errorPrint("The parameter \"compare\" is NULL");
	}
	int count = 0;
	for (int i = 0; i < listGetSize(list); i++) {
		Data value = listGetElement(list, i);
		if (equal(value, target)) {
			count++;
		}
	}
	return count;
}
void listPrintAllElement(List* list) {
	if (list == NULL) {
		errorPrint("list is NULL");
	}

	void (*print)(Data data) = list->print;
	if (print == NULL) {
		errorPrint("equalCompare is NULL");
	}

	int size = listGetSize(list);
	if (size == 0) {
		printf("Empty!!!");
	}
	else {
		printf("[");
		for (int i = 0; i < listGetSize(list) - 1; i++) {
			print(listGetElement(list, i));
			printf(", ");
		}
		print(listGetElement(list, size - 1));
		printf("]");
	}
}


void listEnrollEqual(List* list, int (*equal)(Data data1, Data data2)) {
	if (list == NULL) {
		errorPrint("list is Null");
	}
	else if (equal == NULL) {
		errorPrint("equalCompare is Null");
	}
	else {
		list->equal = equal;
	}
}
void listEnrollCompare(List* list, int (*compare)(Data data1, Data data2)) {
	if (list == NULL) {
		errorPrint("list is NULL");
	}
	if (compare == NULL) {
		errorPrint("equalCompare is NULL");
	}

	list->compare = compare;

}
void listEnrollPrint(List* list, void (*print)(Data data)) {
	if (list == NULL) {
		errorPrint("list is Null");
	}
	if (print == NULL) {
		errorPrint("equalCompare is NULL");
	}
	list->print = print;
}
void listEnrollDelete(List* list, void (*del)(Data data)) {
	if (list == NULL) {
		errorPrint("list is Null");
	}
	if (del == NULL) {
		errorPrint("equalCompare is NULL");
	}
	list->del = del;
}

//listCreateList(listStringEqual, listStringCompare, listStringPrint);


void ListPrintState(List* list) {
	printf("listState:\n");
	printf("\tsize: %d\n", listGetSize(list));
	printf("\telements: ");
	listPrintAllElement(list);
}

