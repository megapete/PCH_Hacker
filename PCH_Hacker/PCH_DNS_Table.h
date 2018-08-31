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

#define MAX_DNS_NAME_LENGTH 128

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

/// Try to find the ipv4 adress for the given site name. The argument 'ipv4' must be initialized as a 4-int array (whatever is already in there will be clobbered). If the name is found, the function returns TRUE, otherwise FALSE.
bool LookupDnsName(PCH_dnsTable *theTable, const char *siteName, int *ipv4);

/// Scan the beginning of each site name in theTable and stuff the first full site name that matches the given pattern into siteBuffer. If bufferSize is less than 0, MAX_DNS_NAME_LENGTH is used and it is assumed that siteBuffer has been initialzed with that length, This function is useful for autocompletion of the name. The function returns TRUE if a match was found, otheriwse FALSE.
bool ScanForSiteName(PCH_dnsTable *theTable, char *findPattern, char *siteBuffer, int bufferSize);

#endif /* PCH_DNS_Table_h */
