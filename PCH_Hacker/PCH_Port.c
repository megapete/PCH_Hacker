//
//  PCH_Port.c
//  PCH_Hacker
//
//  Created by PeterCoolAssHuber on 2018-08-30.
//  Copyright © 2018 Peter Huber. All rights reserved.
//

#include "PCH_Port.h"

#include <string.h>

int PortComparisonFunction(const void *p1, const void *p2);

/// Create a new, empty port list
PCH_PortList CreatePortList()
{
    return CreateList(sizeof(PCH_Port));
}

/// Add a new port to the list
void AppendPort(PCH_PortList *pList, PCH_Port port)
{
    AppendNewData(pList, &port);
}

/// Destroy and free all memory associated with a port list. This should be called before a port list goes out of scope or is no longer needed.
void DestroyPortList(PCH_PortList *theList)
{
    RemoveAll(theList);
}

/// Sort a port list (uses the port number for sorting)
void SortPortList(PCH_PortList *theList)
{
    SortList(theList, &PortComparisonFunction);
}

// Comparison function used to sort port lists
int PortComparisonFunction(const void *p1, const void *p2)
{
    PCH_Port port1 = *(PCH_Port *)p1;
    PCH_Port port2 = *(PCH_Port *)p2;
    
    return (port1.number - port2.number);
}

/// Get the description of the port as a C-string and stuff it into the provided buffer. Pass -1 for the bufferSize to use MAX_PORT_DESCRIPTION_LENGTH as the buffer size (assumes that the calling routine has allocated that much space).
void PortDescription(PCH_Port thePort, char *descBuffer, int bufferSize)
{
    int useSize = MAX_PORT_DESCRIPTION_LENGTH - 1;
    if (bufferSize > 0)
    {
        useSize = bufferSize - 1;
    }
    
    char statusString[256];
    char passwdLength[16];
    snprintf(passwdLength, 15, "%d", (int)strlen(thePort.password));
    
    if (thePort.status == portClosed)
    {
        snprintf(statusString, 255, "CLOSED (Password length: %s", passwdLength);
    }
    else if (thePort.status == portOpenReadOnly)
    {
        snprintf(statusString, 255, "OPEN for READ ONLY");
    }
    else if (thePort.status == portOpenWriteOnly)
    {
        snprintf(statusString, 255, "OPEN for WRITE ONLY");
    }
    else if (thePort.status == portOpenReadWrite)
    {
        snprintf(statusString, 255, "OPEN for READ/WRITE");
    }
    
    snprintf(descBuffer, useSize - 1, "%5d  %s  %s", thePort.number, statusString, thePort.name);
    
    // force the final byte to NULL
    descBuffer[useSize] = '0';
}
