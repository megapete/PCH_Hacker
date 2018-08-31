//
//  PCH_List.c
//  PCH_Hacker
//
//  Created by PeterCoolAssHuber on 2018-08-29.
//  Copyright © 2018 Peter Huber. All rights reserved.
//

#include "PCH_List.h"
#include <string.h>
#include "PCH_C_Logging.h"

typedef struct _listNode *node;

// Creation routines

// Create a new, empty list with the given data size
PCH_List CreateList(size_t dataSize)
{
    PCH_List newList;
    
    newList.currentHead = NULL;
    newList.currentTail = NULL;
    newList.datasize = dataSize;
    newList.numNodes = 0;
    
    return newList;
}

// Create a new list and initialize its members to the elements in the array (array element 0 is assigned to the head)
PCH_List CreateListWithDataArray(void *dataArray, uint numDataElements, size_t dataSize)
{
    PCH_List newList = CreateList(dataSize);
    newList.numNodes = numDataElements;
    
    void *currentDataPtr = dataArray;
    for (int i=0; i<numDataElements; i++)
    {
        void *newNodeData = malloc(dataSize);
        memcpy(newNodeData, currentDataPtr, dataSize);
        currentDataPtr += dataSize;
        
        node newNode = malloc(sizeof(struct _listNode));
        newNode->data = newNodeData;
        newNode->prev = newList.currentTail;
        newNode->next = NULL;
        
        newList.currentTail = newNode;
        
        if (newList.currentHead == NULL)
        {
            newList.currentHead = newNode;
        }
    }
    
    return newList;
}

/// Replace the contents of theList with the contents of dataArray
void SetListWithArray(PCH_List *theListPtr, uint numDataElements, void *dataArray)
{
    if (theListPtr->numNodes > 0)
    {
        RemoveAll(theListPtr);
    }
    
    void *currentDataPtr = dataArray;
    for (int i=0; i<numDataElements; i++)
    {
        void *newNodeData = malloc(theListPtr->datasize);
        memcpy(newNodeData, currentDataPtr, theListPtr->datasize);
        currentDataPtr += theListPtr->datasize;
        
        node newNode = malloc(sizeof(struct _listNode));
        newNode->data = newNodeData;
        newNode->prev = theListPtr->currentTail;
        
        newNode->next = NULL;
        
        theListPtr->currentTail = newNode;
        
        if (theListPtr->currentHead == NULL)
        {
            theListPtr->currentHead = newNode;
        }
        else
        {
            newNode->prev->next = newNode;
        }
        
        theListPtr->numNodes += 1;
    }
}

// Add new data to the head of the list.
void PushNewHead(PCH_List *theListPtr, void *newHeadData)
{
    node oldHead = theListPtr->currentHead;
    
    void *newNodeData = malloc(theListPtr->datasize);
    memcpy(newNodeData, newHeadData, theListPtr->datasize);
    
    node newNode = malloc(sizeof(struct _listNode));
    newNode->data = newNodeData;
    newNode->prev = NULL;
    newNode->next = oldHead;
    oldHead->prev = newNode;
    
    theListPtr->currentHead = newNode;
    
    theListPtr->numNodes += 1;
}

// Add new data to the tail of the list.
void AppendNewData(PCH_List *theListPtr, void *newTailData)
{
    node oldTail = theListPtr->currentTail;
    
    void *newNodeData = malloc(theListPtr->datasize);
    memcpy(newNodeData, newTailData, theListPtr->datasize);
    
    node newNode = malloc(sizeof(struct _listNode));
    newNode->data = newNodeData;
    newNode->prev = oldTail;
    newNode->next = NULL;
    
    if (theListPtr->currentHead == NULL)
    {
        theListPtr->currentHead = newNode;
    }
    
    if (oldTail != NULL)
    {
        oldTail->next = newNode;
    }
    
    theListPtr->currentTail = newNode;
    
    theListPtr->numNodes += 1;
}

// Append listToAppend to the end of theListPtr-> It is up to the calling routine to make sure that destList is not equal to listToAppend. If the two lists are of different datasizes, nothing is done and the routine returns.
void AppendNewList(PCH_List *theListPtr, PCH_List *listToAppend)
{
    if (theListPtr->datasize != listToAppend->datasize)
    {
        ALog("Incompatible data sizes!");
        return;
    }
    
    if (listToAppend->numNodes == 0)
    {
        DLog("List to append is empty");
        return;
    }
    
    listToAppend->currentHead->prev = theListPtr->currentTail;
    theListPtr->currentTail->next = listToAppend->currentHead;
    theListPtr->currentTail = listToAppend->currentTail;
    
    theListPtr->numNodes += listToAppend->numNodes;
}

// Set the data at the index indicated. Whatever was there will be deleted. If index is greater than the size of the list, nothing is set.
void SetDataAt(PCH_List *theListPtr, void *newData, uint index)
{
    if (index >= theListPtr->numNodes)
    {
        DLog("Index is beyond end of list - aborting");
        return;
    }
    
    node theNode = theListPtr->currentHead;
    int nodeIndex = 0;
    
    while (theNode != NULL && nodeIndex < index)
    {
        theNode = theNode->next;
    }
    
    if (theNode == NULL)
    {
        ALog("Something really weird happened!");
    }
    
    memcpy(theNode->data, newData, theListPtr->datasize);
    
}

// Insert new data at the index indicated (this routine can be slow in a large list with a high index)
void InsertNewDataAt(PCH_List *theListPtr, void *newData, uint index)
{
    if (index == 0)
    {
        PushNewHead(theListPtr, newData);
    }
    else if (index >= theListPtr->numNodes - 1)
    {
        AppendNewData(theListPtr, newData);
    }
    else
    {
        void *newNodeData = malloc(theListPtr->datasize);
        memcpy(newNodeData, newData, theListPtr->datasize);
        
        node newNode = malloc(sizeof(struct _listNode));
        newNode->data = newNodeData;
        
        node oldNode = theListPtr->currentHead;
        node oldPrevNode = NULL;
        for (int i=0; i<index; i++)
        {
            oldPrevNode = oldNode;
            oldNode = oldNode->next;
        }
        
        oldPrevNode->next = newNode;
        oldNode->prev = newNode;
        
        newNode->prev = oldPrevNode;
        newNode->next = oldNode;
        
        theListPtr->numNodes += 1;
    }
}

// Returns the data pointer at the head of the list
void *ListHead(PCH_List *theListPtr)
{
    return theListPtr->currentHead->data;
}

// Returns the data pointer at the tail of the list
void *ListTail(PCH_List *theListPtr)
{
    return theListPtr->currentTail->data;
}

// Return the data pointer at index. If index is greater than the length of the list, NULL is returned.
void *ListDataAt(PCH_List *theListPtr, uint index)
{
    if (index >= theListPtr->numNodes)
    {
        DLog("Index is beyond end of list - aborting");
        return NULL;
    }
    
    node theNode = theListPtr->currentHead;
    for (int i=0; i<index; i++)
    {
        theNode = theNode->next;
    }
    
    return theNode->data;
}

// Remove the node at the head of the list and free the memory
void RemoveHead(PCH_List *theListPtr)
{
    node oldHead = theListPtr->currentHead;
    theListPtr->currentHead = oldHead->next;
    theListPtr->currentHead->prev = NULL;
    
    free(oldHead->data);
    free(oldHead);
    
    theListPtr->numNodes -= 1;
}

// Remove the node at the tail of the list and free the memory
void RemoveTail(PCH_List *theListPtr)
{
    node oldTail = theListPtr->currentTail;
    theListPtr->currentTail = oldTail->prev;
    theListPtr->currentTail->next = NULL;
    
    free(oldTail->data);
    free(oldTail);
    
    theListPtr->numNodes -= 1;
}

// Remove the node at index, free the memory and return (does nothing if index is greater than the length of the list
void RemoveDataAt(PCH_List *theListPtr, uint index)
{
    if (index >= theListPtr->numNodes)
    {
        DLog("Index is beyond end of list - aborting");
        return;
    }
    
    if (index == 0)
    {
        RemoveHead(theListPtr);
        return;
    }
    
    if (index == theListPtr->numNodes - 1)
    {
        RemoveTail(theListPtr);
        return;
    }
    
    node lastPrev = theListPtr->currentHead;
    node theNode = lastPrev->next;
    for (int i=1; i<index; i++)
    {
        lastPrev = theNode;
        theNode = theNode->next;
    }
    
    lastPrev->next = theNode->next;
    theNode->next->prev = lastPrev;
    
    free(theNode->data);
    free(theNode);
    
    theListPtr->numNodes -= 1;
}

// Remove all the nodes from the list and free the memory as necessary
void RemoveAll(PCH_List *theListPtr)
{
    node theNode = theListPtr->currentHead;
    
    while (theNode != NULL)
    {
        node deadNode = theNode;
        theNode = theNode->next;
        
        free(deadNode->data);
        free(deadNode);
    }
    
    theListPtr->currentHead = NULL;
    theListPtr->currentTail = NULL;
    theListPtr->numNodes = 0;
}

/// Return the list as a standard C array. The number of elements in the array is returned in numElements (the parameter's value is ignored on entry). It is the calling routine's responsibilty to destroy the array (using free) when it's done with it.
void *ListAsArray(PCH_List *theListPtr, int *numElements)
{    
    void *result = malloc(theListPtr->numNodes * theListPtr->datasize);
    
    node theNode = theListPtr->currentHead;
    
    void *currentElementPtr = result;
    while (theNode != NULL)
    {
        memcpy(currentElementPtr, theNode->data, theListPtr->datasize);
        
        currentElementPtr += theListPtr->datasize;
        theNode = theNode->next;
    }
    
    *numElements = theListPtr->numNodes;
    
    return result;
}

/// Sort the list using the given comparison function. The comparison function return value is the same as required by the qsort() library function, namely: "a then b" returns -1; "a == b" returns 0; "b then a" returns +1
void SortList(PCH_List *theListPtr, int (*compareFunction)(const void *a,const void *b))
{
    // Don't bother going through with the sort if there are zero or one elements in it
    if (theListPtr->numNodes < 2)
    {
        DLog("Less than 2 elements in the list - ignoring call to 'sort'");
        return;
    }
    
    // First, we need to put the list elements into an array
    int numElements = 0;
    void *dataArray = ListAsArray(theListPtr, &numElements);
    
    qsort(dataArray, numElements, theListPtr->datasize, compareFunction);
    
    SetListWithArray(theListPtr, numElements, dataArray);
    
    // release the memory used by the array
    free(dataArray);
}





