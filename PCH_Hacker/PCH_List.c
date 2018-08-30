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
void SetListWithArray(PCH_List theList, uint numDataElements, void *dataArray)
{
    if (theList.numNodes > 0)
    {
        RemoveAll(theList);
    }
    
    void *currentDataPtr = dataArray;
    for (int i=0; i<numDataElements; i++)
    {
        void *newNodeData = malloc(theList.datasize);
        memcpy(newNodeData, currentDataPtr, theList.datasize);
        currentDataPtr += theList.datasize;
        
        node newNode = malloc(sizeof(struct _listNode));
        newNode->data = newNodeData;
        newNode->prev = theList.currentTail;
        newNode->next = NULL;
        
        theList.currentTail = newNode;
        
        if (theList.currentHead == NULL)
        {
            theList.currentHead = newNode;
        }
    }
}

// Add new data to the head of the list.
void PushNewHead(PCH_List theList, void *newHeadData)
{
    node oldHead = theList.currentHead;
    
    void *newNodeData = malloc(theList.datasize);
    memcpy(newNodeData, newHeadData, theList.datasize);
    
    node newNode = malloc(sizeof(struct _listNode));
    newNode->data = newNodeData;
    newNode->prev = NULL;
    newNode->next = oldHead;
    oldHead->prev = newNode;
    
    theList.currentHead = newNode;
    
    theList.numNodes += 1;
}

// Add new data to the tail of the list.
void AppendNewData(PCH_List theList, void *newTailData)
{
    node oldTail = theList.currentTail;
    
    void *newNodeData = malloc(theList.datasize);
    memcpy(newNodeData, newTailData, theList.datasize);
    
    node newNode = malloc(sizeof(struct _listNode));
    newNode->data = newNodeData;
    newNode->prev = oldTail;
    newNode->next = NULL;
    oldTail->next = newNode;
    
    theList.currentTail = newNode;
    
    theList.numNodes += 1;
}

// Append listToAppend to the end of destList. It is up to the calling routine to make sure that destList is not equal to listToAppend. If the two lists are of different datasizes, nothing is done and the routine returns.
void AppendNewList(PCH_List destList, PCH_List listToAppend)
{
    if (destList.datasize != listToAppend.datasize)
    {
        ALog("Incompatible data sizes!");
        return;
    }
    
    if (listToAppend.numNodes == 0)
    {
        DLog("List to append is empty");
        return;
    }
    
    listToAppend.currentHead->prev = destList.currentTail;
    destList.currentTail->next = listToAppend.currentHead;
    destList.currentTail = listToAppend.currentTail;
    
    destList.numNodes += listToAppend.numNodes;
}

// Set the data at the index indicated. Whatever was there will be deleted. If index is greater than the size of the list, nothing is set.
void SetDataAt(PCH_List theList, void *newData, uint index)
{
    if (index >= theList.numNodes)
    {
        DLog("Index is beyond end of list - aborting");
        return;
    }
    
    node theNode = theList.currentHead;
    int nodeIndex = 0;
    
    while (theNode != NULL && nodeIndex < index)
    {
        theNode = theNode->next;
    }
    
    if (theNode == NULL)
    {
        ALog("Something really weird happened!");
    }
    
    memcpy(theNode->data, newData, theList.datasize);
    
}

// Insert new data at the index indicated (this routine can be slow in a large list with a high index)
void InsertNewDataAt(PCH_List theList, void *newData, uint index)
{
    if (index == 0)
    {
        PushNewHead(theList, newData);
    }
    else if (index >= theList.numNodes - 1)
    {
        AppendNewData(theList, newData);
    }
    else
    {
        void *newNodeData = malloc(theList.datasize);
        memcpy(newNodeData, newData, theList.datasize);
        
        node newNode = malloc(sizeof(struct _listNode));
        newNode->data = newNodeData;
        
        node oldNode = theList.currentHead;
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
        
        theList.numNodes += 1;
    }
}

// Returns the data pointer at the head of the list
void *ListHead(PCH_List theList)
{
    return theList.currentHead->data;
}

// Returns the data pointer at the tail of the list
void *ListTail(PCH_List theList)
{
    return theList.currentTail->data;
}

// Return the data pointer at index. If index is greater than the length of the list, NULL is returned.
void *ListDataAt(PCH_List theList, uint index)
{
    if (index >= theList.numNodes)
    {
        DLog("Index is beyond end of list - aborting");
        return NULL;
    }
    
    node theNode = theList.currentHead;
    for (int i=0; i<index; i++)
    {
        theNode = theNode->next;
    }
    
    return theNode->data;
}

// Remove the node at the head of the list and free the memory
void RemoveHead(PCH_List theList)
{
    node oldHead = theList.currentHead;
    theList.currentHead = oldHead->next;
    theList.currentHead->prev = NULL;
    
    free(oldHead->data);
    free(oldHead);
    
    theList.numNodes -= 1;
}

// Remove the node at the tail of the list and free the memory
void RemoveTail(PCH_List theList)
{
    node oldTail = theList.currentTail;
    theList.currentTail = oldTail->prev;
    theList.currentTail->next = NULL;
    
    free(oldTail->data);
    free(oldTail);
    
    theList.numNodes -= 1;
}

// Remove the node at index, free the memory and return (does nothing if index is greater than the length of the list
void RemoveDataAt(PCH_List theList, uint index)
{
    if (index >= theList.numNodes)
    {
        DLog("Index is beyond end of list - aborting");
        return;
    }
    
    if (index == 0)
    {
        RemoveHead(theList);
        return;
    }
    
    if (index == theList.numNodes - 1)
    {
        RemoveTail(theList);
        return;
    }
    
    node lastPrev = theList.currentHead;
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
    
    theList.numNodes -= 1;
}

// Remove all the nodes from the list and free the memory as necessary
void RemoveAll(PCH_List theList)
{
    node theNode = theList.currentHead;
    
    while (theNode != NULL)
    {
        node deadNode = theNode;
        theNode = theNode->next;
        
        free(deadNode->data);
        free(deadNode);
    }
    
    theList.currentHead = NULL;
    theList.currentTail = NULL;
    theList.numNodes = 0;
}

/// Return the list as a standard C array. The number of elements in the array is returned in numElements (the parameter's value is ignored on entry). It is the calling routine's responsibilty to destroy the array (using free) when it's done with it.
void *ListAsArray(PCH_List theList, int *numElements)
{
    void *result = malloc(theList.numNodes * theList.datasize);
    
    node theNode = theList.currentHead;
    
    void *currentElementPtr = result;
    while (theNode != NULL)
    {
        memcpy(currentElementPtr, theNode->data, theList.datasize);
        
        currentElementPtr += theList.datasize;
        theNode = theNode->next;
    }
    
    *numElements = theList.numNodes;
    
    return result;
}

/// Sort the list using the given comparison function. The comparison function return value is the same as required by the qsort() library function, namely: "a then b" returns -1; "a == b" returns 0; "b then a" returns +1
void SortList(PCH_List theList, int (*compareFunction)(const void *a,const void *b))
{
    // Don't bother going through with the sort if there are zero or one elements in it
    if (theList.numNodes < 2)
    {
        DLog("Less than 2 elements in the list - ignoring call to 'sort'");
        return;
    }
    
    // First, we need to put the list elements into an array
    int numElements = 0;
    void *dataArray = ListAsArray(theList, &numElements);
    
    qsort(dataArray, numElements, theList.datasize, compareFunction);
    
    SetListWithArray(theList, numElements, dataArray);
    
    // release the memory used by the array
    free(dataArray);
}





