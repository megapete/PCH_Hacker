//
//  PCH_Port.h
//  PCH_Hacker
//
//  Created by PeterCoolAssHuber on 2018-08-30.
//  Copyright © 2018 Peter Huber. All rights reserved.
//

#ifndef PCH_Port_h
#define PCH_Port_h

#include <stdio.h>
#include "PCH_List.h"
#include "PCH_Directory.h"

#define MAX_PORT_NAME_LENGTH 32
#define MAX_PORT_PASSWORD_LENGTH 128

typedef enum _portStatus {closed, openReadOnly, openWriteOnly, openReadWrite} PCH_portStatus;

typedef struct _port {
    
    int number;
    char name[MAX_PORT_NAME_LENGTH];
    char password[MAX_PORT_PASSWORD_LENGTH];
    PCH_portStatus status;
    
    PCH_Directory root;
    
} PCH_port;

typedef PCH_List PCH_PortList;

// Wrappers for PCH_List functions

/// Create a new, empty port list
PCH_PortList CreatePortList(void);

/// Add a new port to the list
void AppendPort(PCH_PortList pList, PCH_port port);

/// Destroy and free all memory associated with a port list. This should be called before a port list goes out of scope or is no longer needed.
void DestroyPortList(PCH_PortList theList);

/// Sort a port list (uses the port number for sorting)
void SortPortList(PCH_PortList theList);

#endif /* PCH_Port_h */
