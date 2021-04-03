#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "node.h"
#include "error.h"

List* listCreate() {
	List* newList = (List*)malloc(sizeof(List));
	newList->core = nodeCreateNode(0);
	newList->core->next = newList->core;
	newList->core->prev = newList->core;
	newList->num = 0;
	return newList;
}
int listGetSize(List * list) {
	if (list == NULL){
		errorPrint("The parameter \"list\" does not exist");
	}
	else{
		return list->num;
	}
}

static int listIsAccessableByIdx(List* list, int idx) {
	if (0 <= idx && idx < listGetSize(list)){
		return 1;
	}
	else{
		return 0;
	}
}
static Node* listGetCore(List* list) {
	if (list == NULL) {
		errorPrint("The parameter \"list\" does not exist");
	}
	else {
		return list->core;
	}
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
	return listGetNode(list, 0);
}
static Node* listGetLastNode(List* list) {
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
	Node* targetNode = listGetCore(list);
	Node* prevNode = nodeGetPrevNode(targetNode);
	
	nodeSetNextNode(prevNode, node);
	nodeSetPrevNode(node, prevNode);
	nodeSetNextNode(node, targetNode);
	nodeSetPrevNode(targetNode, node);
	list->num++;
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
void listPushList(List* subject, int idx, List* object) {
	Data data;
	int objectSize = listGetSize(object);
	for (int i = 0 ; i < objectSize; i++) {
		data = listGetElement(object, objectSize-1);
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

void listPopElement(List* list, int idx) {
	listPopNode(list, idx);
}

void listDelete(List* list) {
	listEmptyOut(list);
	free(list);
}

void listEmptyOut(List* list) {
	while (listGetSize(list)) {
		listPopElement(list, 0);
	}
}

List* listCopyPartialList(List* list, int from, int to) {
	if (!listIsAccessableByIdx(list, from)) {
		errorPrint("The parameter \"from\" is out of range");
	}
	else if(!listIsAccessableByIdx(list, to)){
		errorPrint("The parameter \"to\" is out of range");
	}
	else if (from > to) {
		errorPrint("The parameter to must less then the parameter to");
	}
	else {
		List* newList = listCreate();
		for (int idx = from; idx <= to; idx++) {
			Data data = listGetElement(list, idx);
			listPushBackElement(newList, data);
		}
		return newList;
	}
}

void listSort(List* list, int(*compare)(Data a, Data b)) {
	if (list == NULL) {
		errorPrint("The parameter \"list\" does not exist");
	}
	else if(compare == NULL){
		errorPrint("The parameter \"compare\" is NULL");
	}
	int size = listGetSize(list);
	if (size == 1) {
		return;
	} 
	else if (size == 2) {
		int first = listGetElement(list, 0);
		int last = listGetElement(list, 1);
		if (!compare(first, last)) {
			listPopElement(list, 0);
			listPushBackElement(list, first);
		}
		return;
	}
	else {
		int size = listGetSize(list);
		List* leftList = listCopyPartialList(list, 0, size/2);
		List* rightList = listCopyPartialList(list, size/2+1, size-1);
		listSort(leftList, compare);
		listSort(rightList, compare);
		listEmptyOut(list);
		listPushBackList(list, leftList);
		listPushBackList(list, rightList);
		listPushBackList(leftList, rightList);
	}
}
