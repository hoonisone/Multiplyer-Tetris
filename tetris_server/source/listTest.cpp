#include "list.h"
#include "test.h"
#include "utill.h"
#include "listTest.h"

void ListTestAll() {
	TestStart();
	Test("CountElement()", ListTestListCountElement);
	Test("FindFirstElement()", ListTestListFindFirstElement);
	Test("ListSort()", ListTestListSort);
	Test("ListPushList", ListTestListPushList);

	TestEnd();
}
int ListTestListCountElement() {
	List* list = listCreateList(listIntEqual, listIntCompare, listIntPrint, listIntDelete);

	list->pushBackElement(list, newInt(1));
	list->pushBackElement(list, newInt(1));
	list->pushBackElement(list, newInt(1));
	list->pushBackElement(list, newInt(2));
	list->pushBackElement(list, newInt(1));
	list->pushBackElement(list, newInt(1));
	list->pushBackElement(list, newInt(2));

	if (list->countElement(list, newInt(1)) != 5) return 0;
	if (list->countElement(list, newInt(2)) != 2) return 0;

	return 1;
}
int ListTestListFindFirstElement() {
	List* list = listCreateList(listIntEqual, listIntCompare, listIntPrint, listIntDelete);
	list->pushBackElement(list, newInt(1));
	list->pushBackElement(list, newInt(1));
	list->pushBackElement(list, newInt(1));
	list->pushBackElement(list, newInt(2));
	list->pushBackElement(list, newInt(1));
	list->pushBackElement(list, newInt(1));
	list->pushBackElement(list, newInt(2));

	if (list->findFirstElement(list, newInt(2)) != 3) return 0;

	return 1;
}
int ListTestListSort() {
	List* list = listCreateList(listIntEqual, listIntCompare, listIntPrint, listIntDelete);
	list->pushBackElement(list, newInt(3));
	list->pushBackElement(list, newInt(5));
	list->pushBackElement(list, newInt(1));
	list->pushBackElement(list, newInt(2));
	list->pushBackElement(list, newInt(7));
	list->pushBackElement(list, newInt(6));
	list->pushBackElement(list, newInt(4));
	list->sort(list);

	if (*(int*)list->getElement(list, 0) != 1) return 0;
	if (*(int*)list->getElement(list, 1) != 2) return 0;
	if (*(int*)list->getElement(list, 2) != 3) return 0;
	if (*(int*)list->getElement(list, 3) != 4) return 0;
	if (*(int*)list->getElement(list, 4) != 5) return 0;
	if (*(int*)list->getElement(list, 5) != 6) return 0;
	if (*(int*)list->getElement(list, 6) != 7) return 0;
	if (list->getSize(list) != 7) return 0;

	return 1;
}
int ListTestListPushList() {
	List* list1 = listCreateList(listIntEqual, listIntCompare, listIntPrint, listIntDelete);
	int* value;

	list1->pushBackElement(list1, newInt(1));
	list1->pushBackElement(list1, newInt(2));
	list1->pushBackElement(list1, newInt(3));
	list1->pushBackElement(list1, newInt(4));
	list1->pushBackElement(list1, newInt(5));
	list1->pushBackElement(list1, newInt(6));
	list1->pushBackElement(list1, newInt(7));

	List* list2 = listCreateList(listIntEqual, listIntCompare, listIntPrint, listIntDelete);
	list2->pushBackElement(list2, newInt(1));
	list2->pushBackElement(list2, newInt(2));
	list2->pushBackElement(list2, newInt(3));
	list2->pushBackElement(list2, newInt(4));


	int total = list1->getSize(list1) + list2->getSize(list2);
	list1->pushBackList(list1, list2);

	if (list1->getSize(list1) != total) return 0;
	if (*(int*)list1->getElement(list1, 7) != 1) return 0;
	if (*(int*)list1->getElement(list1, 8) != 2) return 0;
	if (*(int*)list1->getElement(list1, 9) != 3) return 0;
	if (*(int*)list1->getElement(list1, 10) != 4) return 0;

	return 1;
}