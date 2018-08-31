//
//  PCH_DNS_Table.c
//  PCH_Hacker
//
//  Created by PeterCoolAssHuber on 2018-08-30.
//  Copyright © 2018 Peter Huber. All rights reserved.
//

#include "PCH_DNS_Table.h"

/// Create a new, empty dns table
PCH_dnsTable CreateDnsTable(void)
{
    return CreateList(sizeof(PCH_dnsEntry));
}

/// Add a new port to the list
void AppendDnsEntry(PCH_dnsTable *theTable, PCH_dnsEntry entry)
{
    AppendNewData(theTable, &entry);
}

/// Remove all entries that match either the address or the site name of the given entry
void RemoveDnsEntry(PCH_dnsTable *theTable, PCH_dnsEntry entryToDelete)
{
    struct _listNode *nextEntryNode = theTable->currentHead;
    
    while (nextEntryNode != NULL)
    {
        struct _listNode *theNode = nextEntryNode;
        nextEntryNode = nextEntryNode->next;
        
        PCH_dnsEntry *nextEntryPtr = (PCH_dnsEntry *)(theNode->data);
        
        if (EntriesAreEqual(*nextEntryPtr, entryToDelete))
        {
            struct _listNode *parent = theNode->prev;
            struct _listNode *child = theNode->next;
            
            parent->next = child;
            child->prev = parent;
            
            free(theNode->data);
            free(theNode);
        }
    }
}

/// Compare the two entries and if the fields match, return TRUE, else return FALSE
bool EntriesAreEqual(PCH_dnsEntry entry1, PCH_dnsEntry entry2)
{
    if ((entry1.address[0] == entry2.address[0]) && (entry1.address[1] == entry2.address[1]) && (entry1.address[2] == entry2.address[2]) && (entry1.address[3] == entry2.address[3]) && strcmp(entry1.siteName, entry2.siteName) == 0)
    {
        return true;
    }
    
    return false;
}

/// Destroy and free all memory associated with a port list. This should be called before a port list goes out of scope or is no longer needed.
void DestroyDnsTable(PCH_dnsTable *theTable)
{
    RemoveAll(theTable);
}

/// Try to find the ipv4 adress for the given site name. If it is not in the table, return NULL
int* LookupName(PCH_dnsTable *theTable, char *siteName)
{
    struct _listNode *nextEntryNode = theTable->currentHead;
    
    while (nextEntryNode != NULL)
    {
        PCH_dnsEntry *nextEntryPtr = (PCH_dnsEntry *)(nextEntryNode->data);
        
        if (strcmp(siteName, nextEntryPtr->siteName) == 0)
        {
            return nextEntryPtr->address;
        }
        
        nextEntryNode = nextEntryNode->next;
    }
    
    return NULL;
}

/// Scan the beginning of each site name in theTable and return the first full site name that matches the given pattern (NULL if none). This is useful for autocompletion of the name.
char* ScanForSiteName(PCH_dnsTable *theTable, char *pattern)
{
    size_t maxCharsToCheck = (size_t)strlen(pattern);
    
    struct _listNode *nextEntryNode = theTable->currentHead;
    
    while (nextEntryNode != NULL)
    {
        PCH_dnsEntry *nextEntryPtr = (PCH_dnsEntry *)(nextEntryNode->data);
        char *nextSiteName = nextEntryPtr->siteName;
        
        if ((strlen(nextSiteName) >= maxCharsToCheck) && (strncmp(nextSiteName, pattern, maxCharsToCheck) == 0))
        {
            return nextSiteName;
        }
        
        nextEntryNode = nextEntryNode->next;
    }
    
    return NULL;
}
