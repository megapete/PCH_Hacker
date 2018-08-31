//
//  PCH_DNS_Table.h
//  PCH_Hacker
//
//  Created by PeterCoolAssHuber on 2018-08-30.
//  Copyright © 2018 Peter Huber. All rights reserved.
//

#ifndef PCH_DNS_Table_h
#define PCH_DNS_Table_h

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "PCH_List.h"

#define MAX_DNS_NAME_LENGTH 256

typedef struct _dnsEntry {
    
    int address[4]; // standard ipV4 adress fields
    char siteName[MAX_DNS_NAME_LENGTH];
    
} PCH_dnsEntry;

typedef PCH_List PCH_dnsTable;

/// Create a new, empty dns table
PCH_dnsTable CreateDnsTable(void);

/// Add a new port to the list
void AppendDnsEntry(PCH_dnsTable *theTable, PCH_dnsEntry entry);

/// Remove all entries that match either the address or the site name of the given entry
void RemoveDnsEntry(PCH_dnsTable *theTable, PCH_dnsEntry entryToDelete);

/// Destroy and free all memory associated with a port list. This should be called before a port list goes out of scope or is no longer needed.
void DestroyDnsTable(PCH_dnsTable *theTable);

/// Compare the two entries and if the fields match, return TRUE, else return FALSE
bool EntriesAreEqual(PCH_dnsEntry entry1, PCH_dnsEntry entry2);

/// Try to find the ipv4 adress for the given site name. If it is not in the table, return NULL
int* LookupName(PCH_dnsTable *theTable, char *siteName);

/// Scan the beginning of each site name in theTable and return the first full site name that matches the given pattern (NULL if none). This is useful for autocompletion of the name.
char* ScanForSiteName(PCH_dnsTable *theTable, char *pattern);

#endif /* PCH_DNS_Table_h */
