//
//  PCH_List.h
//  PCH_Hacker
//
//  Created by PeterCoolAssHuber on 2018-08-29.
//  Copyright © 2018 Peter Huber. All rights reserved.
//

// My attempt at a generic list class for C (to make things more portable until/if Swift becomes usable on Windows with MS).

// Note: The data is referred to by reference within the class.
// Note: All data passed to the list is internally malloc'd and copied and so the original data is left untouched by the list.
// Note: This class allows copies of items within the list. If this is not desired, it is up to the calling routine to write the logic to avoid copies.


#ifndef PCH_List_h
#define PCH_List_h

#include <stdio.h>
#include <stdlib.h>

struct _listNode {
    
    struct _listNode *prev;
    
    void *data;
    
    struct _listNode *next;
};

typedef struct _list {
    
    struct _listNode *currentHead;
    struct _listNode *currentTail;
    
    size_t datasize;
    int numNodes;
    
} PCH_List;

// Create a new, empty list with the given data size
PCH_List CreateList(size_t dataSize);

// Create a new list and initialize its members to the elements in the array (array element 0 is assigned to the head)
PCH_List CreateListWithDataArray(void *dataArray, uint numDataElements, size_t dataSize);

// Add new data to the head of the list.
void PushNewHead(PCH_List theList, void *newHeadData);

// Add new data to the tail of the list.
void AppendNewData(PCH_List theList, void *newTailData);

// Append listToAppend to the end of destList. It is up to the calling routine to make sure that destList is not equal to listToAppend
void AppendNewList(PCH_List destList, PCH_List listToAppend);

// Insert new data at the index indicated (this routine can be slow in a large list)
void InsertNewDataAt(PCH_List theList, void *newData, uint index);

// Set the data at the index indicated. Whatever was there will be deleted. If index is greater than the size of the list, nothing is set.
void SetDataAt(PCH_List theList, void *newData, uint index);

// Returns the data pointer at the head of the list
void *ListHead(PCH_List theList);

// Returns the data pointer at the tail of the list
void *ListTail(PCH_List theList);

// Return the data pointer at index. If index is greater than the length of the list, NULL is returned.
void *ListDataAt(PCH_List theList, uint index);

// Remove the node at the head of the list and free the memory
void RemoveHead(PCH_List theList);

// Remove the node at the tail of the list and free the memory
void RemoveTail(PCH_List theList);

// Remove the node at index, free the memory and return (does nothing if index is greater than the length of the list
void RemoveDataAt(PCH_List theList, uint index);

// Remove all the nodes from the list and free the memory as necessary
void RemoveAll(PCH_List theList);


#endif /* PCH_List_h */
