#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4703)

#define COUNT 12
#define TRUE 1
#define FALSE 0

typedef int DATATYPE;

typedef struct BTNode
{
	DATATYPE Data;
	struct BTNode* Left;
	struct BTNode* Right;
} BTNode;

typedef struct AddressNode
{
	DATATYPE Data;
	DATATYPE Parent;
	struct AddressNode* next;
} AddressNode;

typedef struct
{
	BTNode* Root;
	AddressNode* Head;
	AddressNode* Curr;
	AddressNode* Tail;
	int NumofData;
} BTTree;

//binary tree 
BTNode* MakeBTNode(void);
DATATYPE RetData(BTNode* Node);
void SaveData(BTNode* Node, DATATYPE Data);

BTNode* RetSubTreeLeft(BTNode* Node);
BTNode* RetSubTreeRight(BTNode* Node);

void MakeSubTreeLeft(BTNode* Parent, BTNode* Child);
void MakeSubTreeRight(BTNode* Parent, BTNode* Child);

BTNode* RemoveSubTreeLeft(BTNode* Node);
BTNode* RemoveSubTreeRight(BTNode* Node);

void ChangeSubTreeLeft(BTNode* Parent, BTNode* Child);
void ChangeSubTreeRight(BTNode* Parent, BTNode* Child);

//traversal
void PreorderTraversal(BTNode* Node);
void InorderTraversal(BTNode* Node);
void PostorderTraversal(BTNode* Node);

//BST
void MakeBST(BTNode** Node);

BTNode* InsertBST(BTNode** Root, DATATYPE Data);
BTNode* SearchBST(BTNode* Node, DATATYPE Target);
BTNode* RemoveBST(BTNode** Node, DATATYPE Target);

void PrintAllBST(BTNode* Node);

//AVL
BTNode* Rebalance(BTNode** Root);

BTNode* RotateLL(BTNode* Node);
BTNode* RotateRR(BTNode* Node);
BTNode* RotateRL(BTNode* Node);
BTNode* RotateLR(BTNode* Node);

int RetHeight(BTNode* Node);

int RetDiffInHeightOfSubTree(BTNode* Node);

//Disjoint Set
void InitList(BTTree* Tree);
void Insert(BTTree* Tree, DATATYPE Data, DATATYPE Parent);

DATATYPE Search(BTTree* Tree, DATATYPE* Data);
int PosHead(BTTree* Tree, DATATYPE* Data);
int PosNext(BTTree* Tree, DATATYPE* DAta);

int RetTotalHeight(BTTree* Tree);

void MakeAddressMap(BTTree* Tree);
DATATYPE MakeAddressMapWithSubTree(BTTree* Tree, BTNode* Node);

void PrintAddressMap(BTTree* Tree);
void PrintAddressMapNext(BTTree* Tree);

DATATYPE Find(BTTree* Tree, DATATYPE* Data);
int Union(BTTree* Tree1, BTTree* Tree2);

//util
void Print2D(BTNode* root, int space);

int main(int argc, char* argv[])
{
	BTTree S1;
	MakeBST(&S1.Root);

	DATATYPE Target;

	Target = 3;
	printf("Insert %d\n", Target);
	InsertBST(&S1.Root, Target);

	Target = 7;
	printf("Insert %d\n", Target);
	InsertBST(&S1.Root, Target);

	Target = 1;
	printf("Insert %d\n", Target);
	InsertBST(&S1.Root, Target);
	printf("\n");

	printf("Print S1\n");
	PrintAllBST(S1.Root);
	MakeAddressMap(&S1);
	printf("\n");

	printf("Print Address Map\n");
	PrintAddressMap(&S1);
	printf("\n");

	BTTree S2;
	MakeBST(&S2.Root);

	Target = 10;
	printf("Insert %d\n", Target);
	InsertBST(&S2.Root, Target);

	Target = 8;
	printf("Insert %d\n", Target);
	InsertBST(&S2.Root, Target);

	Target = 2;
	printf("Insert %d\n", Target);
	InsertBST(&S2.Root, Target);

	Target = 9;
	printf("Insert %d\n", Target);
	InsertBST(&S2.Root, Target);

	Target = 6;
	printf("Insert %d\n", Target);
	InsertBST(&S2.Root, Target);

	Target = 5;
	printf("Insert %d\n", Target);
	InsertBST(&S2.Root, Target);
	printf("\n");

	printf("Print S2\n");
	PrintAllBST(S2.Root);
	printf("\n");

	MakeAddressMap(&S2);

	printf("\n");

	printf("Print Address Map\n");

	PrintAddressMap(&S2);

	printf("\n");

	BTTree S3;
	MakeBST(&S3.Root);

	Target = 4;
	printf("Insert %d\n", Target);
	InsertBST(&S3.Root, Target);
	printf("\n");

	printf("Print S3\n");
	PrintAllBST(S3.Root);
	MakeAddressMap(&S3);
	printf("\n");

	printf("Print Address Map\n");
	PrintAddressMap(&S3);
	printf("\n");

	DATATYPE Data;
	DATATYPE Parent;

	//Find
	printf("Find roots\n");
	Target = 1;
	Data = Find(&S1, &Target);
	printf("Node %d, Root %d\n", Target, Data);

	Target = 2;
	Data = Find(&S2, &Target);
	printf("Node %d, Root %d\n", Target, Data);

	Target = 3;
	Data = Find(&S1, &Target);
	printf("Node %d, Root %d\n", Target, Data);

	Target = 4;
	Data = Find(&S3, &Target);
	printf("Node %d, Root %d\n", Target, Data);

	Target = 5;
	Data = Find(&S2, &Target);
	printf("Node %d, Root %d\n", Target, Data);

	Target = 6;
	Data = Find(&S2, &Target);
	printf("Node %d, Root %d\n", Target, Data);

	Target = 7;
	Data = Find(&S1, &Target);
	printf("Node %d, Root %d\n", Target, Data);

	Target = 8;
	Data = Find(&S2, &Target);
	printf("Node %d, Root %d\n", Target, Data);

	Target = 9;
	Data = Find(&S2, &Target);
	printf("Node %d, Root %d\n", Target, Data);

	Target = 10;
	Data = Find(&S2, &Target);
	printf("Node %d, Root %d\n", Target, Data);

	printf("\n");

	//Union
	//S1 with S2
	printf("Union\n");
	Data = Union(&S1, &S2);
	if (Data == 1)
	{
		PrintAllBST(S1.Root);
		printf("\n");
		PrintAddressMap(&S1);
		printf("\n");

		Data = Union(&S1, &S3);
		if (Data == 1)
		{
			PrintAllBST(S1.Root);
			printf("\n");
			PrintAddressMap(&S1);
			printf("\n");
		}
		else
		{
			PrintAllBST(S3.Root);
			printf("\n");
			PrintAddressMap(&S3);
			printf("\n");
		}
	}
	else
	{
		PrintAllBST(S2.Root);
		printf("\n");
		PrintAddressMap(&S2);
		printf("\n");

		Data = Union(&S2, &S3);
		if (Data == 1)
		{
			PrintAllBST(S2.Root);
			printf("\n");
			PrintAddressMap(&S2);
			printf("\n");
		}
		else
		{
			PrintAllBST(S3.Root);
			printf("\n");
			PrintAddressMap(&S3);
			printf("\n");
		}
	}

	return 0;
}

BTNode* MakeBTNode(void)
{
	BTNode* Node = (BTNode*)malloc(sizeof(BTNode));
	Node->Left = NULL;
	Node->Right = NULL;
	return Node;
}

DATATYPE RetData(BTNode* Node)
{
	return Node->Data;
}

void SaveData(BTNode* Node, DATATYPE Data)
{
	Node->Data = Data;
}

BTNode* RetSubTreeLeft(BTNode* Node)
{
	return Node->Left;
}

BTNode* RetSubTreeRight(BTNode* Node)
{
	return Node->Right;
}

void MakeSubTreeLeft(BTNode* Parent, BTNode* Child)
{
	//if parent has child
	if (Parent->Left != NULL)
	{
		free(Parent->Left);
	}

	Parent->Left = Child;
}

void MakeSubTreeRight(BTNode* Parent, BTNode* Child)
{
	//if parent has child
	if (Parent->Right != NULL)
	{
		free(Parent->Right);
	}

	Parent->Right = Child;
}

void PreorderTraversal(BTNode* Node)
{
	if (Node == NULL)
	{
		return;
	}

	printf("%d ", Node->Data);
	PreorderTraversal(Node->Left);
	PreorderTraversal(Node->Right);
}

void InorderTraversal(BTNode* Node)
{
	if (Node == NULL)
	{
		return;
	}

	InorderTraversal(Node->Left);
	printf("%d ", Node->Data);
	InorderTraversal(Node->Right);
}

void PostorderTraversal(BTNode* Node)
{
	if (Node == NULL)
	{
		return;
	}

	PostorderTraversal(Node->Left);
	PostorderTraversal(Node->Right);
	printf("%d ", Node->Data);
}

BTNode* RemoveSubTreeLeft(BTNode* Node)
{
	BTNode* Temp;

	if (Node != NULL)
	{
		Temp = Node->Left;
		Node->Left = NULL;
	}

	return Temp;
}

BTNode* RemoveSubTreeRight(BTNode* Node)
{
	BTNode* Temp;

	if (Node != NULL)
	{
		Temp = Node->Right;
		Node->Right = NULL;
	}

	return Temp;
}

void ChangeSubTreeLeft(BTNode* Parent, BTNode* Child)
{
	Parent->Left = Child;
}

void ChangeSubTreeRight(BTNode* Parent, BTNode* Child)
{
	Parent->Right = Child;
}

//BST
void MakeBST(BTNode** Node)
{
	*Node = NULL;
}

BTNode* InsertBST(BTNode** Root, DATATYPE Data)
{
	if (*Root == NULL)
	{
		*Root = MakeBTNode();
		SaveData(*Root, Data);
	}
	else if (Data < RetData(*Root))
	{
		InsertBST(&((*Root)->Left), Data);
		*Root = Rebalance(Root);
	}
	else if (Data > RetData(*Root))
	{
		InsertBST(&((*Root)->Right), Data);
		*Root = Rebalance(Root);
	}
	else
	{
		//do not allow duplicate data
		return NULL;
	}

	return *Root;
}

BTNode* SearchBST(BTNode* Node, DATATYPE Target)
{
	BTNode* Current = Node;
	DATATYPE Data;

	while (Current != NULL)
	{
		Data = RetData(Current);

		if (Target == Data)
		{
			return Current;
		}
		else if (Target < Data)
		{
			Current = RetSubTreeLeft(Current);
		}
		else
		{
			Current = RetSubTreeRight(Current);
		}

	}
	return NULL;
}

BTNode* RemoveBST(BTNode** Root, DATATYPE Target)
{
	//create virtual root
	BTNode* VirtualRoot = MakeBTNode();

	BTNode* Parent = VirtualRoot;
	BTNode* Current = *Root;
	BTNode* TargetNode;

	// make root node to be right child of virtual root
	ChangeSubTreeRight(VirtualRoot, *Root);

	//search target node
	while (Current != NULL && RetData(Current) != Target)
	{
		Parent = Current;

		if (Target < RetData(Current))
		{
			Current = RetSubTreeLeft(Current);

		}
		else
		{
			Current = RetSubTreeRight(Current);
		}
	}

	//if target not exist 
	if (Current == NULL)
	{
		return NULL;
	}

	TargetNode = Current;

	//if target node is edge node
	if (RetSubTreeLeft(TargetNode) == NULL && RetSubTreeRight(TargetNode) == NULL)
	{
		if (RetSubTreeLeft(Parent) == TargetNode)
		{
			RemoveSubTreeLeft(Parent);
		}
		else
		{
			RemoveSubTreeRight(Parent);
		}
	}
	else if (RetSubTreeLeft(TargetNode) == NULL || RetSubTreeRight(TargetNode) == NULL)
	{
		//if target has single child
		BTNode* ChildofTarget;

		//find target
		if (RetSubTreeLeft(TargetNode) != NULL)
		{
			ChildofTarget = RetSubTreeLeft(TargetNode);
		}
		else
		{
			ChildofTarget = RetSubTreeRight(TargetNode);
		}

		//link parent and child of target 
		if (RetSubTreeLeft(Parent) == TargetNode)
		{
			ChangeSubTreeLeft(Parent, ChildofTarget);
		}
		else
		{
			ChangeSubTreeRight(Parent, ChildofTarget);
		}
	}
	else
	{
		//if target has both child
		BTNode* MinimumNode = RetSubTreeRight(TargetNode);
		BTNode* ParentofMinimum = TargetNode;

		DATATYPE Backup;

		//find node to replace target node
		while (RetSubTreeLeft(MinimumNode) != NULL)
		{
			ParentofMinimum = MinimumNode;
			MinimumNode = RetSubTreeLeft(MinimumNode);
		}

		//backup target data
		Backup = RetData(TargetNode);
		//replace data of target node
		SaveData(TargetNode, RetData(MinimumNode));

		//link parent and child of MinimumNode
		if (RetSubTreeLeft(ParentofMinimum) == MinimumNode)
		{
			ChangeSubTreeLeft(ParentofMinimum, RetSubTreeRight(MinimumNode));
		}
		else
		{
			ChangeSubTreeRight(ParentofMinimum, RetSubTreeRight(MinimumNode));
		}

		TargetNode = MinimumNode;
		SaveData(TargetNode, Backup);
	}

	//if target node is root
	if (RetSubTreeRight(VirtualRoot) != *Root)
	{
		*Root = RetSubTreeRight(VirtualRoot);
	}

	free(VirtualRoot);
	return TargetNode;
}

void PrintAllBST(BTNode* Node)
{
	//PreorderTraversal(Node);
 //   InorderTraversal(Node);
	//PostorderTraversal(Node);
	Print2D(Node, 0);
}

void Print2D(BTNode* root, int space)
{
	if (root == NULL)
	{
		return;
	}

	space += COUNT;

	Print2D(root->Right, space);

	printf("\n");
	for (int i = COUNT; i < space; i++)
	{
		printf(" ");
	}
	printf("%d\n", root->Data);

	Print2D(root->Left, space);
}

//AVL
BTNode* Rebalance(BTNode** Root)
{
	int Diff = RetDiffInHeightOfSubTree(*Root);

	if (Diff > 1)
	{
		//if left subtree is higher than 2 
		if (RetDiffInHeightOfSubTree(RetSubTreeLeft(*Root)) > 0)
		{
			printf("Rotate LL\n");
			*Root = RotateLL(*Root);
		}
		else
		{
			printf("Rotate LR\n");
			*Root = RotateLR(*Root);
		}
	}

	if (Diff < -1)
	{
		//if right subtree is higher than 2
		if (RetDiffInHeightOfSubTree(RetSubTreeRight(*Root)) < 0)
		{
			printf("Rotate RR\n");
			*Root = RotateRR(*Root);
		}
		else
		{
			printf("Rotate RL\n");
			*Root = RotateRL(*Root);
		}
	}

	return *Root;
}

BTNode* RotateLL(BTNode* Node)
{
	BTNode* Parent;
	BTNode* Child;

	Parent = Node;
	Child = RetSubTreeLeft(Parent);

	ChangeSubTreeLeft(Parent, RetSubTreeRight(Child));
	ChangeSubTreeRight(Child, Parent);

	return Child;
}

BTNode* RotateRR(BTNode* Node)
{
	BTNode* Parent;
	BTNode* Child;

	Parent = Node;
	Child = RetSubTreeRight(Parent);

	ChangeSubTreeRight(Parent, RetSubTreeLeft(Child));
	ChangeSubTreeLeft(Child, Parent);

	return Child;
}

BTNode* RotateRL(BTNode* Node)
{
	BTNode* Parent;
	BTNode* Child;

	Parent = Node;
	Child = RetSubTreeRight(Parent);

	ChangeSubTreeRight(Parent, RotateLL(Child));

	return RotateRR(Parent);
}

BTNode* RotateLR(BTNode* Node)
{
	BTNode* Parent;
	BTNode* Child;

	Parent = Node;
	Child = RetSubTreeLeft(Parent);

	ChangeSubTreeLeft(Parent, RotateRR(Child));

	return RotateLL(Parent);
}

int RetHeight(BTNode* Node)
{
	int HeightOfLeft;
	int HeightOfRight;

	if (Node == NULL)
	{
		return 0;
	}

	//calculate height of left subtree
	HeightOfLeft = RetHeight(RetSubTreeLeft(Node));

	//calculate height of right subtree
	HeightOfRight = RetHeight(RetSubTreeRight(Node));

	if (HeightOfLeft > HeightOfRight)
	{
		return HeightOfLeft + 1;
	}
	else
	{
		return HeightOfRight + 1;
	}
}

int RetDiffInHeightOfSubTree(BTNode* Node)
{
	int HeightOfLeft;
	int HeightOfRight;

	if (Node == NULL)
	{
		return 0;
	}

	HeightOfLeft = RetHeight(RetSubTreeLeft(Node));
	HeightOfRight = RetHeight(RetSubTreeRight(Node));

	return HeightOfLeft - HeightOfRight;
}

void InitList(BTTree* Tree)
{
	Tree->Head = (AddressNode*)malloc(sizeof(AddressNode));
	Tree->Head->next = NULL;
	Tree->Curr = NULL;
	Tree->Tail = NULL;
	Tree->NumofData = 0;
}

void MakeAddressMap(BTTree* Tree)
{

	InitList(Tree);


	//Make address map
	int Data = MakeAddressMapWithSubTree(Tree, RetSubTreeLeft(Tree->Root));
	if (Data != NULL)
	{
		Insert(Tree, Data, Tree->Root->Data);
	}


	Data = MakeAddressMapWithSubTree(Tree, RetSubTreeRight(Tree->Root));

	if (Data != NULL)
	{
		Insert(Tree, Data, Tree->Root->Data);
	}


	//get height of tree and make address map with root node
	int Height = RetTotalHeight(Tree);
	Insert(Tree, Tree->Root->Data, -Height);


}

void PrintAddressMap(BTTree * Tree)
{
	if (Tree->Head->next == NULL)
	{
		return;
	}

	Tree->Tail = Tree->Head;
	Tree->Curr = Tree->Head->next;
	int Data = Tree->Curr->Data;
	int Parent = Tree->Curr->Parent;

	printf("Node %d, Parent %d\n", Data, Parent);
	PrintAddressMapNext(Tree);
}

void PrintAddressMapNext(BTTree * Tree)
{
	if (Tree->Curr->next == NULL)
	{
		return;
	}

	Tree->Tail = Tree->Curr;
	Tree->Curr = Tree->Curr->next;

	int Data = Tree->Curr->Data;
	int Parent = Tree->Curr->Parent;

	printf("Node %d, Parnet %d\n", Data, Parent);
	PrintAddressMapNext(Tree);
}

int PosHead(BTTree * Tree, DATATYPE * Data)
{
	if (Tree->Head->next == NULL)
	{
		return FALSE;
	}

	Tree->Tail = Tree->Head;
	Tree->Curr = Tree->Head->next;

	*Data = Tree->Curr->Data;

	return TRUE;
}

int PosNext(BTTree * Tree, DATATYPE * Data)
{
	if (Tree->Curr->next == NULL)
	{
		return FALSE;
	}

	Tree->Tail = Tree->Curr;
	Tree->Curr = Tree->Curr->next;

	*Data = Tree->Curr->Data;
	return TRUE;
}


void Insert(BTTree * Tree, DATATYPE Data, DATATYPE Parent) //노드 사용

{
	AddressNode* temp = (AddressNode*)malloc(sizeof(AddressNode));

	temp->Parent = Parent;
	temp->Data = Data;
	temp->next = NULL;
	
	Tree->Curr = Tree->Head;

	while (Tree->Curr->next != NULL) {
		Tree->Curr = Tree->Curr->next;
	}

	Tree->Curr->next = temp;
}

DATATYPE Search(BTTree * Tree, DATATYPE * Data) //posHead, posNext사용
{
	AddressNode* temp = (AddressNode*)malloc(sizeof(AddressNode));

	if (PosHead(Tree, &(temp->Data))) {
		if(*Data == (temp->Data)) {
			return Tree->Curr->Parent;

		}
		while (PosNext(Tree, &(temp->Data))) {
			if (*Data == (temp->Data)) {

				return Tree->Curr->Parent;
			}
		}
	}
}

int RetTotalHeight(BTTree * Tree)//RetHeight이용
{
	return (RetHeight(Tree->Root) - 1);
}


DATATYPE MakeAddressMapWithSubTree(BTTree * Tree, BTNode * Node)//Make address map
{
	
	//null먼저, left, right 순서
	
	if (Node == NULL) {
		return NULL;
	}

	
	if (Node != NULL && RetSubTreeLeft(Node) != NULL ) {
		int data = MakeAddressMapWithSubTree(Tree, RetSubTreeLeft(Node));

		if (data != NULL)
		{
			Insert(Tree, data, Node->Data);
		}
	}

	if (Node != NULL && RetSubTreeRight(Node) != NULL  ) {
		int data = MakeAddressMapWithSubTree(Tree, RetSubTreeRight(Node));

		if (data != NULL)
		{
			Insert(Tree, data, Node->Data);
		}
	}

	return Node->Data;
}

DATATYPE Find(BTTree * Tree, DATATYPE * Data)//Search 이용
{
	DATATYPE parent = Search(Tree, Data);

	if (parent <= 0) {
		return Tree->Curr->Data;
	}
	else {
		Find(Tree, &parent);
	}
}

int Union(BTTree * Tree1, BTTree * Tree2)
{
	DATATYPE data = NULL;
	//T1에 T2
	//lower to higher 음수 -> 작은게 더 크다.
	if (Search(Tree1, &(Tree1->Root->Data)) < Search(Tree2, &(Tree2->Root->Data))) {

		if (PosHead(Tree2, &data)) {

			InsertBST(&(Tree1->Root), data);

			while (PosNext(Tree2, &data)) {
				InsertBST(&(Tree1->Root), data);
			}
		}
		MakeAddressMap(Tree1);

		return 1;
		
		
	}
	//T2에 T1
	else {

		if (PosHead(Tree1, &data)) {
			InsertBST(&(Tree2->Root), data);

			while (PosNext(Tree1, &data)) {
				InsertBST(&(Tree2->Root), data);
			}
		}
		MakeAddressMap(Tree2);

		return 2;

	}
}
