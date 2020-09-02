
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef int DATATYPE;

typedef struct TreeNode
{
	DATATYPE data;
	struct TreeNode* Left;
	struct TreeNode* Right;
} TreeNode;


typedef TreeNode* NDTYPE;

typedef struct Node
{
	NDTYPE data;
	struct Node* next;
} Node;

typedef struct
{
	Node* head;
} ListStack;

TreeNode* MakeExpTree(char exp[]);
int EvalExpTree(TreeNode* tree);

void PrintExpTreePrefix(TreeNode* tree);
void PrintExpTreeInfix(TreeNode* tree);
void PrintExpTreePostfix(TreeNode* tree);

void PreorderTraversal(TreeNode* tree);
void InorderTraversal(TreeNode* tree);
void PostorderTraversal(TreeNode* tree);

TreeNode* MakeTree(void);
DATATYPE RetData(TreeNode* tree);
void SaveData(TreeNode* tree, DATATYPE data);

TreeNode* RetSubTreeLeft(TreeNode* tree);
TreeNode* RetSubTreeRight(TreeNode* tree);

void MakeSubTreeLeft(TreeNode* tree, TreeNode* subtree);
void MakeSubTreeRight(TreeNode* tree, TreeNode* subtree);

void PrintNodeData(int data);

void InitStack(ListStack* stack);
int IsEmpty(ListStack* stack);

void Push(ListStack* stack, NDTYPE data);
NDTYPE Pop(ListStack* stack);
NDTYPE Peek(ListStack* stack);

int main(int argc, char* argv[])
{
	char exp[] = "12+7*";
	TreeNode* tree = MakeExpTree(exp);

	printf("prefix : ");
	PrintExpTreePrefix(tree);
	printf("\n");

	printf("infix : ");
	PrintExpTreeInfix(tree);
	printf("\n");

	printf("postfix : ");
	PrintExpTreePostfix(tree);
	printf("\n");

	printf("result : %d\n", EvalExpTree(tree));

	return 0;
}

TreeNode* MakeExpTree(char exp[])
{
	ListStack stack;
	TreeNode* tree;

	int ExpLen = strlen(exp);

	InitStack(&stack);

	for (int i = 0; i < ExpLen; i++)
	{
		tree = MakeTree();

		if (isdigit(exp[i]))
		{
			tree = MakeTree();
			SaveData(tree, exp[i]-'0');
			//Note, make tree node with integer data
		}
		else
		{
			tree = MakeTree();
			SaveData(tree, exp[i]);
			MakeSubTreeRight(tree, Pop(&stack));
			MakeSubTreeLeft(tree, Pop(&stack));						//Note, make tree, root - operator, childs - integers inserted in stack 
		}

		Push(&stack, tree);
	}

	return Pop(&stack);
}

int EvalExpTree(TreeNode* tree)
{
	//Note, if tree reached one end
	if (tree->Left==NULL && tree->Right == NULL)
	{
		return RetData(tree);
	}

	int op1 = EvalExpTree(RetSubTreeLeft(tree));
	int op2 = EvalExpTree(RetSubTreeRight(tree));


	switch (RetData(tree))
	{
	case '+':
		return op1 + op2;
	case '-':
		return op1 - op2;
	case '*':
		return op1 * op2;
	case '/':
		return op1 / op2;
	}

	return 0;
}

void PrintExpTreePrefix(TreeNode* tree)
{
	PreorderTraversal(tree);
}

void PrintExpTreeInfix(TreeNode* tree)
{
	InorderTraversal(tree);
}

void PrintExpTreePostfix(TreeNode* tree)
{
	PostorderTraversal(tree);
}

void PrintNodeData(int data)
{
	if (0 <= data && data <= 9)
	{
		printf("%d ", data);
	}
	else
	{
		printf("%c ", data);
	}
}

void PreorderTraversal(TreeNode* tree)
{
	if (tree == NULL)
	{
		return;
	}

	PrintNodeData(tree->data);
	PreorderTraversal(tree->Left);
	PreorderTraversal(tree->Right);
}

void InorderTraversal(TreeNode* tree)
{
	if (tree == NULL)
	{
		return;
	}

	InorderTraversal(tree->Left);
	PrintNodeData(tree->data);
	InorderTraversal(tree->Right);
}

void PostorderTraversal(TreeNode* tree)
{
	if (tree == NULL)
	{
		return;
	}

	PostorderTraversal(tree->Left);
	PostorderTraversal(tree->Right);
	PrintNodeData(tree->data);
}

TreeNode* MakeTree(void)
{
	TreeNode* tree = (TreeNode*)malloc(sizeof(TreeNode));
	tree->Left = NULL;
	tree->Right = NULL;

	return tree;
}//change to pass by argument

DATATYPE RetData(TreeNode* tree)
{
	return tree->data;
}

void SaveData(TreeNode* tree, DATATYPE data)
{
	tree->data = data;
}

TreeNode* RetSubTreeLeft(TreeNode* tree)
{
	return tree->Left;
}

TreeNode* RetSubTreeRight(TreeNode* tree)
{
	return tree->Right;
}

void MakeSubTreeLeft(TreeNode* tree, TreeNode* subtree)
{
	if (tree->Left != NULL)
	{
		free(tree->Left);
	}

	tree->Left = subtree;
}

void MakeSubTreeRight(TreeNode* tree, TreeNode* subtree)
{
	if (tree->Right != NULL)
	{
		free(tree->Right);
	}

	tree->Right = subtree;
}

void InitStack(ListStack* stack)
{
	stack->head = NULL;
}

int IsEmpty(ListStack* stack)
{
	if (stack->head == NULL)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void Push(ListStack* stack, NDTYPE data)
{
	Node* temp = (Node*)malloc(sizeof(Node));

	temp->data = data;
	temp->next = stack->head;

	stack->head = temp;
}

NDTYPE Pop(ListStack* stack)
{
	NDTYPE tempData;
	Node* temp;

	if (IsEmpty(stack))
	{
		printf("Stack is empty\n");
		exit(1);
	}

	tempData = stack->head->data;
	temp = stack->head;

	stack->head = stack->head->next;
	free(temp);

	return tempData;
}

NDTYPE Peek(ListStack* stack)
{
	if (IsEmpty(stack))
	{
		printf("Stack is empty\n");
		exit(1);
	}

	return stack->head->data;
}



