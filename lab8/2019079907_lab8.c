#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define HEAP_LEN 100

typedef char DATATYPE;

typedef struct Heap
{
    int NumofData;
    DATATYPE arr[HEAP_LEN];

} Heap;

void HeapInit(Heap *THeap);
int isEmpty(Heap *THeap);

void HeapInsert(Heap *Theap, DATATYPE Data);
DATATYPE HeapDelete(Heap *THeap);

int RetIndexParent(int index);
int RetIndexLeftChild(int index);
int RetIndexRightChild(int index);

int RetIndexHigherPriorityOfChilds(Heap *THeap, int index);

void PrintAll(Heap *THeap);

void HeapInit(Heap *THeap)
{
    THeap->NumofData = 0;
}
int isEmpty(Heap *THeap)
{
    if(THeap->NumofData == 0){
        return TRUE;
    }
    else
    {
        return FALSE;
    }
    
}

void HeapInsert(Heap *THeap, DATATYPE Data)
{
    int index = THeap->NumofData + 1;
    while(index != 1)
    {
        if((Data-THeap->arr[RetIndexParent(index)])>0)
        {
            THeap->arr[index] = THeap->arr[RetIndexParent(index)];
            index=RetIndexParent(index);
            
        }
        else
        {
            break;
        }
        
    }
    THeap->arr[index] = Data;
    THeap->NumofData +=1;
    
}
DATATYPE HeapDelete(Heap *THeap)
{
    DATATYPE Data = THeap->arr[1];
    DATATYPE last = THeap->arr[THeap->NumofData];

    int ParentIndex = 1;
    int ChildIndex;

    while(ChildIndex = RetIndexHigherPriorityOfChilds(THeap, ParentIndex))
    {
        if((THeap->arr[ChildIndex]-last)<=0)
        {
            break;
        }
        THeap->arr[ParentIndex] = THeap->arr[ChildIndex];
        ParentIndex = ChildIndex;
    }

    THeap->arr[ParentIndex] = last;
    THeap->NumofData -= 1;
    return Data;
}

int RetIndexParent(int index)
{
    return index / 2;
}
int RetIndexLeftChild(int index)
{
    return index * 2;
}
int RetIndexRightChild(int index)
{
    return RetIndexLeftChild(index) + 1;
}

int RetIndexHigherPriorityOfChilds(Heap *THeap, int index)
{
    if(RetIndexLeftChild(index) > THeap->NumofData)
    {
        return 0;
    }
    else if(RetIndexLeftChild(index) == THeap->NumofData)
    {
        return RetIndexLeftChild(index);
    }
    else
    {
        if((THeap->arr[RetIndexRightChild(index)] - THeap->arr[RetIndexLeftChild(index)]) > 0)
        {
            return RetIndexRightChild(index);
        }
        else
        {
            return RetIndexLeftChild(index);
        }
        
    }
    
}

void PrintAll(Heap *THeap)
{
    for(int i = 1; i < THeap->NumofData + 1; i++)
    {
        printf("%d : %c\n", i, THeap->arr[i]);
    }
}

int main(int argc, char *argv[])
{
    Heap heap;
    HeapInit(&heap);

    HeapInsert(&heap, 'T');
    HeapInsert(&heap, 'H');
    HeapInsert(&heap, 'I');
    HeapInsert(&heap, 'S');
    HeapInsert(&heap, 'I');
    HeapInsert(&heap, 'S');
    HeapInsert(&heap, 'H');
    HeapInsert(&heap, 'E');
    HeapInsert(&heap, 'A');
    HeapInsert(&heap, 'P');

    PrintAll(&heap);
    printf("\n");

    printf("%c\n", HeapDelete(&heap));
    printf("\n");

    PrintAll(&heap);
    printf("\n");

    while(!isEmpty(&heap))
    {
        printf("%c\n",HeapDelete(&heap));
    }

    return 0;
}
