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
#define MAX_PORT_DESCRIPTION_LENGTH 1024

typedef enum _portStatus {portClosed, portOpenReadOnly, portOpenWriteOnly, portOpenReadWrite} PCH_portStatus;

typedef struct _port {
    
    int number;
    char name[MAX_PORT_NAME_LENGTH];
    char password[MAX_PORT_PASSWORD_LENGTH];
    PCH_portStatus status;
    
    PCH_Directory root;
    
} PCH_Port;

typedef PCH_List PCH_PortList;

// Wrappers for PCH_List functions

/// Create a new, empty port list
PCH_PortList CreatePortList(void);

/// Add a new port to the list
void AppendPort(PCH_PortList *pList, PCH_Port port);

/// Destroy and free all memory associated with a port list. This should be called before a port list goes out of scope or is no longer needed.
void DestroyPortList(PCH_PortList *theList);

/// Sort a port list (uses the port number for sorting)
void SortPortList(PCH_PortList *theList);

/// Get the description of the port as a C-string and stuff it into the provided buffer. Pass -1 for the bufferSize to use MAX_PORT_DESCRIPTION_LENGTH as the buffer size (assumes that the calling routine has allocated that much space).
void GetPortDescription(PCH_Port thePort, char *descBuffer, int bufferSize);



#endif /* PCH_Port_h */
