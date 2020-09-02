#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define STACKLEN 100

typedef int DATATYPE;

//stack
typedef struct
{
    DATATYPE StackArr[STACKLEN];
    int Top;
} ArrayStack;

//list
typedef struct Node
{
    DATATYPE Data;
    struct Node *next;
} Node;

typedef struct LinkedList
{
    Node *Head;
    Node *Curr;
    Node *Prev;
    int NumofData;
} LinkedList;

//graph
enum{A, B, C, D, E, F, G, H, I, J};

typedef struct
{
    int NumofVertex;
    int NumofEdge;
    struct LinkedList *AdjList;
    int *VisitInfo;
} Graph;
//stack
void InitStack(ArrayStack *stack);
int IsEmpty(ArrayStack *stack);

void Push(ArrayStack *stack, DATATYPE data);
DATATYPE Pop(ArrayStack *stack);
DATATYPE Peek(ArrayStack *stack);


//list
void InitList(LinkedList *list);
void Insert(LinkedList *list, DATATYPE Data);

void HeadInsert(LinkedList *list, DATATYPE *Data);
void SortInsert(LinkedList *list, DATATYPE Data);

int PosHead(LinkedList *list, DATATYPE *Data);
int PosNext(LinkedList *list, DATATYPE *Data);

DATATYPE Remove(LinkedList *list);
int RetCount(LinkedList *list);

//graph
void InitGraph(Graph *G, int NumofVertex);
void ReleaseGraph(Graph* G);

void AddEdge(Graph *G, int From, int To);
void PrintGraph(Graph *G);

int VisitVertex(Graph *G, int Visit);
void PrintDFS(Graph *G, int Start);

//stack
void InitStack(ArrayStack *stack){
    stack->Top = -1;
}


int IsEmpty(ArrayStack *stack){
    if(stack->Top == -1){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

void Push(ArrayStack *stack, DATATYPE data){
    stack->Top += 1;
    stack->StackArr[stack->Top] = data;
}

DATATYPE Pop(ArrayStack *stack){
    int tempIdx;

    if(IsEmpty(stack)){
        printf("Stack is empty\n");
        exit(1);
    }
    tempIdx = stack->Top;
    stack->Top -= 1;
    
    return stack->StackArr[tempIdx];
}

DATATYPE Peek(ArrayStack *stack){

    if(IsEmpty(stack)){
        printf("Stack is empty\n");
        exit(1);

    }

    return stack->StackArr[stack->Top];
}

//list
void InitList(LinkedList *list){
    list->Head = (Node*)malloc(sizeof(Node));
    list->Head->next = NULL;
    list->NumofData = 0;
}

void Insert(LinkedList *list, DATATYPE Data){

    if(list->Head->next == NULL){
        HeadInsert(list, Data);
    }
    else{
        SortInsert(list, Data);
    }
}

void HeadInsert(LinkedList *list, DATATYPE *Data){
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->Data = Data;

    temp->next = list->Head->next;
    list->Head->next = temp;

    list->NumofData++;
}

void SortInsert(LinkedList *list, DATATYPE Data){
    Node *new = (Node*)malloc(sizeof(Node));
    Node *pred = list->Head;
    new->Data = Data;

    //find pos
    while((pred->next != NULL) && (Data > pred->next->Data)){
        pred = pred->next;
    }

    new->next = pred->next;
    pred->next = new;

    list->NumofData++;
}

int PosHead(LinkedList *list, DATATYPE *Data){

    if(list->Head->next == NULL){
        return FALSE;
    }

    list->Prev = list->Head;
    list->Curr = list->Head->next;

    *Data = list->Curr->Data;
    return TRUE;
}

int PosNext(LinkedList *list, DATATYPE *Data){
    if(list->Curr->next == NULL){
        return FALSE;
    }

    list->Prev = list->Curr;
    list->Curr = list->Curr->next;

    *Data = list->Curr->Data;
    return TRUE;
}

DATATYPE Remove(LinkedList *list){
    Node *temp = list->Curr;
    DATATYPE tData = temp->Data;

    list->Prev->next = list->Curr->next;
    list->Curr = list->Prev;

    free(temp);
    list->NumofData--;
    return tData;
}

int RetCount(LinkedList *list){
    return list->NumofData;
}

//Graph
void InitGraph(Graph *G, int NumofVertex)
{
    G->AdjList = (LinkedList*)malloc(sizeof(LinkedList) *NumofVertex);
    G->NumofVertex = NumofVertex;
    G->NumofEdge = 0;

    for(int i = 0; i<NumofVertex ; i++){
        InitList(&G->AdjList[i]);
    }

    G->VisitInfo = (int*)malloc(sizeof(int) * NumofVertex);
    for(int i = 0; i< NumofVertex; i++){
        G->VisitInfo[i] = 0;
    }

}

void ReleaseGraph(Graph* G){
    if(G->AdjList != NULL){
        free(G->AdjList);
    }
    if(G->VisitInfo !=NULL){
        free(G->VisitInfo);
    }
}

void AddEdge(Graph *G, int From, int To){
    Insert(&G->AdjList[From],To);
    Insert(&G->AdjList[To], From);
    G->NumofEdge++;
}
void PrintGraph(Graph *G){
    int Vertex;

    for(int i = 0; i<G->NumofVertex; i++){
        printf("Vertex connected with %c : ", i + 65);

        if(PosHead(&G->AdjList[i], &Vertex)){
            printf("%c ", Vertex+65);
            while(PosNext(&G->AdjList[i], &Vertex)){
                printf("%c " , Vertex + 65);
            }
        }
        printf("\n");

    }
}

int VisitVertex(Graph *G, int Visit){
    if(G->VisitInfo[Visit] == 0){
        G->VisitInfo[Visit] = 1;
        printf("%c ", Visit + 65);
        return TRUE;
    }
    return FALSE;
}
void PrintDFS(Graph *G, int Start){
    ArrayStack stack;
    int Visit = Start;
    int Next;

    InitStack(&stack);
    VisitVertex(G, Visit);
    Push(&stack, Visit);

    while(PosHead(&G->AdjList[Visit], &Next)){
        int Flag = FALSE;

        if(VisitVertex(G, Next)){
            Push(&stack, Visit);
            Visit = Next;
            Flag = TRUE;
        }
        else{
            while(PosNext(&G->AdjList[Visit], &Next)){

                if(VisitVertex(G, Next)){
                    Push(&stack, Visit);
                    Visit = Next;
                    Flag = TRUE;
                    break;
                }
            }
        }
        if(Flag == FALSE){
            if(IsEmpty(&stack)){
                break;
            }
            else{
                Visit = Pop(&stack);

            }
        }
    }
    for(int i = 0; i<G->NumofVertex; i++){
        G->VisitInfo[i] = 0;
    }
}


int main(int argc, char *argv[]){
    // Graph graph;
    // printf("lab10_20\n");ka

    // InitGraph(&graph, 5);
    // AddEdge(&graph, A, B);
    // AddEdge(&graph, A, D);
    // AddEdge(&graph, B, C);
    // AddEdge(&graph, C, D);
    // AddEdge(&graph, D, E);
    // AddEdge(&graph, E, A);

    // PrintGraph(&graph);
    // printf("\n");

    
    // PrintDFS(&graph, A);
    // printf("\n");
    // PrintDFS(&graph, D);
    // printf("\n");
    // PrintDFS(&graph, B);
    // printf("\n");

    // ReleaseGraph(&graph);

    Graph graph1;
    InitGraph(&graph1, 7);

    AddEdge(&graph1, A, B);
    AddEdge(&graph1, A, C);
    AddEdge(&graph1, B,D);
    AddEdge(&graph1, C, E);
    AddEdge(&graph1, C, G);
    AddEdge(&graph1, D, F);

    PrintGraph(&graph1);
    printf("\n");

    PrintDFS(&graph1, A);
    printf("\n");
    PrintDFS(&graph1, D);
    printf("\n");
    PrintDFS(&graph1, G);
    printf("\n");

    ReleaseGraph(&graph1);


    Graph graph2;
    InitGraph(&graph2, 7);
    AddEdge(&graph2, A, B);
    AddEdge(&graph2, B, C);
    AddEdge(&graph2, B, D);
    AddEdge(&graph2, C, E);
    AddEdge(&graph2, E, F);
    AddEdge(&graph2, F, G);

    PrintGraph(&graph2);
    printf("\n");
    
    PrintDFS(&graph2, A);
    printf("\n");
    PrintDFS(&graph2, D);
    printf("\n");
    PrintDFS(&graph2, G);
    printf("\n");

    ReleaseGraph(&graph2);

    Graph graph3;
    InitGraph(&graph3, 8 );
    AddEdge(&graph3, A, B);
    AddEdge(&graph3, B, C);
    AddEdge(&graph3, C, D);
    AddEdge(&graph3, D, E);
    AddEdge(&graph3, A, E);
    AddEdge(&graph3, E, F);
    AddEdge(&graph3, F, G);
    AddEdge(&graph3, F, H);

    PrintGraph(&graph3);
    printf("\n");

    PrintDFS(&graph3, A);
    printf("\n");
    PrintDFS(&graph3, E);
    printf("\n");
    PrintDFS(&graph3, G);
    printf("\n");

    ReleaseGraph(&graph3);
    return 0;




}

