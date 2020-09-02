#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define EMPTY -1

typedef int DATATYPE;

typedef struct NODE {
	DATATYPE data;
	struct NODE* next;
}NODE;

typedef struct {
	NODE* head;

}ListStack;

void InitStack(ListStack* stack);
int IsEmpty(ListStack* stack);

void Push(ListStack* stack, DATATYPE data);
DATATYPE Pop(ListStack* stack);
DATATYPE Peek(ListStack* stack);

void ConvertExp(char exp[]);
int GetOperatorPriority(char op);
int CompareOperatorPriority(int op1, int op2);
int EvalExp(char exp[]);


void InitStack(ListStack* stack) {
	stack->head = NULL;
}
int IsEmpty(ListStack* stack) {
	if (stack->head == NULL) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}
void Push(ListStack* stack, DATATYPE data) {
	NODE* temp = (NODE*)malloc(sizeof(NODE));

	temp->data = data;
	temp->next = stack->head;

	stack->head = temp;

}

DATATYPE Pop(ListStack* stack) {
	DATATYPE tempData;
	NODE* temp;
	if (IsEmpty(stack)) {
		printf("Stack is empty\n");
		exit(1);
	}
	tempData = stack->head->data;
	temp = stack->head;

	stack->head = stack->head->next;
	free(temp);

	return tempData;
}

DATATYPE Peek(ListStack* stack) {
	if (IsEmpty(stack)) {
		printf("Stack is empty\n");
		exit(1);
	}
	return stack->head->data;
}

void ConvertExp(char exp[]) {
	
		ListStack stack;//스택
		char ch, top_op;
		int i, len = strlen(exp);
		char* postfix = (char*)malloc(len *2);//exp를 바꿔야 하기 때문에 마지막에 수정할 수 있도록 postfix를 따로 만들었음
		int p = 0;//postfix index

		InitStack(&stack);

		//반복문
		for (i = 0; i < len; i++) {
			
			ch = exp[i];
			
			switch (GetOperatorPriority(ch))
			{
			//연산자
			case 3: case 5:
				
				while (!IsEmpty(&stack) && CompareOperatorPriority(GetOperatorPriority(ch),GetOperatorPriority(Peek(&stack)))!=1) {
					char c = Pop(&stack);
					printf("%c", c);
					postfix[p++] = c;//프린트할때마다 postfix에도 넣어주기				
					
				}
				Push(&stack, ch);
				break;
			//open
			case 1:
				Push(&stack, ch);
				break;
			//close
			case 0:
				top_op = Pop(&stack);
				while (top_op != '(') {
					postfix[p++] = top_op;
					printf("%c", top_op);
					top_op = Pop(&stack);
				}
				
				break;
				
			default:
				postfix[p++] = ch;
				printf("%c", ch);
				break;
			}

		}
		while (!IsEmpty(&stack)) {
			char c = Pop(&stack);
			printf("%c", c);
			postfix[p++] = c;
		}
		//exp 바꿔주기
		for (int i = 0; i < len; i++) {
			exp[i] = postfix[i];
			
		}

	}
	
	
//우선순위
int GetOperatorPriority(char op) {
	if (op == '*' || op == '/') {
		return 5;
	}
	else if (op == '+' || op == '-') {
		return 3;
	}
	else if (op == '(') {
		return 1;
	}
	else if (op == ')') {
		return 0;
	}
	else
		return -1;
}
//비교 CompareOpe
int CompareOperatorPriority(int op1, int op2) {
	if (op1 > op2) {
		return 1;
	}
	else if (op1 < op2) {
		return -1;
	}
	else if (op1 == op2) {
		return 0;
	}
}

int EvalExp(char exp[]) {
	ListStack stack;
	InitStack(&stack);

	int len = strlen(exp);
	char tok, temp1, temp2;

	for (int i = 0; i < len; i++) {
		tok = exp[i];

		if (exp[i] >= '1' && exp[i] <= '9') {
			Push(&stack, tok - '0');
		}
		else {
			temp1 = Pop(&stack);
			temp2 = Pop(&stack);

			switch (tok)
			{
			case '+':
				Push(&stack, temp2 + temp1);
				break;

			case '-':
				Push(&stack, temp2 - temp1);
				break;
			case '*':
				Push(&stack, temp2 * temp1);
				break;
			case '/':
				Push(&stack,(int)temp2 / temp1);
				break;
			default:
				break;
			}
		}
	}
	return Pop(&stack);


}



int main(int argc, char* argv[]) {


	char postExp1[] = "1+2*3";
	char postExp2[] = "(1+2)*3";
	char postExp3[] = "((1-2)+3)*(5-2)";
	char postExp4[] = "(1+2)*3/4";
	char postExp5[] = "8+7*3";
	ConvertExp(postExp1);
	printf(" = %d\n", EvalExp(postExp1));
	ConvertExp(postExp2);
	printf(" = %d\n", EvalExp(postExp2));
	ConvertExp(postExp3);
	printf(" = %d\n", EvalExp(postExp3));
	ConvertExp(postExp4);
	printf(" = %d\n",EvalExp(postExp4));
	ConvertExp(postExp5);
	printf(" = %d\n", EvalExp(postExp5));

	return 0;

}

