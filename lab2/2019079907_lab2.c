#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct {
	int ID;
	const char* Name;
}Student;

typedef struct Node {
	Student data;
	struct Node* next;

}Node;


typedef struct {
	Node* Head;
	Node* Cur;
	Node* Tail;
	int NumofData;
	int(*Comp)(int data1, int data2);
}LinkedList;

void InitList(LinkedList* list);
void Insert(LinkedList* list, Student data );
void HeadInsert(LinkedList* list, Student data);
void SortInsert(LinkedList* list, Student data);

int PosHead(LinkedList* list, Student* data);
int PosNext(LinkedList* list, Student* data);

Student Remove(LinkedList* list);
int RetCount(LinkedList* list);

void SetSortRule(LinkedList* list, int (*Comp)(int data1, int data2));//학번비교를 위해 int로 수정함
int ComparePrecede(int data1, int data2);


void InitList(LinkedList* list) {
	list->Head = (Node*)malloc(sizeof(Node));
	list->Head->next = NULL;
	list->Comp = NULL;
	list->NumofData = 0;
}

void Insert(LinkedList* list, Student data) {
	if (list->Comp == NULL) {
		HeadInsert(list, data);
	}
	else {
		SortInsert(list, data);
	}
}
void HeadInsert(LinkedList* list, Student data) {

	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = data;
	

	temp->next = list->Head->next;
	list->Head->next = temp;

	list->NumofData++;
}

void SortInsert(LinkedList* list, Student data) {
	//이름을 new로하니 오류가나서 newNode로 고침	
	Node* newNode = (Node*)malloc(sizeof(Node));
	Node* pred = list->Head;
	newNode->data = data;


	while ((pred->next != NULL) && (list->Comp(data.ID, pred->next->data.ID) != 0)) {
		pred = pred->next;
	}

	newNode->next = pred->next;
	pred->next = newNode;

	list->NumofData++;
}
int PosHead(LinkedList* list, Student* data) {
	if (list->Head == NULL) {
		return FALSE;
	}

	list->Tail = list->Head;
	list->Cur = list->Head->next;

	*data = list->Cur->data;
	return TRUE;
}
int PosNext(LinkedList* list, Student* data) {
	if (list->Cur->next == NULL) {
		return FALSE;
	}

	list->Tail = list->Cur;
	list->Cur = list->Cur->next;

	*data = list->Cur->data;
	return TRUE;
}

Student Remove(LinkedList* list) {

	Node* temp = list->Cur;
	Student tdata = temp->data;

	list->Tail->next = list->Cur->next;
	list->Cur = list->Tail;

	free(temp);
	list->NumofData--;
	return tdata;
}

int RetCount(LinkedList* list) {
	return list->NumofData;
}

int ComparePrecede(int data1, int data2) {//int비교
	if (data1 < data2) {
		return 0;
	}
	else {
		return 1;
	}
}

void SetSortRule(LinkedList* list, int(*Comp)(int data1,int data2)) {//int비교
	list->Comp = Comp;
}

int main(int argc, char* argv[]) {
	
	LinkedList list;
	InitList(&list);
	Student data;//Student구조체
	SetSortRule(&list, ComparePrecede);
	
	//구조체 선언,데이터지정
	Student a, b, c, d, e;
	a.ID = 2019000101;
	a.Name = "Lee";
	b.ID = 2019000077;
	b.Name = "Kim";
	c.ID = 2019000005;
	c.Name = "Park";
	d.ID = 2019000000;
	d.Name = "Choi";
	e.ID = 2019001409;
	e.Name = "Yoon";
	//insert
	Insert(&list, a);
	Insert(&list, b);
	Insert(&list, c);
	Insert(&list, d);
	Insert(&list, e);
	//sort
	SetSortRule(&list, ComparePrecede);


	printf("Num of datas %d \n", RetCount(&list));

	if (PosHead(&list, &data)) {
		printf("ID : %d, Name : %s ", data.ID,data.Name);
		printf("\n");
		while (PosNext(&list, &data)) {
			printf("ID : %d, Name : %s \n", data.ID, data.Name);

		}
	}
	printf("\n");
	printf("\n");

	int target = 2019000005;
	printf("Delete student node ID = 2019000005\n");
	printf("\n");
	if (PosHead(&list, &data)) {
		if (data.ID == target) {
			Remove(&list);
		}
		while (PosNext(&list, &data)) {
			if (data.ID == target) {
				Remove(&list);
			}
		}

	}
	printf("Num of datas %d\n", RetCount(&list));
	if (PosHead(&list, &data)) {
		printf("ID : %d, Name : %s \n", data.ID, data.Name);
		
		while (PosNext(&list, &data)) {
			printf("ID : %d, Name : %s \n", data.ID, data.Name);
		}
	}
	printf("\n");
	return 0;

}
