#include <stdio.h>
#include "list_test.h"
#include "test.h"

// Test(Data = int)
int ListTestEqual(Data data1, Data data2) {
	return (data1 == data2);
}
int ListTestCompare(Data data1, Data data2) {
	return (data1 < data2);
}
void ListTestPrint(Data data) {
	printf("%d", data);
}
void ListPrintState(List* list) {
	printf("listState:\n");
	printf("\tsize: %d\n", listGetSize(list));
	printf("\telements: ");
	listPrintAllElement(list);
}

void ListTestAll() {
	TestStart();
	Test("CountElement()", ListTestListCountElement);
	Test("FindFirstElement()", ListTestListFindFirstElement);
	Test("ListSort()", ListTestListSort);
	Test("ListPushList", ListTestListPushList);

	TestEnd();
}

int ListTestListCountElement() {
	List* list = listCreateList(ListTestEqual, ListTestCompare, ListTestPrint);

	listPushBackElement(list, 1);
	listPushBackElement(list, 1);
	listPushBackElement(list, 1);
	listPushBackElement(list, 2);
	listPushBackElement(list, 1);
	listPushBackElement(list, 1);
	listPushBackElement(list, 2);

	if (listCountElement(list, 1) != 5) return 0;
	if (listCountElement(list, 2) != 2) return 0;

	return 1;
}

int ListTestListFindFirstElement() {
	List* list = listCreateList(ListTestEqual, ListTestCompare, ListTestPrint);
	listPushBackElement(list, 1);
	listPushBackElement(list, 1);
	listPushBackElement(list, 1);
	listPushBackElement(list, 2);
	listPushBackElement(list, 1);
	listPushBackElement(list, 1);
	listPushBackElement(list, 2);
	
	if (listFindFirstElement(list, 2) != 3) return 0;

	return 1;
}

int ListTestListSort() {
	List* list = listCreateList(ListTestEqual, ListTestCompare, ListTestPrint);
	listPushBackElement(list, 3);
	listPushBackElement(list, 5);
	listPushBackElement(list, 1);
	listPushBackElement(list, 2);
	listPushBackElement(list, 7);
	listPushBackElement(list, 6);
	listPushBackElement(list, 4);
	listSort(list);

	if (listGetElement(list, 0) != 1) return 0;
	if (listGetElement(list, 1) != 2) return 0;
	if (listGetElement(list, 2) != 3) return 0;
	if (listGetElement(list, 3) != 4) return 0;
	if (listGetElement(list, 4) != 5) return 0;
	if (listGetElement(list, 5) != 6) return 0;
	if (listGetElement(list, 6) != 7) return 0;
	if (listGetSize(list) != 7) return 0;

	return 1;
}

int ListTestListPushList() {
	List* list1 = listCreateList(ListTestEqual, ListTestCompare, ListTestPrint);
	listPushBackElement(list1, 1);
	listPushBackElement(list1, 2);
	listPushBackElement(list1, 3);
	listPushBackElement(list1, 4);
	listPushBackElement(list1, 5);
	listPushBackElement(list1, 6);
	listPushBackElement(list1, 7);
	
	List* list2 = listCreateList(ListTestEqual, ListTestCompare, ListTestPrint);
	listPushBackElement(list2, 1);
	listPushBackElement(list2, 2);
	listPushBackElement(list2, 3);
	listPushBackElement(list2, 4);

	
	int total = listGetSize(list1) + listGetSize(list2);
	listPushBackList(list1, list2);

	if (listGetSize(list1) != total) return 0;
	if (listGetElement(list1, 7 ) != 1) return 0;
	if (listGetElement(list1, 8 ) != 2) return 0;
	if (listGetElement(list1, 9 ) != 3) return 0;
	if (listGetElement(list1, 10) != 4) return 0;

	return 1;
}